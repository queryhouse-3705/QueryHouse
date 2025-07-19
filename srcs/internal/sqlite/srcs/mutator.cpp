#include "../include/mutator.h"

#include <assert.h>

#include <algorithm>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cstdio>
#include <ctime>
#include <deque>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <queue>

#include "../include/ast.h"
#include "../include/define.h"
#include "../include/utils.h"
#define _NON_REPLACE_

using namespace std;

vector<string> Mutator::common_string_libary;
vector<unsigned long> Mutator::value_libary;
map<string, vector<string>> Mutator::m_tables;            // Store columns of tables
vector<string> Mutator::v_table_names;                    // Store all tables

map<string, string> Mutator::primary_key;                 // Store PRIMARY KEY columns of tables
vector<string> Mutator::v_primarykey_table_names;         // Store tables with PRIMARY KEY
vector<string> Mutator::v_foreignkey_table_names;         // Store tables with FOREIGN KEY
map<string, IR *> Mutator::tablename_foreignkeycolumn;    // Store FOREIGN KEY columns of tables
schema json_schema;

// std::ofstream mutatortest("/tmp/mutatortest.txt", std::ios::out | std::ios::app);

std::string get_string_by_IRtype(IRTYPE type);
IR *Mutator::deep_copy_with_record(const IR *root, const IR *record) {
  IR *left = NULL, *right = NULL, *copy_res;

  if (root->left_)
    left = deep_copy_with_record(root->left_, record);
  if (root->right_)
    right = deep_copy_with_record(root->right_, record);

  if (root->op_ != NULL)
    copy_res = new IR(
        root->type_,
        OP3(root->op_->prefix_, root->op_->middle_, root->op_->suffix_), left,
        right, root->f_val_, root->str_val_, root->name_, root->mutated_times_);
  else
    copy_res = new IR(root->type_, NULL, left, right, root->f_val_,
                      root->str_val_, root->name_, root->mutated_times_);

  copy_res->id_type_ = root->id_type_;

  if (root == record && record != NULL) {
    this->record_ = copy_res;
  }

  return copy_res;
}

bool Mutator::check_node_num(IR *root, unsigned int limit) {
  auto v_statements = extract_statement(root);
  bool is_good = true;

  if (v_statements.size() > 5) {
    is_good = false;

  } else
    for (auto stmt : v_statements) {
      if (calc_node(stmt) > limit) {
        is_good = false;
        break;
      }
    }

  return is_good;
}

vector<IR *> Mutator::mutate_all(vector<IR *> &v_ir_collector) {
  vector<IR *> res;
  set<unsigned long> res_hash;
  IR *root = v_ir_collector[v_ir_collector.size() - 1];

  for (auto ir : v_ir_collector) {
    if (ir == root || ir->type_ == kProgram) continue;
    vector<IR *> v_mutated_ir = mutate(ir);

    for (auto i : v_mutated_ir) {
      IR *new_ir_tree = deep_copy_with_record(root, ir);
      replace(new_ir_tree, this->record_, i);

      if (!check_node_num(new_ir_tree, 100)) {
        deep_delete(new_ir_tree);
        continue;
      }

      string tmp = extract_struct(new_ir_tree);
      unsigned tmp_hash = hash(tmp);
      if (res_hash.find(tmp_hash) != res_hash.end()) {
        deep_delete(new_ir_tree);
        continue;
      }

      res_hash.insert(tmp_hash);
      res.push_back(new_ir_tree);
    }
  }
  return res;
}

void Mutator::init(string init_lib_path) {
  // init_lib
  std::vector<std::string> file_list = get_all_files_in_dir(init_lib_path.c_str());
  for (auto &f : file_list) {
    std::cerr << "init lib: " << f << std::endl;

    ifstream input_test(init_lib_path + "/" + f);
    string line;

    // init lib from multiple sql
    while (getline(input_test, line)) {
      auto p = parser(line);
      //std::cout << "init" << std::endl;
      if (p == nullptr) {
        continue;
      }

      vector<IR *> v_ir;
      auto res = p->translate(v_ir);
      p->deep_delete();
      p = NULL;
      string strip_sql = extract_struct(res);
      deep_delete(res);
      p = parser(strip_sql);
      //std::cout << "init2" << std::endl;
      if (p == nullptr) {
        continue;
      }

      res = p->translate(v_ir);
      p->deep_delete();
      p = NULL;
      add_to_library(res);
      deep_delete(res);
    }
  }

  // init utils::m_tables
  // vector<string> v_tmp = {"haha1", "haha2", "haha3"};
  // v_table_names.insert(v_table_names.end(), v_tmp.begin(), v_tmp.end());
  // m_tables["haha1"] = {"ducking_column0_1", "ducking_column1_1",
  //                      "ducking_column2_1"};
  // m_tables["haha2"] = {"ducking_column0_2", "ducking_column1_2",
  //                      "ducking_column2_2"};
  // m_tables["haha3"] = {"ducking_column0_3", "ducking_column1_3",
  //                      "ducking_column2_3"};

  // init value_libary
  vector<unsigned long> value_lib_init = {0,
                                          (unsigned long)LONG_MAX,
                                          (unsigned long)ULONG_MAX,
                                          (unsigned long)CHAR_BIT,
                                          (unsigned long)SCHAR_MIN,
                                          (unsigned long)SCHAR_MAX,
                                          (unsigned long)UCHAR_MAX,
                                          (unsigned long)CHAR_MIN,
                                          (unsigned long)CHAR_MAX,
                                          (unsigned long)MB_LEN_MAX,
                                          (unsigned long)SHRT_MIN,
                                          (unsigned long)INT_MIN,
                                          (unsigned long)INT_MAX,
                                          (unsigned long)SCHAR_MIN,
                                          (unsigned long)SCHAR_MIN,
                                          (unsigned long)UINT_MAX,
                                          (unsigned long)FLT_MAX,
                                          (unsigned long)DBL_MAX,
                                          (unsigned long)LDBL_MAX,
                                          (unsigned long)FLT_MIN,
                                          (unsigned long)DBL_MIN,
                                          (unsigned long)LDBL_MIN};

  value_libary.insert(value_libary.begin(), value_lib_init.begin(),
                      value_lib_init.end());

  // init common_string_libary
  common_string_libary.push_back("DO_NOT_BE_EMPTY");
  // if (f_common_string != "") {
  //   ifstream input_string(f_common_string);
  //   string s;

  //   while (getline(input_string, s)) {
  //     common_string_libary.push_back(s);
  //   }
  // }
  string_libary.push_back("x");
  string_libary.push_back("abcdef");
  string_libary.push_back("ghijkl");

  // ifstream input_pragma(pragma);
  // assert(input_pragma.is_open());
  // string s;
  // //cout << "[duck]start init pragma" << endl;
  // while (getline(input_pragma, s)) {
  //   if (s.empty()) continue;

  //   auto pos = s.find('=');
  //   if (pos == string::npos) continue;
  //   string k = s.substr(0, pos - 1);
  //   string v = s.substr(pos + 2);
  //   if (find(cmds_.begin(), cmds_.end(), k) == cmds_.end()) {
  //     cmds_.push_back(k);
  //     //cout << "Pushing: " << s << std::endl;
  //   }
  //   m_cmd_value_lib_[k].push_back(v);
  // }

  // assert(!cmds_.empty());
  relationmap[id_column_name] = id_top_table_name;
  relationmap[id_table_name] = id_top_table_name;
  relationmap[id_index_name] = id_top_table_name;
  relationmap[id_create_column_name] = id_create_table_name;
  relationmap[id_pragma_value] = id_pragma_name;
  cross_map[id_top_table_name] = id_create_table_name;

  relationmap[id_foreignkey_column_name] = id_create_table_name; // fix
  cross_map[id_references_table_name] = id_top_table_name;
  relationmap[id_references_column_name] = id_references_table_name;// fix
  return;
}

vector<IR *> Mutator::mutate(IR *input) {
  vector<IR *> res;

  if (!lucky_enough_to_be_mutated(input->mutated_times_)) {
    return res;  // return a empty set if the IR is not mutated
  }

  res.push_back(strategy_delete(input));
  res.push_back(strategy_insert(input));
  res.push_back(strategy_replace(input));

  // may do some simple filter for res, like removing some duplicated cases

  input->mutated_times_ += res.size();
  for (auto i : res) {
    if (i == NULL) continue;
    i->mutated_times_ = input->mutated_times_;
  }
  return res;
}

bool Mutator::replace(IR *root, IR *old_ir, IR *new_ir) {
  auto parent_ir = locate_parent(root, old_ir);
  if (parent_ir == NULL) return false;
  if (parent_ir->left_ == old_ir) {
    deep_delete(old_ir);
    parent_ir->left_ = new_ir;
    return true;
  } else if (parent_ir->right_ == old_ir) {
    deep_delete(old_ir);
    parent_ir->right_ = new_ir;
    return true;
  }

  return false;
}

// bool Mutator::find_parent(IR *identifier, IDTYPE idtype) {
//   if (identifier->left_->id_type_ == idtype || identifier->right_->id_type_ == idtype) bool true
// }

IR *Mutator::locate_parent(IR *root, IR *old_ir) {
  if (root->left_ == old_ir || root->right_ == old_ir) return root;

  if (root->left_ != NULL)
    if (auto res = locate_parent(root->left_, old_ir)) return res;
  if (root->right_ != NULL)
    if (auto res = locate_parent(root->right_, old_ir)) return res;
  return NULL;
}

void Mutator::fix_foreignkey() {
  for (const auto& entry : tablename_foreignkeycolumn) {
    const std::string& tablename = entry.first;  // table name
    IR* val = entry.second;  // corresponding IR pointer

    // Exception handling for empty m_tables[tablename]
    if (m_tables[tablename].empty()) {
        continue;
    }

    // Update val->str_val_ with random column
    val->str_val_ = vector_rand_ele(m_tables[tablename]);

  }
}

string Mutator::validate(IR *root) {
  if (root == NULL) return "";
  try {
    string sql_str = root->to_string();
    //mutatortest << "-----------------------------------\nsql_str: " << sql_str << std::endl;
    // std::cout << sql_str << std::endl;
    auto parsed_ir = parser(sql_str);
    // std::cout << "validate" << std::endl;
    if (parsed_ir == nullptr) {
      //std::cout << "validate return" << std::endl;
      return "";
    }
    parsed_ir->deep_delete();
    
    reset_counter();

    vector<IR *> ordered_ir;
    auto graph =
        build_dependency_graph(root, relationmap, cross_map, ordered_ir);
    // Return empty string if the foreing key is not syntactic correct
    if (graph == std::map<IR*, std::set<IR*>>{}) {
      return "";
    }

    fix_graph(graph, root, ordered_ir);
    fix_foreignkey();

    // Return empty string if not convertible into string
    if (root->to_string().empty()) {
        return "";
    }
    json_schema.json_ = NULL;
    json_schema.paths.clear();
    json_schema.type.clear();
    json_schema.json_ = generate_random_json();
    return fix(root);

  } catch (...) {
    // invalid sql , skip
  }
  return "";
}

static void collect_ir(IR *root, set<IDTYPE> &type_to_fix,
                       vector<IR *> &ir_to_fix) {
  auto idtype = root->id_type_;
  // mutatortest << "\n???: " << get_string_by_idtype(idtype) << std::endl;
  if (root->left_) {
    collect_ir(root->left_, type_to_fix, ir_to_fix);
  }

  if (type_to_fix.find(idtype) != type_to_fix.end()) {
    ir_to_fix.push_back(root);
  }

  if (root->right_) {
    collect_ir(root->right_, type_to_fix, ir_to_fix);
  }
}

static IR *search_mapped_ir(IR *ir, IDTYPE idtype) {
  vector<IR *> to_search;
  vector<IR *> backup;
  to_search.push_back(ir);
  while (!to_search.empty()) {
    for (auto i : to_search) {
      if (i->id_type_ == idtype) {
        return i;
      }
      if (i->left_) {
        backup.push_back(i->left_);
      }
      if (i->right_) {
        backup.push_back(i->right_);
      }
    }
    to_search = move(backup);
    backup.clear();
  }
  return NULL;
}

void cross_stmt_map(map<IR *, set<IR *>> &graph, vector<IR *> &ir_to_fix,
                    map<IDTYPE, IDTYPE> &cross_map) {
  for (auto m : cross_map) {
    vector<IR *> value;
    vector<IR *> key;
    for (auto &k : graph) {
      if (k.first->id_type_ == m.first) {
        // Save IRs whose id_type is id_top_table_name from graph into key
        //mutatortest << "key: " << get_string_by_idtype(k.first->id_type_) << std::endl;
        key.push_back(k.first);
      }
    }

    for (auto &k : ir_to_fix) {
      if (k->id_type_ == m.second) {
        // Save IRs whose id_type_ is id_create_table_name from ir_to_fix into value
        //mutatortest << "value: " << get_string_by_idtype(k->id_type_) << std::endl;
        value.push_back(k);
      }
    }

    // Return if key is empty 
    if (key.empty()) return;
    for (auto val : value) {
      graph[key[get_rand_int(key.size())]].insert(val);
    }
  }
}

void toptable_map(map<IR *, set<IR *>> &graph, vector<IR *> &ir_to_fix,
                  vector<IR *> &toptable) {
  vector<IR *> tablename;
  for (auto ir : ir_to_fix) {
    if (ir->id_type_ == id_table_name) {
      tablename.push_back(ir);
    } else if (ir->id_type_ == id_top_table_name) {
      toptable.push_back(ir);
    }
  }
  if (toptable.empty()) return;
  for (auto k : tablename) {
    auto r = get_rand_int(toptable.size());
    graph[toptable[r]].insert(k);
  }
}

vector<IR *> Mutator::extract_statement(IR *root) {
  vector<IR *> res;
  deque<IR *> bfs = {root};

  while (bfs.empty() != true) {
    auto node = bfs.front();
    bfs.pop_front();

    if (node->type_ == kStatement) res.push_back(node);
    if (node->left_) bfs.push_back(node->left_);
    if (node->right_) bfs.push_back(node->right_);
  }

  return res;
}

vector<IR *> Mutator::cut_subquery(IR *program, map<IR **, IR *> &m_save) {
  vector<IR *> res;
  vector<IR *> v_statements;
  deque<IR *> dfs = {program};

  while (dfs.empty() != true) {
    auto node = dfs.front();
    dfs.pop_front();

    if (node->type_ == kStatement) v_statements.push_back(node);
    if (node->left_) dfs.push_back(node->left_);
    if (node->right_) dfs.push_back(node->right_);
  }

  reverse(v_statements.begin(), v_statements.end());
  for (auto &stmt : v_statements) {
    deque<IR *> q_bfs = {stmt};
    res.push_back(stmt);

    while (!q_bfs.empty()) {
      auto cur = q_bfs.front();
      q_bfs.pop_front();

      if (cur->left_) {
        q_bfs.push_back(cur->left_);
        if (cur->left_->type_ == kSelectNoParen) {
          res.push_back(cur->left_);
          m_save[&cur->left_] = cur->left_;
          cur->left_ = NULL;
        }
      }

      if (cur->right_) {
        q_bfs.push_back(cur->right_);
        if (cur->right_->type_ == kSelectNoParen) {
          res.push_back(cur->right_);
          m_save[&cur->right_] = cur->right_;
          cur->right_ = NULL;
        }
      }
    }
  }
  return res;
}

bool Mutator::fix_back(map<IR **, IR *> &m_save) {
  for (auto &i : m_save) {
    if (*(i.first) != NULL) return false;
    *(i.first) = i.second;
  }

  return true;
}

map<IR *, set<IR *>> Mutator::build_dependency_graph(
    IR *root, map<IDTYPE, IDTYPE> &relationmap, map<IDTYPE, IDTYPE> &cross_map,
    vector<IR *> &ordered_ir) {
  map<IR *, set<IR *>> graph;
  set<IDTYPE> type_to_fix;
  map<IR **, IR *> m_save;
  // Save all type from relationmap into type_to_fix
  for (auto &iter : relationmap) {
    type_to_fix.insert(iter.first);
    type_to_fix.insert(iter.second);
  }

  auto ir_list = cut_subquery(root, m_save);


  for (auto stmt : ir_list) {
    //mutatortest << "\nstmt: " << stmt->to_string() << std::endl;
    vector<IR *> ir_to_fix;
    collect_ir(stmt, type_to_fix, ir_to_fix);
    for (auto ii : ir_to_fix) {
      ordered_ir.push_back(ii);
    }
    cross_stmt_map(graph, ir_to_fix, cross_map);
    vector<IR *> v_top_table;
    toptable_map(graph, ir_to_fix, v_top_table);
    for (auto ir : ir_to_fix) {
      auto idtype = ir->id_type_;
      // graph[ir].empty();                         // ??
      if (relationmap.find(idtype) == relationmap.end()) { 
        continue;
      }
      auto curptr = ir;
      bool flag = false;
      while (true) {
        auto pptr = locate_parent(stmt, curptr);
        if (pptr == NULL) break;
        while (pptr->left_ == NULL || pptr->right_ == NULL) {
          curptr = pptr;
          pptr = locate_parent(stmt, curptr);
          if (pptr == NULL) {
            flag = true;
            break;
          }
        }
        if (flag) break;

        auto to_search_child = pptr->left_;
        if (pptr->left_ == curptr) {
          to_search_child = pptr->right_;
        }
        auto match_ir = search_mapped_ir(to_search_child, relationmap[idtype]);
        // if (match_ir && match_ir->id_type_){mutatortest << "id_type_: "<<
        // match_ir->id_type_ << std::endl; }
        if (match_ir != NULL) {

          // when table_name.column_name
          if (ir->type_ == kColumnName && ir->left_ != NULL) {
            if (v_top_table.size() > 0) {
              // mutatortest << "1\n";
              match_ir = v_top_table[get_rand_int(v_top_table.size())];
            }
            graph[match_ir].insert(ir->left_);
            if (ir->right_) {
              // mutatortest << "2\n";
              graph[match_ir].insert(ir->right_);
              ir->left_->id_type_ = id_table_name;
              ir->right_->id_type_ = id_column_name;
              ir->id_type_ = id_whatever;
            }
          } else
            graph[match_ir].insert(ir);  // Otherwise add to graph
          break;
        }
        curptr = pptr;
      }
    }
  }

  fix_back(m_save);
  //mutatortest << "build_dependency_graph_END\n";
  return graph;
}

IR *Mutator::strategy_delete(IR *cur) {
  assert(cur);
  MUTATESTART

  DOLEFT
  res = deep_copy(cur);
  if (res->left_ != NULL) deep_delete(res->left_);
  res->left_ = NULL;

  DORIGHT
  res = deep_copy(cur);
  if (res->right_ != NULL) deep_delete(res->right_);
  res->right_ = NULL;

  DOBOTH
  res = deep_copy(cur);
  if (res->left_ != NULL) deep_delete(res->left_);
  if (res->right_ != NULL) deep_delete(res->right_);
  res->left_ = res->right_ = NULL;

  MUTATEEND
}

IR *Mutator::strategy_insert(IR *cur) {
  assert(cur);

  auto res = deep_copy(cur);

  if (cur->type_ == kStatementList) {
    int size = left_lib[kStatementList].size();
    auto new_right = deep_copy(left_lib[kStatementList][get_rand_int(size)]);
    auto new_res = new IR(kStatementList, OPMID(";"), res, new_right);
    return new_res;
  }

  if (res->right_ == NULL && res->left_ != NULL) {
    auto left_type = res->left_->type_;
    auto left_lib_size = left_lib[left_type].size();
    if (left_lib_size != 0) {
      auto new_right =
          deep_copy(left_lib[left_type][get_rand_int(left_lib_size)]);
      res->right_ = new_right;
      return res;
    }
  } else if (res->right_ != NULL && res->left_ == NULL) {
    auto right_type = res->right_->type_;
    auto right_lib_size = right_lib[right_type].size();
    if (right_lib_size != 0) {
      auto new_left =
          deep_copy(right_lib[right_type][get_rand_int(right_lib_size)]);
      res->left_ = new_left;
      return res;
    }
  }

  int lib_size = ir_libary_2D_[res->type_].size();
  if (lib_size == 0) {
    deep_delete(res);
    return NULL;
  }

  auto save = res;
  res = deep_copy(ir_libary_2D_[res->type_][get_rand_int(lib_size)]);
  deep_delete(save);

  return res;
}

IR *Mutator::strategy_replace(IR *cur) {
  assert(cur);

  MUTATESTART

  DOLEFT
  res = deep_copy(cur);

  auto new_node = get_from_libary_2D(res->left_);

  if (new_node != NULL) {
    new_node = deep_copy(new_node);
    if (res->left_ != NULL) {
      new_node->id_type_ = res->left_->id_type_;
    }
  }
  if (res->left_ != NULL) deep_delete(res->left_);
  res->left_ = new_node;

  DORIGHT
  res = deep_copy(cur);

  auto new_node = get_from_libary_2D(res->right_);
  if (new_node != NULL) {
    new_node = deep_copy(new_node);
    if (res->right_ != NULL) {
      new_node->id_type_ = res->right_->id_type_;
    }
  }
  if (res->right_ != NULL) deep_delete(res->right_);
  res->right_ = new_node;

  DOBOTH
  res = deep_copy(cur);

  auto new_left = get_from_libary_2D(res->left_);
  auto new_right = get_from_libary_2D(res->right_);

  if (new_left != NULL) {
    new_left = deep_copy(new_left);
    if (res->left_ != NULL) {
      new_left->id_type_ = res->left_->id_type_;
    }
  }

  if (new_right != NULL) {
    new_right = deep_copy(new_right);
    if (res->right_ != NULL) {
      new_right->id_type_ = res->right_->id_type_;
    }
  }

  if (res->left_) deep_delete(res->left_);
  if (res->right_) deep_delete(res->right_);
  res->left_ = new_left;
  res->right_ = new_right;

  MUTATEEND

  return res;
}

bool Mutator::lucky_enough_to_be_mutated(unsigned int mutated_times) {
  if (int i = get_rand_int(mutated_times + 1) < LUCKY_NUMBER) {
    return true;
  }
  return false;
}

IR *Mutator::get_from_libary_2D(IR *ir) {
  static IR *empty_str = new IR(kStringLiteral, "");

  if (!ir) return NULL;

  auto &i = ir_libary_2D_[ir->type_];
  if (i.size() == 0) return empty_str;
  return i[get_rand_int(i.size())];
}

IR *Mutator::get_from_libary_3D(IR *ir) {
  NODETYPE left_type = kEmpty, right_type = kEmpty;
  if (ir->left_) {
    left_type = ir->left_->type_;
  }
  if (ir->right_) {
    right_type = ir->right_->type_;
  }
  auto &i = ir_libary_3D_[left_type][right_type];
  if (i.size() == 0) return new IR(kStringLiteral, "");
  return i[get_rand_int(i.size())];
}

string Mutator::get_a_string() {
  unsigned com_size = common_string_libary.size();
  unsigned lib_size = string_libary.size();
  unsigned double_lib_size = lib_size * 2;

  unsigned rand_int = get_rand_int(double_lib_size + com_size);
  if (rand_int < double_lib_size) {
    return string_libary[rand_int >> 1];
  } else {
    rand_int -= double_lib_size;
    return common_string_libary[rand_int];
  }
}

unsigned long Mutator::get_a_val() {
  if (value_libary.size() == 0) return 0xdeadbeef;
  return value_libary[get_rand_int(value_libary.size())];
}

unsigned long Mutator::get_library_size() {
  unsigned long res = 0;

  for (auto &i : ir_libary_2D_) {
    res += i.second.size();
  }

  for (auto &i : ir_libary_3D_) {
    for (auto &j : i.second) {
      res += j.second.size();
    }
  }

  for (auto &i : left_lib) {
    res += i.second.size();
  }

  for (auto &i : right_lib) {
    res += i.second.size();
  }

  return res;
}

#ifdef _NON_REPLACE_
void Mutator::add_to_library(IR *ir) {
#else
void Mutator::add_to_library_core(IR *ir) {
#endif
  NODETYPE p_type = ir->type_;
  unsigned long p_hash = hash(ir->to_string());
  if (ir_libary_2D_hash_[p_type].find(p_hash) !=
      ir_libary_2D_hash_[p_type].end()) {
    return;
  }
  IR *ir_copy = deep_copy(ir);
  add_to_library_core(ir_copy);
}

#ifdef _NON_REPLACE_
void Mutator::add_to_library_core(IR *ir) {
#else
void Mutator::add_to_library(IR *ir) {
#endif

  string p_str = ir->to_string();
  unsigned long p_hash = hash(p_str);
  NODETYPE p_type = ir->type_;
  NODETYPE left_type = kEmpty, right_type = kEmpty;

  // update library_2D
  if (ir_libary_2D_hash_[p_type].find(p_hash) !=
      ir_libary_2D_hash_[p_type].end()) {
    return;
  }

  ir_libary_2D_hash_[p_type].insert(p_hash);

#ifdef _NON_REPLACE_
  ir_libary_2D_[p_type].push_back(ir);
#else
  ir_libary_2D_[p_type].push_back(deep_copy(ir));
#endif

  if (ir->left_) {
    left_type = ir->left_->type_;
#ifdef _NON_REPLACE_
    add_to_library_core(ir->left_);
#else
    add_to_library(ir->left_);
#endif
  }
  if (ir->right_) {
    right_type = ir->right_->type_;
#ifdef _NON_REPLACE_
    add_to_library_core(ir->right_);
#else
    add_to_library(ir->right_);
#endif
  }

  // update right_lib, left_lib
  if (ir->right_ && ir->left_) {
#ifdef _NON_REPLACE_
    right_lib[right_type].push_back(ir->left_);
    left_lib[left_type].push_back(ir->right_);
#else
    right_lib[right_type].push_back(deep_copy(ir->left_));
    left_lib[left_type].push_back(deep_copy(ir->right_));
#endif
  }

  // update library_3D
  set<unsigned long> &hash_map = ir_libary_3D_hash_[left_type][right_type];
  if (hash_map.find(p_hash) != hash_map.end()) {
    return;
  }

  ir_libary_3D_hash_[left_type][right_type].insert(p_hash);

#ifdef _NON_REPLACE_
  ir_libary_3D_[left_type][right_type].push_back(ir);
#else
  ir_libary_3D_[left_type][right_type].push_back(deep_copy(ir));
#endif

  return;
}

unsigned long Mutator::hash(string sql) {
  return ducking_hash(sql.c_str(), sql.size());
}

unsigned long Mutator::hash(IR *root) { return this->hash(root->to_string()); }

// IRTYPE to string
std::string get_string_by_IRtype(IRTYPE type) {
  switch (type) {
#define DECLARE_CASE(v) \
  case v:               \
    return #v;
    ALLTYPE(DECLARE_CASE)
#undef DECLARE_CASE

    default:
      return "Unknown IRTYPE";
  }
}

//std::string shorten_string(const std::string &str,
                           //std::size_t max_length = 50) {
  //if (str.length() > max_length) {
    //return str.substr(0, max_length) + "...";  // cut string and append '...'
  //}
  //return str;
//}

//void Mutator::debug(IR *root, int level, bool is_left, bool is_root) {
  //if (!root) return;

  //// Indentation by level
  //std::string indent(level, '\n.');

  //// Print node info
  //if (is_root) {
    //std::cout << indent << "\nRoot Node (Depth " << level
              //<< "): " << get_string_by_IRtype(root->type_) << "\n";
  //} else {
    //std::cout << indent
              //<< (is_left ? "Left Child (Depth " : "Right Child (Depth ")
              //<< level << "): " << get_string_by_IRtype(root->type_) << "\n";
  //}

  //// Print additional info (DataType, DataFlag, Core String, etc)
  //std::cout << indent << "IDTYPE: " << get_string_by_idtype(root->id_type_)
            //<< "\n";
  //std::cout << indent << "Mutated Times: " << root->mutated_times_ << "\n";
  //std::cout << indent << "SQL String: " << shorten_string(root->str_val_)
            //<< "\n\n";

  //if (root->left_) {
    //debug(root->left_, level + 1, true, false);
  //}

  //if (root->right_) {
    //debug(root->right_, level + 1, false, false);
  //}
//}

//std::string Mutator::show_struct(IR *root, int level, bool is_left,
                                 //bool is_root) {
  //assert(root && "Error: Attempted to access a null IR node!");

  //if (!root) {
    //std::cerr << "Error: Null node encountered at level " << level << std::endl;
    //return "N/A";
  //}

  //std::string current_node = get_string_by_IRtype(root->type_) +
                             //"::" + root->str_val_ + "::" + root->name_;
  //std::cout << "IR Node Debug: Type = " << get_string_by_IRtype(root->type_)
            //<< ", str_val_ = " << root->str_val_ << ", name_ = " << root->name_
            //<< std::endl;

  //std::string left_child =
      //(root->left_ ? show_struct(root->left_, level + 1, true, false) : "N/A");
  //std::string right_child =
      //(root->right_ ? show_struct(root->right_, level + 1, false, false)
                    //: "N/A");

  //if (left_child != "N/A" && right_child != "N/A") {
    //return current_node + "[" + left_child + "]" + "[" + right_child + "]";
  //} else if (left_child != "N/A") {
    //return current_node + "[" + left_child + "]";
  //} else if (right_child != "N/A") {
    //return current_node + "[" + right_child + "]";
  //} else {
    //return current_node;
  //}
//}

Mutator::~Mutator() {
  cout << "HERE" << endl;
  // delete ir_libary_3D_
  for (auto &i : ir_libary_3D_) {
    for (auto &j : i.second) {
      for (auto &ir : j.second) {
        deep_delete(ir);
      }
    }
  }

  // delete ir_libary_2D_
  for (auto &i : ir_libary_2D_) {
    for (auto &ir : i.second) {
      deep_delete(ir);
    }
  }

  // delete left_lib
  for (auto &i : left_lib) {
    for (auto &ir : i.second) {
      deep_delete(ir);
    }
  }

  // delete right_lib
  for (auto &i : right_lib) {
    for (auto &ir : i.second) {
      deep_delete(ir);
    }
  }
}

void Mutator::fix_one(map<IR *, set<IR *>> &graph, IR *fixed_key,
                      set<IR *> &visited, IR *root) {
  if (fixed_key->id_type_ == id_create_table_name) {   // table
    string tablename = fixed_key->str_val_;
    auto &columns = m_tables[tablename];
    for (auto &val : graph[fixed_key]) {
      if (val->id_type_ == id_create_column_name) { // primarykey_column_name 
        string new_column = gen_id_name();
        if (is_primary_column(root, val)){
          // new_column = "primary_key";             // will change
          primary_key[tablename] = new_column;    // only primary key
        }
        columns.push_back(new_column);
        val->str_val_ = new_column;
        visited.insert(val);
      } else if (val->id_type_ == id_top_table_name) {
        val->str_val_ = tablename;
        visited.insert(val);
        fix_one(graph, val, visited, root);
      } else if (val->id_type_ == id_foreignkey_column_name) {
        tablename_foreignkeycolumn[tablename] = val;
      }
    } 
  } else if (fixed_key->id_type_ == id_top_table_name) {
      string tablename = fixed_key->str_val_;
      auto &columns = m_tables[tablename];

    for (auto &val : graph[fixed_key]) {
      if (val->id_type_ == id_column_name) {
        val->str_val_ = vector_rand_ele(columns);
        visited.insert(val);
      } else if (val->id_type_ == id_table_name) {
        val->str_val_ = tablename;
        visited.insert(val);
      } else if (val->id_type_ == id_index_name) {
        string new_index = gen_id_name();
        val->str_val_ = new_index;
        m_tables[new_index] = m_tables[tablename];
        v_table_names.push_back(new_index);
      }
    }
  } else if (fixed_key->id_type_ == id_references_table_name ) {
    string tablename = fixed_key->str_val_;
    auto &columns = m_tables[tablename];
    
    for (auto &val : graph[fixed_key]) {
      if (val->id_type_ = id_references_column_name) {
        if (primary_key.find(tablename) == primary_key.end() || primary_key[tablename].empty()) {
            val->str_val_ = vector_rand_ref(m_tables[tablename]);
        } else {
            val->str_val_ = primary_key[tablename];
        }
      }
    }
  }
}



bool Mutator::contains_irtype(IR* root, IRTYPE find_irtype) {
    if (!root) return false;

    if (root->type_ == find_irtype) {
      // std::cout << "exits: " << get_string_by_IRtype(root->type_) << "\n---------------------------------" << std::endl; 
      return true; 
      }

    return contains_irtype(root->left_, find_irtype) || contains_irtype(root->right_, find_irtype);
}


IR *Mutator::find_irtype(IR *root, IRTYPE parent_irtype) {
  if (!root) return nullptr;

  if(root->left_->type_ == parent_irtype) {
      return root;
  }

  if (auto res = find_irtype(root->left_, parent_irtype)) {
    return res;
  }

  return find_irtype(root->right_, parent_irtype);
}

// find primarykey column 
bool Mutator::is_primary_column(IR *root, IR *column) {
  // std::cout << "---------------------------------primary_column_start\norigin_column: " << get_string_by_IRtype(column->type_) << std::endl;
  while(column->type_ != kColumnDeftop){
    column = locate_parent(root, column);
    if(column == NULL) {
        //std::cout << "is_primary_column: NULL\n";
        return false;
    }
    // std::cout << get_string_by_IRtype(column->type_) << std::endl;
    if(column->type_ == kProgram) return false;
  }
  // std::cout << "find column " << get_string_by_IRtype(column->type_) << "\ncolumn_name: " << column->name_ << std::endl;
  return contains_irtype(column, koptPrimarykey);
}

std::string Mutator::find_table(IR *root, IR *column) {
  while(column->type_ != kCreateStatement){
    column = locate_parent(root, column);
    if(column->type_ == kProgram) return "";
  }

  IR* table_ir = find_irtype(column, kTableName);
  IR* identifier = table_ir->left_;
  string table_name = identifier->name_;
  return table_name;
}

bool Mutator::is_primary_table(IR *root, IR *table) {
  // std::cout << "---------------------------------primary_table_start\norigin_table: " << get_string_by_IRtype(table->type_) << std::endl;
  while(table->type_ != kCreateStatement){
    table = locate_parent(root, table);
    if(table == NULL) { 
      // std::cout << "is_primary_table: NULL\n"; 
      return false; 
      }
    if(table->type_ == kProgram) return false;
  }
    // std::cout << "find table " << get_string_by_IRtype(table->type_) << "\ntable_name: " << table->name_ << std::endl;
  return contains_irtype(table, koptPrimarykey);
}

bool Mutator::is_foreignkey_table(IR *root, IR *table) {
    while(table->type_ != kCreateStatement){
    table = locate_parent(root, table);
    if(table->type_ == kProgram) return false;
  }
  
  return contains_irtype(table, kForeignKey);
}

void Mutator::fix_graph(map<IR *, set<IR *>> &graph, IR *root,
                        vector<IR *> &ordered_ir) {
  set<IR *> visited;
  reset_database();
  //mutatortest << "reset_database()\n";

  for (auto ir : ordered_ir) {
    auto iter = make_pair(ir, graph[ir]);

    if (visited.find(iter.first) != visited.end()) {
      continue;
    }

    visited.insert(iter.first);
    if (iter.second.empty()) {
      if (iter.first->id_type_ == id_column_name) {
        string tablename = vector_rand_ele(v_table_names);
        auto &columns = m_tables[tablename];
        iter.first->str_val_ = vector_rand_ele(columns);
        continue;
      }
    }

    if (iter.first->id_type_ == id_create_table_name  ||
        iter.first->id_type_ == id_top_table_name     ||
        iter.first->id_type_ == id_references_table_name ) {
      if (iter.first->id_type_ == id_create_table_name) {
        string new_table_name = gen_id_name();
        if(is_primary_table(root, iter.first)) { 
          //mutatortest << "primary_table: " << new_table_name << std::endl;
          v_primarykey_table_names.push_back(new_table_name);
        } 
        if (is_foreignkey_table(root, iter.first)) {
          //mutatortest << "foreignkey_table: " << new_table_name << std::endl;
          v_foreignkey_table_names.push_back(new_table_name);
        }
        v_table_names.push_back(new_table_name);
        iter.first->str_val_ = new_table_name;
      } else if (iter.first->id_type_ == id_top_table_name) {
        iter.first->str_val_ = vector_rand_ele(v_table_names);
      } else if (iter.first->id_type_ == id_references_table_name) {
        // std::cout << "id_references_table_name_visit\n";
        iter.first->str_val_ = vector_rand_ref(v_primarykey_table_names);
        // iter.first->str_val_ = "references_table";    // will change
      }
      fix_one(graph, iter.first, visited, root);
    }
  }
}


std::string generate_random_string(bool is_key,
                                   size_t length = rand() % 15 + 5) {
  std::string charset;
  if (is_key == true) {
    charset =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ012345678"
        "9";  //!@#$%^&*()_+/;,.<>?:";
  } else {
    charset =
        "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
        //"!@#$%^"
        //"*()_+/,.<>?:"
        ;
  }
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> dist(0, charset.size() - 1);

  std::string first_charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  std::uniform_int_distribution<> first_dist(0, first_charset.size() - 1);

  std::string random_string;
  random_string += first_charset[first_dist(generator)];

  for (size_t i = 0; i < length; ++i) {
    random_string += charset[dist(generator)];
  }
  return random_string;
}

nlohmann::json Mutator::generate_random_json(std::string current_path,
                                             int depth) {
  nlohmann::json result;

  if (depth == 0) {
    int choice = rand() % 5;
    std::string type;
    nlohmann::json value;

    switch (choice) {
      case 0:
        type = "int";
        value = "int";
        // value = (rand() % 2 == 0)
        //         ? -1 * (rand() % 2147483647) - 10
        //         : (rand() % 2147483647) + 10;
        break;

      case 1:
        type = "string";
        value = "string";
        // value = generate_random_string(rand() % 15 + 5);
        break;

      case 2:
        type = "bool";
        value = "bool";
        // value = (rand() % 2 == 0);
        break;

      case 3:
        type = "double";
        value = "double";
        // double boundary_value = static_cast<double>(RAND_MAX) + (rand() %
        // 100 - 50); value = (rand() % 2 == 0) ? boundary_value : -1.0 *
        // boundary_value;
        break;

      case 4:
        type = "null";
        value = "null";
    }

    json_schema.paths.push_back(current_path);
    json_schema.type.push_back(type);
    json_schema.json_ = value;
    return value;
  }

  if (rand() % 2 == 0) {
    int num_keys = rand() % 3 + 1;  // 5 + 1

    for (int i = 0; i < num_keys; ++i) {
      std::string key = generate_random_string(true);
      std::string new_path;
      new_path = current_path + "." + key;  // Append with a dot

      result[key] = generate_random_json(new_path, depth - 1);
      json_schema.paths.push_back(new_path);
    }
  } else {
    int array_size = rand() % 3 + 1;  // 5 + 1

    for (int i = 0; i < array_size; ++i) {
      std::string new_path = current_path + "[" + std::to_string(i) + "]";
      result[i] = generate_random_json(new_path, depth - 1);
    }
    std::string new_path = current_path + "[" + std::to_string(array_size) + "]";
    json_schema.paths.push_back(new_path);
  }
  return result;
}

nlohmann::json generate_random_value(const std::string &type) {
  if (type == "int") {
    return (rand() % 2 == 0) ? -1 * (rand() % 2147483647) - 10
                             : (rand() % 2147483647) + 10;
  } else if (type == "string") {
    return generate_random_string(false);
  } else if (type == "bool") {
    return (rand() % 2 == 0);
  } else if (type == "double") {
    double integerPart = static_cast<double>(get_rand_int(RAND_MAX));
    double fractionalPart = static_cast<double>(get_rand_int(RAND_MAX - 1)) / static_cast<double>(RAND_MAX);
    fractionalPart = std::round(fractionalPart * 1e6) / 1e6;
    if (fractionalPart == 0) {
      return static_cast<int>(integerPart);
    }
    double boundaryValue = integerPart + fractionalPart;

    return (rand() % 2 == 0) ? boundaryValue : static_cast<double>(-1.0) * boundaryValue;
  }

  // unmatched type
  return nullptr;
}

void populate_random_values_in_schema(nlohmann::json &json_data) {
  for (auto &el : json_data.items()) {
    if (el.value().is_string()) {
      std::string type = el.value();
      if (type == "int" || type == "string" || type == "bool" ||
          type == "double" || type == "null") {
        el.value() = generate_random_value(type);
      }
    } else if (el.value().is_object() || el.value().is_array()) {
      populate_random_values_in_schema(el.value());  // recursive call
    }
  }
}

void remove_underscores(std::string &s) {
  s.erase(std::remove(s.begin(), s.end(), '_'), s.end());
}

vector<string> tokenize(const string &s) {
  vector<string> tokens;
  istringstream iss(s);
  string token;

  while (iss >> token) {
    tokens.push_back(token);
  }
  return tokens;
}

/* tranverse ir in the order: _right ==> root ==> left_ */
string Mutator::fix(IR *root) {
  string res;
  auto *right_ = root->right_, *left_ = root->left_;
  auto *op_ = root->op_;
  auto type_ = root->type_;
  auto str_val_ = root->str_val_;
  auto f_val_ = root->f_val_;
  auto int_val_ = root->int_val_;
  auto id_type_ = root->id_type_;

  string tmp_right;
  if (right_ != NULL) tmp_right = fix(right_);

  if (type_ == kIdentifier &&
      (id_type_ == id_database_name || id_type_ == id_schema_name)) {
    if (get_rand_int(2) == 1)
      return string("main");
    else
      return string("temp");
  }

  if (type_ == kCmdPragma) {
    // Unreachable
    // string res = "PRAGMA ";
    // int lib_size = cmds_.size();
    // string &key = cmds_[get_rand_int(lib_size)];
    // res += key;

    // int value_size = m_cmd_value_lib_[key].size();
    // string value = m_cmd_value_lib_[key][get_rand_int(value_size)];
    // if (!value.compare("_int_")) {
    //   value = string("=") +
    //           to_string(value_libary[get_rand_int(value_libary.size())]);
    // } else if (!value.compare("_empty_")) {
    //   value = "";
    // } else if (!value.compare("_boolean_")) {
    //   if (get_rand_int(2) == 0)
    //     value = "=false";
    //   else
    //     value = "=true";
    // } else {
    //   value = "=" + value;
    // }
    // if (!value.empty()) res += value + ";";
    res = "";
    return res;
  }

  if (type_ == kFilePath || type_ == kPrepareTargetQuery ||
      type_ == kOptOrderType || type_ == kColumnType || type_ == kSetType ||
      type_ == kOptJoinType || type_ == kOptDistinct || type_ == kNullLiteral)
    return str_val_;
  if (type_ == kStringLiteral) {
    auto s = string_libary[get_rand_int(string_libary.size())];
    return "'" + s + "'";
  }
  if (type_ == kjson_literal) {
    nlohmann::json copy = json_schema.json_;
    populate_random_values_in_schema(copy);
    return "'" + copy.dump(-1) + "'";
    // return "'{JSON}'";
  }
  if (type_ == kjson_pathliteral) {
    //     for (const auto& path : json_schema.paths) {
    //     std::cout << "json_path size : " << json_schema.paths.size() <<
    //     std::endl; std::cout << "Path: " << path << std::endl;
    // }
    return "'$" + json_schema.paths[rand() % json_schema.paths.size()] + "'";
    // return "'$JSON_PATH'";
  }
  if (type_ == kFtsQueryLiteral) {
    switch (/*get_rand_int(3)*/ 1) {
      case 0: {
        auto s = string_libary[get_rand_int(string_libary.size())];
        remove_underscores(s);
        return "'" + s + "'";
      }
      case 1: {
        int n = get_rand_int(5) + 2;
        string result;
        for (int i = 0; i < n; ++i) {
          auto s = string_libary[get_rand_int(string_libary.size())];
          remove_underscores(s);
          //cout << "string : " << s << endl;
          vector<string> tokens = tokenize(s);
          s = tokens[get_rand_int(tokens.size())];
          for (int i = 0; i < tokens.size(); i++) {
            //cout << "tokens : " << tokens[i] << "\n" << endl;
          }
          result +=
              (i > 0 ? (get_rand_int(2) == 0 ? " AND " : " NOT ") : "") + s;
        }
        return "'" + result + "'";
      }
      case 2: {
        int n = get_rand_int(5) + 2;
        std::string result;
        for (int i = 0; i < n; ++i) {
          auto s = string_libary[get_rand_int(string_libary.size())];
          remove_underscores(s);
          result += (i > 0 ? " " : "") + s;
        }
        return "'\"" + result + "\"'";
      }
    }
  }
  if (type_ == kIntLiteral)
    return std::to_string(value_libary[get_rand_int(value_libary.size())]);
  if (type_ == kFloatLiteral || type_ == kconst_float)
    return std::to_string(
        float(value_libary[get_rand_int(value_libary.size())]) + 0.1);
  if (type_ == kconst_str)
    return string_libary[get_rand_int(string_libary.size())];
  ;
  if (type_ == kconst_int)
    return std::to_string(value_libary[get_rand_int(value_libary.size())]);

  if (!str_val_.empty()) return str_val_;

  if (op_ != NULL) res += op_->prefix_ + " ";
  if (left_ != NULL) res += fix(left_) + " ";
  if (op_ != NULL) res += op_->middle_ + " ";
  if (right_ != NULL) res += tmp_right + " ";
  if (op_ != NULL) res += op_->suffix_;

  trim_string(res);
  return res;
}

unsigned int Mutator::calc_node(IR *root) {
  unsigned int res = 0;
  if (root->left_) res += calc_node(root->left_);
  if (root->right_) res += calc_node(root->right_);

  return res + 1;
}

string Mutator::extract_struct2(IR *root) {
  static int counter = 0;
  string res;
  auto *right_ = root->right_, *left_ = root->left_;
  auto *op_ = root->op_;
  auto type_ = root->type_;
  auto str_val_ = root->str_val_;

  if (type_ == kColumnName && str_val_ == "*") return str_val_;
  if (type_ == kOptOrderType || type_ == kNullLiteral || type_ == kColumnType ||
      type_ == kSetType || type_ == kOptJoinType || type_ == kOptDistinct)
    return str_val_;
  if (root->id_type_ != id_whatever && root->id_type_ != id_module_name) {
    return "x" + to_string(counter++);
  }
  if (type_ == kPrepareTargetQuery || type_ == kStringLiteral) {
    string str_val = str_val_;
    str_val.erase(std::remove(str_val.begin(), str_val.end(), '\''),
                  str_val.end());
    str_val.erase(std::remove(str_val.begin(), str_val.end(), '"'),
                  str_val.end());
    // string magic_string = magic_string_generator(str_val);
    string magic_string = str_val;
    unsigned long h = hash(magic_string);
    //cout << "magic_string : " << magic_string << "\n" << endl;
    if (string_libary_hash_.find(h) == string_libary_hash_.end()) {
      string_libary.push_back(magic_string);
      string_libary_hash_.insert(h);
    }
    return "'y'";
  }
  if (type_ == kIntLiteral) {
    value_libary.push_back(root->int_val_);
    return "10";
  }
  if (type_ == kFloatLiteral || type_ == kconst_float) {
    value_libary.push_back((unsigned long)root->f_val_);
    return "0.1";
  }
  if (type_ == kconst_int) {
    value_libary.push_back(root->int_val_);
    return "11";
  }
  if (type_ == kFilePath) return "'file_name'";

  if (!str_val_.empty()) return str_val_;
  if (op_ != NULL) res += op_->prefix_ + " ";
  if (left_ != NULL) res += extract_struct2(left_) + " ";
  if (op_ != NULL) res += op_->middle_ + " ";
  if (right_ != NULL) res += extract_struct2(right_) + " ";
  if (op_ != NULL) res += op_->suffix_;

  trim_string(res);
  return res;
}

string Mutator::extract_struct(IR *root) {
  static int counter = 0;
  string res;
  auto *right_ = root->right_, *left_ = root->left_;
  auto *op_ = root->op_;
  auto type_ = root->type_;
  auto str_val_ = root->str_val_;

  if (type_ == kColumnName && str_val_ == "*") return str_val_;
  if (type_ == kOptOrderType || type_ == kNullLiteral || type_ == kColumnType ||
      type_ == kSetType || type_ == kOptJoinType || type_ == kOptDistinct)
    return str_val_;
  if (root->id_type_ != id_whatever && root->id_type_ != id_module_name) {
    return "x";
  }
  if (type_ == kPrepareTargetQuery || type_ == kStringLiteral) {
    string str_val = str_val_;
    str_val.erase(std::remove(str_val.begin(), str_val.end(), '\''),
                  str_val.end());
    str_val.erase(std::remove(str_val.begin(), str_val.end(), '"'),
                  str_val.end());
    if (!str_val.empty()) {
      unsigned long h = hash(str_val);
      if (string_libary_hash_.find(h) == string_libary_hash_.end()) {
        string_libary.push_back(str_val);
        string_libary_hash_.insert(h);
      }
    }
    return "'y'";
  }
  if (type_ == kIntLiteral) {
    value_libary.push_back(root->int_val_);
    return "10";
  }
  if (type_ == kFloatLiteral || type_ == kconst_float) {
    value_libary.push_back((unsigned long)root->f_val_);
    return "0.1";
  }
  if (type_ == kconst_int) {
    value_libary.push_back(root->int_val_);
    return "11";
  }
  if (type_ == kFilePath) return "'file_name'";

  if (!str_val_.empty()) return str_val_;
  if (op_ != NULL) res += op_->prefix_ + " ";
  if (left_ != NULL) res += extract_struct(left_) + " ";
  if (op_ != NULL) res += op_->middle_ + " ";
  if (right_ != NULL) res += extract_struct(right_) + " ";
  if (op_ != NULL) res += op_->suffix_;

  trim_string(res);
  return res;
}

// void Mutator::add_new_table(IR *root, string &table_name) {
//   if (root->left_ != NULL) add_new_table(root->left_, table_name);

//   if (root->right_ != NULL) add_new_table(root->right_, table_name);

//   // add to table_name_lib_
//   if (root->type_ == kTableName) {
//     if (root->operand_num_ == 1) {
//       table_name = root->left_->str_val_;
//     } else if (root->operand_num_ == 2) {
//       table_name = root->left_->str_val_ + "." + root->right_->str_val_;
//     }
//   }

//   // add to column_name_lib_
//   if (root->type_ == kColumnDef) {
//     auto tmp = root->left_;
//     if (tmp->type_ == kIdentifier) {
//       if (!table_name.empty() && !tmp->str_val_.empty()){
//         m_tables[table_name].push_back(tmp->str_val_);
//         if (find(v_table_names.begin(), v_table_names.end(), table_name) != v_table_names.end())
//         v_table_names.push_back(table_name);
//       }
//     }
//   }
// }

void Mutator::reset_database() {
  m_tables.clear();
  v_table_names.clear();
  primary_key.clear();
  v_primarykey_table_names.clear();
  v_foreignkey_table_names.clear();
  tablename_foreignkeycolumn.clear();
}


int Mutator::try_fix(char *buf, int len, char *&new_buf, int &new_len) {
  string sql(buf);
  auto ast = parser(sql);
  //std::cout << "try_fix" << std::endl;
  new_buf = buf;
  new_len = len;
  if (ast == nullptr) return 0;

  vector<IR *> v_ir;
  auto ir_root = ast->translate(v_ir);
  ast->deep_delete();

  if (ir_root == NULL) return 0;
  auto fixed = validate(ir_root);
  //std::cout << "try_fix" << std::endl;
  deep_delete(ir_root);
  //std::cout << "deep_delete" << std::endl;
  if (fixed.empty()) return 0;

  char *sfixed = (char *)malloc(fixed.size() + 1);
  memcpy(sfixed, fixed.c_str(), fixed.size());
  sfixed[fixed.size()] = 0;

  new_buf = sfixed;
  new_len = fixed.size();

  return 1;
}


//std::string Mutator::debug_internal_state() {
    //std::ostringstream oss;

    //oss << "----------------- Debugging Mutator Internal State -----------------\n";
    //oss << "m_tables:\n";
    //for (const auto& [table, columns] : m_tables) {
        //oss << "  Table: " << table << "\n    Columns:";
        //for (const auto& column : columns) {
            //oss << " " << column;
        //}
        //oss << "\n";
    //}
    //oss << "v_table_names: ";
    //for (const auto& table_name : v_table_names) {
        //oss << table_name << " ";
    //}
    //oss << "\nprimary_key (Column -> Table):\n";
    //for (const auto& [column, table] : primary_key) {
        //oss << "  " << column << " -> " << table << "\n";
    //}
    //oss << "v_primarykey_table_names: ";
    //for (const auto& table_name : v_primarykey_table_names) {
        //oss << table_name << " ";
    //}
    //oss << "\nv_foreignkey_table_names: ";
    //for (const auto& table_name : v_foreignkey_table_names) {
        //oss << table_name << " ";
    //}
    //oss << "\n";

    //return oss.str();
//}
