#include "postprocess.h"

#include <cstring>
#include <sstream>
#include <vector>

//std::fstream postprocesslog("/tmp/postprocess.Fuzzlog",
                            //std::ios::out | std::ios::app);

// split query with semicolon
std::vector<std::string> splitQuery(const std::string& query) {
  std::vector<std::string> queries;
  std::string query_piece;
  std::istringstream query_stream(query);
  while (std::getline(query_stream, query_piece, ';')) {
    if (!query_piece.empty()) {
      queries.push_back(query_piece);
    }
  }
  return queries;
}

size_t findOppositeParentheses(const std::string& query, int start) {
  int count = 0;
  for (size_t i = start; i < query.size(); i++) {
    if (query[i] == '(') {
      count++;
    } else if (query[i] == ')') {
      count--;
    }
    if (count == 0) {
      return i;
    }
  }
  return -1;
}

std::string strip(const std::string& str) {
  std::string result;
  for (const auto& c : str) {
    if (c != ' ' && c != '\n' && c != '\t') {
      result.push_back(c);
    }
  }
  return result;
}

std::vector<std::string> strip_vector(const std::vector<std::string>& vec) {
  std::vector<std::string> result;
  for (const auto& str : vec) {
    result.push_back(strip(str));
  }
  return result;
}

bool isInt(const std::string& str) {
  return str.find_first_not_of("0123456789") == std::string::npos;
}

bool isFloat(const std::string &str) {
  if (str.empty()) return false;
  std::istringstream iss(str);
  float f;
  iss >> std::noskipws >> f;  // noskipws considers leading whitespace invalid
  return iss.eof() && !iss.fail();
}

// rounding
std::string roundFromFloat(const std::string& str) {
  std::string result;
  std::istringstream float_stream(str);
  float f;
  float_stream >> f;
  result = std::to_string(static_cast<int>(f));
  return result;
}

bool createInfo(const std::string& query, std::string& tablename,
                std::vector<std::pair<std::string, std::string>>& columnnames) {
  std::string create = "CREATE TABLE ";
  size_t create_pos = query.find(create);
  if (create_pos == std::string::npos) {
    return false;
  }
  size_t start = create_pos + create.size();
  size_t end = query.find('(', start);
  tablename = query.substr(start, end - start);
  // IF NOT EXISTS
  if (tablename.find("IF NOT EXISTS") != std::string::npos) {
    tablename = tablename.substr(tablename.find("IF NOT EXISTS") + 13);
  }
  size_t column_start = end;
  size_t column_end = findOppositeParentheses(query, column_start);
  std::string columnsblock =
      query.substr(column_start + 1, column_end - column_start - 1);

  // seprate parenthesis
  std::vector<std::string> columns;
  std::string column;
  for (size_t i = 0; i < columnsblock.size(); i++) {
    if (columnsblock[i] == ' ' && columnsblock[i + 1] == '(') {
      i = findOppositeParentheses(columnsblock, i + 1) + 1;
      if (i == -1) {
        return false;
      }
    }
    if (columnsblock[i] == ',') {
      columns.push_back(column);
      column.clear();
    } else {
      column.push_back(columnsblock[i]);
    }
  }
  columns.push_back(column);
  for (const auto& col : columns) {
    std::istringstream col_stream(col);
    std::string colname;
    std::string coltype;
    col_stream >> colname >> coltype;
    // find ( in coltype and add until )
    if (coltype.find('(') != std::string::npos) {
      col_stream >> coltype;
    }
    columnnames.push_back({colname, coltype});
  }
  return true;
}

bool indexInfo(const std::string& query, std::string& tablename,
               std::vector<std::string>& columnnames) {
  std::string prefix = "CREATE INDEX";
  size_t on_pos = query.find(prefix);
  if (on_pos == std::string::npos) {
    return false;
  }
  prefix = " ON ";
  size_t start = query.find(prefix, on_pos) + prefix.size();
  size_t end = query.find('(', start);
  tablename = query.substr(start, end - start);
  size_t column_start = end;
  size_t column_end = findOppositeParentheses(query, column_start);
  std::string columnsblock =
      query.substr(column_start + 1, column_end - column_start - 1);
  // seprate comma
  std::string column;
  std::vector<std::string> columns;
  for (size_t i = 0; i < columnsblock.size(); i++) {
    if (columnsblock[i] == ',') {
      columns.push_back(column);
      column.clear();
    } else {
      column.push_back(columnsblock[i]);
    }
  }
  columns.push_back(column);
  for (const auto& col : columns) {
    std::istringstream col_stream(col);
    std::string colname;
    col_stream >> colname;
    columnnames.push_back(colname);
  }
  return true;
}

void extractTableNameAndColumns(const std::string& statement,
                                std::string& current_table_name,
                                std::vector<std::string>& table_columns) {
  size_t table_name_start =
      statement.find(" ", statement.find("CREATE TABLE") +
                              std::string("CREATE TABLE").length());
  size_t table_name_end = statement.find("(", table_name_start);
  current_table_name =
      statement.substr(table_name_start, table_name_end - table_name_start);
  current_table_name.erase(0, current_table_name.find_first_not_of(" \t\n\r"));
  current_table_name.erase(current_table_name.find_last_not_of(" \t\n\r") + 1);

  size_t column_start = statement.find("(", table_name_end) + 1;
  size_t column_end = statement.find(")", column_start);
  std::string columns_part =
      statement.substr(column_start, column_end - column_start);

  std::stringstream columns_ss(columns_part);
  std::string column;
  while (std::getline(columns_ss, column, ',')) {
    column.erase(0, column.find_first_not_of(" \t\n\r"));
    column.erase(column.find_last_not_of(" \t\n\r") + 1);

    if (column.find("FOREIGN KEY") != std::string::npos ||
        column.find("PRIMARY KEY") != std::string::npos ||
        column.find("CHECK") != std::string::npos ||
        column.find("UNIQUE") != std::string::npos) {
      continue;
    }

    size_t space_pos = column.find_first_of(" \t\n\r");
    std::string column_name =
        (space_pos != std::string::npos) ? column.substr(0, space_pos) : column;
    column_name.erase(0, column_name.find_first_not_of(" \t\n\r"));
    column_name.erase(column_name.find_last_not_of(" \t\n\r") + 1);

    if (!column_name.empty()) {
      table_columns.push_back(column_name);
    }
  }
}

// SQLite
void sqliteEnableForeignKey_Postprocess(TestGroup& tg) {
  // enable PRAGMA foreign_keys = ON; on head
  std::string query = tg.adapted_queries[Target::SQLite];
  tg.adapted_queries[Target::SQLite] = "PRAGMA foreign_keys = ON;" + query;
}

void mysqlIndexSize_Postprocess(TestGroup& tg) {
  // std::ofstream postprocesslog("/tmp/tmpPostprocess",
  //                              std::ios::out | std::ios::app);
  // postprocesslog << std::unitbuf;
  std::string query = tg.adapted_queries[Target::MySQL];
  std::vector<std::string> queries = splitQuery(query);
  // find create
  std::vector<std::string> create_tablename_vector;
  std::vector<std::vector<std::pair<std::string, std::string>>> create_columnname_vectors;
  std::vector<size_t> create_pos_vector;
  std::string create_tablename;
  std::vector<std::pair<std::string, std::string>> create_columnnames;
  
  for (size_t j = 0; j < queries.size(); j++) {
    if (createInfo(queries[j], create_tablename, create_columnnames)) {
      create_tablename_vector.push_back(create_tablename);
      create_columnname_vectors.push_back(create_columnnames);
      create_pos_vector.push_back(j);
      create_tablename.clear();
      create_columnnames.clear();
    }
  }
  if (create_tablename_vector.empty()) {
    return;
  }

  // postprocesslog << "======" << std::endl;
  // postprocesslog << "query: " << query << std::endl;
  //for (size_t j = 0; j < create_tablename_vector.size(); j++) {
    // postprocesslog << "create tablename: " << create_tablename_vector[j]
    //                << std::endl;
    //for (const auto& col : create_columnname_vectors[j]) {
      // postprocesslog << "column name: " << col.first
      //                << " column type: " << col.second << std::endl;
    //}
  //}
  
  // find index
  std::vector<std::string> index_tablename_vector;
  std::vector<std::vector<std::string>> index_columnname_vectors;
  std::vector<size_t> index_pos_vector;
  for (size_t j = 0; j < queries.size(); j++) {
    std::string index_tablename;
    std::vector<std::string> index_columnnames;
    if (indexInfo(queries[j], index_tablename, index_columnnames)) {
      index_tablename_vector.push_back(index_tablename);
      index_columnname_vectors.push_back(index_columnnames);
      index_pos_vector.push_back(j);
      index_tablename.clear();
      index_columnnames.clear();
    }
  }
  if (index_tablename_vector.empty()) {
    return;
  }

  for (size_t j = 0; j < index_tablename_vector.size(); j++) {
    // check create tablename
    for (size_t k = 0; k < create_tablename_vector.size(); k++) {
      // postprocesslog << "Comparing " << create_tablename_vector[k] << " and
      // "
      //                << index_tablename_vector[j] << std::endl;
      if (strip(create_tablename_vector[k]) ==
              strip(index_tablename_vector[j]) &&
          create_pos_vector[k] < index_pos_vector[j]) {
        // check column name is same and type is TEXT or VARCHAR(*)
        for (const auto& col : create_columnname_vectors[k]) {
          for (const auto& index_col : index_columnname_vectors[j]) {
            if (strip(col.first) == strip(index_col) &&
                (col.second == "TEXT" ||
                  col.second.find("VARCHAR") != std::string::npos)) {
              // replace index column into v0(766)
              std::string original_query = queries[index_pos_vector[j]];
              queries[index_pos_vector[j]] =
                  queries[index_pos_vector[j]].replace(
                      queries[index_pos_vector[j]].find(index_col),
                      index_col.size(), col.first + "(766)");
              tg.adapted_queries[Target::MySQL]
                  .replace(tg.adapted_queries[Target::MySQL].find(original_query),
                           original_query.size(),
                           queries[index_pos_vector[j]]);
            }
          }
        }
      }
    }
  }
  // postprocesslog << "Final query: "
  //                << plan->query_infos.at(Target::MySQL).queries[i]
  //                << std::endl;
}

// INSERT INTO t1 (c0, c1) VALUES (0, 1);
bool insertInfo(const std::string& query, std::string& tablename,
                std::vector<std::string>& columnnames,
                std::vector<std::vector<std::string>>& columnvalues) {
  std::string prefix = "INSERT INTO ";
  size_t insert_pos = query.find(prefix);
  if (insert_pos == std::string::npos) {
    return false;
  }
  size_t start = insert_pos + prefix.size();
  size_t end = query.find(' ', start);
  tablename = query.substr(start, end - start);
  size_t column_start = query.find(' ', end);
  size_t column_end = query.find("VALUES", column_start);
  std::string columnsblock =
      query.substr(column_start + 1, column_end - column_start - 7);
  // check start with '('
  if (columnsblock[0] == '(') {
    columnsblock = columnsblock.substr(1, columnsblock.size() - 2);
    std::string column;
    for (size_t i = 0; i < columnsblock.size(); i++) {
      if (columnsblock[i] == ',') {
        columnnames.push_back(column);
        column.clear();
      } else {
        column.push_back(columnsblock[i]);
      }
    }
    columnnames.push_back(column);
  }
  bool is_next = true;
  while (is_next) {
    size_t value_start = query.find('(', column_end);
    size_t value_end = findOppositeParentheses(query, value_start);
    std::string valuesblock =
        query.substr(value_start + 1, value_end - value_start - 1);
    // seprate comma
    std::string value;
    std::vector<std::string> values;
    for (size_t i = 0; i < valuesblock.size(); i++) {
      if (valuesblock[i] == ',') {
        values.push_back(value);
        value.clear();
      } else {
        value.push_back(valuesblock[i]);
      }
    }
    values.push_back(value);
    columnvalues.push_back(values);
    column_end = value_end;
    if (query.find('(', column_end) == std::string::npos) {
      is_next = false;
    }
  }
  return true;
}

bool whereInfo(const std::string& query, std::string& where) {
  std::string prefix = "WHERE ";
  size_t where_pos = query.find(prefix);
  if (where_pos == std::string::npos) {
    return false;
  }
  where = query.substr(where_pos + prefix.size());
  return true;
}

// check Float data goes into INT
void checkTypeViolation_Postprocess(TestGroup& tg) {
  std::string query = tg.adapted_queries[Target::SQLite];
  std::vector<std::string> queries = splitQuery(query);
  
  // find create
  std::vector<size_t> create_pos_vector;
  std::vector<std::string> create_tablename_vector;
  std::vector<std::vector<std::pair<std::string, std::string>>> create_columnname_vectors;
  std::string create_tablename;
  std::vector<std::pair<std::string, std::string>> create_columnnames;
  for (size_t j = 0; j < queries.size(); j++) {
    if (createInfo(queries[j], create_tablename, create_columnnames)) {
      create_tablename_vector.push_back(create_tablename);
      create_columnname_vectors.push_back(create_columnnames);
      create_tablename.clear();
      create_columnnames.clear();
      create_pos_vector.push_back(j);
    }
  }
  if (create_tablename_vector.empty()) {
    return;
  }

  // find insert
  std::vector<size_t> insert_pos_vector;
  std::vector<std::string> insert_tablename_vector;
  std::vector<std::vector<std::string>> insert_columnname_vectors;
  std::vector<std::vector<std::vector<std::string>>>
      insert_columnvalue_vectors;
  for (size_t j = 0; j < queries.size(); j++) {
    std::string insert_tablename;
    std::vector<std::string> insert_columnnames;
    std::vector<std::vector<std::string>> insert_columnvalues;
    if (insertInfo(queries[j], insert_tablename, insert_columnnames,
                    insert_columnvalues)) {
      insert_tablename_vector.push_back(insert_tablename);
      insert_columnname_vectors.push_back(insert_columnnames);
      insert_columnvalue_vectors.push_back(insert_columnvalues);
      insert_tablename.clear();
      insert_columnnames.clear();
      insert_columnvalues.clear();
      insert_pos_vector.push_back(j);
    }
  }
  if (insert_tablename_vector.empty()) {
    return;
  }

  // log column valye
  // postprocesslog << "Query: " << query << std::endl;
  //for (size_t j = 0; j < insert_columnvalue_vectors.size(); j++) {
    //// postprocesslog << "insert tablename: " << insert_tablename_vector[j]
    ////                << std::endl;
    //if (!insert_columnname_vectors[j].empty()) {
      //for (const auto& col : insert_columnname_vectors[j]) {
        //// postprocesslog << "column name: " << col << std::endl;
      //}
    //}
    //if (!insert_columnvalue_vectors[j].empty()) {
      //for (const auto& values : insert_columnvalue_vectors[j]) {
        //for (const auto& value : values) {
          //// postprocesslog << "value: " << value << std::endl;
        //}
        //// postprocesslog << "======" << std::endl;
      //}
    //}
  //}

  // log
  // postprocesslog << "======" << std::endl;
  // postprocesslog << "query: " << query << std::endl;
  // for (size_t j = 0; j < create_tablename_vector.size(); j++) {
  //   postprocesslog << "create tablename: " << create_tablename_vector[j]
  //                  << std::endl;
  //   for (const auto &col : create_columnname_vectors[j]) {
  //     postprocesslog << "column name: " << col.first
  //                    << " column type: " << col.second << std::endl;
  //   }
  // }
  // for (size_t j = 0; j < insert_tablename_vector.size(); j++) {
  //   postprocesslog << "insert tablename: " << insert_tablename_vector[j]
  //                  << std::endl;
  //   if (!insert_columnname_vectors[j].empty()) {
  //     for (const auto &col : insert_columnname_vectors[j]) {
  //       postprocesslog << "column name: " << col << std::endl;
  //     }
  //   }
  //   if (!insert_columnvalue_vectors[j].empty()) {
  //     for (const auto &values : insert_columnvalue_vectors[j]) {
  //       for (const auto &value : values) {
  //         postprocesslog << "value: " << value << std::endl;
  //       }
  //     }
  //   }
  // }

  // check type violation
  // check size
  for (size_t j = 0; j < insert_pos_vector.size(); j++) {
    // check size
    if (insert_pos_vector.size() != insert_tablename_vector.size() ||
        insert_pos_vector.size() != insert_columnvalue_vectors.size()) {
      continue;
    }
    if (create_pos_vector.size() != create_tablename_vector.size() ||
        create_pos_vector.size() != create_columnname_vectors.size()) {
      continue;
    }

    // case insert column exist
    if (insert_columnname_vectors[j].empty()) {
      for (size_t k = 0; k < create_tablename_vector.size(); k++) {
        // postprocesslog << "Comparing " << create_tablename_vector[k]
        //                << " and " << insert_tablename_vector[j] <<
        //                std::endl;
        if (strip(create_tablename_vector[k]) !=
                strip(insert_tablename_vector[j]) ||
            create_pos_vector[k] > insert_pos_vector[j]) {
          continue;
        }
        // size check
        for (size_t l = 0; l < insert_columnvalue_vectors[j].size(); l++) {
          for (size_t m = 0; m < insert_columnvalue_vectors[j][l].size();
                m++) {
            // size check
            // postprocesslog
            //     << "size check: " << create_columnname_vectors[k].size()
            //     << " " << insert_columnvalue_vectors[j][l].size()
            //     << std::endl;
            if (create_columnname_vectors[k].size() !=
                insert_columnvalue_vectors[j][l].size()) {
              continue;
            }
            if (create_columnname_vectors[k][m].second.find("INT") ==
                std::string::npos) {
              continue;
            }
            // postprocesslog << "Found int column: "
            //                << create_columnname_vectors[k][m].first << " "
            //                << create_columnname_vectors[k][m].second
            //                << std::endl;
            if (isInt(strip(insert_columnvalue_vectors[j][l][m])) ||
                !isFloat(strip(insert_columnvalue_vectors[j][l][m]))) {
              continue;
            }
            // postprocesslog
            //     << "Tar1get Value: " << insert_columnvalue_vectors[j][l][m]
            //     << std::endl;
            // // log lnm
            // postprocesslog << "l: " << l << std::endl;
            // postprocesslog << "m: " << m << std::endl;
            std::vector<std::size_t> value_pos;
            std::string value_block = queries[insert_pos_vector[j]];
            size_t value_start =
                value_block.find('(', value_block.find("VALUE"));
            for (size_t o = 0; o < l; o++) {
              value_start = value_block.find('(', value_start + 1);
            }
            // postprocesslog << "value_start: " << value_start << std::endl;
            size_t value_end =
                findOppositeParentheses(value_block, value_start);
            std::string valuesblock = value_block.substr(
                value_start + 1, value_end - value_start - 1);
            // postprocesslog << "valuesblock: " << valuesblock << std::endl;
            // seprate comma and save pos
            value_pos.push_back(0);
            for (size_t o = 1; o < valuesblock.size(); o++) {
              if (valuesblock[o] == ',') {
                // remove space
                while (valuesblock[o + 1] == ' ') {
                  o++;
                }
                value_pos.push_back(o);
                // postprocesslog << "value_pos: " << o << std::endl;
              }
            }
            // postprocesslog << "compare size: " << value_pos.size() << " "
            //                << insert_columnvalue_vectors[j][l].size()
            //                << std::endl;

            if (value_pos.size() != insert_columnvalue_vectors[j][l].size()) {
              continue;
            }
            // replace to int with pos
            std::string original_query = queries[insert_pos_vector[j]];
            queries[insert_pos_vector[j]] =
                queries[insert_pos_vector[j]].replace(
                    value_start + value_pos[m] + 1,
                    insert_columnvalue_vectors[j][l][m].size(),
                    roundFromFloat(insert_columnvalue_vectors[j][l][m]));
            // postprocesslog << "original_query: " << original_query
            //                << std::endl;
            // postprocesslog << "replace: " << queries[insert_pos_vector[j]]
            //                << std::endl;
            tg.adapted_queries[Target::SQLite]
                .replace(tg.adapted_queries[Target::SQLite].find(original_query),
                         original_query.size(),
                         queries[insert_pos_vector[j]]);
          }

          // postprocesslog << "======" << std::endl;
          // postprocesslog << "Final query: "
          //                << plan->query_infos.at(Target::SQLite).queries[i]
          //                << std::endl;
        }
      }
    }

    else {
      for (size_t k = 0; k < create_tablename_vector.size(); k++) {
        // postprocesslog << "Comparing " << create_tablename_vector[k]
        //                << " and " << insert_tablename_vector[j] <<
        //                std::endl;
        if (strip(create_tablename_vector[k]) !=
                strip(insert_tablename_vector[j]) ||
            create_pos_vector[k] > insert_pos_vector[j]) {
          continue;
        }
        for (size_t l = 0; l < insert_columnname_vectors[j].size(); l++) {
          for (size_t m = 0; m < create_columnname_vectors[k].size(); m++) {
            // postprocesslog
            //     << "Comparing Column: " << insert_columnname_vectors[j][l]
            //     << " and " << create_columnname_vectors[k][m].first << " "
            //     << create_columnname_vectors[k][m].second << std::endl;
            if (strip(insert_columnname_vectors[j][l]) !=
                strip(create_columnname_vectors[k][m].first)) {
              continue;
            }
            if (create_columnname_vectors[k][m].second.find("INT") ==
                std::string::npos) {
              continue;
            }
            for (size_t n = 0; n < insert_columnvalue_vectors[j].size();
                  n++) {
              if (insert_columnvalue_vectors[j][n].size() !=
                  insert_columnname_vectors[j].size()) {
                continue;
              }
              if (isInt(strip(insert_columnvalue_vectors[j][n][l])) ||
                  !isFloat(strip(insert_columnvalue_vectors[j][n][l]))) {
                continue;
              }
              // postprocesslog
              //     << "Target Value: " <<
              //     insert_columnvalue_vectors[j][n][l]
              //     << std::endl;
              std::vector<std::size_t> value_pos;
              std::string value_block = queries[insert_pos_vector[j]];
              size_t value_start =
                  value_block.find('(', value_block.find("VALUE"));
              for (size_t o = 0; o < n + 1; o++) {
                value_start = value_block.find('(', value_start + 1);
              }
              // postprocesslog << "value_start: " << value_start <<
              // std::endl;
              size_t value_end =
                  findOppositeParentheses(value_block, value_start);
              std::string valuesblock = value_block.substr(
                  value_start + 1, value_end - value_start - 1);
              // postprocesslog << "valuesblock: " << valuesblock <<
              // std::endl; seprate comma and save pos
              value_pos.push_back(0);
              for (size_t o = 1; o < valuesblock.size(); o++) {
                if (valuesblock[o] == ',') {
                  // remove space
                  while (valuesblock[o + 1] == ' ') {
                    o++;
                  }
                  value_pos.push_back(o);
                  // postprocesslog << "value_pos: " << o << std::endl;
                }
              }
              // postprocesslog << "compare size: " << value_pos.size() << " "
              //                << insert_columnvalue_vectors[j][n].size()
              //                << std::endl;
              if (value_pos.size() !=
                  insert_columnvalue_vectors[j][n].size()) {
                continue;
              }
              // replace to int with pos
              std::string original_query = queries[insert_pos_vector[j]];
              queries[insert_pos_vector[j]] =
                  queries[insert_pos_vector[j]].replace(
                      value_start + value_pos[l] + 1,
                      insert_columnvalue_vectors[j][n][l].size(),
                      roundFromFloat(insert_columnvalue_vectors[j][n][l]));
              //postprocesslog << "original_query: " << original_query
                              //<< std::endl;
              //postprocesslog << "replace: " << queries[insert_pos_vector[j]]
                              //<< std::endl;
              tg.adapted_queries[Target::SQLite]
                  .replace(tg.adapted_queries[Target::SQLite].find(original_query),
                           original_query.size(),
                           queries[insert_pos_vector[j]]);
            }
            // postprocesslog << "======" << std::endl;
            // postprocesslog << "Final query: "
            //                <<
            //                plan->query_infos.at(Target::SQLite).queries[i]
            //                << std::endl;
          }
        }
      }
    }
  }
}

/*
 * postprocess()
 *
 * Post-processing on each adapted query, including:
 *   - Add type-2 diff test scneario
 */

// Function to add various SQLite PRAGMA commands to the query
void sqliteAddPragmaCommands(std::string& query) {
  std::string new_query;

  if (PROB_MEDIUM()) {
    // Auto vacuum modes: NONE (0), FULL (1), INCREMENTAL (2)
    int auto_vacuum_modes[] = {0, 1, 2};
    int selected_vacuum_mode = auto_vacuum_modes[rand() % 3];
    std::string vacuum_mode = (selected_vacuum_mode == 0)   ? "NONE"
                              : (selected_vacuum_mode == 1) ? "FULL"
                                                            : "INCREMENTAL";
    new_query += "PRAGMA auto_vacuum = " + vacuum_mode + "; ";
  }

  if (PROB_MEDIUM()) {
    bool enable_automatic_index = rand() % 2 == 0;
    new_query += "PRAGMA automatic_index = " +
                 std::string(enable_automatic_index ? "true" : "false") + "; ";
  }

  if (PROB_MEDIUM()) {
    // Random cache size between -500 and 500
    int cache_size = (rand() % 1000) - 500;
    new_query += "PRAGMA cache_size = " + std::to_string(cache_size) + "; ";
  }

  if (PROB_MEDIUM()) {
    if (rand() % 2 == 0) {
      bool cache_spill_enabled = rand() % 2 == 0;
      new_query += "PRAGMA cache_spill = " +
                   std::string(cache_spill_enabled ? "true" : "false") + "; ";
    } else {
      int spill_size = rand() % 1000 + 100;
      new_query += "PRAGMA cache_spill = " + std::to_string(spill_size) + "; ";
    }
  }

  if (PROB_MEDIUM()) {
    bool cell_size_check = rand() % 2 == 0;
    new_query += "PRAGMA cell_size_check = " +
                 std::string(cell_size_check ? "true" : "false") + "; ";
  }

  if (PROB_MEDIUM()) {
    int default_cache_size = rand() % 1000 + 1;
    new_query +=
        "PRAGMA default_cache_size = " + std::to_string(default_cache_size) +
        "; ";
  }

  if (PROB_MEDIUM()) {
    int encoding_choice = rand() % 4;
    std::string encoding = (encoding_choice == 0)   ? "'UTF-8'"
                           : (encoding_choice == 1) ? "'UTF-16'"
                           : (encoding_choice == 2) ? "'UTF-16le'"
                                                    : "'UTF-16be'";
    new_query += "PRAGMA encoding = " + encoding + "; ";
  }

  if (PROB_MEDIUM()) {
    int page_size = (1 << (rand() % 7 + 9));
    new_query += "PRAGMA page_size = " + std::to_string(page_size) + "; ";
  }

  if (PROB_MEDIUM()) {
    bool read_uncommitted = rand() % 2 == 0;
    new_query += "PRAGMA read_uncommitted = " +
                 std::string(read_uncommitted ? "true" : "false") + "; ";
  }

  if (PROB_MEDIUM()) {
    int schema_version = rand() % 10000;
    new_query +=
        "PRAGMA schema_version = " + std::to_string(schema_version) + "; ";
  }

  if (PROB_MEDIUM()) {
    int synchronous_modes[] = {0, 1, 2, 3};
    int selected_synchronous_mode = synchronous_modes[rand() % 4];
    std::string mode_string = (selected_synchronous_mode == 0)
                                  ? "OFF"
                                  : std::to_string(selected_synchronous_mode);
    new_query += "PRAGMA synchronous = " + mode_string + "; ";
  }

  if (PROB_MEDIUM()) {
    int temp_store_modes[] = {0, 1, 2};
    int selected_temp_store_mode = temp_store_modes[rand() % 3];
    std::string mode_string = (selected_temp_store_mode == 0)   ? "DEFAULT"
                              : (selected_temp_store_mode == 1) ? "FILE"
                                                                : "MEMORY";
    new_query += "PRAGMA temp_store = " + mode_string + "; ";
  }

  if (PROB_MEDIUM()) {
    new_query += "PRAGMA optimize; ";
  }

  if (!new_query.empty()) {
    query = new_query + query;
  }
}

void sqliteProcessWithoutRowId(std::string& statement) {
  size_t create_table_pos = statement.find("CREATE TABLE");
  if (create_table_pos != std::string::npos) {
    size_t pk_pos = statement.find("PRIMARY KEY", create_table_pos);
    if (pk_pos != std::string::npos &&
        statement.find("WITHOUT ROWID") == std::string::npos) {
      // Add WITHOUT ROWID with a 30% chance if PRIMARY KEY is present
      if (PROB_MEDIUM()) {
        statement += " WITHOUT ROWID";
      }
    }
  }
}

void sqliteProcessAscDescColumns(std::string& statement,
                                 std::string& first_column_name) {
  size_t open_paren_pos = statement.find("(");
  size_t close_paren_pos = statement.find(")", open_paren_pos);

  if (open_paren_pos != std::string::npos &&
      close_paren_pos != std::string::npos) {
    std::string columns_part = statement.substr(
        open_paren_pos + 1, close_paren_pos - open_paren_pos - 1);
    std::stringstream columns_ss(columns_part);
    std::string column;
    std::string modified_columns;
    bool is_first_column = true;

    while (std::getline(columns_ss, column, ',')) {
      column.erase(0, column.find_first_not_of(" \t\n\r"));
      column.erase(column.find_last_not_of(" \t\n\r") + 1);

      if (is_first_column) {
        first_column_name = column.substr(0, column.find(" "));
        is_first_column = false;
      }

      // 50% chance to add ASC or DESC
      if (PROB_MEDIUM()) {
        std::string order = (rand() % 2 == 0) ? " ASC" : " DESC";
        column += order;
      }

      modified_columns += column + ", ";
    }

    if (!modified_columns.empty()) {
      modified_columns.erase(modified_columns.size() - 2);
    }

    statement = statement.substr(0, open_paren_pos + 1) + modified_columns +
                statement.substr(close_paren_pos);
  }
}

void sqliteProcessPartialIndex(std::string& statement,
                               const std::string& first_column_name) {
  if (first_column_name.empty() || rand() % 100 >= 30) return;

  std::string where_condition;
  std::vector<std::string> conditions;
  std::string random_value;
  int random_choice = rand() % 3;

  if (random_choice == 0) {
    random_value = "NULL";
  } else if (random_choice == 1) {
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < 4; ++i) {
      random_value += characters[rand() % characters.size()];
    }
    random_value = "'" + random_value + "'";
  } else {
    random_value = std::to_string(1 + rand() % 10000);
  }

  conditions.push_back(" IS " + random_value);
  conditions.push_back(" IS NOT " + random_value);
  conditions.push_back(" <> " + random_value);
  conditions.push_back(" = " + random_value);
  conditions.push_back(" < " + random_value);
  conditions.push_back(" > " + random_value);
  conditions.push_back(" <= " + random_value);
  conditions.push_back(" >= " + random_value);

  where_condition =
      " WHERE " + first_column_name + conditions[rand() % conditions.size()];

  statement += where_condition;
}

// void sqliteAddVacuumCommand(std::string& statement) {
//   std::string vacuum_command =
//       "VACUUM " + std::string((rand() % 2 == 0) ? "main" : "temp") +
//       " INTO '/tmp/sqlite_vacuum_file.db';";
//   statement += vacuum_command + " ";
// }

// void sqliteCleanUpVacuumFile() {
//   std::remove("/tmp/sqlite_vacuum_file.db");
//   //if (std::remove("/tmp/sqlite_vacuum_file.db") != 0) {
//     //std::cerr << "Warning: Failed to delete /tmp/sqlite_vacuum_file.db."
//               //<< std::endl;
//   //}
// }

void sqliteAddMaterializedToCTE(std::string& statement) {
  // Define keywords to check
  const std::string cte_with = "WITH";
  const std::string cte_recursive = "RECURSIVE";
  const std::string cte_as = "AS";

  size_t with_pos = statement.find(cte_with);
  if (with_pos != std::string::npos) {
    // Check if the statement is a CTE definition
    size_t as_pos = statement.find(cte_as, with_pos + cte_with.size());
    size_t paren_pos = statement.find("(", as_pos + cte_as.size());

    if (as_pos != std::string::npos && paren_pos != std::string::npos) {
      // Extract the portion before the opening parenthesis
      std::string prefix = statement.substr(0, as_pos + cte_as.size());

      // Determine if RECURSIVE exists
      bool has_recursive =
          (statement.find(cte_recursive, with_pos) != std::string::npos);

      // Randomly decide whether to add MATERIALIZED or NOT MATERIALIZED
      if (PROB_MEDIUM()) {
        std::string materialized_option =
            (rand() % 2 == 0) ? " MATERIALIZED" : " NOT MATERIALIZED";

        // Update the prefix with MATERIALIZED or NOT MATERIALIZED
        prefix += materialized_option;
      }

      // Rebuild the statement with the prefix and the remaining part
      statement = prefix + " " + statement.substr(as_pos + cte_as.size());
    }
  }
}

void processSQLite(std::string& query) {
  srand(time(NULL));  // Initialize the random seed

  // sqliteAddPragmaCommands(query);

  std::stringstream ss(query);
  std::string statement;
  std::string new_query;
  // Process each SQL statement (e.g., CREATE TABLE, INSERT, CREATE INDEX)
  while (std::getline(ss, statement, ';')) {
    // Trim leading and trailing whitespace
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);

    if (statement.empty()) continue;

    // if (PROB_MEDIUM()) {  // 30% chance to add VACUUM
    //   sqliteAddVacuumCommand(statement);
    // }

    // // Add MATERIALIZED or NOT MATERIALIZED to CTE statements
    // sqliteAddMaterializedToCTE(statement);

    // // Process CREATE TABLE statements for WITHOUT ROWID
    // sqliteProcessWithoutRowId(statement);

    // // Process CREATE INDEX statements
    // if (statement.find("CREATE INDEX") != std::string::npos &&
    //     statement.find("UNIQUE") == std::string::npos) {
    //   std::string first_column_name;
    //   sqliteProcessAscDescColumns(statement, first_column_name);
    //   sqliteProcessPartialIndex(statement, first_column_name);
    // }

    // Rebuild the query with modified statements
    if (!statement.empty()) {
      new_query += statement + "; ";
    }
  }

  query = new_query;

  // Clean up generated file after query execution
  // sqliteCleanUpVacuumFile();
}

// MySQL
void mysqlIdentifyCharTypeColumns(
    const std::string& query,
    std::vector<std::pair<std::string, int>>& char_type_columns) {
  std::stringstream ss(query);
  std::string statement;

  while (std::getline(ss, statement, ';')) {
    // Trim leading/trailing spaces
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);

    // Check for CREATE TABLE statement
    size_t create_table_pos = statement.find("CREATE TABLE");
    if (create_table_pos != std::string::npos) {
      size_t column_pos = statement.find("(");
      if (column_pos != std::string::npos) {
        std::stringstream columns_ss(statement.substr(column_pos + 1));
        std::string column_def;

        // Process each column definition individually
        while (std::getline(columns_ss, column_def, ',')) {
          column_def.erase(0, column_def.find_first_not_of(" \t\n\r"));
          column_def.erase(column_def.find_last_not_of(" \t\n\r") + 1);

          // Identify CHAR, VARCHAR, BINARY, VARBINARY types and size
          size_t type_pos = std::string::npos;
          if ((type_pos = column_def.find("CHAR")) != std::string::npos ||
              (type_pos = column_def.find("VARCHAR")) != std::string::npos ||
              (type_pos = column_def.find("BINARY")) != std::string::npos ||
              (type_pos = column_def.find("VARBINARY")) != std::string::npos) {
            // Extract column name and size
            size_t space_pos = column_def.find(" ");
            std::string column_name = column_def.substr(0, space_pos);
            int size = 0;

            // Extract size if specified
            size_t size_start = column_def.find("(", type_pos);
            if (size_start != std::string::npos) {
              size_t size_end = column_def.find(")", size_start);
              if (size_end != std::string::npos) {
                try {
                  size = std::stoi(column_def.substr(
                      size_start + 1, size_end - size_start - 1));
                } catch (const std::invalid_argument& e) {
                  // Handle case where the size is not a valid number
                  size = 0;  // Default value
                  //std::cerr << "Error: Invalid size in column definition: "
                            //<< column_def << " (" << e.what() << ")\n";
                } catch (const std::out_of_range& e) {
                  // Handle case where the size is out of range
                  size = 0;  // Default value
                  //std::cerr << "Error: Size out of range in column definition: "
                            //<< column_def << " (" << e.what() << ")\n";
                }
              }
            }

            // Store column name and size
            char_type_columns.emplace_back(column_name, size);
          }
        }
      }
    }
  }
}

void mysqlAddSizeToIndexColumns(
    std::string& statement,
    const std::vector<std::pair<std::string, int>>& char_type_columns) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (create_index_pos != std::string::npos && !char_type_columns.empty()) {
    for (const auto& [column_name, max_size] : char_type_columns) {
      size_t column_pos = statement.find(column_name, create_index_pos);
      if (column_pos != std::string::npos && max_size > 1) {
        int size = 1 + rand() % (max_size - 1);

        // Add size
        statement.insert(column_pos + column_name.length(),
                         "(" + std::to_string(size) + ")");
        break;
      }
    }
  }
}

void mysqlAddOrderToIndexColumns(std::string& statement, bool& add_order) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (create_index_pos != std::string::npos && !add_order) {
    if (PROB_HIGH()) {
      std::string order = (rand() % 2 == 0) ? " ASC" : " DESC";
      size_t open_paren_pos = statement.find("(", create_index_pos);
      size_t size_end_pos = statement.find(")", open_paren_pos);
      if (size_end_pos != std::string::npos) {
        statement.insert(size_end_pos, order);
        add_order = true;
      }
    }
  }
}

void mysqlAddUsingClauseToIndex(std::string& statement, const bool& add_order) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (create_index_pos != std::string::npos &&
      statement.find("UNIQUE", create_index_pos) == std::string::npos) {
    if (PROB_HIGH()) {
      size_t on_pos = statement.find(" ON ", create_index_pos);
      if (on_pos != std::string::npos) {
        std::string using_clause =
            (!add_order && rand() % 2 == 0) ? " USING HASH" : " USING BTREE";
        statement.insert(on_pos, using_clause);
      }
    }

    if (PROB_HIGH()) {
      size_t end_pos = statement.find_last_of(")");
      if (end_pos != std::string::npos) {
        std::string using_clause_at_end =
            (!add_order && rand() % 2 == 0) ? " USING HASH" : " USING BTREE";
        if (statement.find(using_clause_at_end, end_pos) == std::string::npos) {
          statement += using_clause_at_end;
        }
      }
    }
  }
}

void mysqlAddInvisibleToIndex(std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (create_index_pos != std::string::npos &&
      statement.find("UNIQUE", create_index_pos) == std::string::npos) {
    if (PROB_HIGH() && statement.find("INVISIBLE") == std::string::npos) {
      statement += " INVISIBLE";
    }
  }
}

void mysqlAddInvisibleToAlterIndex(std::string& statement) {
  size_t alter_index_pos = statement.find("ALTER INDEX");
  if (alter_index_pos != std::string::npos) {
    if (PROB_MEDIUM() && statement.find("INVISIBLE") == std::string::npos) {
      statement += " INVISIBLE";
    }
  }
}

void mysqlIdentifyForeignKeyAndTextBlob(const std::string& query,
                                        bool& has_foreign_key,
                                        bool& has_text_or_blob_or_json) {
  has_foreign_key = query.find("FOREIGN KEY") != std::string::npos;
  has_text_or_blob_or_json = query.find("TEXT") != std::string::npos ||
                             query.find("BLOB") != std::string::npos ||
                             query.find("JSON") != std::string::npos;
}

void mysqlAddEngineAndRowFormat(std::string& statement, bool has_foreign_key,
                                bool has_text_or_blob_or_json) {
  if (statement.find("CREATE TABLE") != std::string::npos) {
    std::string engine_clause;
    std::string row_format_clause;
    std::string key_block_size_clause;

    if (has_foreign_key) {
      if (PROB_MEDIUM()) {
        engine_clause = "ENGINE=INNODB";

        // Define possible ROW_FORMAT options for InnoDB
        std::vector<std::string> innodb_formats = {
            "DEFAULT", "REDUNDANT", "COMPACT", "DYNAMIC", "COMPRESSED"};

        // Select a random ROW_FORMAT option
        row_format_clause =
            "ROW_FORMAT=" + innodb_formats[rand() % innodb_formats.size()];

        // Check if ROW_FORMAT is DEFAULT or COMPRESSED, and add KEY_BLOCK_SIZE
        // with a 30% chance
        if (row_format_clause == "ROW_FORMAT=DEFAULT" ||
            row_format_clause == "ROW_FORMAT=COMPRESSED") {
          // 30% probability for KEY_BLOCK_SIZE addition
          if (PROB_MEDIUM()) {
            std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
            int key_block_size =
                key_block_sizes[rand() % key_block_sizes.size()];
            key_block_size_clause =
                "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
          }
        }
      }
    } else {
      if (has_text_or_blob_or_json) {
        if (PROB_MEDIUM()) {
          // Set ENGINE to either INNODB or MYISAM
          engine_clause = (rand() % 2 == 0) ? "ENGINE=INNODB" : "ENGINE=MYISAM";

          if (engine_clause == "ENGINE=INNODB") {
            // InnoDB ROW_FORMAT options
            std::vector<std::string> innodb_formats = {
                "DEFAULT", "REDUNDANT", "COMPACT", "DYNAMIC", "COMPRESSED"};
            row_format_clause =
                "ROW_FORMAT=" + innodb_formats[rand() % innodb_formats.size()];

            // Check if ROW_FORMAT is DEFAULT or COMPRESSED, and add
            // KEY_BLOCK_SIZE with a 30% chance
            if (row_format_clause == "ROW_FORMAT=DEFAULT" ||
                row_format_clause == "ROW_FORMAT=COMPRESSED") {
              // 30% probability for KEY_BLOCK_SIZE addition
              if (PROB_MEDIUM()) {
                std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
                int key_block_size =
                    key_block_sizes[rand() % key_block_sizes.size()];
                key_block_size_clause =
                    "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
              }
            }
          } else {
            // MYISAM ROW_FORMAT options
            std::vector<std::string> myisam_formats = {"DEFAULT", "FIXED",
                                                       "DYNAMIC"};
            row_format_clause =
                "ROW_FORMAT=" + myisam_formats[rand() % myisam_formats.size()];

            // For MYISAM, add KEY_BLOCK_SIZE with a 30% probability regardless
            // of ROW_FORMAT
            // 30% probability for KEY_BLOCK_SIZE addition
            if (PROB_MEDIUM()) {
              std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
              int key_block_size =
                  key_block_sizes[rand() % key_block_sizes.size()];
              key_block_size_clause =
                  "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
            }
          }
        }
      } else {
        if (PROB_MEDIUM()) {
          std::string engines[] = {"ENGINE=INNODB", "ENGINE=MYISAM",
                                   "ENGINE=MEMORY"};
          engine_clause = engines[rand() % 3];

          if (engine_clause == "ENGINE=INNODB") {
            // InnoDB ROW_FORMAT options
            std::vector<std::string> innodb_formats = {
                "DEFAULT", "REDUNDANT", "COMPACT", "DYNAMIC", "COMPRESSED"};
            row_format_clause =
                "ROW_FORMAT=" + innodb_formats[rand() % innodb_formats.size()];

            // Check if ROW_FORMAT is DEFAULT or COMPRESSED, and add
            // KEY_BLOCK_SIZE with a 30% chance
            if (row_format_clause == "ROW_FORMAT=DEFAULT" ||
                row_format_clause == "ROW_FORMAT=COMPRESSED") {
              // 30% probability for KEY_BLOCK_SIZE addition
              if (PROB_MEDIUM()) {
                std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
                int key_block_size =
                    key_block_sizes[rand() % key_block_sizes.size()];
                key_block_size_clause =
                    "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
              }
            }
          } else if (engine_clause == "ENGINE=MYISAM") {
            // MyISAM ROW_FORMAT options
            std::vector<std::string> myisam_formats = {"DEFAULT", "FIXED",
                                                       "DYNAMIC"};
            row_format_clause =
                "ROW_FORMAT=" + myisam_formats[rand() % myisam_formats.size()];

            // For MYISAM, add KEY_BLOCK_SIZE with a 30% probability regardless
            // of ROW_FORMAT
            // 30% probability for KEY_BLOCK_SIZE addition
            if (PROB_MEDIUM()) {
              std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
              int key_block_size =
                  key_block_sizes[rand() % key_block_sizes.size()];
              key_block_size_clause =
                  "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
            }
          } else if (engine_clause == "ENGINE=MEMORY") {
            // MEMORY ROW_FORMAT options
            std::vector<std::string> memory_formats = {"DEFAULT", "REDUNDANT",
                                                       "COMPACT", "FIXED",
                                                       "DYNAMIC", "COMPRESSED"};
            row_format_clause =
                "ROW_FORMAT=" + memory_formats[rand() % memory_formats.size()];

            // For MEMORY, add KEY_BLOCK_SIZE with a 30% probability regardless
            // of ROW_FORMAT
            // 30% probability for KEY_BLOCK_SIZE addition
            if (PROB_MEDIUM()) {
              std::vector<int> key_block_sizes = {1, 2, 4, 8, 16};
              int key_block_size =
                  key_block_sizes[rand() % key_block_sizes.size()];
              key_block_size_clause =
                  "KEY_BLOCK_SIZE=" + std::to_string(key_block_size);
            }
          }
        }
      }
    }

    if (!engine_clause.empty()) {
      statement += " " + engine_clause;
    }
    if (!row_format_clause.empty()) {
      statement += " " + row_format_clause;
    }
    if (!key_block_size_clause.empty()) {
      statement += " " + key_block_size_clause;
    }
  }
}

// Function to extract table name from a CREATE TABLE statement
void mysqlExtractTableName(const std::string& statement, std::string& table_name) {
  size_t table_name_start =
      statement.find("CREATE TABLE") + std::string("CREATE TABLE").length();
  size_t table_name_end = statement.find("(", table_name_start);

  if (table_name_start != std::string::npos &&
      table_name_end != std::string::npos) {
    // Extract the substring containing the table name
    table_name =
        statement.substr(table_name_start, table_name_end - table_name_start);

    // Trim any leading or trailing whitespace from the table name
    table_name.erase(0, table_name.find_first_not_of(" \t\n\r"));
    table_name.erase(table_name.find_last_not_of(" \t\n\r") + 1);
  } else {
    table_name.clear();  // Clear table_name if extraction fails
  }
}

// Function to add OPTIMIZE TABLE command after CREATE TABLE if oracle_plan
// contains only ORACLE_SKIP
void mysqlAddOptimizeTableIfOracleSkip(std::string& query,
                                       const std::string& table_name) {
  // Check if oracle_plan only contains ORACLE_SKIP
  // if (oracle_plan.size() == 1 && oracle_plan[0] == ORACLE_SKIP) {
  if (false) {
    std::string optimize_command =
        "OPTIMIZE NO_WRITE_TO_BINLOG TABLE " + table_name + "; ";
    query += optimize_command;
  }
}

// Function to add ALGORITHM and LOCK clauses to CREATE INDEX statement
void mysqlAddAlgorithmAndLockToIndex(std::string& statement) {
  // Check if the statement is a CREATE INDEX statement
  if (statement.find("CREATE INDEX") == std::string::npos) return;

  // Decide whether to add ALGORITHM and LOCK clauses (30% probability for each)
  bool add_algorithm = PROB_MEDIUM();
  bool add_lock = PROB_MEDIUM();

  std::string algorithm_clause;
  std::string lock_clause;

  // Randomly select an ALGORITHM option
  if (add_algorithm) {
    switch (rand() % 3) {
      case 0:
        algorithm_clause = "ALGORITHM = DEFAULT";
        break;
      case 1:
        algorithm_clause = "ALGORITHM = INPLACE";
        break;
      case 2:
        algorithm_clause = "ALGORITHM = COPY";
        break;
    }
  }

  // Randomly select a LOCK option
  if (add_lock) {
    switch (rand() % 4) {
      case 0:
        lock_clause = "LOCK = DEFAULT";
        break;
      case 1:
        lock_clause = "LOCK = NONE";
        break;
      case 2:
        lock_clause = "LOCK = SHARED";
        break;
      case 3:
        lock_clause = "LOCK = EXCLUSIVE";
        break;
    }
  }

  // Ensure that ALGORITHM = COPY and LOCK = NONE do not appear together
  if (algorithm_clause == "ALGORITHM = COPY" && lock_clause == "LOCK = NONE") {
    lock_clause.clear();  // Remove LOCK clause to avoid conflict
  }

  // Append the clauses to the CREATE INDEX statement
  if (!algorithm_clause.empty()) {
    statement += " " + algorithm_clause;
  }
  if (!lock_clause.empty()) {
    statement += " " + lock_clause;
  }
}

// Function to add multiple ALTER TABLE statements at random positions after
// CREATE TABLE statement
void mysqlAddRandomAlterTableStatements(std::string& new_query,
                                        const std::string& table_name) {
  // List of possible ALTER TABLE statements
  std::vector<std::string> alter_statements = {
      "ALTER TABLE " + table_name + " ALGORITHM=DEFAULT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=INSTANT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=INPLACE; ",
      "ALTER TABLE " + table_name + " ALGORITHM=COPY; ",
      "ALTER TABLE " + table_name + " LOCK=DEFAULT; ",
      "ALTER TABLE " + table_name + " LOCK=EXCLUSIVE; ",
      "ALTER TABLE " + table_name + " ALGORITHM=DEFAULT, LOCK=DEFAULT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=DEFAULT, LOCK=EXCLUSIVE; ",
      "ALTER TABLE " + table_name + " ALGORITHM=INSTANT, LOCK=DEFAULT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=INPLACE, LOCK=DEFAULT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=INPLACE, LOCK=EXCLUSIVE; ",
      "ALTER TABLE " + table_name + " ALGORITHM=COPY, LOCK=DEFAULT; ",
      "ALTER TABLE " + table_name + " ALGORITHM=COPY, LOCK=SHARED; ",
      "ALTER TABLE " + table_name + " ALGORITHM=COPY, LOCK=EXCLUSIVE; "};

  // Randomly insert multiple ALTER TABLE statements (20% probability for each
  // statement)
  for (const auto& alter_stmt : alter_statements) {
    if (PROB_LOW()) {
      // Append each ALTER TABLE statement to new_query
      new_query += alter_stmt;
    }
  }
}

// Function to add COMPRESSION option to CREATE TABLE statement (zlib or lz4)
void mysqlAddCompressionToCreateTable(std::string& statement) {
  // Check if statement is a CREATE TABLE (not TEMPORARY) statement
  if (statement.find("CREATE TABLE") != std::string::npos &&
      statement.find("TEMPORARY") == std::string::npos && PROB_MEDIUM()) {
    // Randomly choose between "zlib" and "lz4" for COMPRESSION
    std::string compression_option =
        (rand() % 2 == 0) ? "COMPRESSION = \"zlib\"" : "COMPRESSION = \"lz4\"";
    statement += " " + compression_option;
  }
}

// Function to add ALTER TABLE statements with COMPRESSION and OPTIMIZE TABLE
// options
void mysqlAddCompressionAndOptimizeAlterTable(std::string& new_query,
                                              const std::string& table_name) {
  // Possible compression options for ALTER TABLE
  std::vector<std::string> compression_options = {
      "ALTER TABLE " + table_name + " COMPRESSION = \"zlib\"; ",
      "ALTER TABLE " + table_name + " COMPRESSION = \"lz4\"; ",
      "ALTER TABLE " + table_name + " COMPRESSION = \"None\"; "};

  // Randomly insert one or more ALTER TABLE statements with COMPRESSION
  bool first_alter_added = false;
  for (const auto& alter_stmt : compression_options) {
    // Ensure at least one ALTER TABLE COMPRESSION statement is added
    if (!first_alter_added &&
        PROB_MEDIUM()) {  // 30% probability for additional options
      new_query += " " + alter_stmt;
      first_alter_added = true;
    }
  }
}

// Function to extract index name from CREATE INDEX statement
std::string mysqlExtractIndexName(const std::string& statement,
                                  size_t create_index_pos) {
  size_t idx_name_start = statement.find(
      " ", create_index_pos + std::string("CREATE INDEX").length());
  size_t idx_name_end = statement.find(" ON ", idx_name_start);
  std::string index_name =
      statement.substr(idx_name_start, idx_name_end - idx_name_start);
  index_name.erase(0, index_name.find_first_not_of(" \t\n\r"));
  index_name.erase(index_name.find_last_not_of(" \t\n\r") + 1);
  return index_name;
}

// Function to generate random hints
std::string generateRandomHint(
    const std::vector<std::string>& table_names,
    const std::map<std::string, std::vector<std::string>>& index_names) {
  std::vector<std::string> hints;

  // 1. Table-specific hints (0+ table names)
  if (!table_names.empty()) {
    if (PROB_MEDIUM())
      hints.push_back("BKA(" + table_names[rand() % table_names.size()] + ")");
    if (PROB_MEDIUM())
      hints.push_back("NO_BKA(" + table_names[rand() % table_names.size()] +
                      ")");
    if (PROB_MEDIUM())
      hints.push_back("DERIVED_CONDITION_PUSHDOWN(" +
                      table_names[rand() % table_names.size()] + ")");
    if (PROB_MEDIUM())
      hints.push_back("NO_DERIVED_CONDITION_PUSHDOWN(" +
                      table_names[rand() % table_names.size()] + ")");
    if (PROB_MEDIUM())
      hints.push_back("MERGE(" + table_names[rand() % table_names.size()] +
                      ")");
    if (PROB_MEDIUM())
      hints.push_back("NO_MERGE(" + table_names[rand() % table_names.size()] +
                      ")");
  }

  // 2. Hints requiring one or more table names (1+ table names)
  if (table_names.size() > 1) {
    if (PROB_MEDIUM())
      hints.push_back("JOIN_ORDER(" + table_names[rand() % table_names.size()] +
                      ")");
    if (PROB_MEDIUM())
      hints.push_back("JOIN_PREFIX(" +
                      table_names[rand() % table_names.size()] + ")");
    if (PROB_MEDIUM())
      hints.push_back("JOIN_SUFFIX(" +
                      table_names[rand() % table_names.size()] + ")");
  }

  // 3. Hints with no arguments
  if (PROB_MEDIUM()) hints.push_back("BNL()");
  if (PROB_MEDIUM()) hints.push_back("NO_BNL()");
  if (PROB_MEDIUM()) hints.push_back("HASH_JOIN()");
  if (PROB_MEDIUM()) hints.push_back("NO_HASH_JOIN()");
  if (PROB_MEDIUM()) hints.push_back("JOIN_FIXED_ORDER()");

  // 4. Hints with table and optional index names (1 table name & 0+ index names on that table)
  for (const auto& table : table_names) {
    if (index_names.count(table) > 0 && !index_names.at(table).empty()) {
      std::string index_hint;
      if (PROB_MEDIUM()) index_hint = "INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "GROUP_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_GROUP_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "JOIN_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_JOIN_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "ORDER_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_ORDER_INDEX(" + table;
      if (PROB_MEDIUM()) index_hint = "INDEX_MERGE(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_INDEX_MERGE(" + table;
      if (PROB_MEDIUM()) index_hint = "MRR(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_MRR(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_ICP(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_RANGE_OPTIMIZATION(" + table;
      if (PROB_MEDIUM()) index_hint = "SKIP_SCAN(" + table;
      if (PROB_MEDIUM()) index_hint = "NO_SKIP_SCAN(" + table;

      // Add random indexes to hint
      std::string indexes;
      for (const auto& index : index_names.at(table)) {
        if (PROB_MEDIUM()) indexes += index + ", ";
      }
      if (!indexes.empty()) {
        indexes.pop_back();  // Remove last comma
        indexes.pop_back();
        index_hint += " [" + indexes + "]";
      }
      index_hint += ")";
      hints.push_back(index_hint);
    }
  }

  // 5. Miscellaneous hints
  if (PROB_MEDIUM()) hints.push_back("SEMIJOIN()");
  if (PROB_MEDIUM()) hints.push_back("NO_SEMIJOIN()");

  // 6. Mandatory SUBQUERY hint (INTOEXISTS or MATERIALIZATION)
  std::string subquery_hint =
      (rand() % 2 == 0) ? "INTOEXISTS" : "MATERIALIZATION";
  hints.push_back("SUBQUERY(" + subquery_hint + ")");

  // Concatenate all hints into a hint clause
  std::string hint_clause = "/*+ ";
  for (const auto& hint : hints) {
    hint_clause += hint + " ";
  }
  hint_clause += "*/";
  return hint_clause;
}

// Function to extract index and table names from CREATE INDEX statements
void mysqlExtractIndexAndTableNames(
    const std::string& statement,
    std::map<std::string, std::vector<std::string>>& index_names,
    std::vector<std::string>& table_names) {
  if (statement.find("CREATE INDEX") != std::string::npos) {
    size_t create_index_pos = statement.find("CREATE INDEX");
    std::string index_name = mysqlExtractIndexName(statement, create_index_pos);
    std::string table_name;
    mysqlExtractTableName(statement, table_name);
    if (!index_name.empty() && !table_name.empty()) {
      index_names[table_name].push_back(index_name);
      if (std::find(table_names.begin(), table_names.end(), table_name) ==
          table_names.end()) {
        // Ensure unique table names in the vector
        table_names.push_back(table_name);
      }
    }
  }
}

// Function to add hints for SQL statements
void mysqlAddHintsToSQLStatement(
    std::string& statement, const std::vector<std::string>& table_names,
    const std::map<std::string, std::vector<std::string>>& index_names) {
  std::vector<std::string> query_types = {"SELECT", "INSERT", "UPDATE",
                                          "DELETE", "REPLACE"};
  for (const auto& query_type : query_types) {
    size_t pos = statement.find(query_type);
    if (pos != std::string::npos &&
        (pos == 0 || std::isspace(statement[pos - 1])) && (PROB_MEDIUM())) {
      std::string hint_clause = generateRandomHint(table_names, index_names);
      statement.insert(pos + query_type.length(), " " + hint_clause);
      break;
    }
  }
}

// Function to identify JSON columns in a CREATE TABLE statement
void mysqlIdentifyJSONColumns(const std::string& query,
                              std::vector<std::string>& json_columns) {
  std::stringstream ss(query);
  std::string statement;

  while (std::getline(ss, statement, ';')) {
    // Trim leading and trailing whitespace
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);

    // Check for CREATE TABLE statement
    size_t create_table_pos = statement.find("CREATE TABLE");
    if (create_table_pos != std::string::npos) {
      size_t column_pos = statement.find("(");
      if (column_pos != std::string::npos) {
        std::stringstream columns_ss(statement.substr(column_pos + 1));
        std::string column_def;

        // Process each column definition individually
        while (std::getline(columns_ss, column_def, ',')) {
          column_def.erase(0, column_def.find_first_not_of(" \t\n\r"));
          column_def.erase(column_def.find_last_not_of(" \t\n\r") + 1);

          // Check if the column type is JSON
          if (column_def.find("JSON") != std::string::npos) {
            // Extract column name
            size_t space_pos = column_def.find(" ");
            std::string column_name = column_def.substr(0, space_pos);

            // Store column name
            json_columns.push_back(column_name);
          }
        }
      }
    }
  }
}

// Helper function to generate random strings
std::string mysqlGenerateRandomString(size_t length) {
  const std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
  std::string random_string;
  for (size_t i = 0; i < length; ++i) {
    random_string += charset[rand() % charset.size()];
  }
  return random_string;
}

// Function to generate random table options
void mysqlAddTableOptions(std::string& statement) {
  if (statement.find("CREATE TABLE") != std::string::npos ||
      statement.find("CREATE TEMPORARY TABLE") != std::string::npos) {
    std::vector<std::string> table_options;
    if (PROB_MEDIUM()) {        // 30% chance to add AUTOEXTEND_SIZE
      int value = rand() % 10 + 1;  // Random value: 1 ~ 10
      table_options.push_back("AUTOEXTEND_SIZE=" + std::to_string(value * 4) +
                              "M");
    }

    if (PROB_MEDIUM()) {    // 30% chance to add AVG_ROW_LENGTH
      uint32_t value = rand();  // Random value: 0 ~ 4294967295
      table_options.push_back("AVG_ROW_LENGTH=" + std::to_string(value));
    }

    if (PROB_MEDIUM()) {   // 30% chance to add CHECKSUM
      int value = rand() % 2;  // Random value: 0 or 1
      table_options.push_back("CHECKSUM=" + std::to_string(value));
    }

    if (PROB_MEDIUM()) {  // 30% chance to add COMMENT
      std::string comment = mysqlGenerateRandomString(32);
      table_options.push_back("COMMENT='" + comment + "'");
    }

    if (PROB_MEDIUM()) {    // 30% chance to add MAX_ROWS
      uint32_t value = rand();  // Random value: 0 ~ 4294967295
      table_options.push_back("MAX_ROWS=" + std::to_string(value));
    }

    if (PROB_MEDIUM()) {    // 30% chance to add MIN_ROWS
      uint32_t value = rand();  // Random value: 0 ~ 4294967295
      table_options.push_back("MIN_ROWS=" + std::to_string(value));
    }

    if (PROB_MEDIUM()) {  // 30% chance to add PACK_KEYS
      std::vector<std::string> pack_keys = {"0", "1", "DEFAULT"};
      table_options.push_back("PACK_KEYS=" + pack_keys[rand() % 3]);
    }

    if (PROB_MEDIUM()) {  // 30% chance to add STATS_AUTO_RECALC
      std::vector<std::string> stats_auto_recalc = {"DEFAULT", "0", "1"};
      table_options.push_back("STATS_AUTO_RECALC=" +
                              stats_auto_recalc[rand() % 3]);
    }

    if (PROB_MEDIUM()) {  // 30% chance to add STATS_PERSISTENT
      std::vector<std::string> stats_persistent = {"DEFAULT", "0", "1"};
      table_options.push_back("STATS_PERSISTENT=" +
                              stats_persistent[rand() % 3]);
    }

    if (PROB_MEDIUM()) {  // 30% chance to add STATS_SAMPLE_PAGES
      uint32_t value = rand() % 65535 + 1;  // Random value: 1 ~ 65535
      table_options.push_back("STATS_SAMPLE_PAGES=" + std::to_string(value));
    }

    // Combine all options into the statement
    if (!table_options.empty()) {
      std::string options = table_options[0];
      for (size_t i = 1; i < table_options.size(); ++i) {
        options += (rand() % 2 == 0 ? ", " : " ") +
                   table_options[i];  // Randomly use ',' or ' ' as separators
      }

      // Add options to the CREATE TABLE statement
      size_t semicolon_pos = statement.find(';');
      if (semicolon_pos != std::string::npos) {
        statement.insert(semicolon_pos, " " + options);
      } else {
        statement += " " + options;
      }
    }
  }
}

void processMySQL(std::string& query) {
  srand(time(NULL));  // Initialize the random seed

  std::stringstream ss(query);
  std::string statement;
  std::string new_query;
  bool add_order = false;  // Flag for adding ASC or DESC

  // Store CHAR, VARCHAR, BINARY, VARBINARY column names and sizes
  std::vector<std::pair<std::string, int>> char_type_columns;

  // Identify CHAR, VARCHAR, BINARY, VARBINARY columns and their sizes
  mysqlIdentifyCharTypeColumns(query, char_type_columns);

  // Check for presence of FOREIGN KEY and TEXT/BLOB
  bool has_foreign_key = false;
  bool has_text_or_blob_or_json = false;
  std::vector<std::string> json_columns;
  mysqlIdentifyForeignKeyAndTextBlob(query, has_foreign_key,
                                      has_text_or_blob_or_json);

  mysqlIdentifyJSONColumns(query, json_columns);

  // std::vector<std::string> table_names;
  // std::map<std::string, std::vector<std::string>> index_names;

  // Process each statement in the query
  while (std::getline(ss, statement, ';')) {
    // Trim leading and trailing whitespace
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);
    if (statement.empty()) continue;

    // Identify CREATE TABLE statements
    if (statement.find("CREATE TABLE") != std::string::npos) {
      std::string table_name;
      mysqlExtractTableName(statement, table_name);  // Extract table name

      mysqlAddTableOptions(statement);

      // CREATE TABLE + COMPRESSION option
      mysqlAddCompressionToCreateTable(statement);
      mysqlAddEngineAndRowFormat(statement, has_foreign_key,
                                  has_text_or_blob_or_json);

      // Add CREATE TABLE statement to new_query first
      new_query += statement + "; ";

      // // Add OPTIMIZE TABLE if oracle_plan contains only ORACLE_SKIP
      // mysqlAddOptimizeTableIfOracleSkip(new_query, table_name);

      // // Add ALTER TABLE statements immediately after CREATE TABLE
      // mysqlAddRandomAlterTableStatements(new_query, table_name);

      // // Add COMPRESSION / OPTIMIZE ALTER TABLE statement
      // mysqlAddCompressionAndOptimizeAlterTable(new_query, table_name);

      // Skip further processing for this CREATE TABLE as it's already added
      // with OPTIMIZE
      continue;
    }

    // Omit CREATE INDEX or ALTER INDEX statements if JSON columns are present
    if (!json_columns.empty() &&
        (statement.find("CREATE INDEX") != std::string::npos ||
          statement.find("ALTER INDEX") != std::string::npos)) {
      continue;  // Skip indexing if there are JSON columns
    }

    // // Extract index and table names from CREATE INDEX statements
    // mysqlExtractIndexAndTableNames(statement, index_names, table_names);
    // // Add hints to SELECT, INSERT, UPDATE, DELETE, and REPLACE statements
    // mysqlAddHintsToSQLStatement(statement, table_names, index_names);
    // // Add other modifications, like size, order, etc., to other statements
    // mysqlAddSizeToIndexColumns(statement, char_type_columns);
    // mysqlAddOrderToIndexColumns(statement, add_order);
    // mysqlAddUsingClauseToIndex(statement, add_order);
    // mysqlAddInvisibleToIndex(statement);
    // mysqlAddInvisibleToAlterIndex(statement);
    // mysqlAddAlgorithmAndLockToIndex(statement);

    // Rebuild the query with modified statements
    if (!statement.empty()) {
      new_query += statement + "; ";
    }
  }
  query = new_query;
}

// PostgreSQL
std::string psqlAddJitSettings(const std::string& query) {
  const std::string jit_settings_query =
      "SET jit = on; "
      "SET jit_above_cost = 0; "
      "SET jit_inline_above_cost = 0; "
      "SET jit_optimize_above_cost = 0; ";

  if (PROB_VERY_HIGH()) {
    return jit_settings_query;
  }
  return "";
}

void psqlModifyCreateIndexStatement(std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (create_index_pos != std::string::npos && PROB_MEDIUM()) {
    std::string using_clause = (rand() % 2 == 0) ? "USING BTREE" : "USING HASH";
    size_t on_pos = statement.find(" ON ", create_index_pos);
    if (on_pos != std::string::npos) {
      size_t column_start_pos = statement.find("(", on_pos);
      if (column_start_pos != std::string::npos) {
        std::string table_name_with_using =
            statement.substr(0, column_start_pos) + " " + using_clause;
        std::string columns_part = statement.substr(column_start_pos);
        statement = table_name_with_using + " " + columns_part;
      }
    }
  }
}

void psqlAddIndexOrdering(std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  size_t open_paren_pos = statement.find("(", create_index_pos);
  size_t close_paren_pos = statement.find(")", open_paren_pos);
  if (open_paren_pos != std::string::npos &&
      close_paren_pos != std::string::npos) {
    std::string columns_part = statement.substr(
        open_paren_pos + 1, close_paren_pos - open_paren_pos - 1);
    std::stringstream columns_ss(columns_part);
    std::string column;
    std::string modified_columns;

    while (std::getline(columns_ss, column, ',')) {
      column.erase(0, column.find_first_not_of(" \t\n\r"));
      column.erase(column.find_last_not_of(" \t\n\r") + 1);

      if (PROB_MEDIUM()) {
        std::string order = (rand() % 2 == 0) ? " ASC" : " DESC";
        column += order;
      }
      modified_columns += column + ", ";
    }

    if (!modified_columns.empty()) {
      modified_columns.erase(modified_columns.size() -
                             2);  // Remove trailing comma and space
    }

    // Rebuild the CREATE INDEX statement with modified column list
    statement = statement.substr(0, open_paren_pos + 1) + modified_columns +
                statement.substr(close_paren_pos);
  }
}

void psqlAddPartialIndexCondition(std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  if (PROB_MEDIUM()) {
    std::vector<std::string> conditions = {
        " IS NULL", " IS NOT NULL", " <> NULL", " = NULL",
        " < NULL",  " > NULL",      " <= NULL", " >= NULL"};

    size_t column_start_pos = statement.find("(", create_index_pos) + 1;
    size_t column_end_pos = statement.find_first_of(" ,)", column_start_pos);
    std::string first_column_name =
        statement.substr(column_start_pos, column_end_pos - column_start_pos);

    std::string where_condition =
        " WHERE " + first_column_name + conditions[rand() % conditions.size()];

    statement += where_condition;
  }
}

void psqlAddNewIndexIfMissing(std::string& statement,
                              const std::string& current_table_name,
                              const std::vector<std::string>& table_columns,
                              int& index_counter) {
  if (!table_columns.empty()) {
    std::string index_name = "idx_" + current_table_name + "_" + std::to_string(index_counter++);
    std::string using_clause = (rand() % 2 == 0) ? "USING BTREE" : "USING HASH";
    int random_column_index = rand() % table_columns.size();
    std::string selected_column = table_columns[random_column_index];

    std::string create_index_stmt = "; CREATE INDEX " + index_name + " ON " +
                                    current_table_name + " " + using_clause +
                                    " ( " + selected_column + " )";
    statement += create_index_stmt;
  }
}

void psqlAddVacuumDatabaseStats(std::string& statement) {
  statement += "; VACUUM (ONLY_DATABASE_STATS)";
}

void psqlAddVacuumWithOptions(std::string& statement) {
  std::string vacuum_command = "; VACUUM (";
  std::vector<std::string> options = {
      "FULL",
      "FREEZE",
      "DISABLE_PAGE_SKIPPING",
      "SKIP_LOCKED",
      "INDEX_CLEANUP " + std::string(rand() % 2 == 0 ? "ON" : "OFF"),
      "TRUNCATE OFF"};

  // Add PARALLEL / BUFFER_USAGE_LIMIT (depending on FULL option)
  bool has_full = PROB_LOW();
  if (has_full) {
    options.push_back("FULL");
  } else {
    options.push_back("DISABLE_PAGE_SKIPPING");
    options.push_back("PARALLEL " + std::to_string(rand() % 1024));  // 0 ~ 1024
  }

  /*
  if (!has_full || rand() % 2 == 0) {
    options.push_back("BUFFER_USAGE_LIMIT " +
                      std::to_string(128 + rand() % (16777216 - 128 + 1)));
  }
  */

  for (const auto& opt : options) {
    if (rand() % 2 == 0) {
      vacuum_command += opt + ", ";
    }
  }

  if (vacuum_command.back() == ' ') vacuum_command.pop_back();
  if (vacuum_command.back() == ',') vacuum_command.pop_back();
  vacuum_command += ")";

  statement += vacuum_command;
}

void psqlAddVacuumAnalyzeTable(std::string& statement,
                               const std::string& table_name,
                               const std::vector<std::string>& columns) {
  std::string vacuum_command = "; VACUUM (ANALYZE, ";
  std::vector<std::string> options = {
      "FULL",
      "FREEZE",
      "DISABLE_PAGE_SKIPPING",
      "SKIP_LOCKED",
      "INDEX_CLEANUP " + std::string(rand() % 2 == 0 ? "ON" : "OFF"),
      "TRUNCATE OFF"};
      
  // Add PARALLEL / BUFFER_USAGE_LIMIT (depending on FULL option)
  bool has_full = PROB_LOW();
  if (has_full) {
    options.push_back("FULL");
  } else {
    options.push_back("DISABLE_PAGE_SKIPPING");
    options.push_back("PARALLEL " + std::to_string(rand() % 1024));  // 0 ~ 1024
  }

  /*
  if (!has_full || rand() % 2 == 0) {
    options.push_back("BUFFER_USAGE_LIMIT " +
                      std::to_string(128 + rand() % (16777216 - 128 + 1)));
  }
  */

  for (const auto& opt : options) {
    if (opt == "DISABLE_PAGE_SKIPPING" && has_full) {
      continue;
    }
    if (rand() % 2 == 0) {
      vacuum_command += opt + ", ";
    }
  }

  if (vacuum_command.back() == ' ') vacuum_command.pop_back();
  if (vacuum_command.back() == ',') vacuum_command.pop_back();
  vacuum_command += ") " + table_name + " (";

  bool has_columns = false;
  for (const auto& column : columns) {
    if (rand() % 2 == 0) {
      vacuum_command += column + ", ";
      has_columns = true;
    }
  }

  // 1+ columns
  if (!has_columns && !columns.empty()) {
    vacuum_command += columns.front() + ", ";
  }

  if (vacuum_command.back() == ' ') vacuum_command.pop_back();
  if (vacuum_command.back() == ',') vacuum_command.pop_back();
  vacuum_command += ")";

  statement += vacuum_command;
}

int getRandomInt(int min, int max) { return min + rand() % (max - min + 1); }

double getRandomDouble(double min, double max) {
  double f = static_cast<double>(rand()) / RAND_MAX;
  return min + f * (max - min);
}

// CREATE TABLE WITH clause
void psqlAddWithClauseStorageOption(std::string& statement) {
  if (statement.find("WITH") != std::string::npos || rand() % 100 >= 30) {
    return;
  }

  std::vector<std::string> with_options;

  if (PROB_MEDIUM())
    with_options.push_back("fillfactor = " +
                           std::to_string(getRandomInt(10, 100)));
  if (PROB_MEDIUM())
    with_options.push_back("toast_tuple_target = " +
                           std::to_string(getRandomInt(128, 8160)));
  if (PROB_MEDIUM())
    with_options.push_back("parallel_workers = " +
                           std::to_string(getRandomInt(0, 1024)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_enabled = " +
                           std::string(rand() % 2 == 0 ? "TRUE" : "FALSE"));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_enabled = " +
                           std::string(rand() % 2 == 0 ? "TRUE" : "FALSE"));
  if (PROB_MEDIUM())
    with_options.push_back("vacuum_index_cleanup = " +
                           std::string(rand() % 3 == 0
                                           ? "AUTO"
                                           : (rand() % 2 == 0 ? "ON" : "OFF")));
  if (PROB_MEDIUM())
    with_options.push_back("toast.vacuum_index_cleanup = " +
                           std::string(rand() % 3 == 0
                                           ? "AUTO"
                                           : (rand() % 2 == 0 ? "ON" : "OFF")));
  if (PROB_MEDIUM())
    with_options.push_back("vacuum_truncate = " +
                           std::string(rand() % 2 == 0 ? "TRUE" : "FALSE"));
  if (PROB_MEDIUM())
    with_options.push_back("toast.vacuum_truncate = " +
                           std::string(rand() % 2 == 0 ? "TRUE" : "FALSE"));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_threshold = " +
                           std::to_string(getRandomInt(0, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_threshold = " +
                           std::to_string(getRandomInt(0, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_scale_factor = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_scale_factor = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_insert_threshold = " +
                           std::to_string(getRandomInt(-1, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_insert_threshold = " +
                           std::to_string(getRandomInt(-1, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_insert_scale_factor = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_insert_scale_factor = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_analyze_threshold = " +
                           std::to_string(getRandomInt(0, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_analyze_scale_factor = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_cost_delay = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_cost_delay = " +
                           std::to_string(getRandomDouble(0.0, 100.0)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_vacuum_cost_limit = " +
                           std::to_string(getRandomInt(1, 10000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_vacuum_cost_limit = " +
                           std::to_string(getRandomInt(1, 10000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_freeze_min_age = " +
                           std::to_string(getRandomInt(0, 1000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_freeze_min_age = " +
                           std::to_string(getRandomInt(0, 1000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_freeze_max_age = " +
                           std::to_string(getRandomInt(100000, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_freeze_max_age = " +
                           std::to_string(getRandomInt(100000, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_freeze_table_age = " +
                           std::to_string(getRandomInt(0, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_freeze_table_age = " +
                           std::to_string(getRandomInt(0, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_multixact_freeze_min_age = " +
                           std::to_string(getRandomInt(0, 1000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_multixact_freeze_min_age = " +
                           std::to_string(getRandomInt(0, 1000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_multixact_freeze_max_age = " +
                           std::to_string(getRandomInt(10000, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_multixact_freeze_max_age = " +
                           std::to_string(getRandomInt(10000, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("autovacuum_multixact_freeze_table_age = " +
                           std::to_string(getRandomInt(0, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.autovacuum_multixact_freeze_table_age = " +
                           std::to_string(getRandomInt(0, 2000000000)));
  if (PROB_MEDIUM())
    with_options.push_back("log_autovacuum_min_duration = " +
                           std::to_string(getRandomInt(-1, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("toast.log_autovacuum_min_duration = " +
                           std::to_string(getRandomInt(-1, 2147483647)));
  if (PROB_MEDIUM())
    with_options.push_back("user_catalog_table = " +
                           std::string(rand() % 2 == 0 ? "TRUE" : "FALSE"));

  // Add WITH cluase
  std::string with_clause = "WITH (";
  for (const auto& opt : with_options) {
    with_clause += opt + ", ";
  }
  with_clause.erase(with_clause.size() - 2);
  with_clause += ")";

  // Add WITH clause after CREATE TABLE
  statement += " " + with_clause;
}

void psqlAddMaterializedToCTE(std::string& statement) {
  // Define keywords to check
  const std::string cte_with = "WITH";
  const std::string cte_recursive = "RECURSIVE";
  const std::string cte_as = "AS";

  size_t with_pos = statement.find(cte_with);
  if (with_pos != std::string::npos) {
    // Check if the statement is a CTE definition
    size_t as_pos = statement.find(cte_as, with_pos + cte_with.size());
    size_t paren_pos = statement.find("(", as_pos + cte_as.size());

    if (as_pos != std::string::npos && paren_pos != std::string::npos) {
      // Extract the portion before the opening parenthesis
      std::string prefix = statement.substr(0, as_pos + cte_as.size());

      // Determine if RECURSIVE exists
      bool has_recursive =
          (statement.find(cte_recursive, with_pos) != std::string::npos);

      // Randomly decide whether to add MATERIALIZED or NOT MATERIALIZED
      if (PROB_MEDIUM()) {
        std::string materialized_option =
            (rand() % 2 == 0) ? " MATERIALIZED" : " NOT MATERIALIZED";

        // Update the prefix with MATERIALIZED or NOT MATERIALIZED
        prefix += materialized_option;
      }

      // Rebuild the statement with the prefix and the remaining part
      statement = prefix + " " + statement.substr(as_pos + cte_as.size());
    }
  }
}

void processPostgreSQL(std::string& query) {
  srand(time(NULL));

  std::stringstream ss(query);
  std::string statement;
  std::string new_query;
  // bool index_found = false;
  // bool table_found = false;
  // int index_counter = 0;
  // std::string current_table_name;
  // std::vector<std::string> table_columns;

  std::string query_prefix = ""; // psqlAddJitSettings(query);

  while (std::getline(ss, statement, ';')) {
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);
    if (statement.empty()) continue;

    // psqlAddMaterializedToCTE(statement);

    // if (statement.find("CREATE INDEX") != std::string::npos) {
    //   index_found = true;
    //   psqlModifyCreateIndexStatement(statement);
    //   psqlAddIndexOrdering(statement);
    //   psqlAddPartialIndexCondition(statement);
    // }
    // if (statement.find("CREATE TABLE") != std::string::npos) {
    //   table_found = true;
    //   table_columns.clear();
    //   extractTableNameAndColumns(statement, current_table_name,
    //                               table_columns);

    //   psqlAddWithClauseStorageOption(statement);
    // }

    // // CREATE INDEX idx_...
    // if (table_found && !index_found && PROB_MEDIUM()) {
    //   psqlAddNewIndexIfMissing(statement, current_table_name, table_columns,
    //                             index_counter);
    // }

    // // VACUUM (...)
    // if (PROB_VERY_LOW()) {  // 5%
    //   psqlAddVacuumWithOptions(statement);
    // }

    // // VACUUM (ONLY_DATABASE_STATS)
    // if (PROB_VERY_LOW()) {  // 5%
    //   psqlAddVacuumDatabaseStats(statement);
    // }

    // // VACUUM (ANALYZE, ...)
    // if (table_found && PROB_VERY_LOW()) {
    //   psqlAddVacuumAnalyzeTable(statement, current_table_name, table_columns);
    // }

    // Rebuild the query with modified statements
    if (!statement.empty()) {
      new_query += statement + "; ";
    }
  }

  query = query_prefix + new_query;
}

// Oracle
std::string extractIndexName(const std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  size_t idx_name_start = statement.find(
      " ", create_index_pos + std::string("CREATE INDEX").length());
  size_t idx_name_end = statement.find(" ON ", idx_name_start);
  std::string index_name =
      statement.substr(idx_name_start, idx_name_end - idx_name_start);
  index_name.erase(0, index_name.find_first_not_of(" \t\n\r"));
  index_name.erase(index_name.find_last_not_of(" \t\n\r") + 1);
  return index_name;
}

void oracleConvertToBitmapIndex(std::string& statement) {
  if (PROB_MEDIUM()) {
    statement.replace(statement.find("CREATE INDEX"), std::string("CREATE INDEX").length(),
                      "CREATE BITMAP INDEX");
  }
}

void oracleAddInvisibleOrUnusable(std::string& statement) {
  if (statement.find("UNIQUE") == std::string::npos &&
      statement.find("MULTIVALUE") == std::string::npos) {
    if (PROB_MEDIUM()) {
      statement += (rand() % 2 == 0) ? " INVISIBLE" : " UNUSABLE";
    }
  }
}

void oracleAddColumnOrdering(std::string& statement) {
  size_t create_index_pos = statement.find("CREATE INDEX");
  size_t open_paren_pos = statement.find("(", create_index_pos);
  size_t close_paren_pos = statement.find(")", open_paren_pos);
  if (open_paren_pos != std::string::npos &&
      close_paren_pos != std::string::npos) {
    std::string columns_part = statement.substr(
        open_paren_pos + 1, close_paren_pos - open_paren_pos - 1);
    std::stringstream columns_ss(columns_part);
    std::string column;
    std::string modified_columns;

    while (std::getline(columns_ss, column, ',')) {
      column.erase(0, column.find_first_not_of(" \t\n\r"));
      column.erase(column.find_last_not_of(" \t\n\r") + 1);

      if (PROB_MEDIUM()) {
        std::string order = (rand() % 2 == 0) ? " ASC" : " DESC";
        column += order;
      }
      modified_columns += column + ", ";
    }

    if (!modified_columns.empty()) {
      // Remove trailing comma and space
      modified_columns.erase(modified_columns.size() - 2);
    }

    // Rebuild the CREATE INDEX statement with modified column list
    statement = statement.substr(0, open_paren_pos + 1) + modified_columns +
                statement.substr(close_paren_pos);
  }
}

void oracleAddAlterIndexStatements(std::string& statement,
                                   const std::vector<std::string>& index_names) {
  if (PROB_MEDIUM()) {
    statement += "; ALTER INDEX " + index_names[rand() % index_names.size()] + " UNUSABLE; ";
  }
  if (PROB_MEDIUM()) {
    statement += "; ALTER INDEX " + index_names[rand() % index_names.size()] + " COMPILE; ";
  }
  if (PROB_MEDIUM()) {
    statement += "; ALTER INDEX " + index_names[rand() % index_names.size()] + " INVISIBLE; ";
  }
}

void oracleProcessCreateIndexStatement(std::string& statement) {
  oracleConvertToBitmapIndex(statement);  // BITMAP
  oracleAddInvisibleOrUnusable(statement);
  oracleAddColumnOrdering(statement);
}

void oracleProcessAlterIndexStatement(std::string& statement) {
  if (PROB_MEDIUM() && statement.find("INVISIBLE") == std::string::npos) {
    statement += " INVISIBLE";
  }
}

std::string oracleGetRandomCompressionOption() {
  std::vector<std::string> compression_options = {
      "NOCOMPRESS", "ROW STORE COMPRESS", "ROW STORE COMPRESS BASIC",
      "ROW STORE COMPRESS ADVANCED"};
  return compression_options[rand() % compression_options.size()];
}

void oracleAddCompressionOption(std::string& statement) {
  if (statement.find("CREATE TABLE") != std::string::npos) {
    if (PROB_HIGH()) {  // 50% chance to add compression
      statement += " " + oracleGetRandomCompressionOption();
    }
  }
}

void oracleAddAlterTableCompressionOption(std::string& statement, const std::vector<std::string>& table_names) {
  std::string alter_statement = "; ALTER TABLE " + table_names[rand() % table_names.size()];

  if (PROB_MEDIUM()) {  // 30% chance to add MOVE
    alter_statement += " MOVE";
  }
  alter_statement += " " + oracleGetRandomCompressionOption();
  if (PROB_MEDIUM()) {  // 30% chance to add ONLINE
    alter_statement += " ONLINE";
  } 
  statement += alter_statement;
}

void oracleAddCreateBitmapIndex(std::string& statement,
                                const std::map<std::string, std::vector<std::string>>& table_columns,
                                int& index_counter) {
  std::string random_table = std::next(std::begin(table_columns), rand() % table_columns.size())->first;
  if (table_columns.at(random_table).size() == 0) return;
  std::string random_column = table_columns.at(random_table)[rand() % table_columns.at(random_table).size()];
  std::string index_name = "idx_" + random_table + "_" + std::to_string(index_counter++);
  std::string create_statement = "; CREATE BITMAP INDEX " + index_name + " ON " +
                             random_table + " (" + random_column +")";
  statement += create_statement;
}

void processOracle(std::string& query) {
  srand(time(NULL));

  std::stringstream ss(query);
  std::string statement;
  std::string new_query;
  std::string current_table_name;
  // std::vector<std::string> table_names;
  // std::vector<std::string> current_table_columns;
  // std::map<std::string, std::vector<std::string>> table_columns;
  // std::vector<std::string> index_names;
  // int index_counter = 0;

  while (std::getline(ss, statement, ';')) {
    statement.erase(0, statement.find_first_not_of(" \t\n\r"));
    statement.erase(statement.find_last_not_of(" \t\n\r") + 1);
    if (statement.empty()) continue;

    // // Process CREATE TABLE statements
    // if (statement.find("CREATE TABLE") != std::string::npos) {
    //   extractTableNameAndColumns(statement, current_table_name, current_table_columns);
    //   table_names.push_back(current_table_name);
    //   table_columns[current_table_name] = current_table_columns;
      
    //   oracleAddCompressionOption(statement);
    // }
    // // Process CREATE INDEX statements
    // else if (statement.find("CREATE INDEX") != std::string::npos) {
    //   std::string index_name = extractIndexName(statement);
    //   index_names.push_back(index_name);
    //   oracleProcessCreateIndexStatement(statement);
    // }
    // // Process ALTER INDEX statements
    // else if (statement.find("ALTER INDEX") != std::string::npos) {
    //   // oracleProcessAlterIndexStatement(statement);
    // }

    // // ALTER TABLE ... COMPRESS
    // if (!table_names.empty() && PROB_LOW()) {  // 20%
    //   oracleAddAlterTableCompressionOption(statement, table_names);
    // }

    // // CREATE BITMAP INDEX ...
    // if (!table_columns.empty() && PROB_LOW()) {  // 10%
    //   oracleAddCreateBitmapIndex(statement, table_columns, index_counter);
    // }

    // // ALTER INDEX ...
    // if (!index_names.empty() && PROB_MEDIUM()) {  // 30%
    //   oracleAddAlterIndexStatements(statement, index_names);
    // }

    // Rebuild the query with modified statements
    if (!statement.empty()) {
      new_query += statement + "; ";
    }
  }
  query = new_query;  // Replace the query with the modified version
}

/*
 * postprocess_core()
 *
 *  Essential post-processing steps
 */
void postprocess_core(TestGroup& tg) {
  sqliteEnableForeignKey_Postprocess(tg);
  mysqlIndexSize_Postprocess(tg);
  checkTypeViolation_Postprocess(tg);
  // checkTextComparison(plan);
  // removeIndexIfJson(plan);
}

void postprocess(TestGroup& tg) {
  if (!tg.is_valid()) {
    return;
  }

  postprocess_core(tg);

  // Additional post-processing steps can be added here based on your needs
  for (auto& [target, query] : tg.adapted_queries) {
    switch (target) {
      case Target::SQLite:
        processSQLite(query);
        break;
      case Target::MySQL:
        processMySQL(query);
        break;
      case Target::PostgreSQL:
        processPostgreSQL(query);
        break;
      case Target::Oracle:
        processOracle(query);
        break;
      case Target::MariaDB:
        break;
      default:
        //std::cerr << "Unsupported DBMS target encountered: "
                  //<< target_to_string(dbms_target) << ".\n";
        break;
    }
  }
}
