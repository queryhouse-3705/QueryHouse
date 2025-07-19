/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_HSQL_BISON_PARSER_H_INCLUDED
# define YY_HSQL_BISON_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HSQL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HSQL_DEBUG 1
#  else
#   define HSQL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HSQL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HSQL_DEBUG */
#if HSQL_DEBUG
extern int hsql_debug;
#endif
/* "%code requires" blocks.  */
#line 30 "bison_parser.y"

// %code requires block

#include "../include/ast.h"
#include "../include/define.h"
//#include "../include/utils.h"
#include "parser_typedef.h"


// Auto update column and line number
#define YY_USER_ACTION \
        yylloc->first_line = yylloc->last_line; \
        yylloc->first_column = yylloc->last_column; \
        for(int i = 0; yytext[i] != '\0'; i++) { \
            yylloc->total_column++; \
            yylloc->string_length++; \
                if(yytext[i] == '\n') { \
                        yylloc->last_line++; \
                        yylloc->last_column = 0; \
                } \
                else { \
                        yylloc->last_column++; \
                } \
        }

#line 83 "bison_parser.h"

/* Token kinds.  */
#ifndef HSQL_TOKENTYPE
# define HSQL_TOKENTYPE
  enum hsql_tokentype
  {
    SQL_HSQL_EMPTY = -2,
    SQL_YYEOF = 0,                 /* "end of file"  */
    SQL_HSQL_error = 256,          /* error  */
    SQL_HSQL_UNDEF = 257,          /* "invalid token"  */
    SQL_STRING = 258,              /* STRING  */
    SQL_IDENTIFIER = 259,          /* IDENTIFIER  */
    SQL_ESCAPED_CURLY_LITERAL = 260, /* ESCAPED_CURLY_LITERAL  */
    SQL_ESCAPED_BRACKET_LITERAL = 261, /* ESCAPED_BRACKET_LITERAL  */
    SQL_JSONPATH_STRING = 262,     /* JSONPATH_STRING  */
    SQL_FLOATVAL = 263,            /* FLOATVAL  */
    SQL_INTVAL = 264,              /* INTVAL  */
    SQL_DEALLOCATE = 265,          /* DEALLOCATE  */
    SQL_PARAMETERS = 266,          /* PARAMETERS  */
    SQL_INTERSECT = 267,           /* INTERSECT  */
    SQL_TEMPORARY = 268,           /* TEMPORARY  */
    SQL_TIMESTAMP = 269,           /* TIMESTAMP  */
    SQL_DISTINCT = 270,            /* DISTINCT  */
    SQL_NVARCHAR = 271,            /* NVARCHAR  */
    SQL_RESTRICT = 272,            /* RESTRICT  */
    SQL_TRUNCATE = 273,            /* TRUNCATE  */
    SQL_ANALYZE = 274,             /* ANALYZE  */
    SQL_BETWEEN = 275,             /* BETWEEN  */
    SQL_CASCADE = 276,             /* CASCADE  */
    SQL_COLUMNS = 277,             /* COLUMNS  */
    SQL_CONTROL = 278,             /* CONTROL  */
    SQL_DEFAULT = 279,             /* DEFAULT  */
    SQL_EXECUTE = 280,             /* EXECUTE  */
    SQL_EXPLAIN = 281,             /* EXPLAIN  */
    SQL_INTEGER = 282,             /* INTEGER  */
    SQL_NATURAL = 283,             /* NATURAL  */
    SQL_PREPARE = 284,             /* PREPARE  */
    SQL_PRIMARY = 285,             /* PRIMARY  */
    SQL_SCHEMAS = 286,             /* SCHEMAS  */
    SQL_SPATIAL = 287,             /* SPATIAL  */
    SQL_VARCHAR = 288,             /* VARCHAR  */
    SQL_VIRTUAL = 289,             /* VIRTUAL  */
    SQL_DESCRIBE = 290,            /* DESCRIBE  */
    SQL_BEFORE = 291,              /* BEFORE  */
    SQL_COLUMN = 292,              /* COLUMN  */
    SQL_CREATE = 293,              /* CREATE  */
    SQL_DELETE = 294,              /* DELETE  */
    SQL_DIRECT = 295,              /* DIRECT  */
    SQL_DOUBLE = 296,              /* DOUBLE  */
    SQL_ESCAPE = 297,              /* ESCAPE  */
    SQL_EXCEPT = 298,              /* EXCEPT  */
    SQL_EXISTS = 299,              /* EXISTS  */
    SQL_EXTRACT = 300,             /* EXTRACT  */
    SQL_GLOBAL = 301,              /* GLOBAL  */
    SQL_HAVING = 302,              /* HAVING  */
    SQL_IMPORT = 303,              /* IMPORT  */
    SQL_INSERT = 304,              /* INSERT  */
    SQL_ISNULL = 305,              /* ISNULL  */
    SQL_OFFSET = 306,              /* OFFSET  */
    SQL_RENAME = 307,              /* RENAME  */
    SQL_SCHEMA = 308,              /* SCHEMA  */
    SQL_SELECT = 309,              /* SELECT  */
    SQL_SORTED = 310,              /* SORTED  */
    SQL_TABLES = 311,              /* TABLES  */
    SQL_UNIQUE = 312,              /* UNIQUE  */
    SQL_UNLOAD = 313,              /* UNLOAD  */
    SQL_UPDATE = 314,              /* UPDATE  */
    SQL_VALUES = 315,              /* VALUES  */
    SQL_AFTER = 316,               /* AFTER  */
    SQL_ALTER = 317,               /* ALTER  */
    SQL_CROSS = 318,               /* CROSS  */
    SQL_DELTA = 319,               /* DELTA  */
    SQL_FLOAT = 320,               /* FLOAT  */
    SQL_GROUP = 321,               /* GROUP  */
    SQL_INDEX = 322,               /* INDEX  */
    SQL_INNER = 323,               /* INNER  */
    SQL_LIMIT = 324,               /* LIMIT  */
    SQL_LOCAL = 325,               /* LOCAL  */
    SQL_MERGE = 326,               /* MERGE  */
    SQL_MINUS = 327,               /* MINUS  */
    SQL_ORDER = 328,               /* ORDER  */
    SQL_OUTER = 329,               /* OUTER  */
    SQL_RIGHT = 330,               /* RIGHT  */
    SQL_TABLE = 331,               /* TABLE  */
    SQL_UNION = 332,               /* UNION  */
    SQL_USING = 333,               /* USING  */
    SQL_WHERE = 334,               /* WHERE  */
    SQL_CALL = 335,                /* CALL  */
    SQL_CASE = 336,                /* CASE  */
    SQL_CHAR = 337,                /* CHAR  */
    SQL_DATE = 338,                /* DATE  */
    SQL_DESC = 339,                /* DESC  */
    SQL_DROP = 340,                /* DROP  */
    SQL_ELSE = 341,                /* ELSE  */
    SQL_FILE = 342,                /* FILE  */
    SQL_FROM = 343,                /* FROM  */
    SQL_FULL = 344,                /* FULL  */
    SQL_HASH = 345,                /* HASH  */
    SQL_HINT = 346,                /* HINT  */
    SQL_INTO = 347,                /* INTO  */
    SQL_JOIN = 348,                /* JOIN  */
    SQL_LEFT = 349,                /* LEFT  */
    SQL_LIKE = 350,                /* LIKE  */
    SQL_LOAD = 351,                /* LOAD  */
    SQL_NULL = 352,                /* NULL  */
    SQL_PLAN = 353,                /* PLAN  */
    SQL_SHOW = 354,                /* SHOW  */
    SQL_TEXT = 355,                /* TEXT  */
    SQL_THEN = 356,                /* THEN  */
    SQL_TIME = 357,                /* TIME  */
    SQL_VIEW = 358,                /* VIEW  */
    SQL_WHEN = 359,                /* WHEN  */
    SQL_WITH = 360,                /* WITH  */
    SQL_ADD = 361,                 /* ADD  */
    SQL_ALL = 362,                 /* ALL  */
    SQL_AND = 363,                 /* AND  */
    SQL_ASC = 364,                 /* ASC  */
    SQL_CSV = 365,                 /* CSV  */
    SQL_END = 366,                 /* END  */
    SQL_FOR = 367,                 /* FOR  */
    SQL_INT = 368,                 /* INT  */
    SQL_KEY = 369,                 /* KEY  */
    SQL_NOT = 370,                 /* NOT  */
    SQL_OFF = 371,                 /* OFF  */
    SQL_SET = 372,                 /* SET  */
    SQL_TBL = 373,                 /* TBL  */
    SQL_TOP = 374,                 /* TOP  */
    SQL_AS = 375,                  /* AS  */
    SQL_BY = 376,                  /* BY  */
    SQL_IF = 377,                  /* IF  */
    SQL_IN = 378,                  /* IN  */
    SQL_IS = 379,                  /* IS  */
    SQL_OF = 380,                  /* OF  */
    SQL_ON = 381,                  /* ON  */
    SQL_OR = 382,                  /* OR  */
    SQL_TO = 383,                  /* TO  */
    SQL_ARRAY = 384,               /* ARRAY  */
    SQL_CONCAT = 385,              /* CONCAT  */
    SQL_ILIKE = 386,               /* ILIKE  */
    SQL_SECOND = 387,              /* SECOND  */
    SQL_MINUTE = 388,              /* MINUTE  */
    SQL_HOUR = 389,                /* HOUR  */
    SQL_DAY = 390,                 /* DAY  */
    SQL_MONTH = 391,               /* MONTH  */
    SQL_YEAR = 392,                /* YEAR  */
    SQL_TRUE = 393,                /* TRUE  */
    SQL_FALSE = 394,               /* FALSE  */
    SQL_FOREIGN = 395,             /* FOREIGN  */
    SQL_REFERENCES = 396,          /* REFERENCES  */
    SQL_ACTION = 397,              /* ACTION  */
    SQL_JSON = 398,                /* JSON  */
    SQL_STORED = 399,              /* STORED  */
    SQL_RECURSIVE = 400,           /* RECURSIVE  */
    SQL_TRASH = 401,               /* TRASH  */
    SQL_ARROW = 402,               /* ARROW  */
    SQL_CUME_DIST = 403,           /* CUME_DIST  */
    SQL_DENSE_RANK = 404,          /* DENSE_RANK  */
    SQL_PERCENT_RANK = 405,        /* PERCENT_RANK  */
    SQL_RANK = 406,                /* RANK  */
    SQL_ROW_NUMBER = 407,          /* ROW_NUMBER  */
    SQL_LAG = 408,                 /* LAG  */
    SQL_LEAD = 409,                /* LEAD  */
    SQL_NTILE = 410,               /* NTILE  */
    SQL_FIRST_VALUE = 411,         /* FIRST_VALUE  */
    SQL_LAST_VALUE = 412,          /* LAST_VALUE  */
    SQL_NTH_VALUE = 413,           /* NTH_VALUE  */
    SQL_AVG = 414,                 /* AVG  */
    SQL_MAX = 415,                 /* MAX  */
    SQL_MIN = 416,                 /* MIN  */
    SQL_SUM = 417,                 /* SUM  */
    SQL_COUNT = 418,               /* COUNT  */
    SQL_PRAGMA = 419,              /* PRAGMA  */
    SQL_REINDEX = 420,             /* REINDEX  */
    SQL_GENERATED = 421,           /* GENERATED  */
    SQL_ALWAYS = 422,              /* ALWAYS  */
    SQL_CHECK = 423,               /* CHECK  */
    SQL_CONFLICT = 424,            /* CONFLICT  */
    SQL_IGNORE = 425,              /* IGNORE  */
    SQL_REPLACE = 426,             /* REPLACE  */
    SQL_ROLLBACK = 427,            /* ROLLBACK  */
    SQL_ABORT = 428,               /* ABORT  */
    SQL_FAIL = 429,                /* FAIL  */
    SQL_AUTOINCR = 430,            /* AUTOINCR  */
    SQL_BEGIN = 431,               /* BEGIN  */
    SQL_TRIGGER = 432,             /* TRIGGER  */
    SQL_TEMP = 433,                /* TEMP  */
    SQL_INSTEAD = 434,             /* INSTEAD  */
    SQL_EACH = 435,                /* EACH  */
    SQL_ROW = 436,                 /* ROW  */
    SQL_OVER = 437,                /* OVER  */
    SQL_FILTER = 438,              /* FILTER  */
    SQL_PARTITION = 439,           /* PARTITION  */
    SQL_CURRENT = 440,             /* CURRENT  */
    SQL_EXCLUDE = 441,             /* EXCLUDE  */
    SQL_FOLLOWING = 442,           /* FOLLOWING  */
    SQL_GROUPS = 443,              /* GROUPS  */
    SQL_NO = 444,                  /* NO  */
    SQL_OTHERS = 445,              /* OTHERS  */
    SQL_PRECEDING = 446,           /* PRECEDING  */
    SQL_RANGE = 447,               /* RANGE  */
    SQL_ROWS = 448,                /* ROWS  */
    SQL_TIES = 449,                /* TIES  */
    SQL_UNBOUNDED = 450,           /* UNBOUNDED  */
    SQL_WINDOW = 451,              /* WINDOW  */
    SQL_ATTACH = 452,              /* ATTACH  */
    SQL_DETACH = 453,              /* DETACH  */
    SQL_DATABASE = 454,            /* DATABASE  */
    SQL_INDEXED = 455,             /* INDEXED  */
    SQL_CAST = 456,                /* CAST  */
    SQL_SAVEPOINT = 457,           /* SAVEPOINT  */
    SQL_RELEASE = 458,             /* RELEASE  */
    SQL_VACUUM = 459,              /* VACUUM  */
    SQL_TRANSACTION = 460,         /* TRANSACTION  */
    SQL_DEFFERED = 461,            /* DEFFERED  */
    SQL_EXCLUSIVE = 462,           /* EXCLUSIVE  */
    SQL_IMEDIATE = 463,            /* IMEDIATE  */
    SQL_COMMIT = 464,              /* COMMIT  */
    SQL_GLOB = 465,                /* GLOB  */
    SQL_MATCH = 466,               /* MATCH  */
    SQL_REGEX = 467,               /* REGEX  */
    SQL_NOTHING = 468,             /* NOTHING  */
    SQL_NULLS = 469,               /* NULLS  */
    SQL_LAST = 470,                /* LAST  */
    SQL_FIRST = 471,               /* FIRST  */
    SQL_DO = 472,                  /* DO  */
    SQL_COLLATE = 473,             /* COLLATE  */
    SQL_EQUALS = 474,              /* EQUALS  */
    SQL_NOTEQUALS = 475,           /* NOTEQUALS  */
    SQL_LESS = 476,                /* LESS  */
    SQL_GREATER = 477,             /* GREATER  */
    SQL_LESSEQ = 478,              /* LESSEQ  */
    SQL_GREATEREQ = 479,           /* GREATEREQ  */
    SQL_NOTNULL = 480,             /* NOTNULL  */
    SQL_UMINUS = 481               /* UMINUS  */
  };
  typedef enum hsql_tokentype hsql_token_kind_t;
#endif

/* Value type.  */
#if ! defined HSQL_STYPE && ! defined HSQL_STYPE_IS_DECLARED
#line 92 "bison_parser.y"
union HSQL_STYPE
{
#line 92 "bison_parser.y"

    double fval;
    int64_t ival;
    char* sval;
    uintmax_t uval;
    bool bval;

    Action_type* Action_type_t;
    opt_ForeignKeylist* opt_ForeignKeylist_t;
    ForeignKeylist* ForeignKeylist_t;
    ForeignKey* ForeignKey_t;
    ColumnInParen_ForeignKey* Column_In_Paren_ForeignKey_t;
    ColumnInParen_References* Column_In_Paren_References_t;
    ForeignKeyColumn* ForeignKeyColumn_t;
    ForeignKeyRef* ForeignKeyRef_t;
    FkNoOptstmt* FkNoOptstmt_t;
    opt_Actiontypelist* opt_Actiontypelist_t;
    Action_typelist* Action_typelist_t;
    CreateInparan* CreateInparan_t;
    Jsonexpr_all* Jsonexpr_all_t;
    Jsonpath* Jsonpath_t;
    Jsondata* Jsondata_t;
    json_literal* json_literal_t;
    json_pathliteral* json_pathliteral_t;
    opt_generatedarg* opt_generatedarg_t;
    WithRecursiveClause* WithRecursiveClause_t;
    JsonExpr* json_expr_t;
    WithRecDescList* with_rec_desc_list_t;
    WithRecDesc* with_recursive_description_t;
    WithRecursiveSelect* with_recursive_select_t;
    InitSelect* init_select_t;
    OptRecursiveSelect* opt_recursive_select_t;
	SelListAlias* select_list_essential_alias_t;
	ExprListAlias* expr_list_essential_alias_t;
	ExprEssentialAlias* expr_essential_alias_t;
    FtsQueryLiteral* fts_query_literal_t;
    WindowWithOrder* window_with_order_t;
    WindowNoOrder* window_no_order_t;
    Order*  order_t;
    OverClause* over_clause_t;
    OverClauseWithOrder* over_clause_with_order_t;
    OverClauseNoOrder* over_clause_no_order_t;
    WindowFuncNoArg* window_func_no_arg_t;
    WindowFunc* window_func_t;
    AggregationFunc* aggregation_func_t;
    ColumnDefListNoType* column_def_list_no_type_t;
    ColumnDefNoType* column_def_no_type_t;
    ColumnNameList_ForeignKey* ColumnNameList_ForeignKey_t;
    ColumnNameList_References* ColumnNameList_References_t;
    ColumnName_ForeignKey* ColumnName_ForeignKey_t;
    ColumnName_References* ColumnName_References_t;

    Program* program_t;
    StatementList* statement_list_t;
    Statement* statement_t;
    PreparableStatement* preparable_statement_t;
    OptionalHints* optional_hints_t;
    HintList* hint_list_t;
    Hint* hint_t;
    PrepareStatement* prepare_statement_t;
    PrepareTargetQuery* prepare_target_query_t;
    ExecuteStatement* execute_statement_t;
    ImportStatement* import_statement_t;
    ImportFileType* import_file_type_t;
    FilePath* file_path_t;
    TableRefCommaList* table_ref_commalist_t;
    ShowStatement* show_statement_t;
    CreateStatement* create_statement_t;
    OptNotExists* opt_not_exists_t;
    ColumnDefCommaList* column_def_comma_list_t;
    ColumnDef* column_def_t;
    ColumnType* column_type_t;
    //OptColumnNullable* opt_column_nullable_t;
    DropStatement* drop_statement_t;
    OptExists* opt_exists_t;
    DeleteStatement* delete_statement_t;
    InsertStatement* insert_statement_t;
    OptColumnList* opt_column_list_t;
    UpdateStatement* update_statement_t;
    UpdateClauseCommalist* update_clause_commalist_t;
    UpdateClause* update_clause_t;
    SelectStatement* select_statement_t;
    SelectWithParen* select_with_paren_t;
    SelectParenOrClause* select_paren_or_clause_t;
    SelectNoParen* select_no_paren_t;
    SetOperator* set_operator_t;
    SetType* set_type_t;
    OptAll* opt_all_t;
    IdentCommaList* ident_commalist_t;
    SelectClause* select_clause_t;
    OptDistinct* opt_distinct_t;
    SelectList* select_list_t;
    OptFromClause* opt_from_clause_t;
    FromClause* from_clause_t;
    OptWhere* opt_where_t;
    OptGroup* opt_group_t;
    OptHaving* opt_having_t;
    OptOrder* opt_order_t;
    OrderList* order_list_t;
    OrderDesc* order_desc_t;
    OptOrderType* opt_order_type_t;
    OptTop* opt_top_t;
    OptLimit* opt_limit_t;
    ExprList* expr_list_t;
    OptLiteralList* opt_literal_list_t;
    LiteralList* literal_list_t;
    ExprAlias* expr_alias_t;
    Expr* expr_t;
    Operand* operand_t;
    ScalarExpr* scalar_expr_t;
    UnaryExpr* unary_expr_t;
    BinaryExpr* binary_expr_t;
    LogicExpr* logic_expr_t;
    InExpr* in_expr_t;
    CompExpr * comp_expr_t;
    CaseExpr* case_expr_t;
    CaseClause* case_clause_t;
    CaseList* case_list_t;
    ExistsExpr* exists_expr_t;
    FunctionExpr* function_expr_t;
    ExtractExpr* extract_expr_t;
    DatetimeField* datetime_field_t;
    ArrayExpr* array_expr_t;
    ArrayIndex* array_index_t;
    BetweenExpr* between_expr_t;
    ColumnName* column_name_t;
    Literal* literal_t;
    StringLiteral* string_literal_t;
    BoolLiteral* bool_literal_t;
    NumLiteral* num_literal_t;
    IntLiteral* int_literal_t;
    NullLiteral* null_literal_t;
    ParamExpr* param_expr_t;
    TableRef* table_ref_t;
    TableRefAtomic* table_ref_atomic_t;
    NonjoinTableRefAtomic* nonjoin_table_ref_atomic_t;
    TableRefName* table_ref_name_t;
    TableRefNameNoAlias* table_ref_name_no_alias_t;
    TableName* table_name_t;
    TableAlias* table_alias_t;
    OptTableAlias* opt_table_alias_t;
    Alias* alias_t;
    OptAlias* opt_alias_t;
    OptWithClause* opt_with_clause_t;
    WithClause* with_clause_t;
    WithDescriptionList* with_description_list_t;
    WithDescription* with_description_t;
    JoinClause* join_clause_t;
    OptJoinType* opt_join_type_t;
    JoinCondition* join_condition_t;
    OptSemicolon* opt_semicolon_t;
    Identifier* identifier_t;
    Cmd * cmd_t;
    CmdAttach * cmd_attach_t;
    CmdDetach * cmd_detach_t;
    CmdReindex * cmd_reindex_t;
    CmdAnalyze * cmd_analyze_t;
    CmdPragma * cmd_pragma_t;
    PragmaKey * pragma_key_t;
    PragmaValue * pragma_value_t;
    PragmaName * pragma_name_t;
    SchemaName * schema_name_t;
    OptColumnArglist*	opt_column_arglist_t;
	ColumnArglist*	column_arglist_t;
	ColumnArg*	column_arg_t;
	OptOnConflict*	opt_on_conflict_t;
	ResolveType*	resolve_type_t;
	OptAutoinc*	opt_autoinc_t;
	OptUnique*	opt_unique_t;
	IndexName*	index_name_t;
	TriggerDeclare*	trigger_declare_t;
	OptTmp*	opt_tmp_t;
	TriggerName*	trigger_name_t;
	OptTriggerTime*	opt_trigger_time_t;
	TriggerEvent*	trigger_event_t;
	OptOfColumnList*	opt_of_column_list_t;
	OptForEach*	opt_for_each_t;
	OptWhen*	opt_when_t;
	TriggerCmdList*	trigger_cmd_list_t;
	TriggerCmd*	trigger_cmd_t;
	ModuleName*	module_name_t;
	OptOverClause*	opt_over_clause_t;
	OptFilterClause*	opt_filter_clause_t;
	WindowClause*	window_clause_t;
	WindowDefnList*	window_defn_list_t;
	WindowDefn*	window_defn_t;
	Window*	window_t;
	OptBaseWindowName*	opt_base_window_name_t;
	OptFrame*	opt_frame_t;
	RangeOrRows*	range_or_rows_t;
	FrameBoundS*	frame_bound_s_t;
	FrameBoundE*	frame_bound_e_t;
	FrameBound*	frame_bound_t;
	OptFrameExclude*	opt_frame_exclude_t;
	FrameExclude*	frame_exclude_t;
    InsertType * insert_type_t;
    SuperList * super_list_t;
    JoinKw* join_kw_t;

    TablePrefix * table_prefix_t;
    JoinOp * join_op_t;
    OptIndex * opt_index_t;
    OptOn * opt_on_t;
    OptUsing * opt_using_t;

    CastExpr * cast_expr_t;
    AlterStatement * alter_statement_t;
    OptColumn * opt_column_t;
    CmdRelease * cmd_release_t;
    SavepointName * savepoint_name_t;
    VacuumStatement * vacuum_statement_t;
    OptSchemaName * opt_schema_name_t;
    RollbackStatement * rollback_statement_t;
    OptTransaction * opt_transaction_t;
    OptToSavepoint * opt_to_savepoint_t;
    BeginStatement * begin_statement_t;
    CommitStatement * commit_statement_t;
    UpsertClause * upsert_clause_t;
    IndexedColumnList * indexed_column_list_t;
    IndexedColumn * indexed_column_t;
    OptCollate * opt_collate_t;
    AssignList * assign_list_t;
    OptNull * opt_null_t;
    AssignClause * assign_clause_t;
    ColumnNameList * column_name_list_t;
    CollationName * collation_name_t;
    OptUpsertClause * opt_upsert_clause_t;

    std::vector<char*>* str_vec;
    std::vector<TableRef*>* table_vec;
    std::vector<ColumnDef*>* column_vec;
    std::vector<UpdateClause*>* update_vec;
    std::vector<Expr*>* expr_vec;
    std::vector<OrderDesc*>* order_vec;
    std::vector<WithDescription*>* with_description_vec;

#line 564 "bison_parser.h"

};
#line 92 "bison_parser.y"
typedef union HSQL_STYPE HSQL_STYPE;
# define HSQL_STYPE_IS_TRIVIAL 1
# define HSQL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined HSQL_LTYPE && ! defined HSQL_LTYPE_IS_DECLARED
typedef struct HSQL_LTYPE HSQL_LTYPE;
struct HSQL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define HSQL_LTYPE_IS_DECLARED 1
# define HSQL_LTYPE_IS_TRIVIAL 1
#endif




int hsql_parse (Program * result, yyscan_t scanner);


#endif /* !YY_HSQL_BISON_PARSER_H_INCLUDED  */
