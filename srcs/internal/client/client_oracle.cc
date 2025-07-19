#include "client_oracle.h"

#include <oci.h>

#include <chrono>  // for performance check
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//std::fstream oracle_log("/tmp/oracle.Fuzzlog",
                            //std::ios::out | std::ios::app);
namespace client {

void OracleClient::initialize(YAML::Node config) {
  host_ = config["host"].as<std::string>();
  port_ = config["port"].as<std::string>();
  service_ = config["service"].as<std::string>();
  user_name_ = config["user_name"].as<std::string>();
  passwd_ = config["passwd"].as<std::string>();
  db_prefix_ = config["db_prefix"].as<std::string>();
  //oracle_log << "Oracle client initialized" << std::endl;
}

void OracleClient::prepare_env() {
  ++database_id_;
  std::string schema_name = db_prefix_ + std::to_string(database_id_);

  if (!create_schema(schema_name)) {
    //oracle_log << "Failed to create schema." << std::endl;
  } else {
    // Save newly created schema name
    default_schema_ = "C##" + schema_name;
  }

  //oracle_log << "Prepared environment with schema: " << schema_name
                 //<< std::endl;
}

ExecutionStatus OracleClient::execute(
    const char *query, size_t size,
    std::vector<std::vector<std::string>> &result) {
  //oracle_log << "[Oracle] Executing queries..." << std::endl;
  std::vector<std::string> queries = split_query(query, size);
  for (auto &q : queries) {
    if (q.back() == ';') {
      q.pop_back();
    }
  }
  //oracle_log << "Size: " << queries.size() << std::endl;

  OCIEnv *env = nullptr;
  OCIError *err = nullptr;
  OCISvcCtx *svc = nullptr;
  OCIDefine *defn = nullptr;

  if (!create_connection(env, err, svc)) {
    //oracle_log << "Cannot create connection at execute" << std::endl;
    return kServerCrash;
  }

  // Process each query
  for (const auto &q : queries) {
    //oracle_log << "[Oracle] Execute query: " << q << std::endl;
    //oracle_log << "Size: " << queries.size() << std::endl;
    OCIStmt *stmt = nullptr;
    OCIHandleAlloc(env, (void **)&stmt, OCI_HTYPE_STMT, 0, nullptr);

    if (OCIStmtPrepare(stmt, err, (text *)q.c_str(), (ub4)q.size(),
                       OCI_NTV_SYNTAX, OCI_DEFAULT) != OCI_SUCCESS) {
      //oracle_log << "Failed to prepare statement" << std::endl;

      // Retrieve detailed error message
      text errbuf[512];
      sb4 errcode;
      OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                  OCI_HTYPE_ERROR);
      //oracle_log << "Error - " << errbuf << std::endl;

      clean_up_connection(env, err, svc);
      return kSyntaxError;
    }

    // Check if it's a SELECT statement
    if (q.find("SELECT") != std::string::npos) {
      //oracle_log << "SELECT Query" << std::endl;
      if (OCIStmtExecute(svc, stmt, err, 0, 0, nullptr, nullptr,
                         OCI_DESCRIBE_ONLY) != OCI_SUCCESS) {
        //oracle_log << "Failed to execute DESCRIBE query" << std::endl;

        // Retrieve detailed error message
        text errbuf[512];
        sb4 errcode;
        OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                    OCI_HTYPE_ERROR);
        //oracle_log << "Error - " << errbuf << std::endl;

        clean_up_connection(env, err, svc);
        return kSemanticError;
      }
      ub4 columnCount;
      if (OCIAttrGet(stmt, OCI_HTYPE_STMT, &columnCount, 0,
                     OCI_ATTR_PARAM_COUNT, err) != OCI_SUCCESS) {
        //oracle_log << "Failed to get column count" << std::endl;

        // Retrieve detailed error message
        text errbuf[512];
        sb4 errcode;
        OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                    OCI_HTYPE_ERROR);
        //oracle_log << "Error - " << errbuf << std::endl;

        clean_up_connection(env, err, svc);
        return kSemanticError;
      }
      //oracle_log << "Column count: " << columnCount << std::endl;

      char result_string[1024][1024] = {0};

      for (ub4 i = 1; i <= columnCount; i++) {
        if (OCIDefineByPos(stmt, &defn, err, i, result_string[i], 1024,
                           SQLT_STR, nullptr, nullptr, nullptr,
                           OCI_DEFAULT) != OCI_SUCCESS) {
          //oracle_log << "Failed to define column " << i << std::endl;

          // Retrieve detailed error message
          text errbuf[512];
          sb4 errcode;
          OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                      OCI_HTYPE_ERROR);
          //oracle_log << "Error - " << errbuf << std::endl;

          clean_up_connection(env, err, svc);
          return kSemanticError;
        }
        //oracle_log << "Column " << i << " defined" << std::endl;
      }

      // Execute the query
      if (OCIStmtExecute(svc, stmt, err, 0, 0, nullptr, nullptr, OCI_DEFAULT) !=
          OCI_SUCCESS) {
        //oracle_log << "Failed to execute SELECT query" << std::endl;

        // Retrieve detailed error message
        text errbuf[512];
        sb4 errcode;
        OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                    OCI_HTYPE_ERROR);
        //oracle_log << "Error - " << errbuf << std::endl;

        clean_up_connection(env, err, svc);
        return kSemanticError;
      }
      //oracle_log << "SELECT query executed" << std::endl;
      // add error handling
      while (true) {
        if (OCIStmtFetch2(stmt, err, 1, OCI_FETCH_NEXT, 0, OCI_DEFAULT) !=
            OCI_SUCCESS) {
          //oracle_log << "Failed to fetch result" << std::endl;

          // Retrieve detailed error message
          text errbuf[512];
          sb4 errcode;
          OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                      OCI_HTYPE_ERROR);
          //oracle_log << "Error code - " << errcode << std::endl;
          if (errcode == 1403) {
            break;
          } else if (errcode != 1405) {
            //oracle_log << "Error - " << errbuf << std::endl;
            clean_up_connection(env, err, svc);
            return kSemanticError;
          }
        }
        //oracle_log << "Result: ";
        vector<string> row;
        for (ub4 j = 1; j <= columnCount; j++) {
          row.push_back(result_string[j]);
          //oracle_log << result_string[j] << " ";
        }
        result.push_back(row);
        //oracle_log << std::endl;
      }
    } else {
      // For non-SELECT statements, simply execute
      if (OCIStmtExecute(svc, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT) !=
          OCI_SUCCESS) {
        //oracle_log << "Failed to execute non-SELECT query" << std::endl;

        // Retrieve detailed error message
        text errbuf[512];
        sb4 errcode;
        OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                    OCI_HTYPE_ERROR);
        //oracle_log << "Error code: " << errcode << std::endl;
        //oracle_log << "Error - " << errbuf << std::endl;

        clean_up_connection(env, err, svc);
        return kSemanticError;
      }
    }

    OCIHandleFree(stmt, OCI_HTYPE_STMT);
  }

  clean_up_connection(env, err, svc);
  return kNormal;
}

void OracleClient::clean_up_env() {
  std::string schema_name = db_prefix_ + std::to_string(database_id_);
  std::string prefix = "C##";
  std::string common_user_name = prefix + schema_name;
  std::string drop_query = "DROP USER " + common_user_name + " CASCADE";

  //oracle_log << "Dropping schema: " << drop_query << std::endl;

  OCIEnv *env = nullptr;
  OCIError *err = nullptr;
  OCISvcCtx *svc = nullptr;
  if (create_connection(env, err, svc)) {
    OCIStmt *stmt = nullptr;
    OCIHandleAlloc(env, (void **)&stmt, OCI_HTYPE_STMT, 0, nullptr);
    OCIStmtPrepare(stmt, err, (text *)drop_query.c_str(),
                   (ub4)drop_query.size(), OCI_NTV_SYNTAX, OCI_DEFAULT);
    OCIStmtExecute(svc, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT);
    OCIHandleFree(stmt, OCI_HTYPE_STMT);
    clean_up_connection(env, err, svc);
  }
}

bool OracleClient::check_alive() {
  OCIEnv *env = nullptr;
  OCIError *err = nullptr;
  OCISvcCtx *svc = nullptr;

  bool alive = create_connection(env, err, svc);
  if (alive) {
    clean_up_connection(env, err, svc);
  }
  return alive;
}

bool OracleClient::create_schema(const std::string &schema_name) {
  std::string common_user_name = "C##" + schema_name;
  std::string create_user_query =
      "CREATE USER " + common_user_name + " IDENTIFIED BY password";
  std::vector<std::string> privileges = {"ALL PRIVILEGES", "EXECUTE ON CTX_DDL",
                                         "EXECUTE ON CTX_CAT",
                                         "EXECUTE ON CTX_QUERY"};

  OCIEnv *env = nullptr;
  OCIError *err = nullptr;
  OCISvcCtx *svc = nullptr;

  if (!create_connection(env, err, svc)) {
    return false;
  }

  OCIStmt *stmt = nullptr;
  OCIHandleAlloc(env, (void **)&stmt, OCI_HTYPE_STMT, 0, nullptr);

  // Try to execute the "CREATE USER" query
  if (OCIStmtPrepare(stmt, err, (text *)create_user_query.c_str(),
                     (ub4)create_user_query.size(), OCI_NTV_SYNTAX,
                     OCI_DEFAULT) != OCI_SUCCESS) {
    //oracle_log << "Failed to prepare CREATE USER statement" << std::endl;
    clean_up_connection(env, err, svc);
    return false;
  }

  if (OCIStmtExecute(svc, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT) !=
      OCI_SUCCESS) {
    //oracle_log << "Failed to create schema" << std::endl;

    // Retrieve detailed error message
    text errbuf[512];
    sb4 errcode;
    OCIErrorGet(err, 1, NULL, &errcode, errbuf, sizeof(errbuf),
                OCI_HTYPE_ERROR);
    //oracle_log << "Error - " << errbuf << std::endl;

    clean_up_connection(env, err, svc);
    return false;
  }

  // Grant privileges
  for (std::string privilege : privileges) {
    std::string grant_query = "GRANT " + privilege + " TO " + common_user_name;
    if (OCIStmtPrepare(stmt, err, (text *)grant_query.c_str(),
                       (ub4)grant_query.size(), OCI_NTV_SYNTAX,
                       OCI_DEFAULT) != OCI_SUCCESS) {
      //oracle_log << "Failed to prepare GRANT statement" << std::endl;
      clean_up_connection(env, err, svc);
      return false;
    }
    OCIStmtExecute(svc, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT);
  }

  OCIHandleFree(stmt, OCI_HTYPE_STMT);

  clean_up_connection(env, err, svc);
  return true;
}

bool OracleClient::create_connection(OCIEnv *&env, OCIError *&err,
                                     OCISvcCtx *&svc) {
  // Initialize OCI environment
  if (OCIEnvCreate(&env, OCI_DEFAULT, nullptr, nullptr, nullptr, nullptr, 0,
                   nullptr) != OCI_SUCCESS) {
    //oracle_log << "Failed to create OCI environment" << std::endl;
    return false;
  }

  // Allocate OCI error handle
  OCIHandleAlloc(env, (void **)&err, OCI_HTYPE_ERROR, 0, nullptr);

  // Create connection string: "//host:port/service"
  std::string conn_string = "//" + host_ + ":" + port_ + "/" + service_;

  // Log in to the database
  if (OCILogon(env, err, &svc, (text *)user_name_.c_str(),
               (ub4)user_name_.size(), (text *)passwd_.c_str(),
               (ub4)passwd_.size(), (text *)conn_string.c_str(),
               (ub4)conn_string.size()) != OCI_SUCCESS) {
    //oracle_log << "Failed to connect to Oracle database" << std::endl;
    OCIHandleFree(err, OCI_HTYPE_ERROR);
    OCIHandleFree(env, OCI_HTYPE_ENV);
    return false;
  }

  // Change schema to the newly created schema
  if (!default_schema_.empty()) {
    std::string alter_schema_query =
        "ALTER SESSION SET CURRENT_SCHEMA = " + default_schema_;
    //oracle_log << "Changing schema to " << default_schema_ << std::endl;
    OCIStmt *stmt = nullptr;
    OCIHandleAlloc(env, (void **)&stmt, OCI_HTYPE_STMT, 0, nullptr);
    if (OCIStmtPrepare(stmt, err, (text *)alter_schema_query.c_str(),
                       (ub4)alter_schema_query.size(), OCI_NTV_SYNTAX,
                       OCI_DEFAULT) != OCI_SUCCESS) {
      //oracle_log << "Failed to change schema after connection" << std::endl;
      OCIHandleFree(stmt, OCI_HTYPE_STMT);
      clean_up_connection(env, err, svc);
      return false;
    }
    OCIStmtExecute(svc, stmt, err, 1, 0, nullptr, nullptr, OCI_DEFAULT);
    OCIHandleFree(stmt, OCI_HTYPE_STMT);
  }
  return true;
}

ExecutionStatus OracleClient::clean_up_connection(OCIEnv *env, OCIError *err,
                                                  OCISvcCtx *svc) {
  if (svc) {
    OCILogoff(svc, err);
  }
  if (err) {
    OCIHandleFree(err, OCI_HTYPE_ERROR);
  }
  if (env) {
    OCIHandleFree(env, OCI_HTYPE_ENV);
  }
  return kNormal;
}
};  // namespace client
