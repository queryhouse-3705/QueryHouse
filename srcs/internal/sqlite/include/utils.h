#ifndef __UTILS_H__
#define __UTILS_H__
#include <string>

#include "../parser/bison_parser.h"
#include "../parser/flex_lexer.h"
#include "ast.h"
#include "define.h"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>

using std::string;

#define get_rand_int(range) rand() % (range)
//#define vector_rand_ele(a) (a[get_rand_int(a.size())])
#define vector_rand_ele(a) \
  (a.size() != 0 ? a[get_rand_int(a.size())] : gen_id_name())

#define vector_rand_ref(a) \
 (a.size() != 0 ? a[get_rand_int(a.size())] : vector_rand_ele(v_table_names))

IR *deep_copy(const IR *root);
void deep_delete(IR *root);

Program *parser(string sql);
string get_string_by_type(IRTYPE);
void print_ir(IR *ir);
void print_v_ir(vector<IR *> &v_ir_collector);
uint64_t ducking_hash(const void *key, int len);
void trim_string(string &);
vector<string> get_all_files_in_dir(const char *dir_name,
                                    bool absolute = false);
string magic_string_generator(string &s);

#endif
