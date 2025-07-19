#ifndef __DB_H__
#define __DB_H__
#include "common.h"
#include "yaml-cpp/yaml.h"
#include "cov/kwcov.h"

class DataBase {
 public:
  // Set up the database.
  virtual bool initialize(YAML::Node config) = 0;
  // Mutate the query and return the number of new queries.
  virtual size_t mutate(TestGroup::Raw &r) = 0;
  // Return an new query to test. The `buffer` should be unmanaged,
  virtual TestGroup::Raw *get_next_mutated_query() = 0;
  virtual bool has_mutated_test_cases() = 0;
  // Save the interesting query to the dictionary.
  virtual bool save_interesting_query(const std::string &) = 0;
  virtual ~DataBase() {};

  // Keyword Coverage
  std::unique_ptr<KeywordCoverage> kwcov;
};

DataBase *create_database(YAML::Node config);
#endif  // __DB_H__
