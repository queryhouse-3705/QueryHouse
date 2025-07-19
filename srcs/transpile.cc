#include "transpile.h"

#include <pybind11/embed.h>

#include <cstring>
#include <vector>

// Python module in C++
namespace py = pybind11;
py::scoped_interpreter guard{};

//std::ofstream transpile_logfile("/tmp/transpile.Fuzzlog",
                                    //std::ios::out | std::ios::app);

std::string trim(const std::string &str) {
  size_t start = str.find_first_not_of(" \t\n\r");
  if (start == std::string::npos) return "";
  size_t end = str.find_last_not_of(" \t\n\r");
  return str.substr(start, end - start + 1);
}

/***************************************
 * Transpiler
 ***************************************/
/*
 * transpile()
 *
 * Transpiles a given `query` for DBMSs specified by the bitmask `targets`
 *
 * Returns the QueryQueue containing the transpilation result
 *
 * This is a wrapper for transpile_for()
 */
#ifdef ENABLE_TRANSPILER
TestGroup transpile(const std::string &query, TargetsMask targets) {
  TestGroup tg(query);
  tg.targets = targets;

  std::vector<std::string> stmts = split_query(query.c_str(), query.size());

  for (Target &t : to_targets(targets)) {
    if (t == Target::SQLite) {
      // SQLite does not need transpilation
      tg.adapted_queries[t] = query;
    } else {
      // Transpile each statement for others
      for (const auto &stmt : stmts) {
        std::string transpiled_query = trim(transpile_for(stmt, t));
        if (!transpiled_query.empty()) {
          tg.adapted_queries[t] += transpiled_query + "; ";
        }
      }
    }
  }
  return tg;
}
#else
TestGroup transpile(const std::string &query, TargetsMask targets) {
  TestGroup tg(query);
  tg.targets = targets;
  for (Target &t : to_targets(targets)) {
    tg.adapted_queries[t] = query;
  }
  return tg;
}
#endif  // ENABLE_TRANSPILER

// ; as delim, skip empty queries
std::vector<std::string> split_query(const char *buf, size_t len) {
  std::vector<std::string> queries;
  std::string query;
  for (size_t i = 0; i < len; i++) {
    if (buf[i] == ';') {
      query.push_back(buf[i]);
      query = trim(query);
      if (!query.empty()) {
        queries.push_back(query);
      }
      query.clear();
    } else {
      query.push_back(buf[i]);
    }
  }

  // Last query
  query = trim(query);
  if (!query.empty()) {
    queries.push_back(query);
  }
  return queries;
}

/*
 * transpile_for()
 *
 * Transpiles a given `query` for the specified DBMS `target`
 *
 * This is a actual worker of transpiler.
 */
std::string transpile_for(const std::string &query, Target target) {
  // Import the SQLglot module
  py::object sqlglot = py::module::import("sqlglot");

  // Set the appropriate dialect for the target
  std::string dialect;
  switch (target) {
    case Target::MySQL:
      dialect = "mysql";
      break;
    case Target::PostgreSQL:
      dialect = "postgres";
      break;
    case Target::Oracle:
      dialect = "oracle";
      break;
    case Target::MariaDB:
      dialect = "mysql";
      break;
    case Target::SQLite:
      throw std::invalid_argument("SQLite does not need transpilation");
    default:
      throw std::invalid_argument("Unsupported target");
  }

  try {
    // Call the transpile function from SQLglot to convert the query
    py::object transpile_func = sqlglot.attr("transpile");

    // Pass the query and target dialect to SQLglot for transpiling
    py::object transpiled_query_obj =
        transpile_func(query, py::arg("write") = dialect);

    // Convert the Python object (likely a list) to a Python list
    py::list transpiled_query_list = transpiled_query_obj.cast<py::list>();

    // Extract the first query from the list if it's not empty
    std::string transpiled_query = "";
    if (!transpiled_query_list.empty()) {
      // Get the first element from the list and cast it to std::string
      transpiled_query = transpiled_query_list[0].cast<std::string>();
    } else {
      throw std::runtime_error("Transpiling returned an empty list");
    }

    return transpiled_query;
  } catch (py::error_already_set &e) {
    // std::cerr << "Python error: " << e.what() << std::endl;
    return "";
  } catch (const std::exception &e) {
    // std::cerr << "C++ error: " << e.what() << std::endl;
    return "";
  }
}
