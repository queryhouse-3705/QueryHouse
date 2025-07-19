#include "executor.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// extern std::ofstream outfile;
std::ofstream reportfile("/tmp/report.Fuzzlog", std::ios::out | std::ios::app);

#ifdef LOG_INPUT
size_t input_count = 0;
#endif  // LOG_INPUT

/***************************************
 * Result Analyzer (Normalizer)
 ***************************************/

bool isJSON(const std::string &data) {
  //outfile << data << std::endl;
  if (data.empty()) return false;
  // trimming
  size_t start = data.find_first_not_of(" \t\n\r");
  if (start == std::string::npos) return false;
  char first_char = data[start];
  return first_char == '{' || first_char == '[';
};

std::string fixJSONCase(const std::string &data) {
  std::string fixed_data = data;
  size_t pos = 0;

  // Replace "TRUE" with "true"
  while ((pos = fixed_data.find("TRUE", pos)) != std::string::npos) {
    fixed_data.replace(pos, 4, "true");
    pos += 4;
  }

  // Replace "FALSE" with "false"
  pos = 0;
  while ((pos = fixed_data.find("FALSE", pos)) != std::string::npos) {
    fixed_data.replace(pos, 5, "false");
    pos += 5;
  }

  // Replace "NULL" with "null"
  pos = 0;
  while ((pos = fixed_data.find("NULL", pos)) != std::string::npos) {
    fixed_data.replace(pos, 4, "null");
    pos += 4;
  }

  return fixed_data;
}

// Normalize JSON string
std::string formatJSON(std::string &data) {
  try {
    data = fixJSONCase(data);
    json obj = json::parse(data);

    return obj.dump();
  } catch (const json::parse_error &e) {
    return data;
  }
}

// Trim quotation marks from strings
std::string trimQuotes(const std::string &str) {
  //outfile << str << std::endl;
  if (str.size() < 2) return str;
  if ((str.front() == '"' && str.back() == '"') ||
      (str.front() == '\'' && str.back() == '\'')) {
    return str.substr(
        1, str.size() - 2);  // Remove the first and last character (quotes)
  }
  return str;
}

bool isInt(const std::string &str) {
  if (str.empty()) return false;
  size_t start = (str[0] == '-') ? 1 : 0;
  return std::all_of(str.begin() + start, str.end(), ::isdigit);
}

bool isFloat(const std::string &str) {
  if (str.empty()) return false;
  std::istringstream iss(str);
  float f;
  iss >> std::noskipws >> f;  // noskipws considers leading whitespace invalid
  return iss.eof() && !iss.fail();
}

// Normalize integer string
std::string formatInt(const std::string &intStr) {
  // -0 = 0 in SQL
  if (intStr == "-0") return "0";
  return intStr;
}

// Normalize float string
std::string formatFloat(const std::string &floatStr) {
  std::ostringstream oss;
  long double f = std::stold(floatStr);
  oss << std::setprecision(6) << f;

  // -0 = 0 in SQL
  if (oss.str() == "-0") oss.str("0");
  
  return oss.str();
}

// Normalize Scientific Notation
std::string normalizeScientificNotation(const std::string &num) {
  try {
    // scientific notation string -> double -> fixed point float
    double value = std::stod(num);
    std::ostringstream stream;
    stream << std::scientific << std::setprecision(3) << value;
    return stream.str();
  } catch (...) {
    // Return original strin back if failed
    return num;
  }
}

/* 
 * normalizeValues():
 *
 * Normalize values before sorting, handling constants, integers, floats,
 * JSON strings, and quoted strings.
 */
std::vector<std::vector<std::string>> normalizeValues(
    const std::vector<std::vector<std::string>> &result) {
  // string replace map
  std::map<std::string, std::string> replace_map = {
      {"t", "1"}, {"f", "0"}, {"TRUE", "1"}, {"FALSE", "0"}, {"NULL", ""}};
  auto normalized_result = result;
  for (auto &row : normalized_result) {
    for (auto &cell : row) {
      // Replace
      for (const auto &[pattern, replacement] : replace_map) {
        if (cell == pattern) {
          cell = replacement;
        }
      }
      if (isInt(cell)) {
        cell = formatInt(cell);
      } else if (isFloat(cell)) {
        //outfile << CYAN << "Formatting float: " << cell;
        // Format floats to a standard representation
        cell = formatFloat(cell);
        //outfile << " -> " << cell << RESET << std::endl;
      } else if (isJSON(cell)) {
        cell = formatJSON(cell);
      } else {
        // Remove quotes if any
        cell = trimQuotes(cell);
      }
    }
  }
  return normalized_result;
}

/***************************************
 * Result Analyzer (Comparator)
 ***************************************/

/*
 * checkFloatEqual()
 *
 * Compares two float strings and returns true if they are equal, false otherwise.
*/
bool checkFloatEqual(const std::string &str1, const std::string &str2) {
  try {
    //outfile << YELLOW << "[Check Float Equal]" << RESET << std::endl;

    // Try convert string to double
    double value1, value2;
    try {
      value1 = std::stod(str1);
      value2 = std::stod(str2);
    } catch (const std::invalid_argument &e) {
      //outfile << "Not a float: " << vec1[i][j] << " vs " << vec2[i][j]
              //<< std::endl;
      return false;  // Fail to convert -> Not equal
    } catch (const std::out_of_range &e) {
      //outfile << "Value out of range: " << vec1[i][j] << " vs "
              //<< vec2[i][j] << std::endl;
      return false;  // Out-of-range -> Not equal
    }

    // double to string (handle scientific notation)
    std::ostringstream streama, streamb;
    streama << value1;
    streamb << value2;

    std::string strValue1 = streama.str();
    std::string strValue2 = streamb.str();

    bool hasExponent1 = strValue1.find('e') != std::string::npos;
    bool hasExponent2 = strValue2.find('e') != std::string::npos;

    //outfile << "Comparing " << value1 << " and " << value2 << std::endl;

    if (hasExponent1 && hasExponent2) {
      // Normalize (scientific notation)
      std::string normalized1 = normalizeScientificNotation(str1);
      std::string normalized2 = normalizeScientificNotation(str2);

      //outfile << "Normalized Comparison: " << normalized1 << " and "
              //<< normalized2 << std::endl;

      // Compare normalized strings
      if (normalized1 != normalized2) {
        //outfile << "Value mismatch after normalization: " << normalized1
                //<< " vs " << normalized2 << std::endl;
        return false;
      }
    } else {
      // Rounding
      double scale = std::pow(10.0, 3);  // 10^precision
      double roundedValue1 = std::round(value1 * scale) / scale;
      double roundedValue2 = std::round(value2 * scale) / scale;

      //outfile << "Rounded Comparison: " << roundedValue1 << " and "
              //<< roundedValue2 << std::endl;

      // Compare
      double epsilon = 1e-9;    // Margin of error
      if (std::fabs(roundedValue1 - roundedValue2) >= epsilon) {
        //outfile << "Value mismatch: " << value1 << " vs " << value2
                //<< std::endl;
        return false;
      }
      // Unify decimal places
      std::ostringstream stream1, stream2;
      stream1 << std::fixed << std::setprecision(3) << value1;
      stream2 << std::fixed << std::setprecision(3) << value2;

      std::string normalized3 = stream1.str();
      std::string normalized4 = stream2.str();

      //outfile << "Comparing with precision: " << normalized3 << " and "
              //<< normalized4 << std::endl;

      // Compare normalized string
      if (normalized3 != normalized4) {
        //outfile << "Value mismatch: " << normalized3 << " vs "
                //<< normalized4 << std::endl;
        return false;
      }
    }

    return true;

  } catch (const std::exception &e) {
    //outfile << "Exception occurred: " << e.what() << std::endl;
    return false;
  }
}

/*
 * compare_row_num()
 *
 * Compares the number of rows between query results from multiple DBMS.
 * Returns true if the row counts are the same across all DBMS, false otherwise.
 */
bool compare_row_num(std::vector<Result> &results) {
  if (results.empty()) {
    //outfile << "No results to compare." << std::endl;
    return true;
  }

  // Filter results with status == client::kNormal
  std::vector<Result> normal_results;
  for (const auto &result : results) {
    if (result.status == client::kNormal) {
      normal_results.push_back(result);
    } //else {
      //outfile << "Error: " << target_to_string(result.target)
              //<< " returned with status: " << result.status << std::endl;
    //}
  }

  if (normal_results.size() < 2) {
    //outfile << "No results with status kNormal to compare." << std::endl;
    return true;
  }

  // Get the row count of the first DBMS as the reference
  size_t reference_row_count = normal_results.front().result.size();

  // Compare the row count of each DBMS with the reference
  for (const auto &result : normal_results) {
    if (result.result.size() != reference_row_count) {
      return false;
    }
  }

  return true;
}

/*
 * compare_row()
 *
 * Compares each database result with the first database result after
 * normalizing and sorting the values.
 * Returns true if the results are the same across all DBMS, false otherwise.
 */
bool compare_row(std::vector<Result> &results) {
  if (results.empty()) {
    //outfile << "No results to compare." << std::endl;
    return true;
  }

  // Filter results with status == client::kNormal
  std::vector<Result> normal_results;
  for (const auto &result : results) {
    if (result.status == client::kNormal) {
      normal_results.push_back(result);
    } //else {
      //outfile << "Error: " << target_to_string(result.target)
              //<< " returned with status: " << result.status << std::endl;
    //}
  }

  if (normal_results.size() < 2) {
    //outfile << "No results with status kNormal to compare." << std::endl;
    return true;
  }

  // Prepare to store normalized and sorted results for all DBMS
  std::vector<Result> sorted_results;

  // Normalize and sort all DBMS results
  for (const auto &result : normal_results) {
    // Get normalized values
    auto normalized_result = normalizeValues(result.result);
    // Sort normalized values
    std::sort(normalized_result.begin(), normalized_result.end());
    // Store sorted, normalized results
    sorted_results.push_back({result.target, normalized_result, result.status, result.executed_query});
  }

  // Use the first DBMS's sorted result as the baseline for comparison
  const Result &ref_result = sorted_results.front();
  
  bool match = true;

  // Compare all other DBMS results to the reference
  for (const Result &result : sorted_results) {
    if (result.target == ref_result.target)
      continue;  // Skip comparison with itself

    // Compare each row
    for (size_t i = 0; i < ref_result.result.size(); ++i) {
      if (ref_result.result[i].size() != result.result[i].size()) {
        match = false;
        break;
      }

      // Compare each column
      for (size_t j = 0; j < ref_result.result[i].size(); ++j) {
        const std::string &value = result.result[i][j];
        const std::string &ref_value = ref_result.result[i][j];
        if (value != ref_value && !checkFloatEqual(value, ref_value)) {
          match = false;
          
          break;
        }
      }

      if (!match) {
        break;
      }
    }

    if (!match) {
      break;
    }
  }

  return match;
}

/***************************************
 * Executor
 ***************************************/

/*
 * execute_testgroup()
 *
 * Executes queries for each DBMS and compares the results row by row.
 * Returns true if no error occurs, false otherwise.
 */
bool execute_testgroup(
    TestGroup &testgroup,
    const std::map<Target, std::unique_ptr<client::DBClient>> &db_clients,
    std::vector<Result> &results,
    unsigned long batch_number,
    int index_in_batch) {

  // Execute queries
  std::vector<std::vector<std::string>> results_buffer;
  for (const auto &target : to_targets(testgroup.targets)) {
    const char *query = testgroup.adapted_queries[target].c_str();
    size_t query_len = testgroup.adapted_queries[target].size();
    client::ExecutionStatus status_buffer =
        db_clients.at(target)->execute(query, query_len, results_buffer);
    results.push_back({target, results_buffer, status_buffer, query});
    results_buffer.clear();
  }

  // Compare results
  if (!compare_row_num(results) || !compare_row(results)) {
    report(testgroup, results, batch_number, index_in_batch);
    return false;
  }

  return true;
}

/***************************************
 * Reporter
 ***************************************/

/*
 * report()
 *
 * Reports a bug when different results are found.
 *  - Log on file
 *  - Prints queries & results
 */
void report(TestGroup &tg, std::vector<Result> &results, unsigned long batch_number, int index_in_batch) {
  //outfile << YELLOW << "[Reporting Bug]" << RESET << std::endl;

  if (!reportfile.is_open()) {
    //outfile << RED << "Error: Could not open the log file." << RESET
            //<< std::endl;
    return;
  }

  reportfile << std::unitbuf;
  reportfile << "batch-index: " << batch_number << "-" << index_in_batch << std::endl;
  reportfile << "Bug Report:\n";

  for (const auto &result : results) {
    if (result.status == client::kNormal) {
      log_result_one(result);
    }
  }
}

/*
 * log_result_one()
 *
 * Logs the result of a single DBMS.
 */
void log_result_one(const Result &result) {
  if (!reportfile.is_open()) return;

  reportfile << " " << target_to_string(result.target)
      << ": "  << result.executed_query << "\n";

  reportfile << "Results: \n";
  for (const auto &row : result.result) {
    for (const auto &col : row) {
      reportfile << col << " ";
    }
    reportfile << "\n";
  }
  reportfile << "\n";
}


/*
 * log_stats()
 *
 * Logs the statistics of the fuzz campaign.
 */
void log_stats(
    size_t base_query_count, size_t base_statement_count, size_t dbms_statement_count,
    std::map<Target, size_t> &dbms_valid_query_count,
    std::map<int, size_t> &validity_score_distribution) {
  // Update feedback log
  std::ofstream logfile("/tmp/stats.Fuzzlog", std::ios::trunc);

  logfile << "[INFO] Base query count: " << base_query_count << "\n\n";
  logfile << "[INFO] Base statement count: " << base_statement_count << "\n\n";
  logfile << "[INFO] DBMS statement count: " << dbms_statement_count << "\n\n";

  logfile << "[INFO] DBMS-specific valid queries:\n";
  for (const auto &[target, count] : dbms_valid_query_count) {
    logfile << "  - " << target_to_string(target) << ": " << count << "\n";
  }
  
  logfile << "\n"
      << "[INFO] Validity score distribution:\n";
  for (const auto &[score, count] : validity_score_distribution) {
    logfile << "  - " << score << ": " << count << "\n";
  }

  logfile.close();
}

#ifdef LOG_INPUT
/*
 * log_input()
 *
 * Sequentially logs the executed input queries in /tmp/input directory
 */
void log_input(TestGroup *tg) {
  std::string filename = "/tmp/input/" + std::to_string(input_count);
  std::ofstream outfile(filename, std::ios::trunc);
  outfile << tg->base_query << "\n";
  for (const auto &target : to_targets(tg->targets)) {
    outfile << target_to_string(target) << ": " << tg->adapted_queries[target] << "\n";
  }
  outfile.close();
  input_count++;
}
#endif  // LOG_INPUT

#ifdef LOG_TRANSPILE_FAIL
/*
 * log_transpile_fail()
 *
 * Logs cases where the transpiler fails: Valid in SQLite, but not in others.
 */
void log_transpile_fail(std::vector<Result> &results) {

  // Check transpiler failure
  bool is_sqlite_valid = false;
  bool invalid_exists = false;
  for (const auto &result : results) {
    if (result.target == Target::SQLite) {
      if (result.status == client::kNormal) {
        is_sqlite_valid = true;
      }
    }
    if (result.status != client::kNormal) {
      invalid_exists = true;
    }
  }

  if (!is_sqlite_valid || !invalid_exists) {
    return;
  }

  // Log the failed queries
  std::ofstream outfile("/tmp/transpile_fail.Fuzzlog", std::ios::app);
  outfile << input_count;
  for (const auto &result : results) {
    if (result.status != client::kNormal) {
      outfile << " " << target_to_string(result.target);
    }
  }
  outfile << "\n";
  outfile.close();
}
#endif  // LOG_TRANSPILE_FAIL
