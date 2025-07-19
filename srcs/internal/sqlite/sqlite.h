#ifndef __SQLITE_H_H_H__
#define __SQLITE_H_H_H__
#include <memory>
#include <stack>
#include <string>

#include "db.h"
#include "common.h"
#include "cov/kwcov.h"

class Mutator;
class IR;
class SQLiteDB : public DataBase {
 public:
  SQLiteDB();
  virtual bool initialize(YAML::Node config);
  virtual size_t mutate(TestGroup::Raw &r);
  virtual bool save_interesting_query(const std::string &);
  virtual TestGroup::Raw *get_next_mutated_query();
  virtual bool has_mutated_test_cases();

 private:
  std::vector<std::string> validate_all(const std::vector<IR *> &ir_set);
  std::unique_ptr<Mutator> mutator_;
  std::stack<TestGroup::Raw *> validated_test_cases_;

};

SQLiteDB *create_sqlite();
#endif
