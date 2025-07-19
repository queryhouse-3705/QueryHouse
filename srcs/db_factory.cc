#include <cassert>

#include "db.h"

#ifdef __QUERYHOUSE_SQLITE__
#include "sqlite.h"
#endif

DataBase* create_database(YAML::Node config) {
  const std::string db_name = config["db"].as<std::string>();
  DataBase* result = nullptr;

  if (db_name == "sqlite") {
    result = create_sqlite();
  } else {
    assert(false && "Unreachable");
  }

  assert(result && "Unreachable");
  result->initialize(config);
  return result;
}

