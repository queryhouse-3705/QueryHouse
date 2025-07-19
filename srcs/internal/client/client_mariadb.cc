#include "client_mariadb.h"

#include <unistd.h>

#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "mysql.h"
#include "errmsg.h"
#include "mysqld_error.h"

//std::fstream mariadb_log("/tmp/mariadb.Fuzzlog",
                           //std::ios::out | std::ios::app);

using namespace std;
namespace {
bool is_crash_response(int response) {
  //mariadb_log << "[mariadb] Checking crash response: " << response
				//<< std::endl;
  return response == CR_SERVER_LOST || response == CR_SERVER_GONE_ERROR;
}
};  // namespace

namespace client {

void MARIADBClient::initialize(YAML::Node config) {
  host_ = config["host"].as<std::string>();
  user_name_ = config["user_name"].as<std::string>();
  passwd_ = config["passwd"].as<std::string>();
  sock_path_ = config["sock_path"].as<std::string>();
  db_prefix_ = config["db_prefix"].as<std::string>();
}

void MARIADBClient::prepare_env() {
  ++database_id_;
  std::string database_name = db_prefix_ + std::to_string(database_id_);
  if (!create_database(database_name)) {
    //mariadb_log << "Failed to create database." << std::endl;
  }
}

ExecutionStatus MARIADBClient::execute(
    const char *query, size_t size,
    std::vector<std::vector<std::string>> &result) {
  //mariadb_log << "[mariadb] Executing queries..." << std::endl;

  std::vector<std::string> queries = split_query(query, size);

  std::string database_name = db_prefix_ + std::to_string(database_id_);

  std::optional<MYSQL> connection = create_connection(database_name);
  if (!connection.has_value()) {
    //mariadb_log << "Cannot create connection at execute" << std::endl;
    mysql_close(&(*connection));

    return kConnectFailed;
  }

  // Process each query
  for (const auto &q : queries) {
    //mariadb_log << "[mariadb] Execute query: " << q << std::endl;

    // Execute query
    int server_response = mysql_real_query(&(*connection), q.c_str(), q.size());
    if (server_response != 0) {
      //mariadb_log << "mariadb query error: " << mysql_error(&(*connection))
                    //<< std::endl;
      clean_up_connection(*connection);
      mysql_close(&(*connection));
      return kExecuteError;
    }

    // Store results
    MYSQL_RES *query_result = mysql_store_result(&(*connection));
    if (!query_result && mysql_errno(&(*connection)) != 0) {
      //mariadb_log << "mariadb store result error: "
                    //<< mysql_error(&(*connection)) << std::endl;
      clean_up_connection(*connection);
      mysql_close(&(*connection));
      return kExecuteError;
    }

    // Process results
    if (query_result) {
      int num_fields = mysql_num_fields(query_result);
      MYSQL_ROW row;
      while ((row = mysql_fetch_row(query_result))) {
        //mariadb_log << "[mariadb] Result: ";
        std::vector<std::string> row_result;
        for (int i = 0; i < num_fields; ++i) {
          row_result.push_back(row[i] ? row[i] : "NULL");
          //mariadb_log << row_result.back() << " ";
        }
        result.push_back(row_result);
        //mariadb_log << std::endl;
      }
      mysql_free_result(query_result);
    }

    // Process next statement result
    int next_result_response = mysql_next_result(&(*connection));
    if (next_result_response > 0) {
      //mariadb_log << "mariadb error while executing next query: "
                    //<< mysql_error(&(*connection)) << std::endl;
      clean_up_connection(*connection);
      mysql_close(&(*connection));
      return kSyntaxError;
    }
  }

  //// [Disabled] Schma check ----
  ////mariadb_log << "[mariadb] Retrieving schema information..." << std::endl;
  //std::string schema_query =
      //"SELECT table_name, table_type FROM information_schema.tables WHERE "
      //"table_schema = '" +
      //database_name + "';";
  //int schema_response = mysql_real_query(&(*connection), schema_query.c_str(),
                                         //schema_query.size());

  //if (schema_response != 0) {
    ////mariadb_log << "mariadb schema query error: " << mysql_error(&(*connection))
                  ////<< std::endl;
    //clean_up_connection(*connection);
    //mysql_close(&(*connection));
    //return kSyntaxError;
  //}
  //// [Disabled] End of Schma check ----

  // Close connection
  ExecutionStatus server_status = clean_up_connection(*connection);
  mysql_close(&(*connection));
  return server_status;
}

void MARIADBClient::clean_up_env() {
  std::string database_name = db_prefix_ + std::to_string(database_id_);
  string reset_query = "DROP DATABASE IF EXISTS " + database_name + ";";
  std::optional<MYSQL> connection = create_connection("");
  if (!connection.has_value()) {
    return;
  }

  mysql_real_query(&(*connection), reset_query.c_str(), reset_query.size());
  clean_up_connection((*connection));
  mysql_close(&(*connection));
}

std::optional<MYSQL> MARIADBClient::create_connection(std::string_view db_name) {
  MYSQL result;
  if (mysql_init(&result) == NULL) return std::nullopt;

  if (mysql_real_connect(&result, host_.c_str(), user_name_.c_str(),
                         passwd_.c_str(), db_name.data(), 0, sock_path_.c_str(),
                         CLIENT_MULTI_STATEMENTS) == NULL) {
    //mariadb_log << "Create connection failed: " << mysql_errno(&result)
                  //<< mysql_error(&result) << std::endl;
    mysql_close(&result);
    return std::nullopt;
  }

  return result;
}

bool MARIADBClient::check_alive() {
  std::optional<MYSQL> connection = create_connection("");
  if (!connection.has_value()) {
    return false;
  }
  mysql_close(&(*connection));
  return true;
}

bool MARIADBClient::create_database(const std::string &database) {
  MYSQL tmp_m;

  if (mysql_init(&tmp_m) == NULL) {
    mysql_close(&tmp_m);
    return false;
  }

  if (mysql_real_connect(&tmp_m, host_.c_str(), user_name_.c_str(),
                         passwd_.c_str(), nullptr, 0, sock_path_.c_str(),
                         CLIENT_MULTI_STATEMENTS) == NULL) {
    //fprintf(stderr, "Connection error3 %d, %s\n", mysql_errno(&tmp_m),
            //mysql_error(&tmp_m));
    mysql_close(&tmp_m);
    return false;
  }

  string cmd = "CREATE DATABASE IF NOT EXISTS " + database + ";";
  mysql_real_query(&tmp_m, cmd.c_str(), cmd.size());
  clean_up_connection(tmp_m);
  mysql_close(&tmp_m);
  return true;
}

ExecutionStatus MARIADBClient::clean_up_connection(MYSQL &mm) {
  int res = -1;
  //mariadb_log << "[mariadb] Cleaning up connection..." << std::endl;

  do {
    auto q_result = mysql_store_result(&mm);
    if (q_result) {
      mysql_free_result(q_result);
    } // else if (mysql_errno(&mm)) {
      //mariadb_log << "[mariadb] Error while fetching result: "
                    //<< mysql_errno(&mm) << " - " << mysql_error(&mm)
                    //<< std::endl;
      //// Log error and continue
    //}
  } while ((res = mysql_next_result(&mm)) == 0);

  if (res != -1) {
    res = mysql_errno(&mm);
    if (is_crash_response(res)) {
      //mariadb_log << "[mariadb] Server crash detected: " << res
                    //<< std::endl;
      return kServerCrash;
    }
    if (res == ER_PARSE_ERROR) {
      return kSyntaxError;
    } else {
      //mariadb_log << "[mariadb] Error code: " << res << " - "
                    //<< mysql_error(&mm) << std::endl;
      return kSemanticError;
    }
  }

  return kNormal;
}

};  // namespace client
