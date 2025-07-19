#include "sqlite.h"

#include <string>
#include <vector>
#include <fstream>

#include "ast.h"
#include "define.h"
#include "mutator.h"
#include "transpile.h"
#include "postprocess.h"
#include "utils.h"
#include "cov/kwcov.h"

// std::ofstream mutateOutfile("/tmp/mutator.Fuzzlog");

SQLiteDB *create_sqlite() { return new SQLiteDB; }
SQLiteDB::SQLiteDB() {
    mutator_ = std::make_unique<Mutator>();
    kwcov = std::make_unique<KeywordCoverage>();
}

bool SQLiteDB::initialize(YAML::Node config) {
  const std::string init_lib_path = config["init_lib"].as<std::string>();
  std::cerr << "Init path" << init_lib_path << std::endl;
  mutator_->init(init_lib_path);
  kwcov->init(config["keyword_coverage"]);
  return true;
}

bool SQLiteDB::save_interesting_query(const std::string &query) {
  //std::cerr << "save_interesting_query: " << query << std::endl;
  Program *program = parser(query);
  //std::cout << "save_interesting_query" << std::endl;
  if (program != nullptr) {
    std::vector<IR *> ir_set;
    IR *ir = program->translate(ir_set);
    ir_set.clear();
    string strip_sql = mutator_->extract_struct(ir);
    // string strip_sql = ir->to_string();
    auto p_strip_sql = parser(strip_sql);
    //std::cout << "save_interesting_query_2" << std::endl;
    if (p_strip_sql != nullptr) {
      auto root_ir = p_strip_sql->translate(ir_set);
      p_strip_sql->deep_delete();
      // mutator_->add_ir_to_library(root_ir);
      mutator_->add_to_library(root_ir);
      deep_delete(root_ir);
    }
    return true;
  } else {
    //std::cerr << "Error: SQL parser returned null for query: " << query
              //<< "?????" << std::endl;
    return false;
  }
}

std::vector<std::string> SQLiteDB::validate_all(
    const std::vector<IR *> &ir_set) {
  std::vector<std::string> validated_queries;

  for (IR *ir : ir_set) {
    if (ir == nullptr) {
      //std::cerr << "Error: IR pointer is null!" << std::endl;
      continue;
    }

    std::string validated_ir = mutator_->validate(ir);
    if (validated_ir.empty()) {
      //std::cout << "String is empty: " << validated_ir << std::endl;
      continue;
    }
    //std::cout << "String is: " << validated_ir << std::endl;
    // Save validated_query in the vector
    validated_queries.push_back(std::move(validated_ir));
  }

  return validated_queries;
}

bool SQLiteDB::has_mutated_test_cases() {
  return !validated_test_cases_.empty();
}

size_t SQLiteDB::mutate(TestGroup::Raw &r) {
  std::vector<IR *> ir_set, mutated_tree;
  Program *program_root = parser(std::string(r.buf_queries));
  if (program_root == nullptr) {
    return 0;
  }
  
  // TODO: Remove this uncessary try.
  // Or we will have exception from the parser?
  try {
    program_root->translate(ir_set);
  } catch (...) {
    for (auto ir : ir_set) {
      delete ir;
    }
    ir_set.clear();
    program_root->deep_delete();
  }
  program_root->deep_delete();

  mutated_tree = mutator_->mutate_all(ir_set);
  if (!ir_set.empty()) {
      deep_delete(ir_set[ir_set.size() - 1]);
  }

  std::vector<std::string> validated_queries = validate_all(mutated_tree);

  for (const auto &validated_query : validated_queries) {
    TestGroup tg = transpile(validated_query, r.targets);
    postprocess(tg);

    // Keyword Coverage
    double kwcov_val = kwcov->update_kwcov(validated_query);
    //mutateOutfile << "Keyword coverage of this query: " << kwcov_val << "%\n";

    // Add to testcases only if testgroup is valid
    if (tg.is_valid()) {
      validated_test_cases_.push(tg.encode());
    }
  }

  size_t validated_ir_size = validated_test_cases_.size();
  for (auto ir : mutated_tree) {
    deep_delete(ir);
  }

  return validated_ir_size;
}

TestGroup::Raw *SQLiteDB::get_next_mutated_query() {
  auto result = validated_test_cases_.top();
  validated_test_cases_.pop();
  return result;
}
