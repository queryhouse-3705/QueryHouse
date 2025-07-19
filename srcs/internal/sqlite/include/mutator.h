#ifndef __MUTATOR_H__
#define __MUTATOR_H__

#include "ast.h"
#include "define.h"
#include "utils.h"
#include <cstdint>
#include <stdint.h>
#define LUCKY_NUMBER 500

#include <iostream>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <ctime>
#include <variant>
#include <vector>
#include <string>
#include <queue>

using namespace std;

  struct schema
  {
      nlohmann::json json_;
      vector<string> paths;
      vector<string> type;
  };

class Mutator {
 public:
  Mutator() { srand(time(nullptr)); }

  IR *deep_copy_with_record(const IR *root, const IR *record);
  unsigned long hash(IR *);
  unsigned long hash(string);

  IR *ir_random_generator(vector<IR *> v_ir_collector);

  vector<IR *> mutate_all(vector<IR *> &v_ir_collector);

  vector<IR *> mutate(IR *input);
  IR *strategy_delete(IR *cur);
  IR *strategy_insert(IR *cur);
  IR *strategy_replace(IR *cur);

  bool replace(IR *root, IR *old_ir, IR *new_ir);
  IR *locate_parent(IR *root, IR *old_ir);
  string validate(IR *root);

  void minimize(vector<IR *> &);
  bool lucky_enough_to_be_mutated(unsigned int mutated_times);

  void add_to_library(IR *);
  void add_to_library_core(IR *);
  IR *get_from_libary_3D(IR *);
  IR *get_from_libary_2D(IR *);

  void init(string init_lib_path);
  string fix(IR *root);
  string extract_struct(IR *root);
  string extract_struct2(IR *root);
  // void add_new_table(IR *root, string &table_name);
  void reset_database();

  bool check_node_num(IR *root, unsigned int limit);
  vector<IR *> extract_statement(IR *root);
  unsigned int calc_node(IR *root);

  map<IR *, set<IR *>> build_dependency_graph(IR *root,
                                              map<IDTYPE, IDTYPE> &relationmap,
                                              map<IDTYPE, IDTYPE> &crssmap,
                                              vector<IR *> &ordered_ir);
  vector<IR *> cut_subquery(IR *program, map<IR **, IR *> &m_save);
  bool fix_back(map<IR **, IR *> &m_save);
  void fix_one(map<IR *, set<IR *>> &graph, IR *fixed_key, set<IR *> &visited, IR *root);
  void fix_graph(map<IR *, set<IR *>> &graph, IR *root,
                 vector<IR *> &ordered_ir);

  string get_a_string();
  unsigned long get_a_val();
  static vector<string> common_string_libary;
  static vector<unsigned long> value_libary;
  static map<string, vector<string>> m_tables;
  static vector<string> v_table_names;
  static vector<string> v_primarykey_table_names;
  static vector<string> v_foreignkey_table_names;
  static map<string, string> primary_key;
  static map<string, IR *> tablename_foreignkeycolumn;

  ~Mutator();
  nlohmann::json generate_random_json(std::string current_path = "", int depth = 2); // 3
  bool is_primary_table(IR *root, IR *table);
  bool is_primary_column(IR *root, IR *column);
  bool is_foreignkey_table(IR *root, IR *table);
  string find_table(IR *root, IR *column);
  IR *find_irtype(IR *root, IRTYPE parent_irtype);
  bool contains_irtype(IR* root, IRTYPE find_irtype);
  string debug_internal_state();
  void fix_foreignkey();
  void debug(IR *root, int level = 0, bool is_left = true, bool is_last = true);
  string show_struct(IR *root, int level = 0, bool is_left = true, bool is_root = true);
  unsigned long get_library_size();
  int try_fix(char *buf, int len, char *&new_buf, int &new_len);

 private:
  IR *record_ = NULL;
  map<NODETYPE, map<NODETYPE, vector<IR *>>> ir_libary_3D_;
  map<NODETYPE, map<NODETYPE, set<unsigned long>>> ir_libary_3D_hash_;
  map<NODETYPE, set<unsigned long>> ir_libary_2D_hash_;
  map<NODETYPE, vector<IR *>> ir_libary_2D_;
  map<NODETYPE, vector<IR *>> left_lib;
  map<NODETYPE, vector<IR *>> right_lib;
  vector<string> string_libary;
  map<IDTYPE, IDTYPE> relationmap;
  map<IDTYPE, IDTYPE> cross_map;
  set<unsigned long> string_libary_hash_;

  string s_table_name;

  map<NODETYPE, int> type_counter_;
};

#endif