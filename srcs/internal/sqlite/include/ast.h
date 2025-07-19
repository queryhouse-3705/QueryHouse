#ifndef __AST_H__
#define __AST_H__

#include <algorithm>  // std::find
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>  // std::runtime_error
#include <string>
#include <unordered_map>
#include <vector>

#include "define.h"

using namespace std;

struct TableInfo {
  std::vector<std::string> columns;  // List of columns
  std::string primary_key;           // Primary key column
};

#define DECLARE_CLASS(v) class v;

ALLCLASS(DECLARE_CLASS);
#undef DECLARE_CLASS

#define GEN_NAME() name_ = gen_id_name();

// Adapt id ring size to batch size
#ifdef BATCH_SIZE
  #define G_ID_COUNTER_MAX (BATCH_SIZE * 50)
#else
  #define G_ID_COUNTER_MAX 1000
#endif

#define reset_counter() { if(g_id_counter > G_ID_COUNTER_MAX) g_id_counter = 0; }

static unsigned long g_id_counter;

static inline void clear_id() { g_id_counter = 0; }

static string gen_id_name() { return "v" + to_string(g_id_counter++); }

enum CASEIDX { CASE0, CASE1, CASE2, CASE3, CASE4, CASE5, CASE6, CASE7, CASE8 };

enum NODETYPE {
  kconst_str,
  kconst_int,
  kconst_float,
#define DECLARE_TYPE(v) v,
  ALLTYPE(DECLARE_TYPE)
#undef DECLARE_TYPE
};

enum IDTYPE {
  id_whatever,

  id_top_table_name,
  id_column_name,
  id_table_name,
  id_create_table_name,
  id_create_column_name,

  id_schema_name,
  id_pragma_name,
  id_pragma_value,

  id_index_name,
  id_trigger_name,
  id_module_name,

  id_window_def_name,
  id_window_name,

  id_window_base_name,
  id_savepoint_name,
  id_collation_name,
  id_database_name,

  id_references_table_name,
  id_references_column_name,
  id_foreignkey_column_name,
};

// IDTYPE to string
std::string get_string_by_idtype(IDTYPE type);


typedef NODETYPE IRTYPE;

class IROperator {
 public:
  IROperator(string prefix = "", string middle = "", string suffix = "")
      : prefix_(prefix), middle_(middle), suffix_(suffix) {}

  string prefix_;
  string middle_;
  string suffix_;
};

class IR {
 public:
  IR(IRTYPE type, IROperator* op, IR* left = NULL, IR* right = NULL)
      : type_(type),
        op_(op),
        left_(left),
        right_(right),
        operand_num_((!!right) + (!!left)),
        id_type_(id_whatever) {
    GEN_NAME();
  }

  IR(IRTYPE type, string str_val, IDTYPE id_type = id_whatever)
      : type_(type),
        str_val_(str_val),
        op_(NULL),
        left_(NULL),
        right_(NULL),
        operand_num_(0),
        id_type_(id_type) {
    GEN_NAME();
  }

  IR(IRTYPE type, bool b_val)
      : type_(type),
        b_val_(b_val),
        left_(NULL),
        op_(NULL),
        right_(NULL),
        operand_num_(0),
        id_type_(id_whatever) {
    GEN_NAME();
  }

  IR(IRTYPE type, unsigned long int_val)
      : type_(type),
        int_val_(int_val),
        left_(NULL),
        op_(NULL),
        right_(NULL),
        operand_num_(0),
        id_type_(id_whatever) {
    GEN_NAME();
  }

  IR(IRTYPE type, double f_val)
      : type_(type),
        f_val_(f_val),
        left_(NULL),
        op_(NULL),
        right_(NULL),
        operand_num_(0),
        id_type_(id_whatever) {
    GEN_NAME();
  }

  IR(IRTYPE type, IROperator* op, IR* left, IR* right, double f_val,
     string str_val, string name, unsigned int mutated_times )
      : type_(type),
        op_(op),
        left_(left),
        right_(right),
        operand_num_((!!right) + (!!left)),
        name_(name),
        str_val_(str_val),
        f_val_(f_val),
        mutated_times_(mutated_times),
        id_type_(id_whatever) {}

  union {
    unsigned long int_val_;
    double f_val_;
    bool b_val_;
  };
  IDTYPE id_type_;
  IRTYPE type_;
  string name_;
  string str_val_;
  IROperator* op_;
  IR* left_;
  IR* right_;
  int operand_num_;
  unsigned int mutated_times_ = 0;
  string to_string();
};

class IRCollector {
 public:
  vector<IR*> parse(Program* entry);
};

class Node {
 public:
  void set_sub_type(unsigned int i) { sub_type_ = i; }
  IDTYPE id_type_;
  NODETYPE type_;
  unsigned int sub_type_;
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class Opt : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  bool is_existed_;
};

class OptString : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_;
};

class Program : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  StatementList* statement_list_;
  OptSemicolon* opt_semicolon_;
};

class StatementList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<Statement*> v_statement_list_;
};

class Statement : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR *>& v_ir_collector);
  OptionalHints* optional_hints_;
  PreparableStatement* preparable_statement_;
  PrepareStatement* prepare_statement_;
  ShowStatement* show_statement_;
  Cmd* cmd_;
};
class Cmd : public Statement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class CmdAttach : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  SchemaName* schema_name_;
};

class CmdDetach : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SchemaName* schema_name_;
};

class CmdReindex : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
};

class CmdAnalyze : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
};

class SuperList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<LiteralList*> v_super_list_;
};
class OptionalHints : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  HintList* hint_list_;
};

class CmdPragma : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  PragmaKey* pragma_key_;
  PragmaValue* pragma_value_;
  TableName* table_name_;
};

class PragmaKey : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  PragmaName* pragma_name_;
  SchemaName* schema_name_;
};

class PragmaValue : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  NumLiteral* num_literal_;
  StringLiteral* string_literal_;
  Identifier* id_;
};

class PragmaName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class SchemaName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class PrepareStatement : public Statement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  PrepareTargetQuery* prep_target_que_;
};

class PreparableStatement : public Statement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class ShowStatement : public Statement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
};

class Hint : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  LiteralList* literal_list_;
  Identifier* id_;
};

class HintList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<Hint*> v_hint_list_;
};

class PrepareTargetQuery : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string prep_target_que_;
};

class SelectStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptWithClause* opt_with_clause_;
  SelectWithParen* select_with_paren_;
  SelectNoParen* select_no_paren_;
  SetOperator* set_operator_;
  SelectParenOrClause* select_paren_or_clause_;
  OptOrder* opt_order_;
  OptLimit* opt_limit_;
};

class ImportStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ImportFileType* import_file_type_;
  FilePath* file_path_;
  TableName* table_name_;
};

class CreateStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptNotExists* opt_not_exists_;
  TableName* table_name_;
  FilePath* file_path_;
  ColumnDefCommaList* column_def_comma_list_;
  SelectStatement* select_statement_;
  OptColumnList* opt_column_list_;
  OptUnique* opt_unique_;
  IndexName* index_name_;
  IdentCommaList* ident_commalist_;
  OptWhere* opt_where_;
  ModuleName* module_name_;
  TriggerDeclare* trigger_declare_;
  TriggerCmdList* trigger_cmd_list_;
  CreateInparan* CreateInparan_;
  OptTmp* OptTmp_;
  ColumnDefListNoType* ColumnDefListNoType_;
};

class InsertStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  InsertType* insert_type_;
  TableName* table_name_;
  OptColumnList* opt_column_list_;
  SuperList* super_list_;
  SelectNoParen* select_no_paren_;
  OptUpsertClause* opt_upsert_clause_;
};

class DeleteStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
  OptWhere* opt_where_;
};

class UpdateStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableRefNameNoAlias* table_ref_name_no_alias_;
  UpdateClauseCommalist* update_clause_comma_list_;
  OptWhere* opt_where_;
};

class DropStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptExists* opt_exists_;
  TableName* table_name_;
  Identifier* id_;
  SchemaName* schema_name_;
  TriggerName* trigger_name_;
};

class ExecuteStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  OptLiteralList* opt_literal_list_;
};

class ImportFileType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class FilePath : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptNotExists : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class ColumnDefCommaList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnDef*> v_column_def_comma_list_;
};

class ColumnDef : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  ColumnType* column_type_;
  OptColumnArglist* opt_column_arglist_;
    // Default constructor
    ColumnDef() : id_(nullptr), column_type_(nullptr), opt_column_arglist_(nullptr) {}

    // Parameterized constructor
    ColumnDef(Identifier* i, ColumnType* c, OptColumnArglist* o)
        : id_(i), column_type_(c), opt_column_arglist_(o) {}
};

class ColumnType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptColumnNullable : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptExists : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptColumnList : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IdentCommaList* ident_comma_list_;
};

class UpdateClauseCommalist : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<UpdateClause*> v_update_clause_list_;
};

class UpdateClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  Expr* expr_;
};

class SelectWithParen : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SelectNoParen* select_no_paren_;
  SelectWithParen* select_with_paren_;
};

class SelectParenOrClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SelectWithParen* select_with_paren_;
  SelectClause* select_clause_;
};

class SelectNoParen : public SelectWithParen {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SelectClause* select_clause_;
  OptOrder* opt_order_;
  OptLimit* opt_limit_;
  SetOperator* set_operator_;
  SelectParenOrClause* select_paren_or_clause_;
};

class SetOperator : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SetType* set_type_;
  OptAll* opt_all_;
};

class SetType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptAll : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class SelectClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptTop* opt_top_;
  OptDistinct* opt_distinct_;
  SelectList* select_list_;
  OptFromClause* opt_from_clause_;
  OptWhere* opt_where_;
  OptGroup* opt_group_;
  WindowClause* window_clause_;
};

class OptDistinct : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class SelectList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ExprList* expr_list_;
};

class FromClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableRef* table_ref_;
};

class OptFromClause : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  FromClause* from_clause_;
};

class OptWhere : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class OptGroup : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ExprList* expr_list_;
  OptHaving* opt_having_;
};

class OptHaving : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class OptOrder : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Order* order_;
};

class OrderList : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<OrderDesc*> v_order_desc_;
};

class OrderDesc : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  OptOrderType* opt_order_type_;
  OptNull* opt_null_;
};

class OptOrderType : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptTop : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IntLiteral* int_literal_;
};

class OptLimit : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr1_;
  Expr* expr2_;
};

class ExprList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ExprAlias*> v_expr_list_;
};

class LiteralList : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<Literal*> v_literal_list_;
};

class OptLiteralList : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  LiteralList* literal_list_;
};

class Alias : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  bool has_as_;
  Identifier* id_;
};

class Expr : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class ExprAlias : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  OptAlias* opt_alias_;
};

class Operand : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  SelectNoParen* select_no_paren_;
};

class BetweenExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Operand* operand1_;
  Operand* operand2_;
  Operand* operand3_;
};

class LogicExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr1_;
  Expr* expr2_;
  string operator_;
};

class ExistsExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SelectNoParen* select_no_paren_;
};

class InExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Operand* operand_;
  ExprList* expr_list_;
  SelectNoParen* select_no_paren_;
};

class ArrayIndex : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IntLiteral* int_literal_;
  Operand* operand_;
};

class ScalarExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnName* column_name_;
  Literal* literal_;
};

class UnaryExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Operand* operand_;
  string operator_;
};

class BinaryExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Operand* operand1_;
  Operand* operand2_;
  string operator_;
  CompExpr* comp_expr_;
  // add k
  ColumnName* column_name_;
  FtsQueryLiteral* FtsQueryLiteral_;
};

class CompExpr : public BinaryExpr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class CaseExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* case_expr_;
  Expr* else_expr_;
  CaseList* case_list_;
};

class FunctionExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  OptDistinct* opt_distinct_;
  ExprList* expr_list_;
  OptFilterClause* opt_filter_clause_;
  OptOverClause* opt_over_clause_;
  WindowFuncNoArg* WindowFuncNoArg_;
  OverClauseWithOrder* OverClauseWithOrder_;
  WindowFunc* WindowFunc_;
  OverClause* OverClause_;
  AggregationFunc* AggregationFunc_;
};

class ExtractExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  DatetimeField* datetime_field_;
  Expr* expr_;
};

class ArrayExpr : public Operand {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ExprList* expr_list_;
};

class CaseClause : public Node {
 public:
  CaseClause(Expr* exp1, Expr* exp2) : when_expr_(exp1), then_expr_(exp2) {}
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* when_expr_;
  Expr* then_expr_;
};

class CaseList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<CaseClause*> v_case_list_;
};

class DatetimeField : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class ColumnName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* identifier1_;
  Identifier* identifier2_;
};

class Literal : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class StringLiteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class json_literal : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class json_pathliteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class BoolLiteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  bool b_val_;
};

class NumLiteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  double f_val_;
  IntLiteral* int_literal_;
};

class IntLiteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  unsigned long int_val_;
};

class FloatLiteral : public NumLiteral {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class NullLiteral : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class ParamExpr : public Literal {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
};

class Identifier : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier(string s, IDTYPE id_type = id_whatever)
      : id_(s), id_type_(id_type) {}
  string id_;
  IDTYPE id_type_;
};

class TableRefCommaList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<TableRefAtomic*> v_table_ref_comma_list_;
};

class TableRefAtomic : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  NonjoinTableRefAtomic* nonjoin_table_ref_atomic_;
  JoinClause* join_clause_;
};

class NonjoinTableRefAtomic : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableRefName* table_ref_name_;
  SelectStatement* select_statement_;
  OptTableAlias* opt_table_alias_;
};

class TableRefName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
  OptTableAlias* opt_table_alias_;
};

class TableRefNameNoAlias : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
};

class TableName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* database_name_;
  Identifier* table_name_;
};

class TableAlias : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Alias* alias_;
  IdentCommaList* ident_comma_list_;
  Identifier* id_;
};

class OptTableAlias : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableAlias* table_alias_;
};

class OptAlias : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Alias* alias_;
};

class WithClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WithDescriptionList* with_description_list_;
};

class OptWithClause : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WithClause* with_clause_;
  WithRecursiveClause* WithRecursiveClause_;
};

class WithDescriptionList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<WithDescription*> v_with_description_list_;
};

class WithDescription : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SelectWithParen* select_with_paren_;
  Identifier* id_;
};

class JoinClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableRefAtomic* table_ref_atomic1_;
  NonjoinTableRefAtomic* nonjoin_table_ref_atomic_;
  OptJoinType* opt_join_type_;
  TableRefAtomic* table_ref_atomic2_;
  ColumnName* column_name_;
  JoinCondition* join_condition_;
};

class OptJoinType : public OptString {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class JoinCondition : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class OptSemicolon : public OptString {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class IdentCommaList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<Identifier*> v_iden_comma_list_;
};

class OptColumnArglist : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnArglist* column_arglist_;
};

class ColumnArglist : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnArg*> v_column_arg_;
};

class ColumnArg : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptOnConflict* opt_on_conflict_;
  OptOrderType* opt_order_type_;
  OptAutoinc* opt_autoinc_;
  Expr* expr_;
  opt_generatedarg* opt_generatedarg_;
};

class OptOnConflict : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ResolveType* resolve_type_;
};

class ResolveType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptAutoinc : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptUnique : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class IndexName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class TriggerDeclare : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptTmp* opt_tmp_;
  OptNotExists* opt_not_exists_;
  TriggerName* trigger_name_;
  OptTriggerTime* opt_trigger_time_;
  TriggerEvent* trigger_event_;
  TableName* table_name_;
  OptForEach* opt_for_each_;
  OptWhen* opt_when_;
};

class OptTmp : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class TriggerName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class OptTriggerTime : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class TriggerEvent : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptOfColumnList* opt_of_column_list_;
};

class OptOfColumnList : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IdentCommaList* ident_commalist_;
};

class OptForEach : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptWhen : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class TriggerCmdList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<TriggerCmd*> v_trigger_cmd_list_;
};

class TriggerCmd : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  PreparableStatement* stmt_;
};

class ModuleName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class OptOverClause : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OverClause* OverClause_;
};

class OptFilterClause : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class WindowClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WindowDefnList* windowdefn_list_;
};

class WindowDefnList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<WindowDefn*> v_windowdefn_list_;
};

class WindowDefn : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  Window* window_;
};

class Window : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WindowWithOrder* WindowWithOrder_;
  WindowNoOrder* WindowNoOrder_;
};

class OptBaseWindowName : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class OptFrame : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  RangeOrRows* range_or_rows_;
  FrameBoundS* frame_bound_s_;
  OptFrameExclude* opt_frame_exclude_;
  FrameBoundE* frame_bound_e_;
};

class RangeOrRows : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class FrameBoundS : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  FrameBound* frame_bound_;
};

class FrameBoundE : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  FrameBound* frame_bound_;
};

class FrameBound : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  string str_val_;
};

class OptFrameExclude : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  FrameExclude* frame_exclude_;
};

class FrameExclude : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class InsertType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
  ResolveType* resolve_type_;
};

class TableRef : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptAlias* opt_alias_;
  OptIndex* opt_index_;
  ExprList* expr_list_;
  TablePrefix* table_prefix_;
  OptOn* opt_on_;
  SelectNoParen* select_no_paren_;
  OptUsing* opt_using_;
  TableName* table_name_;
  TableRef* table_ref_;
};

class TablePrefix : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  JoinOp* join_op_;
  TableRef* table_ref_;
};

class JoinOp : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  JoinKw* join_kw_;
  Identifier* id1_;
  Identifier* id2_;
};

class JoinKw : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptIndex : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnName* column_name_;
};

class OptOn : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
};

class OptUsing : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IdentCommaList* ident_commalist_;
};

class CastExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnType* column_type_;
  Expr* expr_;
};

class AlterStatement : public PreparableStatement {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnDef* column_def_;
  TableName* table_name1_;
  TableName* table_name2_;
  ColumnName* column_name1_;
  ColumnName* column_name2_;
  OptColumn* opt_column_;
};

class OptColumn : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class CmdRelease : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SavepointName* savepoint_name_;
};

class SavepointName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class VacuumStatement : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptSchemaName* opt_schema_name_;
  FilePath* file_path_;
};

class OptSchemaName : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SchemaName* schema_name_;
};

class RollbackStatement : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptTransaction* opt_transaction_;
  OptToSavepoint* opt_to_savepoint_;
};

class OptTransaction : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class OptToSavepoint : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  SavepointName* savepoint_name_;
};

class BeginStatement : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptTransaction* opt_transaction_;
};

class CommitStatement : public Cmd {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptTransaction* opt_transaction_;
};

class OptUpsertClause : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  UpsertClause* upsert_clause_;
};

class UpsertClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  IndexedColumnList* indexed_column_list_;
  AssignList* assign_list_;
  OptWhere* opt_where1_;
  OptWhere* opt_where2_;
};

class IndexedColumnList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<IndexedColumn*> v_indexed_column_list_;
};

class IndexedColumn : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptOrderType* opt_order_type_;
  Expr* expr_;
  OptCollate* opt_collate_;
};

class OptCollate : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  CollationName* collation_name_;
  string str_val_;
};

class AssignList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<AssignClause*> v_assign_list_;
};

class OptNull : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class AssignClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnNameList* column_name_list_;
  Expr* expr_;
};

class ColumnNameList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnName*> v_column_name_list_;
};

class CollationName : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

class ColumnInParen_ForeignKey : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnNameList_ForeignKey* column_name_list_ForeignKey_;
};

class ColumnInParen_References : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnNameList_References* column_name_list_References_;
};

class ColumnNameList_ForeignKey : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnName_ForeignKey*> v_column_name_list_ForeignKey_;
};

class ColumnNameList_References : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnName_References*> v_column_name_list_References_;
};

class ColumnName_ForeignKey : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* identifier_;
};

class ColumnName_References : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* identifier_;
};

class opt_ForeignKeylist : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ForeignKeylist* ForeignKeylist_;
};

class ForeignKeylist : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ForeignKey*> v_ForeignKey;
};

class ForeignKey : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  FkNoOptstmt* FkNoOptstmt_;
  opt_Actiontypelist* opt_Actiontypelist_;
};

class ForeignKeyColumn : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnInParen_ForeignKey* column_name_ForeignKey_;
};

class FkNoOptstmt : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ForeignKeyColumn* ForeignKeyColumn_;
  ForeignKeyRef* ForeignKeyRef_;
};

class ForeignKeyRef : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  TableName* table_name_;
  ColumnInParen_References* column_name_References_;
};

class opt_Actiontypelist : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Action_typelist* Action_typelist_;
};

class Action_typelist : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<Action_type*> v_Action_type;
};

class Action_type : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class CreateInparan : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ColumnDefCommaList* column_def_commalist_;
  opt_ForeignKeylist* opt_ForeignKeylist_;
};

class Jsonexpr_all : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Jsondata* Jsondata_;
  Jsonpath* Jsonpath_;
};

class Jsondata : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  json_literal* json_literal_;
  ColumnName* column_name_;
};

class Jsonpath : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  json_pathliteral* json_pathliteral_;
};

class opt_generatedarg : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class JsonExpr : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Jsonexpr_all* Jsonexpr_all_;
};

class WithRecursiveClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WithRecDescList* with_rec_desc_list;
};

class WithRecDescList : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<WithRecDesc*> v_with_rec_desc_list;
};

class WithRecDesc : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
  WithRecursiveSelect* with_recursive_select_;
};

class WithRecursiveSelect : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  InitSelect* init_select_;
  OptRecursiveSelect* opt_recursive_select_;
};

class OptRecursiveSelect : public Opt {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptDistinct* opt_distinct_;
  SelectList* select_list_;
  OptFromClause* opt_from_clause_;
  OptWhere* opt_where_;
  OptGroup* opt_group_;
  OptOrder* opt_order_;
};

class InitSelect : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptDistinct* opt_distinct_;
  SelListAlias* select_list_essential_alias_;
  OptFromClause* opt_from_clause_;
  OptWhere* opt_where_;
  OptGroup* opt_group_;
};

class SelListAlias : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  ExprListAlias* expr_list_essential_alias_;
};

class ExprListAlias : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ExprEssentialAlias*> v_expr_list_essential_alias_;
};

class ExprEssentialAlias : public Expr {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Expr* expr_;
  Alias* alias_;
};

class FtsQueryLiteral : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class WindowWithOrder : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptBaseWindowName* opt_base_window_name_;
  ExprList* expr_list_;
  Order* order_;
  OptFrame* opt_frame_;
};

class WindowNoOrder : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OptBaseWindowName* opt_base_window_name_;
  ExprList* expr_list_;
  OptFrame* opt_frame_;
};

class Order : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OrderList* order_list_;
};

class OverClauseWithOrder : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WindowWithOrder* WindowWithOrder_;
};

class OverClauseNoOrder : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  WindowNoOrder* WindowNoOrder_;
};

class OverClause : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  OverClauseWithOrder* OverClauseWithOrder_;
  OverClauseNoOrder* OverClauseNoOrder_;
  Identifier* id_;
};

class WindowFuncNoArg : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class WindowFunc : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class AggregationFunc : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  string str_val_;
};

class ColumnDefListNoType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  vector<ColumnDefNoType*> v_column_def_no_type_list_;
};

class ColumnDefNoType : public Node {
 public:
  virtual void deep_delete();
  virtual IR* translate(vector<IR*>& v_ir_collector);
  Identifier* id_;
};

#endif
