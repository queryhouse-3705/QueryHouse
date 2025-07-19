#include "client.h"

#include <cassert>
#include <iostream>
#include <string>

#ifdef __QUERYHOUSE_MYSQL__
#include "client_mysql.h"
#endif

#ifdef __QUERYHOUSE_POSTGRESQL__
#include "client_postgresql.h"
#endif

#ifdef __QUERYHOUSE_SQLITE__
#include "client_sqlite.h"
#endif

#ifdef __QUERYHOUSE_ORACLE__
#include "client_oracle.h"
#endif

#ifdef __QUERYHOUSE_MARIADB__
#include "client_mariadb.h"
#endif

namespace client {

DBClient *create_client(const std::string &db_name, const YAML::Node &config) {
  DBClient *result = nullptr;
  std::cerr << "Create client: " << db_name << std::endl;

  if (db_name == "mysql") {
#ifdef __QUERYHOUSE_MYSQL__
    result = new MySQLClient;
#endif
  } else if (db_name == "postgresql") {
#ifdef __QUERYHOUSE_POSTGRESQL__
    result = new PostgreSQLClient;
#endif
  } else if (db_name == "sqlite") {
#ifdef __QUERYHOUSE_SQLITE__
    std::cerr << "Create SQLite client" << std::endl;
    result = new SQLiteClient;
#endif
  } else if (db_name == "oracle") {
#ifdef __QUERYHOUSE_ORACLE__
    std::cerr << "Create Oracle client" << std::endl;
    result = new OracleClient;
#endif
  } else if (db_name == "mariadb") {
#ifdef __QUERYHOUSE_MARIADB__
    std::cerr << "Create MariaDB client" << std::endl;
    result = new MARIADBClient;
#endif
  }

  assert(result && "It is not supported!");
  result->initialize(config);
  return result;
}

std::string execution_status_to_string(ExecutionStatus status) {
  switch (status) {
    case kConnectFailed:
      return "kConnectFailed";
    case kExecuteError:
      return "kExecuteError";
    case kServerCrash:
      return "kServerCrash";
    case kNormal:
      return "kNormal";
    case kTimeout:
      return "kTimeout";
    case kSyntaxError:
      return "kSyntaxError";
    case kSemanticError:
      return "kSemanticError";
    default:
      return "Unknown";
  }
}

};  // namespace client
