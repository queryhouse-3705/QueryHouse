#include "client_sqlite.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//std::fstream sqlite_log("/tmp/sqlite_log.Fuzzlog",
                            //std::ios::out | std::ios::app);

namespace client {

void SQLiteClient::initialize(YAML::Node config) {
  db_prefix_ = config["db_prefix"].as<std::string>();
  db_path_ = config["db_path"].as<std::string>();
}

void SQLiteClient::prepare_env() {
  ++database_id_;
  std::string db_name = db_prefix_ + std::to_string(database_id_) + ".db";
  db_path_ = db_name;
  //sqlite_log << "[SQLite] Prepared environment with DB: " << db_path_
                 //<< std::endl;
}

ExecutionStatus SQLiteClient::execute(
    const char *query, size_t size,
    std::vector<std::vector<std::string>> &result) {
  // sqlite_log << "[SQLite] Executing queries..." << std::endl;
  // sqlite_log << query << std::endl;

  // sqlite_log << "[SQLite] Result before execute: " << std::endl;
  std::vector<std::string> queries = split_query(query, size);
  sqlite3 *db = nullptr;

  // Database connection
  if (auto conn = create_connection(); conn) {
    db = *conn;
    //sqlite_log << "[SQLite] Connected to SQLite database" << std::endl;
  } else {
    //sqlite_log << "Failed to connect to SQLite database" << std::endl;
    return kServerCrash;
  }

  // Process each query
  for (const auto &q : queries) {
    //sqlite_log << "[SQLite] Execute query: " << q << std::endl;

    sqlite3_stmt *stmt = nullptr;
    int result_code = sqlite3_prepare_v2(db, q.c_str(), -1, &stmt, nullptr);

    if (result_code != SQLITE_OK) {
      //sqlite_log << "SQLite error preparing statement: "
                     //<< sqlite3_errmsg(db) << std::endl;
      close_connection(db);
      return kSyntaxError;
    }

    // Query Execution & Process results
    while (true) {
      result_code = sqlite3_step(stmt);

      if (result_code == SQLITE_ROW) {
        std::vector<std::string> row;
        for (int i = 0; i < sqlite3_column_count(stmt); i++) {
          const char *col =
              reinterpret_cast<const char *>(sqlite3_column_text(stmt, i));
          row.push_back(col ? col : "NULL");
        }
        result.push_back(row);
      } else if (result_code == SQLITE_DONE) {
        break;  // Query done
      } else {
        //sqlite_log << "SQLite error executing step: " << sqlite3_errmsg(db)
                       //<< std::endl;
        sqlite3_finalize(stmt);
        close_connection(db);
        return kExecuteError;
      }
    }

    sqlite3_finalize(stmt);
  }

  //if (result.empty()) {
    //sqlite_log << "[SQLite] No result" << std::endl;
  //} else {
    //sqlite_log << "[SQLite] Execute Query: ";
    //sqlite_log << query << std::endl;
    //sqlite_log << "[SQLite] Result: " << std::endl;
    //for (const auto &row : result) {
      //for (const auto &col : row) {
        //sqlite_log << col << " ";
      //}
      //sqlite_log << std::endl;
    //}
  //}

  //// [Disabled] Schema check ---
  ////sqlite_log << "[SQLite] Retrieving schema information..." << std::endl;
  //const char *schema_query =
      //"SELECT type, name, tbl_name, sql FROM sqlite_master WHERE "
      //"type='table';";
  //sqlite3_stmt *schema_stmt = nullptr;
  //int schema_result =
      //sqlite3_prepare_v2(db, schema_query, -1, &schema_stmt, nullptr);

  //if (schema_result != SQLITE_OK) {
    ////sqlite_log << "SQLite error retrieving schema: " << sqlite3_errmsg(db)
                   ////<< std::endl;
    //close_connection(db);
    //return kSyntaxError;
  //}

  //while (sqlite3_step(schema_stmt) == SQLITE_ROW) {
    //const char *type =
        //reinterpret_cast<const char *>(sqlite3_column_text(schema_stmt, 0));
    //const char *name =
        //reinterpret_cast<const char *>(sqlite3_column_text(schema_stmt, 1));
    //const char *tbl_name =
        //reinterpret_cast<const char *>(sqlite3_column_text(schema_stmt, 2));
    //const char *sql =
        //reinterpret_cast<const char *>(sqlite3_column_text(schema_stmt, 3));

    ////sqlite_log << "Type: " << (type ? type : "NULL")
                   ////<< ", Name: " << (name ? name : "NULL")
                   ////<< ", Table: " << (tbl_name ? tbl_name : "NULL")
                   ////<< ", SQL: " << (sql ? sql : "NULL") << std::endl;
  //}

  //sqlite3_finalize(schema_stmt);
  //// [Disabled] End of Schema check ---

  // Close connection
  close_connection(db);
  return kNormal;
}

void SQLiteClient::clean_up_env() {
  std::string db_name = db_prefix_ + std::to_string(database_id_) + ".db";
  if (remove(db_name.c_str()) != 0) {
    //sqlite_log << "Error deleting database file: " << db_name << std::endl;
  } //else {
    //sqlite_log << "[SQLite] Deleted database: " << db_name << std::endl;
  //}
}

bool SQLiteClient::check_alive() {
  if (auto conn = create_connection(); conn) {
    close_connection(*conn);
    return true;
  }
  return false;
}

std::optional<sqlite3 *> SQLiteClient::create_connection() {
  sqlite3 *db = nullptr;
  //sqlite_log << "[SQLite] Connecting to SQLite database: " << db_path_
                 //<< std::endl;
  if (sqlite3_open(db_path_.c_str(), &db) != SQLITE_OK) {
    //sqlite_log << "Failed to open SQLite database: " << sqlite3_errmsg(db)
                   //<< std::endl;
    return std::nullopt;
  }
  return db;
}

void SQLiteClient::close_connection(sqlite3 *db) { sqlite3_close(db); }

}  // namespace client
