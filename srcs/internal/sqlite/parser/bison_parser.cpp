/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HSQL_STYPE
#define YYLTYPE         HSQL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         hsql_parse
#define yylex           hsql_lex
#define yyerror         hsql_error
#define yydebug         hsql_debug
#define yynerrs         hsql_nerrs

/* First part of user prologue.  */
#line 1 "bison_parser.y"

/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 *
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "bison_parser.h"
#include "flex_lexer.h"

#include <stdio.h>
#include <string.h>


int yyerror(YYLTYPE* llocp, Program * result, yyscan_t scanner, const char *msg);


#line 102 "bison_parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bison_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_IDENTIFIER = 4,                 /* IDENTIFIER  */
  YYSYMBOL_ESCAPED_CURLY_LITERAL = 5,      /* ESCAPED_CURLY_LITERAL  */
  YYSYMBOL_ESCAPED_BRACKET_LITERAL = 6,    /* ESCAPED_BRACKET_LITERAL  */
  YYSYMBOL_JSONPATH_STRING = 7,            /* JSONPATH_STRING  */
  YYSYMBOL_FLOATVAL = 8,                   /* FLOATVAL  */
  YYSYMBOL_INTVAL = 9,                     /* INTVAL  */
  YYSYMBOL_DEALLOCATE = 10,                /* DEALLOCATE  */
  YYSYMBOL_PARAMETERS = 11,                /* PARAMETERS  */
  YYSYMBOL_INTERSECT = 12,                 /* INTERSECT  */
  YYSYMBOL_TEMPORARY = 13,                 /* TEMPORARY  */
  YYSYMBOL_TIMESTAMP = 14,                 /* TIMESTAMP  */
  YYSYMBOL_DISTINCT = 15,                  /* DISTINCT  */
  YYSYMBOL_NVARCHAR = 16,                  /* NVARCHAR  */
  YYSYMBOL_RESTRICT = 17,                  /* RESTRICT  */
  YYSYMBOL_TRUNCATE = 18,                  /* TRUNCATE  */
  YYSYMBOL_ANALYZE = 19,                   /* ANALYZE  */
  YYSYMBOL_BETWEEN = 20,                   /* BETWEEN  */
  YYSYMBOL_CASCADE = 21,                   /* CASCADE  */
  YYSYMBOL_COLUMNS = 22,                   /* COLUMNS  */
  YYSYMBOL_CONTROL = 23,                   /* CONTROL  */
  YYSYMBOL_DEFAULT = 24,                   /* DEFAULT  */
  YYSYMBOL_EXECUTE = 25,                   /* EXECUTE  */
  YYSYMBOL_EXPLAIN = 26,                   /* EXPLAIN  */
  YYSYMBOL_INTEGER = 27,                   /* INTEGER  */
  YYSYMBOL_NATURAL = 28,                   /* NATURAL  */
  YYSYMBOL_PREPARE = 29,                   /* PREPARE  */
  YYSYMBOL_PRIMARY = 30,                   /* PRIMARY  */
  YYSYMBOL_SCHEMAS = 31,                   /* SCHEMAS  */
  YYSYMBOL_SPATIAL = 32,                   /* SPATIAL  */
  YYSYMBOL_VARCHAR = 33,                   /* VARCHAR  */
  YYSYMBOL_VIRTUAL = 34,                   /* VIRTUAL  */
  YYSYMBOL_DESCRIBE = 35,                  /* DESCRIBE  */
  YYSYMBOL_BEFORE = 36,                    /* BEFORE  */
  YYSYMBOL_COLUMN = 37,                    /* COLUMN  */
  YYSYMBOL_CREATE = 38,                    /* CREATE  */
  YYSYMBOL_DELETE = 39,                    /* DELETE  */
  YYSYMBOL_DIRECT = 40,                    /* DIRECT  */
  YYSYMBOL_DOUBLE = 41,                    /* DOUBLE  */
  YYSYMBOL_ESCAPE = 42,                    /* ESCAPE  */
  YYSYMBOL_EXCEPT = 43,                    /* EXCEPT  */
  YYSYMBOL_EXISTS = 44,                    /* EXISTS  */
  YYSYMBOL_EXTRACT = 45,                   /* EXTRACT  */
  YYSYMBOL_GLOBAL = 46,                    /* GLOBAL  */
  YYSYMBOL_HAVING = 47,                    /* HAVING  */
  YYSYMBOL_IMPORT = 48,                    /* IMPORT  */
  YYSYMBOL_INSERT = 49,                    /* INSERT  */
  YYSYMBOL_ISNULL = 50,                    /* ISNULL  */
  YYSYMBOL_OFFSET = 51,                    /* OFFSET  */
  YYSYMBOL_RENAME = 52,                    /* RENAME  */
  YYSYMBOL_SCHEMA = 53,                    /* SCHEMA  */
  YYSYMBOL_SELECT = 54,                    /* SELECT  */
  YYSYMBOL_SORTED = 55,                    /* SORTED  */
  YYSYMBOL_TABLES = 56,                    /* TABLES  */
  YYSYMBOL_UNIQUE = 57,                    /* UNIQUE  */
  YYSYMBOL_UNLOAD = 58,                    /* UNLOAD  */
  YYSYMBOL_UPDATE = 59,                    /* UPDATE  */
  YYSYMBOL_VALUES = 60,                    /* VALUES  */
  YYSYMBOL_AFTER = 61,                     /* AFTER  */
  YYSYMBOL_ALTER = 62,                     /* ALTER  */
  YYSYMBOL_CROSS = 63,                     /* CROSS  */
  YYSYMBOL_DELTA = 64,                     /* DELTA  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_GROUP = 66,                     /* GROUP  */
  YYSYMBOL_INDEX = 67,                     /* INDEX  */
  YYSYMBOL_INNER = 68,                     /* INNER  */
  YYSYMBOL_LIMIT = 69,                     /* LIMIT  */
  YYSYMBOL_LOCAL = 70,                     /* LOCAL  */
  YYSYMBOL_MERGE = 71,                     /* MERGE  */
  YYSYMBOL_MINUS = 72,                     /* MINUS  */
  YYSYMBOL_ORDER = 73,                     /* ORDER  */
  YYSYMBOL_OUTER = 74,                     /* OUTER  */
  YYSYMBOL_RIGHT = 75,                     /* RIGHT  */
  YYSYMBOL_TABLE = 76,                     /* TABLE  */
  YYSYMBOL_UNION = 77,                     /* UNION  */
  YYSYMBOL_USING = 78,                     /* USING  */
  YYSYMBOL_WHERE = 79,                     /* WHERE  */
  YYSYMBOL_CALL = 80,                      /* CALL  */
  YYSYMBOL_CASE = 81,                      /* CASE  */
  YYSYMBOL_CHAR = 82,                      /* CHAR  */
  YYSYMBOL_DATE = 83,                      /* DATE  */
  YYSYMBOL_DESC = 84,                      /* DESC  */
  YYSYMBOL_DROP = 85,                      /* DROP  */
  YYSYMBOL_ELSE = 86,                      /* ELSE  */
  YYSYMBOL_FILE = 87,                      /* FILE  */
  YYSYMBOL_FROM = 88,                      /* FROM  */
  YYSYMBOL_FULL = 89,                      /* FULL  */
  YYSYMBOL_HASH = 90,                      /* HASH  */
  YYSYMBOL_HINT = 91,                      /* HINT  */
  YYSYMBOL_INTO = 92,                      /* INTO  */
  YYSYMBOL_JOIN = 93,                      /* JOIN  */
  YYSYMBOL_LEFT = 94,                      /* LEFT  */
  YYSYMBOL_LIKE = 95,                      /* LIKE  */
  YYSYMBOL_LOAD = 96,                      /* LOAD  */
  YYSYMBOL_NULL = 97,                      /* NULL  */
  YYSYMBOL_PLAN = 98,                      /* PLAN  */
  YYSYMBOL_SHOW = 99,                      /* SHOW  */
  YYSYMBOL_TEXT = 100,                     /* TEXT  */
  YYSYMBOL_THEN = 101,                     /* THEN  */
  YYSYMBOL_TIME = 102,                     /* TIME  */
  YYSYMBOL_VIEW = 103,                     /* VIEW  */
  YYSYMBOL_WHEN = 104,                     /* WHEN  */
  YYSYMBOL_WITH = 105,                     /* WITH  */
  YYSYMBOL_ADD = 106,                      /* ADD  */
  YYSYMBOL_ALL = 107,                      /* ALL  */
  YYSYMBOL_AND = 108,                      /* AND  */
  YYSYMBOL_ASC = 109,                      /* ASC  */
  YYSYMBOL_CSV = 110,                      /* CSV  */
  YYSYMBOL_END = 111,                      /* END  */
  YYSYMBOL_FOR = 112,                      /* FOR  */
  YYSYMBOL_INT = 113,                      /* INT  */
  YYSYMBOL_KEY = 114,                      /* KEY  */
  YYSYMBOL_NOT = 115,                      /* NOT  */
  YYSYMBOL_OFF = 116,                      /* OFF  */
  YYSYMBOL_SET = 117,                      /* SET  */
  YYSYMBOL_TBL = 118,                      /* TBL  */
  YYSYMBOL_TOP = 119,                      /* TOP  */
  YYSYMBOL_AS = 120,                       /* AS  */
  YYSYMBOL_BY = 121,                       /* BY  */
  YYSYMBOL_IF = 122,                       /* IF  */
  YYSYMBOL_IN = 123,                       /* IN  */
  YYSYMBOL_IS = 124,                       /* IS  */
  YYSYMBOL_OF = 125,                       /* OF  */
  YYSYMBOL_ON = 126,                       /* ON  */
  YYSYMBOL_OR = 127,                       /* OR  */
  YYSYMBOL_TO = 128,                       /* TO  */
  YYSYMBOL_ARRAY = 129,                    /* ARRAY  */
  YYSYMBOL_CONCAT = 130,                   /* CONCAT  */
  YYSYMBOL_ILIKE = 131,                    /* ILIKE  */
  YYSYMBOL_SECOND = 132,                   /* SECOND  */
  YYSYMBOL_MINUTE = 133,                   /* MINUTE  */
  YYSYMBOL_HOUR = 134,                     /* HOUR  */
  YYSYMBOL_DAY = 135,                      /* DAY  */
  YYSYMBOL_MONTH = 136,                    /* MONTH  */
  YYSYMBOL_YEAR = 137,                     /* YEAR  */
  YYSYMBOL_TRUE = 138,                     /* TRUE  */
  YYSYMBOL_FALSE = 139,                    /* FALSE  */
  YYSYMBOL_FOREIGN = 140,                  /* FOREIGN  */
  YYSYMBOL_REFERENCES = 141,               /* REFERENCES  */
  YYSYMBOL_ACTION = 142,                   /* ACTION  */
  YYSYMBOL_JSON = 143,                     /* JSON  */
  YYSYMBOL_STORED = 144,                   /* STORED  */
  YYSYMBOL_RECURSIVE = 145,                /* RECURSIVE  */
  YYSYMBOL_TRASH = 146,                    /* TRASH  */
  YYSYMBOL_ARROW = 147,                    /* ARROW  */
  YYSYMBOL_CUME_DIST = 148,                /* CUME_DIST  */
  YYSYMBOL_DENSE_RANK = 149,               /* DENSE_RANK  */
  YYSYMBOL_PERCENT_RANK = 150,             /* PERCENT_RANK  */
  YYSYMBOL_RANK = 151,                     /* RANK  */
  YYSYMBOL_ROW_NUMBER = 152,               /* ROW_NUMBER  */
  YYSYMBOL_LAG = 153,                      /* LAG  */
  YYSYMBOL_LEAD = 154,                     /* LEAD  */
  YYSYMBOL_NTILE = 155,                    /* NTILE  */
  YYSYMBOL_FIRST_VALUE = 156,              /* FIRST_VALUE  */
  YYSYMBOL_LAST_VALUE = 157,               /* LAST_VALUE  */
  YYSYMBOL_NTH_VALUE = 158,                /* NTH_VALUE  */
  YYSYMBOL_AVG = 159,                      /* AVG  */
  YYSYMBOL_MAX = 160,                      /* MAX  */
  YYSYMBOL_MIN = 161,                      /* MIN  */
  YYSYMBOL_SUM = 162,                      /* SUM  */
  YYSYMBOL_COUNT = 163,                    /* COUNT  */
  YYSYMBOL_PRAGMA = 164,                   /* PRAGMA  */
  YYSYMBOL_REINDEX = 165,                  /* REINDEX  */
  YYSYMBOL_GENERATED = 166,                /* GENERATED  */
  YYSYMBOL_ALWAYS = 167,                   /* ALWAYS  */
  YYSYMBOL_CHECK = 168,                    /* CHECK  */
  YYSYMBOL_CONFLICT = 169,                 /* CONFLICT  */
  YYSYMBOL_IGNORE = 170,                   /* IGNORE  */
  YYSYMBOL_REPLACE = 171,                  /* REPLACE  */
  YYSYMBOL_ROLLBACK = 172,                 /* ROLLBACK  */
  YYSYMBOL_ABORT = 173,                    /* ABORT  */
  YYSYMBOL_FAIL = 174,                     /* FAIL  */
  YYSYMBOL_AUTOINCR = 175,                 /* AUTOINCR  */
  YYSYMBOL_BEGIN = 176,                    /* BEGIN  */
  YYSYMBOL_TRIGGER = 177,                  /* TRIGGER  */
  YYSYMBOL_TEMP = 178,                     /* TEMP  */
  YYSYMBOL_INSTEAD = 179,                  /* INSTEAD  */
  YYSYMBOL_EACH = 180,                     /* EACH  */
  YYSYMBOL_ROW = 181,                      /* ROW  */
  YYSYMBOL_OVER = 182,                     /* OVER  */
  YYSYMBOL_FILTER = 183,                   /* FILTER  */
  YYSYMBOL_PARTITION = 184,                /* PARTITION  */
  YYSYMBOL_CURRENT = 185,                  /* CURRENT  */
  YYSYMBOL_EXCLUDE = 186,                  /* EXCLUDE  */
  YYSYMBOL_FOLLOWING = 187,                /* FOLLOWING  */
  YYSYMBOL_GROUPS = 188,                   /* GROUPS  */
  YYSYMBOL_NO = 189,                       /* NO  */
  YYSYMBOL_OTHERS = 190,                   /* OTHERS  */
  YYSYMBOL_PRECEDING = 191,                /* PRECEDING  */
  YYSYMBOL_RANGE = 192,                    /* RANGE  */
  YYSYMBOL_ROWS = 193,                     /* ROWS  */
  YYSYMBOL_TIES = 194,                     /* TIES  */
  YYSYMBOL_UNBOUNDED = 195,                /* UNBOUNDED  */
  YYSYMBOL_WINDOW = 196,                   /* WINDOW  */
  YYSYMBOL_ATTACH = 197,                   /* ATTACH  */
  YYSYMBOL_DETACH = 198,                   /* DETACH  */
  YYSYMBOL_DATABASE = 199,                 /* DATABASE  */
  YYSYMBOL_INDEXED = 200,                  /* INDEXED  */
  YYSYMBOL_CAST = 201,                     /* CAST  */
  YYSYMBOL_SAVEPOINT = 202,                /* SAVEPOINT  */
  YYSYMBOL_RELEASE = 203,                  /* RELEASE  */
  YYSYMBOL_VACUUM = 204,                   /* VACUUM  */
  YYSYMBOL_TRANSACTION = 205,              /* TRANSACTION  */
  YYSYMBOL_DEFFERED = 206,                 /* DEFFERED  */
  YYSYMBOL_EXCLUSIVE = 207,                /* EXCLUSIVE  */
  YYSYMBOL_IMEDIATE = 208,                 /* IMEDIATE  */
  YYSYMBOL_COMMIT = 209,                   /* COMMIT  */
  YYSYMBOL_GLOB = 210,                     /* GLOB  */
  YYSYMBOL_MATCH = 211,                    /* MATCH  */
  YYSYMBOL_REGEX = 212,                    /* REGEX  */
  YYSYMBOL_NOTHING = 213,                  /* NOTHING  */
  YYSYMBOL_NULLS = 214,                    /* NULLS  */
  YYSYMBOL_LAST = 215,                     /* LAST  */
  YYSYMBOL_FIRST = 216,                    /* FIRST  */
  YYSYMBOL_DO = 217,                       /* DO  */
  YYSYMBOL_COLLATE = 218,                  /* COLLATE  */
  YYSYMBOL_219_ = 219,                     /* '='  */
  YYSYMBOL_EQUALS = 220,                   /* EQUALS  */
  YYSYMBOL_NOTEQUALS = 221,                /* NOTEQUALS  */
  YYSYMBOL_222_ = 222,                     /* '<'  */
  YYSYMBOL_223_ = 223,                     /* '>'  */
  YYSYMBOL_LESS = 224,                     /* LESS  */
  YYSYMBOL_GREATER = 225,                  /* GREATER  */
  YYSYMBOL_LESSEQ = 226,                   /* LESSEQ  */
  YYSYMBOL_GREATEREQ = 227,                /* GREATEREQ  */
  YYSYMBOL_NOTNULL = 228,                  /* NOTNULL  */
  YYSYMBOL_229_ = 229,                     /* '+'  */
  YYSYMBOL_230_ = 230,                     /* '-'  */
  YYSYMBOL_231_ = 231,                     /* '*'  */
  YYSYMBOL_232_ = 232,                     /* '/'  */
  YYSYMBOL_233_ = 233,                     /* '%'  */
  YYSYMBOL_234_ = 234,                     /* '^'  */
  YYSYMBOL_UMINUS = 235,                   /* UMINUS  */
  YYSYMBOL_236_ = 236,                     /* '['  */
  YYSYMBOL_237_ = 237,                     /* ']'  */
  YYSYMBOL_238_ = 238,                     /* '('  */
  YYSYMBOL_239_ = 239,                     /* ')'  */
  YYSYMBOL_240_ = 240,                     /* '.'  */
  YYSYMBOL_241_ = 241,                     /* ';'  */
  YYSYMBOL_242_ = 242,                     /* ','  */
  YYSYMBOL_243_ = 243,                     /* '?'  */
  YYSYMBOL_YYACCEPT = 244,                 /* $accept  */
  YYSYMBOL_input = 245,                    /* input  */
  YYSYMBOL_statement_list = 246,           /* statement_list  */
  YYSYMBOL_statement = 247,                /* statement  */
  YYSYMBOL_cmd = 248,                      /* cmd  */
  YYSYMBOL_cmd_release = 249,              /* cmd_release  */
  YYSYMBOL_savepoint_name = 250,           /* savepoint_name  */
  YYSYMBOL_cmd_pragma = 251,               /* cmd_pragma  */
  YYSYMBOL_cmd_reindex = 252,              /* cmd_reindex  */
  YYSYMBOL_cmd_analyze = 253,              /* cmd_analyze  */
  YYSYMBOL_cmd_attach = 254,               /* cmd_attach  */
  YYSYMBOL_cmd_detach = 255,               /* cmd_detach  */
  YYSYMBOL_pragma_key = 256,               /* pragma_key  */
  YYSYMBOL_pragma_value = 257,             /* pragma_value  */
  YYSYMBOL_schema_name = 258,              /* schema_name  */
  YYSYMBOL_pragma_name = 259,              /* pragma_name  */
  YYSYMBOL_preparable_statement = 260,     /* preparable_statement  */
  YYSYMBOL_rollback_statement = 261,       /* rollback_statement  */
  YYSYMBOL_opt_transaction = 262,          /* opt_transaction  */
  YYSYMBOL_opt_to_savepoint = 263,         /* opt_to_savepoint  */
  YYSYMBOL_vacuum_statement = 264,         /* vacuum_statement  */
  YYSYMBOL_opt_schema_name = 265,          /* opt_schema_name  */
  YYSYMBOL_begin_statement = 266,          /* begin_statement  */
  YYSYMBOL_commit_statement = 267,         /* commit_statement  */
  YYSYMBOL_opt_upsert_clause = 268,        /* opt_upsert_clause  */
  YYSYMBOL_upsert_clause = 269,            /* upsert_clause  */
  YYSYMBOL_indexed_column_list = 270,      /* indexed_column_list  */
  YYSYMBOL_indexed_column = 271,           /* indexed_column  */
  YYSYMBOL_opt_collate = 272,              /* opt_collate  */
  YYSYMBOL_assign_list = 273,              /* assign_list  */
  YYSYMBOL_opt_null = 274,                 /* opt_null  */
  YYSYMBOL_assign_clause = 275,            /* assign_clause  */
  YYSYMBOL_column_name_list = 276,         /* column_name_list  */
  YYSYMBOL_collation_name = 277,           /* collation_name  */
  YYSYMBOL_opt_hints = 278,                /* opt_hints  */
  YYSYMBOL_hint_list = 279,                /* hint_list  */
  YYSYMBOL_hint = 280,                     /* hint  */
  YYSYMBOL_prepare_statement = 281,        /* prepare_statement  */
  YYSYMBOL_prepare_target_query = 282,     /* prepare_target_query  */
  YYSYMBOL_execute_statement = 283,        /* execute_statement  */
  YYSYMBOL_import_statement = 284,         /* import_statement  */
  YYSYMBOL_import_file_type = 285,         /* import_file_type  */
  YYSYMBOL_file_path = 286,                /* file_path  */
  YYSYMBOL_show_statement = 287,           /* show_statement  */
  YYSYMBOL_alter_statement = 288,          /* alter_statement  */
  YYSYMBOL_opt_column = 289,               /* opt_column  */
  YYSYMBOL_create_statement = 290,         /* create_statement  */
  YYSYMBOL_column_def_list_no_type = 291,  /* column_def_list_no_type  */
  YYSYMBOL_column_def_no_type = 292,       /* column_def_no_type  */
  YYSYMBOL_opt_tmp = 293,                  /* opt_tmp  */
  YYSYMBOL_CreateInparan = 294,            /* CreateInparan  */
  YYSYMBOL_opt_ForeignKeylist = 295,       /* opt_ForeignKeylist  */
  YYSYMBOL_ForeignKeylist = 296,           /* ForeignKeylist  */
  YYSYMBOL_ForeignKey = 297,               /* ForeignKey  */
  YYSYMBOL_FkNoOptstmt = 298,              /* FkNoOptstmt  */
  YYSYMBOL_ForeignKeyColumn = 299,         /* ForeignKeyColumn  */
  YYSYMBOL_ForeignKeyRef = 300,            /* ForeignKeyRef  */
  YYSYMBOL_opt_Actiontypelist = 301,       /* opt_Actiontypelist  */
  YYSYMBOL_Action_typelist = 302,          /* Action_typelist  */
  YYSYMBOL_Action_type = 303,              /* Action_type  */
  YYSYMBOL_ColumnInParen_ForeignKey = 304, /* ColumnInParen_ForeignKey  */
  YYSYMBOL_ColumnNameList_ForeignKey = 305, /* ColumnNameList_ForeignKey  */
  YYSYMBOL_ColumnName_ForeignKey = 306,    /* ColumnName_ForeignKey  */
  YYSYMBOL_ColumnInParen_References = 307, /* ColumnInParen_References  */
  YYSYMBOL_ColumnNameList_References = 308, /* ColumnNameList_References  */
  YYSYMBOL_ColumnName_References = 309,    /* ColumnName_References  */
  YYSYMBOL_opt_unique = 310,               /* opt_unique  */
  YYSYMBOL_index_name = 311,               /* index_name  */
  YYSYMBOL_trigger_declare = 312,          /* trigger_declare  */
  YYSYMBOL_trigger_name = 313,             /* trigger_name  */
  YYSYMBOL_opt_trigger_time = 314,         /* opt_trigger_time  */
  YYSYMBOL_trigger_event = 315,            /* trigger_event  */
  YYSYMBOL_opt_of_column_list = 316,       /* opt_of_column_list  */
  YYSYMBOL_opt_for_each = 317,             /* opt_for_each  */
  YYSYMBOL_opt_when = 318,                 /* opt_when  */
  YYSYMBOL_trigger_cmd_list = 319,         /* trigger_cmd_list  */
  YYSYMBOL_trigger_cmd = 320,              /* trigger_cmd  */
  YYSYMBOL_module_name = 321,              /* module_name  */
  YYSYMBOL_opt_not_exists = 322,           /* opt_not_exists  */
  YYSYMBOL_column_def_commalist = 323,     /* column_def_commalist  */
  YYSYMBOL_column_def = 324,               /* column_def  */
  YYSYMBOL_opt_column_arglist = 325,       /* opt_column_arglist  */
  YYSYMBOL_column_arglist = 326,           /* column_arglist  */
  YYSYMBOL_column_arg = 327,               /* column_arg  */
  YYSYMBOL_opt_generatedarg = 328,         /* opt_generatedarg  */
  YYSYMBOL_opt_on_conflict = 329,          /* opt_on_conflict  */
  YYSYMBOL_resolve_type = 330,             /* resolve_type  */
  YYSYMBOL_opt_autoinc = 331,              /* opt_autoinc  */
  YYSYMBOL_column_type = 332,              /* column_type  */
  YYSYMBOL_drop_statement = 333,           /* drop_statement  */
  YYSYMBOL_opt_exists = 334,               /* opt_exists  */
  YYSYMBOL_delete_statement = 335,         /* delete_statement  */
  YYSYMBOL_truncate_statement = 336,       /* truncate_statement  */
  YYSYMBOL_insert_statement = 337,         /* insert_statement  */
  YYSYMBOL_super_list = 338,               /* super_list  */
  YYSYMBOL_insert_type = 339,              /* insert_type  */
  YYSYMBOL_opt_column_list = 340,          /* opt_column_list  */
  YYSYMBOL_update_statement = 341,         /* update_statement  */
  YYSYMBOL_update_clause_commalist = 342,  /* update_clause_commalist  */
  YYSYMBOL_update_clause = 343,            /* update_clause  */
  YYSYMBOL_select_statement = 344,         /* select_statement  */
  YYSYMBOL_select_with_paren = 345,        /* select_with_paren  */
  YYSYMBOL_select_paren_or_clause = 346,   /* select_paren_or_clause  */
  YYSYMBOL_select_no_paren = 347,          /* select_no_paren  */
  YYSYMBOL_set_operator = 348,             /* set_operator  */
  YYSYMBOL_set_type = 349,                 /* set_type  */
  YYSYMBOL_opt_all = 350,                  /* opt_all  */
  YYSYMBOL_select_clause = 351,            /* select_clause  */
  YYSYMBOL_window_clause = 352,            /* window_clause  */
  YYSYMBOL_windowdefn_list = 353,          /* windowdefn_list  */
  YYSYMBOL_windowdefn = 354,               /* windowdefn  */
  YYSYMBOL_window = 355,                   /* window  */
  YYSYMBOL_window_with_order = 356,        /* window_with_order  */
  YYSYMBOL_window_no_order = 357,          /* window_no_order  */
  YYSYMBOL_opt_base_window_name = 358,     /* opt_base_window_name  */
  YYSYMBOL_opt_frame = 359,                /* opt_frame  */
  YYSYMBOL_range_or_rows = 360,            /* range_or_rows  */
  YYSYMBOL_frame_bound_s = 361,            /* frame_bound_s  */
  YYSYMBOL_frame_bound_e = 362,            /* frame_bound_e  */
  YYSYMBOL_frame_bound = 363,              /* frame_bound  */
  YYSYMBOL_opt_frame_exclude = 364,        /* opt_frame_exclude  */
  YYSYMBOL_frame_exclude = 365,            /* frame_exclude  */
  YYSYMBOL_opt_distinct = 366,             /* opt_distinct  */
  YYSYMBOL_select_list = 367,              /* select_list  */
  YYSYMBOL_opt_from_clause = 368,          /* opt_from_clause  */
  YYSYMBOL_from_clause = 369,              /* from_clause  */
  YYSYMBOL_opt_where = 370,                /* opt_where  */
  YYSYMBOL_opt_group = 371,                /* opt_group  */
  YYSYMBOL_opt_having = 372,               /* opt_having  */
  YYSYMBOL_opt_order = 373,                /* opt_order  */
  YYSYMBOL_order = 374,                    /* order  */
  YYSYMBOL_order_list = 375,               /* order_list  */
  YYSYMBOL_order_desc = 376,               /* order_desc  */
  YYSYMBOL_opt_order_type = 377,           /* opt_order_type  */
  YYSYMBOL_opt_top = 378,                  /* opt_top  */
  YYSYMBOL_opt_limit = 379,                /* opt_limit  */
  YYSYMBOL_expr_list = 380,                /* expr_list  */
  YYSYMBOL_opt_literal_list = 381,         /* opt_literal_list  */
  YYSYMBOL_literal_list = 382,             /* literal_list  */
  YYSYMBOL_expr_alias = 383,               /* expr_alias  */
  YYSYMBOL_expr = 384,                     /* expr  */
  YYSYMBOL_operand = 385,                  /* operand  */
  YYSYMBOL_json_expr = 386,                /* json_expr  */
  YYSYMBOL_Jsonexpr_all = 387,             /* Jsonexpr_all  */
  YYSYMBOL_Jsondata = 388,                 /* Jsondata  */
  YYSYMBOL_Jsonpath = 389,                 /* Jsonpath  */
  YYSYMBOL_cast_expr = 390,                /* cast_expr  */
  YYSYMBOL_scalar_expr = 391,              /* scalar_expr  */
  YYSYMBOL_unary_expr = 392,               /* unary_expr  */
  YYSYMBOL_binary_expr = 393,              /* binary_expr  */
  YYSYMBOL_fts_query_literal = 394,        /* fts_query_literal  */
  YYSYMBOL_logic_expr = 395,               /* logic_expr  */
  YYSYMBOL_in_expr = 396,                  /* in_expr  */
  YYSYMBOL_case_expr = 397,                /* case_expr  */
  YYSYMBOL_case_list = 398,                /* case_list  */
  YYSYMBOL_exists_expr = 399,              /* exists_expr  */
  YYSYMBOL_comp_expr = 400,                /* comp_expr  */
  YYSYMBOL_function_expr = 401,            /* function_expr  */
  YYSYMBOL_aggregation_func = 402,         /* aggregation_func  */
  YYSYMBOL_window_func_no_arg = 403,       /* window_func_no_arg  */
  YYSYMBOL_window_func = 404,              /* window_func  */
  YYSYMBOL_opt_over_clause = 405,          /* opt_over_clause  */
  YYSYMBOL_over_clause = 406,              /* over_clause  */
  YYSYMBOL_over_clause_with_order = 407,   /* over_clause_with_order  */
  YYSYMBOL_over_clause_no_order = 408,     /* over_clause_no_order  */
  YYSYMBOL_opt_filter_clause = 409,        /* opt_filter_clause  */
  YYSYMBOL_extract_expr = 410,             /* extract_expr  */
  YYSYMBOL_datetime_field = 411,           /* datetime_field  */
  YYSYMBOL_array_expr = 412,               /* array_expr  */
  YYSYMBOL_array_index = 413,              /* array_index  */
  YYSYMBOL_between_expr = 414,             /* between_expr  */
  YYSYMBOL_column_name = 415,              /* column_name  */
  YYSYMBOL_literal = 416,                  /* literal  */
  YYSYMBOL_string_literal = 417,           /* string_literal  */
  YYSYMBOL_json_literal = 418,             /* json_literal  */
  YYSYMBOL_json_pathliteral = 419,         /* json_pathliteral  */
  YYSYMBOL_bool_literal = 420,             /* bool_literal  */
  YYSYMBOL_num_literal = 421,              /* num_literal  */
  YYSYMBOL_int_literal = 422,              /* int_literal  */
  YYSYMBOL_null_literal = 423,             /* null_literal  */
  YYSYMBOL_param_expr = 424,               /* param_expr  */
  YYSYMBOL_table_ref = 425,                /* table_ref  */
  YYSYMBOL_table_prefix = 426,             /* table_prefix  */
  YYSYMBOL_join_op = 427,                  /* join_op  */
  YYSYMBOL_opt_index = 428,                /* opt_index  */
  YYSYMBOL_opt_on = 429,                   /* opt_on  */
  YYSYMBOL_opt_using = 430,                /* opt_using  */
  YYSYMBOL_table_ref_name_no_alias = 431,  /* table_ref_name_no_alias  */
  YYSYMBOL_table_name = 432,               /* table_name  */
  YYSYMBOL_alias = 433,                    /* alias  */
  YYSYMBOL_opt_alias = 434,                /* opt_alias  */
  YYSYMBOL_opt_with_clause = 435,          /* opt_with_clause  */
  YYSYMBOL_with_clause = 436,              /* with_clause  */
  YYSYMBOL_WithRecursiveClause = 437,      /* WithRecursiveClause  */
  YYSYMBOL_with_recursive_description_list = 438, /* with_recursive_description_list  */
  YYSYMBOL_with_recursive_description = 439, /* with_recursive_description  */
  YYSYMBOL_with_recursive_select = 440,    /* with_recursive_select  */
  YYSYMBOL_opt_recursive_select = 441,     /* opt_recursive_select  */
  YYSYMBOL_init_select = 442,              /* init_select  */
  YYSYMBOL_select_list_essential_alias = 443, /* select_list_essential_alias  */
  YYSYMBOL_expr_list_essential_alias = 444, /* expr_list_essential_alias  */
  YYSYMBOL_expr_essential_alias = 445,     /* expr_essential_alias  */
  YYSYMBOL_with_description_list = 446,    /* with_description_list  */
  YYSYMBOL_with_description = 447,         /* with_description  */
  YYSYMBOL_join_kw = 448,                  /* join_kw  */
  YYSYMBOL_opt_semicolon = 449,            /* opt_semicolon  */
  YYSYMBOL_ident_commalist = 450           /* ident_commalist  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL \
             && defined HSQL_STYPE_IS_TRIVIAL && HSQL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  178
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1972

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  244
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  207
/* YYNRULES -- Number of rules.  */
#define YYNRULES  493
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  912

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   481


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   233,     2,     2,
     238,   239,   231,   229,   242,   230,   240,   232,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   241,
     222,   219,   223,   243,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   236,     2,   237,   234,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   220,   221,   224,   225,   226,   227,
     228,   235
};

#if HSQL_DEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   666,   666,   675,   680,   687,   693,   699,   705,   714,
     715,   716,   717,   718,   719,   720,   721,   722,   723,   727,
     732,   740,   748,   753,   759,   768,   769,   773,   774,   778,
     784,   793,   798,   806,   807,   811,   812,   813,   814,   815,
     816,   820,   826,   832,   833,   834,   835,   836,   837,   838,
     839,   840,   841,   845,   853,   858,   866,   871,   876,   884,
     890,   898,   903,   910,   915,   920,   925,   933,   938,   947,
     948,   951,   955,   961,   967,   979,   983,   990,   999,  1004,
    1013,  1018,  1026,  1030,  1034,  1041,  1049,  1053,  1060,  1072,
    1077,  1082,  1086,  1090,  1096,  1110,  1118,  1127,  1133,  1147,
    1156,  1160,  1174,  1178,  1184,  1199,  1205,  1213,  1223,  1228,
    1242,  1251,  1260,  1269,  1282,  1296,  1305,  1313,  1317,  1324,
    1332,  1333,  1334,  1338,  1343,  1344,  1348,  1352,  1359,  1367,
    1375,  1382,  1391,  1392,  1396,  1403,  1407,  1411,  1419,  1426,
    1430,  1437,  1442,  1449,  1453,  1460,  1465,  1466,  1470,  1474,
    1488,  1492,  1493,  1494,  1495,  1499,  1500,  1501,  1505,  1506,
    1510,  1511,  1515,  1516,  1520,  1521,  1525,  1526,  1527,  1528,
    1532,  1537,  1538,  1542,  1546,  1553,  1564,  1565,  1569,  1573,
    1580,  1581,  1582,  1589,  1590,  1597,  1601,  1602,  1603,  1606,
    1607,  1611,  1612,  1613,  1614,  1615,  1619,  1620,  1625,  1626,
    1628,  1629,  1630,  1634,  1637,  1638,  1649,  1657,  1665,  1671,
    1679,  1688,  1689,  1698,  1708,  1723,  1738,  1756,  1759,  1766,
    1767,  1768,  1772,  1773,  1783,  1792,  1796,  1802,  1816,  1822,
    1828,  1842,  1843,  1847,  1848,  1852,  1859,  1871,  1879,  1880,
    1881,  1885,  1886,  1890,  1901,  1915,  1919,  1920,  1924,  1928,
    1929,  1933,  1941,  1951,  1958,  1967,  1968,  1972,  1979,  1987,
    1991,  1992,  1997,  1998,  2002,  2003,  2007,  2008,  2009,  2013,
    2014,  2018,  2019,  2020,  2021,  2026,  2027,  2031,  2038,  2039,
    2043,  2048,  2049,  2053,  2059,  2063,  2064,  2067,  2068,  2072,
    2076,  2077,  2081,  2085,  2086,  2087,  2092,  2097,  2104,  2105,
    2106,  2107,  2108,  2109,  2116,  2120,  2126,  2131,  2137,  2141,
    2148,  2156,  2157,  2158,  2159,  2160,  2161,  2165,  2166,  2167,
    2168,  2169,  2170,  2171,  2172,  2173,  2174,  2175,  2179,  2187,
    2195,  2200,  2208,  2215,  2223,  2224,  2228,  2234,  2240,  2246,
    2252,  2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,
    2270,  2271,  2272,  2273,  2280,  2284,  2288,  2289,  2293,  2294,
    2295,  2296,  2302,  2303,  2304,  2305,  2309,  2310,  2314,  2315,
    2319,  2320,  2321,  2322,  2323,  2324,  2325,  2329,  2337,  2347,
    2354,  2363,  2369,  2397,  2398,  2399,  2400,  2401,  2405,  2406,
    2407,  2408,  2409,  2413,  2414,  2415,  2416,  2417,  2418,  2424,
    2425,  2429,  2434,  2439,  2448,  2452,  2456,  2457,  2462,  2471,
    2472,  2473,  2474,  2475,  2476,  2480,  2484,  2488,  2492,  2493,
    2494,  2495,  2499,  2500,  2501,  2502,  2503,  2504,  2505,  2509,
    2513,  2514,  2518,  2522,  2523,  2527,  2528,  2532,  2536,  2540,
    2552,  2563,  2574,  2583,  2595,  2601,  2607,  2608,  2609,  2610,
    2616,  2628,  2629,  2630,  2634,  2635,  2639,  2640,  2645,  2652,
    2653,  2664,  2669,  2670,  2678,  2679,  2680,  2684,  2688,  2692,
    2696,  2704,  2713,  2721,  2733,  2737,  2748,  2755,  2759,  2765,
    2775,  2779,  2786,  2800,  2801,  2802,  2803,  2804,  2808,  2809,
    2824,  2825,  2830,  2831
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "IDENTIFIER",
  "ESCAPED_CURLY_LITERAL", "ESCAPED_BRACKET_LITERAL", "JSONPATH_STRING",
  "FLOATVAL", "INTVAL", "DEALLOCATE", "PARAMETERS", "INTERSECT",
  "TEMPORARY", "TIMESTAMP", "DISTINCT", "NVARCHAR", "RESTRICT", "TRUNCATE",
  "ANALYZE", "BETWEEN", "CASCADE", "COLUMNS", "CONTROL", "DEFAULT",
  "EXECUTE", "EXPLAIN", "INTEGER", "NATURAL", "PREPARE", "PRIMARY",
  "SCHEMAS", "SPATIAL", "VARCHAR", "VIRTUAL", "DESCRIBE", "BEFORE",
  "COLUMN", "CREATE", "DELETE", "DIRECT", "DOUBLE", "ESCAPE", "EXCEPT",
  "EXISTS", "EXTRACT", "GLOBAL", "HAVING", "IMPORT", "INSERT", "ISNULL",
  "OFFSET", "RENAME", "SCHEMA", "SELECT", "SORTED", "TABLES", "UNIQUE",
  "UNLOAD", "UPDATE", "VALUES", "AFTER", "ALTER", "CROSS", "DELTA",
  "FLOAT", "GROUP", "INDEX", "INNER", "LIMIT", "LOCAL", "MERGE", "MINUS",
  "ORDER", "OUTER", "RIGHT", "TABLE", "UNION", "USING", "WHERE", "CALL",
  "CASE", "CHAR", "DATE", "DESC", "DROP", "ELSE", "FILE", "FROM", "FULL",
  "HASH", "HINT", "INTO", "JOIN", "LEFT", "LIKE", "LOAD", "NULL", "PLAN",
  "SHOW", "TEXT", "THEN", "TIME", "VIEW", "WHEN", "WITH", "ADD", "ALL",
  "AND", "ASC", "CSV", "END", "FOR", "INT", "KEY", "NOT", "OFF", "SET",
  "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF", "ON", "OR", "TO",
  "ARRAY", "CONCAT", "ILIKE", "SECOND", "MINUTE", "HOUR", "DAY", "MONTH",
  "YEAR", "TRUE", "FALSE", "FOREIGN", "REFERENCES", "ACTION", "JSON",
  "STORED", "RECURSIVE", "TRASH", "ARROW", "CUME_DIST", "DENSE_RANK",
  "PERCENT_RANK", "RANK", "ROW_NUMBER", "LAG", "LEAD", "NTILE",
  "FIRST_VALUE", "LAST_VALUE", "NTH_VALUE", "AVG", "MAX", "MIN", "SUM",
  "COUNT", "PRAGMA", "REINDEX", "GENERATED", "ALWAYS", "CHECK", "CONFLICT",
  "IGNORE", "REPLACE", "ROLLBACK", "ABORT", "FAIL", "AUTOINCR", "BEGIN",
  "TRIGGER", "TEMP", "INSTEAD", "EACH", "ROW", "OVER", "FILTER",
  "PARTITION", "CURRENT", "EXCLUDE", "FOLLOWING", "GROUPS", "NO", "OTHERS",
  "PRECEDING", "RANGE", "ROWS", "TIES", "UNBOUNDED", "WINDOW", "ATTACH",
  "DETACH", "DATABASE", "INDEXED", "CAST", "SAVEPOINT", "RELEASE",
  "VACUUM", "TRANSACTION", "DEFFERED", "EXCLUSIVE", "IMEDIATE", "COMMIT",
  "GLOB", "MATCH", "REGEX", "NOTHING", "NULLS", "LAST", "FIRST", "DO",
  "COLLATE", "'='", "EQUALS", "NOTEQUALS", "'<'", "'>'", "LESS", "GREATER",
  "LESSEQ", "GREATEREQ", "NOTNULL", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'^'", "UMINUS", "'['", "']'", "'('", "')'", "'.'", "';'", "','", "'?'",
  "$accept", "input", "statement_list", "statement", "cmd", "cmd_release",
  "savepoint_name", "cmd_pragma", "cmd_reindex", "cmd_analyze",
  "cmd_attach", "cmd_detach", "pragma_key", "pragma_value", "schema_name",
  "pragma_name", "preparable_statement", "rollback_statement",
  "opt_transaction", "opt_to_savepoint", "vacuum_statement",
  "opt_schema_name", "begin_statement", "commit_statement",
  "opt_upsert_clause", "upsert_clause", "indexed_column_list",
  "indexed_column", "opt_collate", "assign_list", "opt_null",
  "assign_clause", "column_name_list", "collation_name", "opt_hints",
  "hint_list", "hint", "prepare_statement", "prepare_target_query",
  "execute_statement", "import_statement", "import_file_type", "file_path",
  "show_statement", "alter_statement", "opt_column", "create_statement",
  "column_def_list_no_type", "column_def_no_type", "opt_tmp",
  "CreateInparan", "opt_ForeignKeylist", "ForeignKeylist", "ForeignKey",
  "FkNoOptstmt", "ForeignKeyColumn", "ForeignKeyRef", "opt_Actiontypelist",
  "Action_typelist", "Action_type", "ColumnInParen_ForeignKey",
  "ColumnNameList_ForeignKey", "ColumnName_ForeignKey",
  "ColumnInParen_References", "ColumnNameList_References",
  "ColumnName_References", "opt_unique", "index_name", "trigger_declare",
  "trigger_name", "opt_trigger_time", "trigger_event",
  "opt_of_column_list", "opt_for_each", "opt_when", "trigger_cmd_list",
  "trigger_cmd", "module_name", "opt_not_exists", "column_def_commalist",
  "column_def", "opt_column_arglist", "column_arglist", "column_arg",
  "opt_generatedarg", "opt_on_conflict", "resolve_type", "opt_autoinc",
  "column_type", "drop_statement", "opt_exists", "delete_statement",
  "truncate_statement", "insert_statement", "super_list", "insert_type",
  "opt_column_list", "update_statement", "update_clause_commalist",
  "update_clause", "select_statement", "select_with_paren",
  "select_paren_or_clause", "select_no_paren", "set_operator", "set_type",
  "opt_all", "select_clause", "window_clause", "windowdefn_list",
  "windowdefn", "window", "window_with_order", "window_no_order",
  "opt_base_window_name", "opt_frame", "range_or_rows", "frame_bound_s",
  "frame_bound_e", "frame_bound", "opt_frame_exclude", "frame_exclude",
  "opt_distinct", "select_list", "opt_from_clause", "from_clause",
  "opt_where", "opt_group", "opt_having", "opt_order", "order",
  "order_list", "order_desc", "opt_order_type", "opt_top", "opt_limit",
  "expr_list", "opt_literal_list", "literal_list", "expr_alias", "expr",
  "operand", "json_expr", "Jsonexpr_all", "Jsondata", "Jsonpath",
  "cast_expr", "scalar_expr", "unary_expr", "binary_expr",
  "fts_query_literal", "logic_expr", "in_expr", "case_expr", "case_list",
  "exists_expr", "comp_expr", "function_expr", "aggregation_func",
  "window_func_no_arg", "window_func", "opt_over_clause", "over_clause",
  "over_clause_with_order", "over_clause_no_order", "opt_filter_clause",
  "extract_expr", "datetime_field", "array_expr", "array_index",
  "between_expr", "column_name", "literal", "string_literal",
  "json_literal", "json_pathliteral", "bool_literal", "num_literal",
  "int_literal", "null_literal", "param_expr", "table_ref", "table_prefix",
  "join_op", "opt_index", "opt_on", "opt_using", "table_ref_name_no_alias",
  "table_name", "alias", "opt_alias", "opt_with_clause", "with_clause",
  "WithRecursiveClause", "with_recursive_description_list",
  "with_recursive_description", "with_recursive_select",
  "opt_recursive_select", "init_select", "select_list_essential_alias",
  "expr_list_essential_alias", "expr_essential_alias",
  "with_description_list", "with_description", "join_kw", "opt_semicolon",
  "ident_commalist", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-788)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-491)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1763,    65,   121,   121,   127,   137,   121,    77,    68,   174,
     151,   121,    74,   183,    71,    84,   156,   284,   121,  -788,
     156,   186,   945,    31,    29,   367,   156,   415,   206,  -788,
    -788,  -788,  -788,  -788,  -788,  -788,  -788,   352,  -788,  -788,
    -788,  -788,   352,  -788,  -788,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,   383,  -788,  -788,   -16,  -788,  -788,   475,   244,
    -788,  -788,   255,   411,  -788,  -788,   443,  -788,   121,  -788,
      69,   438,   371,   121,   418,   417,   424,  -788,   121,   421,
     421,   421,   121,  -788,   444,   559,   337,  -788,  -788,  -788,
     345,  -101,   360,  -788,  -788,   471,   156,   156,   156,  -788,
    -788,   280,  -788,  -788,  -788,  -788,   372,   373,  1067,  -788,
    1505,   376,  -788,  -788,   601,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,  -788,  -788,  -788,  -788,  -788,  -788,  -788,  -788,
    -788,  1408,   377,  1602,  -788,  1189,  -788,   370,   233,  -788,
    -788,   462,  -788,  -788,  -788,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,   378,   379,   382,  -788,  -788,  -788,  -788,   -73,
    -788,  -788,   466,  -788,  -788,  -788,  -788,  -788,  -788,  -788,
     367,  -788,  -788,   610,  -788,  -788,   526,  -788,  -788,  1685,
    -788,   528,  -788,  -788,   121,   502,   -16,   324,  -788,   308,
    -788,   619,    23,   621,   503,   388,   503,   503,   503,   242,
     548,  -788,   541,  -788,  -788,  -788,  -788,  -788,  -788,   625,
      37,   586,   121,   121,   627,  -788,   394,   513,   392,  -788,
     631,   365,   365,   633,    33,  -788,  -788,  -788,  -788,    12,
      21,   584,   425,  1408,   322,   218,   401,  1602,   555,  1408,
    -788,   380,  1408,   240,   402,   -63,  1408,   367,  1408,  1602,
    -788,  1602,    13,   404,   198,  1602,  1602,  1602,  1602,  1602,
    1602,  1602,  1602,  1602,  1602,  1602,  1602,  1602,  1602,  1602,
    1602,  1602,   635,  -788,  -788,    19,   407,  1408,   637,  -788,
    -788,   644,  -788,   410,   388,   635,   634,   412,   413,  -788,
    -788,  -788,   -16,   546,   533,   -16,   286,  -788,  -788,   416,
     414,  -788,  -788,  -788,  -788,   542,   121,   654,   540,   121,
     657,   658,   235,   422,  -788,  -788,  -788,  -788,  1408,  -788,
     644,   445,   -36,  -788,    35,   628,  -788,  -788,  -788,   345,
     426,  -788,  -788,   430,   559,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,  -788,   428,  -788,  -788,   610,  -788,  -788,   486,
    1408,  -788,  -788,   432,  -788,  -788,  -788,  -788,  -788,  -788,
     585,   315,   239,  1408,  1408,  -788,   584,   577,  -158,  -788,
     381,   367,   384,  -788,  -788,  -788,  -788,   566,   304,  1027,
    1602,   437,  1189,  -788,   579,   442,  1027,  1027,  1027,  1027,
    1027,  1027,    85,    85,    85,    85,   240,   240,   -76,   -76,
     -76,   152,   446,   486,  1408,   499,   120,  -788,  -788,  -788,
    -788,   678,    88,  -788,  1408,  -788,  -788,  -788,   614,  -788,
    -788,  -788,  1408,   614,  1408,  1286,  -788,  -788,    23,   645,
     612,  -788,   144,   583,    -1,  -788,    44,  -788,   567,  -788,
     451,  -788,   323,   603,  1408,   625,  -788,  -788,   121,    26,
     692,   657,   643,  -788,  -788,  -788,  -788,   460,  -788,   178,
    -788,  1408,  1408,  1408,  -788,   310,   350,   463,  -788,  1408,
     695,  -788,  -788,  -788,   325,  1602,  1027,  1189,   464,   264,
    -788,  -788,   522,   290,   467,  -788,   522,   468,   300,  -788,
     469,   582,   638,   485,   286,   491,  -788,   386,   286,   323,
     677,   222,  -788,  -788,   733,  -788,   734,  -788,   622,   583,
     692,  -788,  -788,   616,   338,   121,  -788,   121,   323,  -788,
    -788,   505,   611,   325,  -788,  -788,   634,   665,   664,   486,
     -11,   323,   375,  -788,  1408,  -788,  -788,  -788,  -788,   510,
    -788,  -788,   511,  -788,  -788,  -788,   512,   555,   514,   306,
    -788,  -788,    16,  -788,  -788,  -788,  -788,   486,   746,  -788,
      23,  -788,   678,    23,   -59,   587,  -788,  -788,  -788,   548,
    -788,  -788,  1408,  -788,  -788,   538,  -788,  1408,  1408,  -788,
     516,  -788,   668,  -788,   519,   517,  -788,  -788,  -788,  -788,
     636,   640,   524,  -788,    26,   230,  1408,   653,   525,  1408,
    -788,  -788,  -788,   323,   760,   763,  -788,  -788,  -788,  -788,
     746,   522,  -788,   544,    55,   307,  -788,   330,   552,  -788,
     -87,     8,    18,   713,  -788,    87,  -788,   323,   323,   776,
     644,  -788,    42,  -788,   654,  -788,   121,   654,  -788,   680,
     669,   669,   699,   630,   560,  -788,   230,  -788,   381,   638,
     557,  -788,   748,  -788,    25,   565,   569,   570,   105,  -788,
    -788,   685,   142,  -788,  -788,    23,   -10,  1408,  -788,  -788,
    -788,   736,  -788,   737,  -788,  -788,    56,   584,   -61,   691,
     617,  -788,  -788,  -788,   334,  -788,  -788,   700,   573,  -788,
     690,   676,  -788,   576,   707,   336,     1,   651,  -788,  -788,
     669,   701,  1408,  -788,  -788,   548,  1408,   634,  -788,  -788,
    -788,  -788,   703,  -788,  -788,  -788,   562,  1408,  -788,   341,
     708,  -788,   342,  -788,   -50,  -788,  -788,    62,  -788,   588,
      28,  1408,   -34,  1408,   822,  -788,  -788,   776,   590,   689,
     791,  -788,  -788,  -788,   121,  -788,   652,   729,   548,   669,
     417,  -788,   596,    32,   713,  -788,  1408,  1408,   726,   655,
     646,   649,  -788,   245,   -26,  -788,    26,   548,  1408,   834,
       1,   747,  -788,   719,   719,   353,   642,   722,   718,    -8,
     725,   604,  -788,  -788,   843,  -788,  -788,    36,   620,   667,
    1408,  -788,  -788,   674,  -788,  1408,  -788,  -788,   638,   -21,
     742,  -788,  -788,    91,  -788,  -788,  -788,   142,   -35,  -788,
    -113,  -788,   650,  -788,  -788,  -788,  -788,  -788,   718,   718,
     719,  -788,    26,  1408,   781,  1408,  -788,   623,   822,  -788,
     354,  -788,  -788,   765,   721,   856,  -788,  -788,   323,  -788,
    -788,    38,   548,  -788,   848,  -788,   687,   679,  -788,  -788,
    -788,    26,  -788,  1408,    26,    -9,   781,   781,   718,  -788,
     323,   632,  -788,   323,   746,  -788,  -788,   843,  -788,  -788,
    -788,   355,  -788,    83,   713,   684,   649,  -788,  -788,  -788,
    -788,   323,  -788,   749,  -788,  -788,  -788,   781,   654,   656,
    -788,  -788,  -788,  -788,   856,  -788,  -788,  -788,   614,  -788,
    -788,    26,  -788,   359,  -788,  -788,   803,   -35,  -788,   881,
    -788,  -788
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
     466,     0,     0,    27,     0,     0,     0,   122,     0,     0,
     219,     0,     0,     0,     0,     0,    55,     0,    25,   220,
      55,    55,     0,     0,     0,    62,    55,     0,   491,     3,
       8,    14,     9,    10,    11,    12,    13,    90,    15,    16,
      17,    18,    90,    51,    44,     7,    52,    45,    50,    47,
      48,    46,     0,    49,    43,     0,   464,   465,     0,   459,
     214,    28,    97,     0,   104,   120,     0,   146,     0,   121,
       0,     0,     0,     0,     0,     0,     0,   458,     0,   212,
     212,   212,     0,   102,     0,     0,   467,   480,    54,    68,
      42,    22,     0,    33,    26,    58,    55,    55,    55,    63,
     429,   418,   430,   431,   435,   437,     0,     0,     0,   438,
       0,     0,   433,   434,     0,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   383,   384,   385,   386,
     387,     0,     0,     0,   420,     0,   439,     0,   311,   327,
     328,     0,   316,   319,   320,   321,   313,   315,   322,   314,
     341,   323,     0,     0,     0,   324,   325,   318,   312,   334,
     335,   422,   423,   424,   425,   426,   436,   427,   428,    41,
       0,    31,    21,     0,    20,    61,    60,    67,     1,   466,
       2,     0,     6,     5,     0,   297,     0,   228,   229,   288,
     208,     0,   307,     0,   172,   223,   172,   172,   172,   466,
     282,   100,     0,   191,   192,   193,   194,   195,   221,     0,
       0,     0,     0,     0,     0,   103,     0,     0,   468,   469,
       0,     0,     0,     0,     0,    53,    64,    66,    65,   276,
       0,     0,     0,     0,     0,     0,     0,     0,   337,     0,
     432,     0,     0,   336,     0,     0,     0,     0,     0,     0,
     338,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   329,   332,   276,     0,     0,     0,    32,
      19,     0,     4,     0,   223,     0,   276,     0,     0,   239,
     240,   238,     0,   242,     0,     0,   303,   287,   460,     0,
     306,   308,   423,    96,    95,     0,     0,     0,     0,     0,
       0,     0,   466,     0,   169,   168,   167,   166,     0,   213,
       0,     0,   282,   225,   109,   109,   211,   206,   207,   150,
       0,   210,   482,     0,     0,   481,    37,    40,    39,    38,
      23,    36,    35,     0,    42,    34,     0,    56,   275,   407,
       0,   419,   421,     0,   409,   410,   411,   412,   413,   414,
       0,     0,     0,     0,     0,   364,     0,     0,     0,   304,
     463,     0,     0,   326,   317,   356,    29,   357,     0,   348,
       0,     0,     0,   339,     0,   351,   350,   352,   354,   370,
     371,   372,   373,   374,   375,   376,   343,   342,   345,   344,
     346,   347,     0,   407,     0,     0,     0,   355,   353,    59,
     101,     0,     0,   296,     0,   232,   231,   233,   288,   234,
     241,   237,     0,   288,     0,     0,   235,    98,     0,     0,
       0,   492,     0,   466,     0,   150,   154,   148,     0,   116,
       0,   164,   281,     0,     0,     0,   224,   108,     0,     0,
       0,     0,     0,   471,   470,    24,    57,     0,   377,     0,
     368,     0,     0,     0,   362,     0,     0,     0,   415,     0,
       0,   462,   310,    30,     0,     0,   349,     0,     0,     0,
     340,   416,   400,     0,     0,   381,     0,    93,     0,    91,
       0,    70,   279,   277,   303,   289,   290,   295,   303,   299,
     301,   298,   309,   171,     0,   222,     0,   113,     0,   466,
       0,   151,   152,     0,     0,     0,   165,     0,   227,   226,
     105,   418,     0,     0,   107,   209,   276,   474,     0,   407,
       0,   366,     0,   365,     0,   369,   305,   461,   199,     0,
     201,   200,     0,   204,   198,   205,     0,   417,     0,     0,
     360,   358,     0,   379,   399,   401,   402,   407,   256,   382,
       0,    89,     0,     0,    70,     0,   216,    69,   445,   282,
     278,   230,     0,   294,   293,    84,   236,     0,     0,   170,
       0,   493,     0,   112,     0,   125,   173,   153,   155,   156,
     159,     0,     0,    99,     0,   177,     0,     0,     0,     0,
     378,   408,   363,   367,     0,     0,   333,   361,   359,   403,
     256,   400,   255,     0,     0,     0,    92,     0,     0,   215,
       0,   280,     0,   284,   291,     0,   292,   302,   300,     0,
       0,   111,     0,   123,     0,   157,     0,     0,   106,     0,
     190,   190,     0,     0,     0,   175,   176,   179,     0,   279,
     476,   477,     0,   472,     0,     0,     0,     0,   259,   380,
     404,     0,   259,    94,   217,     0,     0,     0,   489,   488,
     483,   487,   447,   485,   446,   444,     0,   445,   463,     0,
     243,    83,    82,   119,     0,   117,   110,     0,   124,   127,
     133,     0,   174,   158,   161,     0,   295,     0,   183,   180,
     190,     0,     0,   178,   479,   282,     0,   276,   406,   202,
     203,   405,     0,   260,   261,   254,     0,     0,   252,     0,
       0,    71,     0,    75,    79,   486,   484,     0,   448,     0,
       0,     0,   453,     0,     0,   244,   115,     0,     0,     0,
       0,   128,   132,   134,     0,   129,     0,   163,   282,   190,
       0,   181,     0,     0,   284,   478,     0,     0,     0,     0,
       0,   270,   262,     0,     0,   218,     0,   282,     0,     0,
     295,     0,   449,   463,   463,     0,     0,     0,   455,   286,
       0,   245,   246,   118,     0,   130,   126,     0,     0,     0,
       0,   149,   114,   197,   189,     0,   185,   475,   279,   259,
       0,   268,   263,     0,   257,   267,   266,   259,   282,    80,
       0,    86,     0,    76,    88,    78,    77,   450,   455,   455,
     463,   452,     0,     0,   457,     0,   283,     0,     0,   141,
       0,   139,   135,     0,     0,     0,   131,   160,   162,   196,
     182,     0,   282,   253,     0,   273,     0,     0,   274,   269,
     251,     0,    72,     0,     0,     0,   457,   457,   455,   451,
     454,     0,   440,   285,   256,   247,   138,     0,   136,   137,
     145,     0,   143,   188,   284,     0,   270,   264,   272,   271,
      81,    85,    87,     0,    73,   442,   443,   457,     0,     0,
     249,   250,   140,   142,     0,   187,   186,   184,   288,   265,
     258,     0,   441,     0,   248,   144,     0,   282,   456,     0,
      74,   473
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -788,  -788,  -788,   712,  -788,  -788,  -132,  -788,  -788,  -788,
    -788,  -788,  -788,   672,    -6,   673,  -788,  -788,   312,  -788,
    -788,  -788,  -788,  -788,   333,  -788,  -788,   130,  -788,    -2,
    -788,    49,  -788,  -788,   859,  -788,   340,  -788,  -788,  -788,
    -788,  -788,  -306,  -788,  -788,   578,  -788,  -788,   167,  -788,
    -788,  -788,  -788,   166,  -788,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,    39,  -788,  -788,    14,  -788,  -788,  -788,  -215,
    -788,  -788,  -788,  -788,  -788,  -788,   595,  -788,   406,  -788,
    -459,  -788,  -788,   263,  -788,  -369,   160,  -788,   389,  -788,
     429,  -137,  -788,   -95,  -788,  -788,   629,   -67,  -788,   470,
    -186,    52,   624,  -133,   727,  -788,  -788,   259,  -788,  -788,
      86,  -788,    53,    54,   362,  -538,  -788,   164,  -788,    79,
      48,  -788,  -263,   169,  -588,  -788,  -321,  -642,  -788,  -413,
    -559,  -788,   356,  -631,  -788,   -65,  -235,  -788,  -270,   457,
     -22,   -70,  -788,  -788,  -788,  -788,  -788,  -788,  -788,  -788,
    -788,  -788,  -788,  -788,   696,  -788,  -788,  -788,  -788,  -788,
    -788,   320,   447,   527,  -788,  -355,  -788,  -788,  -788,  -788,
    -788,  -440,  -185,  -206,  -184,   793,  -788,   331,    20,  -788,
    -788,   258,  -788,  -788,  -788,  -519,  -787,  -788,     0,   288,
    -555,  -788,  -788,  -788,  -788,   605,  -788,  -788,  -788,  -788,
    -788,   231,  -788,   720,  -788,  -788,  -613
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    27,    28,    29,    30,    31,   174,    32,    33,    34,
      35,    36,    91,   340,    92,    93,    37,    38,    89,   225,
      39,   176,    40,    41,   566,   567,   722,   723,   770,   808,
     626,   809,   810,   815,   182,   488,   489,    42,   304,    43,
      44,   202,   409,    45,    46,   449,    47,   684,   685,    70,
     584,   633,   688,   689,   690,   691,   745,   741,   742,   743,
     785,   830,   831,   836,   871,   872,    71,   438,    72,   331,
     514,   591,   635,   747,   791,   312,   313,   580,   306,   585,
     524,   645,   646,   647,   897,   698,   208,   840,   546,    48,
     212,    49,    50,    51,   564,    52,   308,    53,   322,   323,
      54,   417,   418,   188,   292,   293,   421,   189,   735,   781,
     782,   889,   613,   657,   658,   715,   716,   761,   876,   762,
     804,   849,   350,   492,   569,   570,   319,   680,   826,   296,
     297,   495,   496,   575,   286,   426,   493,   299,   300,   369,
     370,   138,   139,   140,   141,   273,   142,   143,   144,   145,
     408,   146,   147,   148,   235,   149,   150,   151,   152,   153,
     154,   553,   554,   555,   556,   458,   155,   360,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   621,   622,   675,   778,   824,   862,    76,    60,   471,
     472,    55,    56,    57,   218,   219,   453,   598,   527,   649,
     650,   651,    86,    87,   676,   180,   432
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     137,   446,   244,    61,   368,   494,    64,   301,   302,   522,
     498,    77,   404,   317,   443,   341,   341,   171,    94,   175,
     609,   693,    59,   414,   695,   351,   100,   348,   102,   103,
     521,   104,   105,   172,   348,   169,   668,   172,   185,   825,
     238,   280,   406,   318,   318,   246,   523,   294,   482,   720,
     883,   586,   294,   288,   255,   662,   668,   832,   246,   470,
     727,   705,   314,   243,   248,   749,   771,   565,   195,   885,
     886,   669,   447,   200,  -331,   410,   670,   248,   210,   468,
     511,   776,   215,   671,   469,   573,   234,   508,    84,   324,
      65,   669,   347,    82,    58,   436,   670,   246,   353,   662,
     902,   672,   673,   671,   315,   512,   853,   187,   380,   241,
     574,    66,   797,   245,   410,   459,   248,   895,   221,   509,
     109,   672,   673,   732,   718,    59,   317,    83,   294,   854,
     666,    62,   316,   246,    67,   250,   381,   222,   278,   816,
     246,    63,   185,   325,  -147,   196,   246,   479,   490,   728,
      78,   667,   248,   833,   638,   772,    73,   845,   271,   248,
     272,   112,   113,   448,   279,   248,   777,   238,   769,   483,
     114,   713,   714,   692,   600,   314,   374,   731,   294,   378,
      68,   379,   687,   618,   284,   385,   386,   387,   388,   389,
     390,   391,   392,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   611,   721,   884,   807,   445,   851,   330,   254,
     842,   361,   327,   328,   456,   255,   469,   315,   818,   819,
     372,   469,   186,   513,   375,   834,   377,   896,   601,    85,
     170,   173,   898,   467,   469,   346,   525,   510,   287,   661,
     807,   376,   549,   502,   302,   316,   197,   507,   623,   478,
     674,   349,   352,   249,   610,    69,   677,   134,   403,    79,
     639,   843,    74,   596,   708,   858,   136,   774,   332,   850,
     674,   796,   699,   578,     8,   903,   846,   873,    75,   491,
     847,     8,   255,   250,    10,   848,    80,   640,    90,   712,
     615,    10,   402,   617,    11,   383,   442,   713,   714,   856,
     857,    11,   681,   682,   363,   413,   430,  -491,  -491,   434,
     476,  -491,  -491,   384,   266,   267,   268,   269,   270,   271,
     289,   272,   364,   583,   686,   463,   811,   641,   251,   365,
     246,   751,    95,    99,   713,   714,   289,   424,   177,   887,
      15,   465,   466,   364,   548,   642,   439,    15,   252,   248,
     464,   290,   538,   246,   250,   425,   253,   254,   539,   486,
      81,    88,   469,   255,   256,   473,   540,   290,   100,   336,
     255,   169,   248,   104,   105,   301,   302,   588,   301,   302,
     793,   294,   859,   505,   754,   291,   506,   589,   272,   337,
     541,    88,    96,    97,    98,   719,   643,   590,   644,   251,
     497,   291,   499,   501,   338,   547,    19,   542,   226,   227,
     228,   811,   475,    19,   882,   178,   462,   529,   246,   367,
     469,   533,   518,   246,   410,   543,   233,   792,   254,   571,
     246,   246,   805,   576,   255,   256,   806,   248,   544,   530,
     531,   532,   248,   257,   756,   258,   812,   179,   520,   248,
     248,   534,   259,   260,   261,   262,   263,   181,   246,   264,
     265,   811,   266,   267,   268,   269,   270,   271,   545,   272,
     573,   268,   269,   270,   271,   184,   272,   248,   246,   190,
     301,   302,   764,   246,   191,   906,   602,   852,   246,   246,
     247,   339,   246,   192,   246,   574,   775,   248,   779,   193,
     371,   470,   248,   551,   474,   198,   469,   248,   248,   213,
     214,   248,   603,   248,   257,   592,   258,   593,   229,   194,
     230,   874,   799,   259,   260,   261,   262,   263,   201,   557,
     264,   265,   469,   266,   267,   268,   269,   270,   271,   561,
     272,   209,   562,   211,   729,   608,   663,   199,   469,   428,
     497,   419,   342,   342,   419,   627,   628,   354,   355,   356,
     357,   358,   359,   217,   216,   100,   101,   102,   103,   664,
     104,   105,   428,   736,   648,   748,   737,   654,   506,   220,
     765,   767,   758,   428,   768,   -41,   910,   203,   204,   205,
     206,   207,   820,   866,   893,   469,   867,   894,   908,   224,
     223,   506,   309,   310,   311,   250,   106,   107,   240,   114,
     231,   232,   239,  -330,   172,   242,   275,   276,   281,   283,
     277,   285,   678,   298,   303,   305,   307,   318,   320,   321,
     326,   329,   186,   333,   334,    84,   694,   344,   185,   366,
     407,   373,   382,   108,   105,   724,   405,   100,   411,   348,
     251,   415,   416,   420,   422,   427,   428,   429,   431,   109,
     433,   435,   437,   441,   444,   447,   451,   455,   452,   457,
     367,   460,   380,   461,   246,   477,   480,   110,   272,   254,
     753,   484,   487,   481,   648,   255,   256,   294,    15,   503,
     504,   111,   516,   515,   763,   517,   523,   526,   528,   537,
     112,   113,   535,   550,   552,   558,   560,   563,   565,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   568,   469,   577,   100,
     101,   102,   103,   572,   104,   105,   763,   579,   581,   594,
     582,   587,   597,   599,   788,   230,   724,   759,   604,   605,
     612,   606,   625,   607,   629,   630,   620,   760,   631,   632,
     652,   634,   637,   132,   653,   257,   636,   258,   838,   655,
     106,   107,   656,   841,   259,   260,   261,   262,   263,   679,
     683,   264,   265,   660,   266,   267,   268,   269,   270,   271,
     665,   272,   133,   134,   696,   697,   700,   701,   702,   706,
     135,   860,   707,   863,   709,   136,   717,   108,   710,   711,
     725,   726,   733,   734,   738,   739,   740,   744,   506,   746,
     750,   752,   763,   109,   757,   766,   780,   773,   784,   687,
     787,   881,   789,   790,   795,   803,   801,   802,   814,   470,
     817,   110,   821,   822,   823,   827,   828,   829,   837,   839,
     844,   100,   101,   102,   103,   111,   104,   105,   835,   861,
     870,   864,   868,   869,   112,   113,   901,   855,   878,   879,
     888,   899,   909,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     911,   282,   106,   107,   343,   904,   345,   619,   813,   907,
     880,   183,   616,   450,   783,   786,   892,   440,   905,   703,
     794,   759,   595,   412,   865,   519,   295,   890,   891,   423,
     614,   760,   800,   877,   900,   798,   536,   132,   624,   108,
     362,   659,   485,   559,   274,   730,   704,   755,     0,   454,
     335,     0,     0,     0,     0,   109,     0,     0,   100,   101,
     102,   103,     0,   104,   105,     0,   133,   134,     0,     0,
       0,     0,     0,   110,   135,     0,     0,     0,     0,   136,
       0,     0,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,     0,   106,
     107,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,     0,
       0,     0,     0,   759,     0,     0,     0,     0,     0,     0,
       0,     0,   109,   875,     0,     0,     0,     0,     0,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     100,   101,   102,   103,   111,   104,   105,   250,   133,   134,
       0,     0,     0,   112,   113,     0,   135,     0,     0,     0,
       0,   136,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     0,
       0,   106,   107,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -491,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   131,     0,   132,     0,   108,     0,
       0,   254,     0,     0,     0,     0,     0,   255,  -491,     0,
       0,     0,     0,     0,   109,     0,     0,     0,     0,     0,
       0,   233,     0,     0,     0,   133,   134,     0,     0,     0,
       0,     0,   110,   135,     0,     0,     0,     0,   136,     0,
       0,     0,   100,   101,   102,   103,   111,   104,   105,     0,
       0,     0,     0,     0,     0,   112,   113,     0,     0,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,     0,     0,   106,   107,     0,     0,  -491,     0,  -491,
       0,     0,     0,   185,     0,     0,  -491,  -491,  -491,   262,
     263,     0,     0,   264,   265,     0,   266,   267,   268,   269,
     270,   271,     0,   272,     0,     0,     0,     0,   132,     0,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,     0,     0,   100,
     101,   102,   103,     0,   104,   105,     0,   133,   134,     0,
       0,     0,     0,     0,   110,   135,     0,     0,     0,     0,
     136,     0,     0,     0,     0,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,     0,
     106,   107,     0,     0,     0,     0,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   108,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   109,     0,     0,     0,     0,     0,     0,
     132,     0,     0,   500,     0,     0,     0,     0,     0,     0,
       0,   110,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,   101,   102,   103,   111,   104,   105,     0,   133,
     134,     0,     0,     0,   112,   113,     0,   135,     0,     0,
       0,     0,   136,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,     0,   106,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   132,     0,   108,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   109,     0,     0,   100,   101,
     102,   103,     0,   104,   105,     0,   133,   134,     0,     0,
       0,     0,     0,   110,   135,     0,     0,     0,     0,   136,
       0,     0,     0,     0,     0,     0,     0,   111,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,     0,   236,
     107,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,     0,     0,   100,   101,   102,   103,   132,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
     237,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   111,     0,     0,     0,   133,   134,
       0,     0,     0,   112,   113,     0,   135,   107,     0,     0,
       0,   136,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,     0,  -490,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,   109,
       0,     0,     0,     2,     3,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     5,     0,     0,   237,     0,     0,
       6,     0,     0,     7,     8,     0,     0,     0,     0,     0,
       0,   111,     0,     9,    10,   133,   134,     0,     0,     0,
     112,   113,     0,   135,    11,     0,     0,    12,   136,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,     0,     0,     0,     0,
      13,     0,     0,     1,     0,     0,     0,     0,     0,     0,
       0,     2,     3,     0,    14,     0,     0,     0,     4,     0,
      15,     0,     5,     0,     0,     0,    16,     0,     6,     0,
       0,     7,     8,     0,     0,     0,     0,     0,     0,     0,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,     0,     0,    12,     0,     0,     0,     0,
       0,     0,   133,   134,     0,     0,     0,     0,     0,     0,
     135,     0,     0,     0,     0,   136,     0,     0,    13,    17,
      18,     0,     0,     0,     0,     0,    19,    20,     0,     0,
       0,    21,    14,     0,     0,     0,     0,     0,    15,     0,
       0,     0,     0,     0,    16,     0,     0,     0,     0,     0,
       0,     0,    22,    23,     0,     0,     0,     0,    24,    25,
       0,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    18,     0,
       0,     0,     0,     0,    19,    20,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      22,    23,     0,     0,     0,     0,    24,    25,     0,     0,
       0,     0,    26
};

static const yytype_int16 yycheck[] =
{
      22,   322,   135,     3,   239,   418,     6,   192,   192,   449,
     423,    11,   275,   199,   320,   221,   222,    23,    18,    25,
       4,   634,     4,   286,   637,     4,     3,    15,     5,     6,
       4,     8,     9,     4,    15,     4,    28,     4,    54,    47,
     110,   173,   277,    79,    79,   108,     4,    73,   403,    59,
      59,   510,    73,   186,   130,   614,    28,    21,   108,   120,
       4,   649,   199,   133,   127,   696,     4,   126,    68,   856,
     857,    63,    37,    73,   147,   281,    68,   127,    78,   237,
      36,   115,    82,    75,   242,    84,   108,    88,     4,    52,
      13,    63,   224,    22,    29,   310,    68,   108,   231,   658,
     887,    93,    94,    75,   199,    61,   219,    55,    95,   131,
     109,    34,   754,   135,   320,   350,   127,    34,   219,   120,
      97,    93,    94,   678,   662,     4,   312,    56,    73,   242,
     217,     4,   199,   108,    57,    50,   123,   238,   211,   770,
     108,     4,    54,   106,    67,    76,   108,   382,    60,    93,
      76,   238,   127,   117,   594,    93,    88,    66,   234,   127,
     236,   138,   139,   128,   170,   127,   200,   237,   218,   404,
     147,   192,   193,   632,   529,   312,   239,   238,    73,   249,
     103,   251,   140,   242,   184,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   557,   213,   213,   764,   242,   242,   214,   124,
     798,   233,   212,   213,   346,   130,   242,   312,   773,   774,
     242,   242,   238,   179,   246,   189,   248,   144,   239,   145,
     199,   202,   874,   366,   242,   202,   451,   238,   186,   184,
     799,   247,   477,   428,   428,   312,   177,   433,   569,   382,
     242,   239,   231,    20,   238,   178,   238,   231,   239,    76,
      30,   799,    88,   526,   239,   820,   243,   239,   216,   807,
     242,   239,   641,    51,    39,   888,   185,   239,   127,   412,
     189,    39,   130,    50,    49,   194,   103,    57,     4,   184,
     560,    49,   272,   563,    59,    97,   318,   192,   193,   818,
     819,    59,   215,   216,    86,   285,   306,   222,   223,   309,
     380,   226,   227,   115,   229,   230,   231,   232,   233,   234,
      12,   236,   104,   509,   630,    86,   766,    97,    95,   111,
     108,   700,    20,    21,   192,   193,    12,    51,    26,   858,
     105,   363,   364,   104,   477,   115,   111,   105,   115,   127,
     111,    43,    27,   108,    50,    69,   123,   124,    33,   239,
     177,   205,   242,   130,   131,   371,    41,    43,     3,     4,
     130,     4,   127,     8,     9,   560,   560,    39,   563,   563,
     749,    73,   822,   239,   705,    77,   242,    49,   236,    24,
      65,   205,   206,   207,   208,   665,   166,    59,   168,    95,
     422,    77,   424,   425,    39,   475,   171,    82,    96,    97,
      98,   851,   108,   171,   854,     0,   101,   239,   108,   115,
     242,   111,   444,   108,   630,   100,   104,   748,   124,   494,
     108,   108,   187,   498,   130,   131,   191,   127,   113,   461,
     462,   463,   127,   210,   707,   212,   767,   241,   448,   127,
     127,   101,   219,   220,   221,   222,   223,   105,   108,   226,
     227,   901,   229,   230,   231,   232,   233,   234,   143,   236,
      84,   231,   232,   233,   234,    92,   236,   127,   108,     4,
     665,   665,   717,   108,   240,   898,   111,   808,   108,   108,
     120,   126,   108,   238,   108,   109,   731,   127,   733,    88,
     120,   120,   127,   239,   120,    67,   242,   127,   127,    80,
      81,   127,   534,   127,   210,   515,   212,   517,   238,    76,
     240,   842,   757,   219,   220,   221,   222,   223,   110,   239,
     226,   227,   242,   229,   230,   231,   232,   233,   234,   239,
     236,   117,   242,   122,   677,   239,   239,   176,   242,   242,
     572,   292,   221,   222,   295,   577,   578,   132,   133,   134,
     135,   136,   137,     4,   120,     3,     4,     5,     6,   239,
       8,     9,   242,   239,   596,   239,   242,   599,   242,   242,
     239,   239,    20,   242,   242,   240,   907,   170,   171,   172,
     173,   174,   239,   239,   239,   242,   242,   242,   239,   128,
     240,   242,   196,   197,   198,    50,    44,    45,     7,   147,
     238,   238,   236,   147,     4,   238,   238,   238,    92,    91,
     238,   119,   622,     4,     3,   122,   238,    79,    87,     4,
      44,     4,   238,   120,   242,     4,   636,     4,    54,   238,
       3,   239,   238,    81,     9,   667,   239,     3,   238,    15,
      95,   239,   239,   107,   121,   239,   242,   115,     4,    97,
     120,     4,     4,   241,   219,    37,   240,   239,   238,   183,
     115,   239,    95,    88,   108,   238,    97,   115,   236,   124,
     702,   182,     4,   237,   706,   130,   131,    73,   105,    44,
      78,   129,   241,   126,   716,    92,     4,    54,   238,     4,
     138,   139,   239,   239,   182,   238,   238,   238,   126,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    88,   242,    51,     3,
       4,     5,     6,   242,     8,     9,   758,     4,     4,   128,
     118,   125,    77,    79,   744,   240,   768,   185,   238,   238,
       4,   239,   214,   239,   238,    87,   169,   195,   239,   242,
     107,   125,   238,   201,   239,   210,   126,   212,   790,     9,
      44,    45,     9,   795,   219,   220,   221,   222,   223,    66,
       4,   226,   227,   239,   229,   230,   231,   232,   233,   234,
     238,   236,   230,   231,   114,   126,    97,   167,   238,   242,
     238,   823,    54,   825,   239,   243,   121,    81,   239,   239,
      74,    74,   121,   196,   114,   242,   126,   141,   242,   112,
     169,   120,   844,    97,   121,   117,     4,   239,   238,   140,
      39,   853,   180,   104,   238,   186,   181,   191,     4,   120,
      93,   115,   200,   121,   126,   120,   242,     4,   181,   175,
     108,     3,     4,     5,     6,   129,     8,     9,   238,    78,
       4,   238,    97,   142,   138,   139,   117,   217,   181,   190,
     238,   187,    69,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
       9,   179,    44,    45,   222,   239,   223,   564,   768,   901,
     851,    42,   562,   325,   737,   739,   867,   312,   894,   646,
     750,   185,   523,   284,   828,   445,   189,   864,   864,   295,
     558,   195,   758,   844,   876,   756,   469,   201,   572,    81,
     234,   611,   405,   486,   141,   677,   648,   706,    -1,   334,
     220,    -1,    -1,    -1,    -1,    97,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,   230,   231,    -1,    -1,
      -1,    -1,    -1,   115,   238,    -1,    -1,    -1,    -1,   243,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,   139,    -1,    44,
      45,    -1,    -1,    -1,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,   185,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,   195,    -1,    -1,    -1,    -1,    -1,   201,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,   129,     8,     9,    50,   230,   231,
      -1,    -1,    -1,   138,   139,    -1,   238,    -1,    -1,    -1,
      -1,   243,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,    -1,
      -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   199,    -1,   201,    -1,    81,    -1,
      -1,   124,    -1,    -1,    -1,    -1,    -1,   130,   131,    -1,
      -1,    -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,
      -1,   104,    -1,    -1,    -1,   230,   231,    -1,    -1,    -1,
      -1,    -1,   115,   238,    -1,    -1,    -1,    -1,   243,    -1,
      -1,    -1,     3,     4,     5,     6,   129,     8,     9,    -1,
      -1,    -1,    -1,    -1,    -1,   138,   139,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,    -1,    -1,    44,    45,    -1,    -1,   210,    -1,   212,
      -1,    -1,    -1,    54,    -1,    -1,   219,   220,   221,   222,
     223,    -1,    -1,   226,   227,    -1,   229,   230,   231,   232,
     233,   234,    -1,   236,    -1,    -1,    -1,    -1,   201,    -1,
      81,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,     3,
       4,     5,     6,    -1,     8,     9,    -1,   230,   231,    -1,
      -1,    -1,    -1,    -1,   115,   238,    -1,    -1,    -1,    -1,
     243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   138,   139,    -1,
      44,    45,    -1,    -1,    -1,    -1,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    97,    -1,    -1,    -1,    -1,    -1,    -1,
     201,    -1,    -1,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,   129,     8,     9,    -1,   230,
     231,    -1,    -1,    -1,   138,   139,    -1,   238,    -1,    -1,
      -1,    -1,   243,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
      -1,    -1,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   201,    -1,    81,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    97,    -1,    -1,     3,     4,
       5,     6,    -1,     8,     9,    -1,   230,   231,    -1,    -1,
      -1,    -1,    -1,   115,   238,    -1,    -1,    -1,    -1,   243,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   138,   139,    -1,    44,
      45,    -1,    -1,    -1,    -1,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    97,    -1,    -1,     3,     4,     5,     6,   201,
       8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   129,    -1,    -1,    -1,   230,   231,
      -1,    -1,    -1,   138,   139,    -1,   238,    45,    -1,    -1,
      -1,   243,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    -1,     0,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    10,    -1,    -1,    -1,    97,
      -1,    -1,    -1,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    29,    -1,    -1,   115,    -1,    -1,
      35,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,    48,    49,   230,   231,    -1,    -1,    -1,
     138,   139,    -1,   238,    59,    -1,    -1,    62,   243,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,    -1,    -1,    -1,    -1,
      85,    -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    18,    19,    -1,    99,    -1,    -1,    -1,    25,    -1,
     105,    -1,    29,    -1,    -1,    -1,   111,    -1,    35,    -1,
      -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,   230,   231,    -1,    -1,    -1,    -1,    -1,    -1,
     238,    -1,    -1,    -1,    -1,   243,    -1,    -1,    85,   164,
     165,    -1,    -1,    -1,    -1,    -1,   171,   172,    -1,    -1,
      -1,   176,    99,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,   111,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   198,    -1,    -1,    -1,    -1,   203,   204,
      -1,    -1,    -1,    -1,   209,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   164,   165,    -1,
      -1,    -1,    -1,    -1,   171,   172,    -1,    -1,    -1,   176,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     197,   198,    -1,    -1,    -1,    -1,   203,   204,    -1,    -1,
      -1,    -1,   209
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,    10,    18,    19,    25,    29,    35,    38,    39,    48,
      49,    59,    62,    85,    99,   105,   111,   164,   165,   171,
     172,   176,   197,   198,   203,   204,   209,   245,   246,   247,
     248,   249,   251,   252,   253,   254,   255,   260,   261,   264,
     266,   267,   281,   283,   284,   287,   288,   290,   333,   335,
     336,   337,   339,   341,   344,   435,   436,   437,    29,     4,
     432,   432,     4,     4,   432,    13,    34,    57,   103,   178,
     293,   310,   312,    88,    88,   127,   431,   432,    76,    76,
     103,   177,    22,    56,     4,   145,   446,   447,   205,   262,
       4,   256,   258,   259,   432,   262,   206,   207,   208,   262,
       3,     4,     5,     6,     8,     9,    44,    45,    81,    97,
     115,   129,   138,   139,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   199,   201,   230,   231,   238,   243,   384,   385,   386,
     387,   388,   390,   391,   392,   393,   395,   396,   397,   399,
     400,   401,   402,   403,   404,   410,   412,   413,   414,   415,
     416,   417,   418,   419,   420,   421,   422,   423,   424,     4,
     199,   258,     4,   202,   250,   258,   265,   262,     0,   241,
     449,   105,   278,   278,    92,    54,   238,   345,   347,   351,
       4,   240,   238,    88,    76,   432,    76,   177,    67,   176,
     432,   110,   285,   170,   171,   172,   173,   174,   330,   117,
     432,   122,   334,   334,   334,   432,   120,     4,   438,   439,
     242,   219,   238,   240,   128,   263,   262,   262,   262,   238,
     240,   238,   238,   104,   384,   398,    44,   115,   385,   236,
       7,   384,   238,   385,   347,   384,   108,   120,   127,    20,
      50,    95,   115,   123,   124,   130,   131,   210,   212,   219,
     220,   221,   222,   223,   226,   227,   229,   230,   231,   232,
     233,   234,   236,   389,   419,   238,   238,   238,   211,   258,
     250,    92,   247,    91,   432,   119,   378,   345,   347,    12,
      43,    77,   348,   349,    73,   348,   373,   374,     4,   381,
     382,   416,   418,     3,   282,   122,   322,   238,   340,   322,
     322,   322,   319,   320,   335,   337,   341,   344,    79,   370,
      87,     4,   342,   343,    52,   106,    44,   432,   432,     4,
     258,   313,   345,   120,   242,   447,     4,    24,    39,   126,
     257,   417,   421,   257,     4,   259,   202,   250,    15,   239,
     366,     4,   231,   347,   132,   133,   134,   135,   136,   137,
     411,   384,   398,    86,   104,   111,   238,   115,   380,   383,
     384,   120,   384,   239,   239,   384,   258,   384,   385,   385,
      95,   123,   238,    97,   115,   385,   385,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   385,   385,
     385,   385,   422,   239,   366,   239,   380,     3,   394,   286,
     417,   238,   340,   422,   366,   239,   239,   345,   346,   351,
     107,   350,   121,   346,    51,    69,   379,   239,   242,   115,
     432,     4,   450,   120,   432,     4,   313,     4,   311,   111,
     320,   241,   384,   286,   219,   242,   370,    37,   128,   289,
     289,   240,   238,   440,   439,   239,   250,   183,   409,   380,
     239,    88,   101,    86,   111,   384,   384,   347,   237,   242,
     120,   433,   434,   258,   120,   108,   385,   238,   347,   380,
      97,   237,   409,   380,   182,   407,   239,     4,   279,   280,
      60,   347,   367,   380,   373,   375,   376,   384,   373,   384,
     107,   384,   416,    44,    78,   239,   242,   344,    88,   120,
     238,    36,    61,   179,   314,   126,   241,    92,   384,   343,
     432,     4,   415,     4,   324,   313,    54,   442,   238,   239,
     384,   384,   384,   111,   101,   239,   383,     4,    27,    33,
      41,    65,    82,   100,   113,   143,   332,   385,   347,   380,
     239,   239,   182,   405,   406,   407,   408,   239,   238,   406,
     238,   239,   242,   238,   338,   126,   268,   269,    88,   368,
     369,   379,   242,    84,   109,   377,   379,    51,    51,     4,
     321,     4,   118,   344,   294,   323,   324,   125,    39,    49,
      59,   315,   432,   432,   128,   332,   366,    77,   441,    79,
     409,   239,   111,   384,   238,   238,   239,   239,   239,     4,
     238,   409,     4,   356,   358,   382,   280,   382,   242,   268,
     169,   425,   426,   370,   376,   214,   274,   384,   384,   238,
      87,   239,   242,   295,   125,   316,   126,   238,   415,    30,
      57,    97,   115,   166,   168,   325,   326,   327,   384,   443,
     444,   445,   107,   239,   384,     9,     9,   357,   358,   405,
     239,   184,   374,   239,   239,   238,   217,   238,    28,    63,
      68,    75,    93,    94,   242,   427,   448,   238,   432,    66,
     371,   215,   216,     4,   291,   292,   286,   140,   296,   297,
     298,   299,   324,   450,   432,   450,   114,   126,   329,   329,
      97,   167,   238,   327,   433,   368,   242,    54,   239,   239,
     239,   239,   184,   192,   193,   359,   360,   121,   359,   382,
      59,   213,   270,   271,   384,    74,    74,     4,    93,   347,
     425,   238,   434,   121,   196,   352,   239,   242,   114,   242,
     126,   301,   302,   303,   141,   300,   112,   317,   239,   377,
     169,   329,   120,   384,   370,   445,   366,   121,    20,   185,
     195,   361,   363,   384,   380,   239,   117,   239,   242,   218,
     272,     4,    93,   239,   239,   380,   115,   200,   428,   380,
       4,   353,   354,   292,   238,   304,   297,    39,   432,   180,
     104,   318,   370,   329,   330,   238,   239,   371,   367,   380,
     361,   181,   191,   186,   364,   187,   191,   374,   273,   275,
     276,   415,   370,   271,     4,   277,   377,    93,   434,   434,
     239,   200,   121,   126,   429,    47,   372,   120,   242,     4,
     305,   306,    21,   117,   189,   238,   307,   181,   384,   175,
     331,   384,   368,   359,   108,    66,   185,   189,   194,   365,
     359,   242,   370,   219,   242,   217,   429,   429,   434,   415,
     384,    78,   430,   384,   238,   354,   239,   242,    97,   142,
       4,   308,   309,   239,   370,   195,   362,   363,   181,   190,
     275,   384,   415,    59,   213,   430,   430,   429,   238,   355,
     356,   357,   306,   239,   242,    34,   144,   328,   371,   187,
     364,   117,   430,   450,   239,   309,   373,   273,   239,    69,
     370,     9
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   244,   245,   246,   246,   247,   247,   247,   247,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   249,
     249,   250,   251,   251,   251,   252,   252,   253,   253,   254,
     254,   255,   255,   256,   256,   257,   257,   257,   257,   257,
     257,   258,   259,   260,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   261,   262,   262,   263,   263,   263,   264,
     264,   265,   265,   266,   266,   266,   266,   267,   267,   268,
     268,   269,   269,   269,   269,   270,   270,   271,   272,   272,
     273,   273,   274,   274,   274,   275,   276,   276,   277,   278,
     278,   279,   279,   280,   280,   281,   282,   283,   283,   284,
     285,   286,   287,   287,   287,   288,   288,   288,   289,   289,
     290,   290,   290,   290,   290,   290,   290,   291,   291,   292,
     293,   293,   293,   294,   295,   295,   296,   296,   297,   298,
     299,   300,   301,   301,   302,   303,   303,   303,   304,   305,
     305,   306,   307,   308,   308,   309,   310,   310,   311,   312,
     313,   314,   314,   314,   314,   315,   315,   315,   316,   316,
     317,   317,   318,   318,   319,   319,   320,   320,   320,   320,
     321,   322,   322,   323,   323,   324,   325,   325,   326,   326,
     327,   327,   327,   327,   327,   327,   328,   328,   328,   329,
     329,   330,   330,   330,   330,   330,   331,   331,   332,   332,
     332,   332,   332,   332,   332,   332,   333,   333,   333,   333,
     333,   334,   334,   335,   336,   337,   337,   338,   338,   339,
     339,   339,   340,   340,   341,   342,   342,   343,   344,   344,
     344,   345,   345,   346,   346,   347,   347,   348,   349,   349,
     349,   350,   350,   351,   351,   352,   353,   353,   354,   355,
     355,   356,   356,   357,   357,   358,   358,   359,   359,   359,
     360,   360,   361,   361,   362,   362,   363,   363,   363,   364,
     364,   365,   365,   365,   365,   366,   366,   367,   368,   368,
     369,   370,   370,   371,   371,   372,   372,   373,   373,   374,
     375,   375,   376,   377,   377,   377,   378,   378,   379,   379,
     379,   379,   379,   379,   380,   380,   381,   381,   382,   382,
     383,   384,   384,   384,   384,   384,   384,   385,   385,   385,
     385,   385,   385,   385,   385,   385,   385,   385,   386,   387,
     388,   388,   389,   390,   391,   391,   392,   392,   392,   392,
     392,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   394,   395,   395,   396,   396,
     396,   396,   397,   397,   397,   397,   398,   398,   399,   399,
     400,   400,   400,   400,   400,   400,   400,   401,   401,   401,
     401,   401,   401,   402,   402,   402,   402,   402,   403,   403,
     403,   403,   403,   404,   404,   404,   404,   404,   404,   405,
     405,   406,   406,   406,   407,   408,   409,   409,   410,   411,
     411,   411,   411,   411,   411,   412,   413,   414,   415,   415,
     415,   415,   416,   416,   416,   416,   416,   416,   416,   417,
     418,   418,   419,   420,   420,   421,   421,   422,   423,   424,
     425,   425,   425,   425,   426,   426,   427,   427,   427,   427,
     427,   428,   428,   428,   429,   429,   430,   430,   431,   432,
     432,   433,   434,   434,   435,   435,   435,   436,   437,   438,
     438,   439,   440,   441,   441,   442,   443,   444,   444,   445,
     446,   446,   447,   448,   448,   448,   448,   448,   448,   448,
     449,   449,   450,   450
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     3,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       2,     1,     2,     4,     5,     1,     2,     1,     2,     4,
       5,     2,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     2,     3,     0,     4,
       2,     1,     0,     2,     3,     3,     3,     2,     2,     1,
       0,     4,     7,     8,    11,     1,     3,     3,     2,     0,
       1,     3,     2,     2,     0,     3,     1,     3,     1,     5,
       0,     1,     3,     1,     4,     4,     1,     2,     5,     7,
       1,     1,     2,     3,     2,     6,     8,     6,     1,     0,
       9,     8,     7,     6,    11,    10,     5,     1,     3,     1,
       1,     1,     0,     2,     2,     0,     3,     1,     2,     2,
       3,     3,     1,     0,     1,     3,     4,     4,     3,     1,
       3,     1,     3,     1,     3,     1,     1,     0,     1,    10,
       1,     1,     1,     2,     0,     1,     1,     2,     2,     0,
       3,     0,     2,     0,     2,     3,     1,     1,     1,     1,
       1,     3,     0,     1,     3,     3,     1,     0,     2,     1,
       2,     3,     5,     2,     7,     4,     1,     1,     0,     3,
       0,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       1,     1,     4,     4,     1,     1,     4,     4,     3,     6,
       4,     2,     0,     4,     2,     7,     6,     3,     5,     1,
       1,     3,     3,     0,     5,     1,     3,     3,     2,     2,
       6,     3,     3,     1,     1,     3,     5,     2,     1,     1,
       1,     1,     0,     7,     8,     2,     1,     3,     5,     1,
       1,     6,     3,     5,     2,     1,     0,     3,     6,     0,
       1,     1,     1,     2,     1,     2,     2,     2,     2,     2,
       0,     2,     2,     1,     1,     1,     0,     1,     1,     0,
       2,     2,     0,     4,     0,     2,     0,     1,     0,     3,
       1,     3,     3,     1,     1,     0,     2,     0,     2,     2,
       4,     2,     4,     0,     1,     3,     1,     0,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     1,     2,
       1,     1,     1,     6,     1,     1,     2,     2,     2,     3,
       4,     1,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     3,     3,     3,     3,     1,     3,     3,     5,     6,
       5,     6,     4,     6,     3,     5,     4,     5,     4,     5,
       3,     3,     3,     3,     3,     3,     3,     4,     6,     5,
       7,     4,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     2,     4,     4,     5,     0,     6,     1,
       1,     1,     1,     1,     1,     4,     4,     5,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       6,     8,     7,     7,     2,     0,     1,     1,     2,     3,
       4,     3,     2,     0,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     0,     1,     1,     0,     2,     3,     1,
       3,     3,     4,    11,     0,     6,     1,     1,     3,     2,
       1,     3,     3,     1,     2,     1,     2,     1,     1,     1,
       1,     0,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = SQL_HSQL_EMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == SQL_HSQL_EMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use SQL_HSQL_error or SQL_HSQL_UNDEF. */
#define YYERRCODE SQL_HSQL_UNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if HSQL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Program * result, yyscan_t scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Program * result, yyscan_t scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, Program * result, yyscan_t scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HSQL_DEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HSQL_DEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Program * result, yyscan_t scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_STRING: /* STRING  */
#line 590 "bison_parser.y"
            { free( (((*yyvaluep).sval)) ); }
#line 2592 "bison_parser.cpp"
        break;

    case YYSYMBOL_IDENTIFIER: /* IDENTIFIER  */
#line 590 "bison_parser.y"
            { free( (((*yyvaluep).sval)) ); }
#line 2598 "bison_parser.cpp"
        break;

    case YYSYMBOL_ESCAPED_CURLY_LITERAL: /* ESCAPED_CURLY_LITERAL  */
#line 590 "bison_parser.y"
            { free( (((*yyvaluep).sval)) ); }
#line 2604 "bison_parser.cpp"
        break;

    case YYSYMBOL_ESCAPED_BRACKET_LITERAL: /* ESCAPED_BRACKET_LITERAL  */
#line 590 "bison_parser.y"
            { free( (((*yyvaluep).sval)) ); }
#line 2610 "bison_parser.cpp"
        break;

    case YYSYMBOL_JSONPATH_STRING: /* JSONPATH_STRING  */
#line 590 "bison_parser.y"
            { free( (((*yyvaluep).sval)) ); }
#line 2616 "bison_parser.cpp"
        break;

    case YYSYMBOL_FLOATVAL: /* FLOATVAL  */
#line 589 "bison_parser.y"
            { }
#line 2622 "bison_parser.cpp"
        break;

    case YYSYMBOL_INTVAL: /* INTVAL  */
#line 589 "bison_parser.y"
            { }
#line 2628 "bison_parser.cpp"
        break;

    case YYSYMBOL_input: /* input  */
#line 589 "bison_parser.y"
            { }
#line 2634 "bison_parser.cpp"
        break;

    case YYSYMBOL_statement_list: /* statement_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).statement_list_t)!=NULL)((*yyvaluep).statement_list_t)->deep_delete(); }
#line 2640 "bison_parser.cpp"
        break;

    case YYSYMBOL_statement: /* statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).statement_t)!=NULL)((*yyvaluep).statement_t)->deep_delete(); }
#line 2646 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd: /* cmd  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_t)!=NULL)((*yyvaluep).cmd_t)->deep_delete(); }
#line 2652 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_release: /* cmd_release  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_release_t)!=NULL)((*yyvaluep).cmd_release_t)->deep_delete(); }
#line 2658 "bison_parser.cpp"
        break;

    case YYSYMBOL_savepoint_name: /* savepoint_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).savepoint_name_t)!=NULL)((*yyvaluep).savepoint_name_t)->deep_delete(); }
#line 2664 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_pragma: /* cmd_pragma  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_pragma_t)!=NULL)((*yyvaluep).cmd_pragma_t)->deep_delete(); }
#line 2670 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_reindex: /* cmd_reindex  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_reindex_t)!=NULL)((*yyvaluep).cmd_reindex_t)->deep_delete(); }
#line 2676 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_analyze: /* cmd_analyze  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_analyze_t)!=NULL)((*yyvaluep).cmd_analyze_t)->deep_delete(); }
#line 2682 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_attach: /* cmd_attach  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_attach_t)!=NULL)((*yyvaluep).cmd_attach_t)->deep_delete(); }
#line 2688 "bison_parser.cpp"
        break;

    case YYSYMBOL_cmd_detach: /* cmd_detach  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cmd_detach_t)!=NULL)((*yyvaluep).cmd_detach_t)->deep_delete(); }
#line 2694 "bison_parser.cpp"
        break;

    case YYSYMBOL_pragma_key: /* pragma_key  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).pragma_key_t)!=NULL)((*yyvaluep).pragma_key_t)->deep_delete(); }
#line 2700 "bison_parser.cpp"
        break;

    case YYSYMBOL_pragma_value: /* pragma_value  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).pragma_value_t)!=NULL)((*yyvaluep).pragma_value_t)->deep_delete(); }
#line 2706 "bison_parser.cpp"
        break;

    case YYSYMBOL_schema_name: /* schema_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).schema_name_t)!=NULL)((*yyvaluep).schema_name_t)->deep_delete(); }
#line 2712 "bison_parser.cpp"
        break;

    case YYSYMBOL_pragma_name: /* pragma_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).pragma_name_t)!=NULL)((*yyvaluep).pragma_name_t)->deep_delete(); }
#line 2718 "bison_parser.cpp"
        break;

    case YYSYMBOL_preparable_statement: /* preparable_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).preparable_statement_t)!=NULL)((*yyvaluep).preparable_statement_t)->deep_delete(); }
#line 2724 "bison_parser.cpp"
        break;

    case YYSYMBOL_rollback_statement: /* rollback_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).rollback_statement_t)!=NULL)((*yyvaluep).rollback_statement_t)->deep_delete(); }
#line 2730 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_transaction: /* opt_transaction  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_transaction_t)!=NULL)((*yyvaluep).opt_transaction_t)->deep_delete(); }
#line 2736 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_to_savepoint: /* opt_to_savepoint  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_to_savepoint_t)!=NULL)((*yyvaluep).opt_to_savepoint_t)->deep_delete(); }
#line 2742 "bison_parser.cpp"
        break;

    case YYSYMBOL_vacuum_statement: /* vacuum_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).vacuum_statement_t)!=NULL)((*yyvaluep).vacuum_statement_t)->deep_delete(); }
#line 2748 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_schema_name: /* opt_schema_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_schema_name_t)!=NULL)((*yyvaluep).opt_schema_name_t)->deep_delete(); }
#line 2754 "bison_parser.cpp"
        break;

    case YYSYMBOL_begin_statement: /* begin_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).begin_statement_t)!=NULL)((*yyvaluep).begin_statement_t)->deep_delete(); }
#line 2760 "bison_parser.cpp"
        break;

    case YYSYMBOL_commit_statement: /* commit_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).commit_statement_t)!=NULL)((*yyvaluep).commit_statement_t)->deep_delete(); }
#line 2766 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_upsert_clause: /* opt_upsert_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_upsert_clause_t)!=NULL)((*yyvaluep).opt_upsert_clause_t)->deep_delete(); }
#line 2772 "bison_parser.cpp"
        break;

    case YYSYMBOL_upsert_clause: /* upsert_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).upsert_clause_t)!=NULL)((*yyvaluep).upsert_clause_t)->deep_delete(); }
#line 2778 "bison_parser.cpp"
        break;

    case YYSYMBOL_indexed_column_list: /* indexed_column_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).indexed_column_list_t)!=NULL)((*yyvaluep).indexed_column_list_t)->deep_delete(); }
#line 2784 "bison_parser.cpp"
        break;

    case YYSYMBOL_indexed_column: /* indexed_column  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).indexed_column_t)!=NULL)((*yyvaluep).indexed_column_t)->deep_delete(); }
#line 2790 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_collate: /* opt_collate  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_collate_t)!=NULL)((*yyvaluep).opt_collate_t)->deep_delete(); }
#line 2796 "bison_parser.cpp"
        break;

    case YYSYMBOL_assign_list: /* assign_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).assign_list_t)!=NULL)((*yyvaluep).assign_list_t)->deep_delete(); }
#line 2802 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_null: /* opt_null  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_null_t)!=NULL)((*yyvaluep).opt_null_t)->deep_delete(); }
#line 2808 "bison_parser.cpp"
        break;

    case YYSYMBOL_assign_clause: /* assign_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).assign_clause_t)!=NULL)((*yyvaluep).assign_clause_t)->deep_delete(); }
#line 2814 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_name_list: /* column_name_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_name_list_t)!=NULL)((*yyvaluep).column_name_list_t)->deep_delete(); }
#line 2820 "bison_parser.cpp"
        break;

    case YYSYMBOL_collation_name: /* collation_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).collation_name_t)!=NULL)((*yyvaluep).collation_name_t)->deep_delete(); }
#line 2826 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_hints: /* opt_hints  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).optional_hints_t)!=NULL)((*yyvaluep).optional_hints_t)->deep_delete(); }
#line 2832 "bison_parser.cpp"
        break;

    case YYSYMBOL_hint_list: /* hint_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).hint_list_t)!=NULL)((*yyvaluep).hint_list_t)->deep_delete(); }
#line 2838 "bison_parser.cpp"
        break;

    case YYSYMBOL_hint: /* hint  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).hint_t)!=NULL)((*yyvaluep).hint_t)->deep_delete(); }
#line 2844 "bison_parser.cpp"
        break;

    case YYSYMBOL_prepare_statement: /* prepare_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).prepare_statement_t)!=NULL)((*yyvaluep).prepare_statement_t)->deep_delete(); }
#line 2850 "bison_parser.cpp"
        break;

    case YYSYMBOL_prepare_target_query: /* prepare_target_query  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).prepare_target_query_t)!=NULL)((*yyvaluep).prepare_target_query_t)->deep_delete(); }
#line 2856 "bison_parser.cpp"
        break;

    case YYSYMBOL_execute_statement: /* execute_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).execute_statement_t)!=NULL)((*yyvaluep).execute_statement_t)->deep_delete(); }
#line 2862 "bison_parser.cpp"
        break;

    case YYSYMBOL_import_statement: /* import_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).import_statement_t)!=NULL)((*yyvaluep).import_statement_t)->deep_delete(); }
#line 2868 "bison_parser.cpp"
        break;

    case YYSYMBOL_import_file_type: /* import_file_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).import_file_type_t)!=NULL)((*yyvaluep).import_file_type_t)->deep_delete(); }
#line 2874 "bison_parser.cpp"
        break;

    case YYSYMBOL_file_path: /* file_path  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).file_path_t)!=NULL)((*yyvaluep).file_path_t)->deep_delete(); }
#line 2880 "bison_parser.cpp"
        break;

    case YYSYMBOL_show_statement: /* show_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).show_statement_t)!=NULL)((*yyvaluep).show_statement_t)->deep_delete(); }
#line 2886 "bison_parser.cpp"
        break;

    case YYSYMBOL_alter_statement: /* alter_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).alter_statement_t)!=NULL)((*yyvaluep).alter_statement_t)->deep_delete(); }
#line 2892 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_column: /* opt_column  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_column_t)!=NULL)((*yyvaluep).opt_column_t)->deep_delete(); }
#line 2898 "bison_parser.cpp"
        break;

    case YYSYMBOL_create_statement: /* create_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).create_statement_t)!=NULL)((*yyvaluep).create_statement_t)->deep_delete(); }
#line 2904 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_def_list_no_type: /* column_def_list_no_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_def_list_no_type_t)!=NULL)((*yyvaluep).column_def_list_no_type_t)->deep_delete(); }
#line 2910 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_def_no_type: /* column_def_no_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_def_no_type_t)!=NULL)((*yyvaluep).column_def_no_type_t)->deep_delete(); }
#line 2916 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_tmp: /* opt_tmp  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_tmp_t)!=NULL)((*yyvaluep).opt_tmp_t)->deep_delete(); }
#line 2922 "bison_parser.cpp"
        break;

    case YYSYMBOL_CreateInparan: /* CreateInparan  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).CreateInparan_t)!=NULL)((*yyvaluep).CreateInparan_t)->deep_delete(); }
#line 2928 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_ForeignKeylist: /* opt_ForeignKeylist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_ForeignKeylist_t)!=NULL)((*yyvaluep).opt_ForeignKeylist_t)->deep_delete(); }
#line 2934 "bison_parser.cpp"
        break;

    case YYSYMBOL_ForeignKeylist: /* ForeignKeylist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ForeignKeylist_t)!=NULL)((*yyvaluep).ForeignKeylist_t)->deep_delete(); }
#line 2940 "bison_parser.cpp"
        break;

    case YYSYMBOL_ForeignKey: /* ForeignKey  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ForeignKey_t)!=NULL)((*yyvaluep).ForeignKey_t)->deep_delete(); }
#line 2946 "bison_parser.cpp"
        break;

    case YYSYMBOL_FkNoOptstmt: /* FkNoOptstmt  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).FkNoOptstmt_t)!=NULL)((*yyvaluep).FkNoOptstmt_t)->deep_delete(); }
#line 2952 "bison_parser.cpp"
        break;

    case YYSYMBOL_ForeignKeyColumn: /* ForeignKeyColumn  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ForeignKeyColumn_t)!=NULL)((*yyvaluep).ForeignKeyColumn_t)->deep_delete(); }
#line 2958 "bison_parser.cpp"
        break;

    case YYSYMBOL_ForeignKeyRef: /* ForeignKeyRef  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ForeignKeyRef_t)!=NULL)((*yyvaluep).ForeignKeyRef_t)->deep_delete(); }
#line 2964 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_Actiontypelist: /* opt_Actiontypelist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_Actiontypelist_t)!=NULL)((*yyvaluep).opt_Actiontypelist_t)->deep_delete(); }
#line 2970 "bison_parser.cpp"
        break;

    case YYSYMBOL_Action_typelist: /* Action_typelist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Action_typelist_t)!=NULL)((*yyvaluep).Action_typelist_t)->deep_delete(); }
#line 2976 "bison_parser.cpp"
        break;

    case YYSYMBOL_Action_type: /* Action_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Action_type_t)!=NULL)((*yyvaluep).Action_type_t)->deep_delete(); }
#line 2982 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnInParen_ForeignKey: /* ColumnInParen_ForeignKey  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Column_In_Paren_ForeignKey_t)!=NULL)((*yyvaluep).Column_In_Paren_ForeignKey_t)->deep_delete(); }
#line 2988 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnNameList_ForeignKey: /* ColumnNameList_ForeignKey  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ColumnNameList_ForeignKey_t)!=NULL)((*yyvaluep).ColumnNameList_ForeignKey_t)->deep_delete(); }
#line 2994 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnName_ForeignKey: /* ColumnName_ForeignKey  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ColumnName_ForeignKey_t)!=NULL)((*yyvaluep).ColumnName_ForeignKey_t)->deep_delete(); }
#line 3000 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnInParen_References: /* ColumnInParen_References  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Column_In_Paren_References_t)!=NULL)((*yyvaluep).Column_In_Paren_References_t)->deep_delete(); }
#line 3006 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnNameList_References: /* ColumnNameList_References  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ColumnNameList_References_t)!=NULL)((*yyvaluep).ColumnNameList_References_t)->deep_delete(); }
#line 3012 "bison_parser.cpp"
        break;

    case YYSYMBOL_ColumnName_References: /* ColumnName_References  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ColumnName_References_t)!=NULL)((*yyvaluep).ColumnName_References_t)->deep_delete(); }
#line 3018 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_unique: /* opt_unique  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_unique_t)!=NULL)((*yyvaluep).opt_unique_t)->deep_delete(); }
#line 3024 "bison_parser.cpp"
        break;

    case YYSYMBOL_index_name: /* index_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).index_name_t)!=NULL)((*yyvaluep).index_name_t)->deep_delete(); }
#line 3030 "bison_parser.cpp"
        break;

    case YYSYMBOL_trigger_declare: /* trigger_declare  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).trigger_declare_t)!=NULL)((*yyvaluep).trigger_declare_t)->deep_delete(); }
#line 3036 "bison_parser.cpp"
        break;

    case YYSYMBOL_trigger_name: /* trigger_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).trigger_name_t)!=NULL)((*yyvaluep).trigger_name_t)->deep_delete(); }
#line 3042 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_trigger_time: /* opt_trigger_time  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_trigger_time_t)!=NULL)((*yyvaluep).opt_trigger_time_t)->deep_delete(); }
#line 3048 "bison_parser.cpp"
        break;

    case YYSYMBOL_trigger_event: /* trigger_event  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).trigger_event_t)!=NULL)((*yyvaluep).trigger_event_t)->deep_delete(); }
#line 3054 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_of_column_list: /* opt_of_column_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_of_column_list_t)!=NULL)((*yyvaluep).opt_of_column_list_t)->deep_delete(); }
#line 3060 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_for_each: /* opt_for_each  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_for_each_t)!=NULL)((*yyvaluep).opt_for_each_t)->deep_delete(); }
#line 3066 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_when: /* opt_when  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_when_t)!=NULL)((*yyvaluep).opt_when_t)->deep_delete(); }
#line 3072 "bison_parser.cpp"
        break;

    case YYSYMBOL_trigger_cmd_list: /* trigger_cmd_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).trigger_cmd_list_t)!=NULL)((*yyvaluep).trigger_cmd_list_t)->deep_delete(); }
#line 3078 "bison_parser.cpp"
        break;

    case YYSYMBOL_trigger_cmd: /* trigger_cmd  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).trigger_cmd_t)!=NULL)((*yyvaluep).trigger_cmd_t)->deep_delete(); }
#line 3084 "bison_parser.cpp"
        break;

    case YYSYMBOL_module_name: /* module_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).module_name_t)!=NULL)((*yyvaluep).module_name_t)->deep_delete(); }
#line 3090 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_not_exists: /* opt_not_exists  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_not_exists_t)!=NULL)((*yyvaluep).opt_not_exists_t)->deep_delete(); }
#line 3096 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_def_commalist: /* column_def_commalist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_def_comma_list_t)!=NULL)((*yyvaluep).column_def_comma_list_t)->deep_delete(); }
#line 3102 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_def: /* column_def  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_def_t)!=NULL)((*yyvaluep).column_def_t)->deep_delete(); }
#line 3108 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_column_arglist: /* opt_column_arglist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_column_arglist_t)!=NULL)((*yyvaluep).opt_column_arglist_t)->deep_delete(); }
#line 3114 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_arglist: /* column_arglist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_arglist_t)!=NULL)((*yyvaluep).column_arglist_t)->deep_delete(); }
#line 3120 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_arg: /* column_arg  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_arg_t)!=NULL)((*yyvaluep).column_arg_t)->deep_delete(); }
#line 3126 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_generatedarg: /* opt_generatedarg  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_generatedarg_t)!=NULL)((*yyvaluep).opt_generatedarg_t)->deep_delete(); }
#line 3132 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_on_conflict: /* opt_on_conflict  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_on_conflict_t)!=NULL)((*yyvaluep).opt_on_conflict_t)->deep_delete(); }
#line 3138 "bison_parser.cpp"
        break;

    case YYSYMBOL_resolve_type: /* resolve_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).resolve_type_t)!=NULL)((*yyvaluep).resolve_type_t)->deep_delete(); }
#line 3144 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_autoinc: /* opt_autoinc  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_autoinc_t)!=NULL)((*yyvaluep).opt_autoinc_t)->deep_delete(); }
#line 3150 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_type: /* column_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_type_t)!=NULL)((*yyvaluep).column_type_t)->deep_delete(); }
#line 3156 "bison_parser.cpp"
        break;

    case YYSYMBOL_drop_statement: /* drop_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).drop_statement_t)!=NULL)((*yyvaluep).drop_statement_t)->deep_delete(); }
#line 3162 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_exists: /* opt_exists  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_exists_t)!=NULL)((*yyvaluep).opt_exists_t)->deep_delete(); }
#line 3168 "bison_parser.cpp"
        break;

    case YYSYMBOL_delete_statement: /* delete_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).delete_statement_t)!=NULL)((*yyvaluep).delete_statement_t)->deep_delete(); }
#line 3174 "bison_parser.cpp"
        break;

    case YYSYMBOL_truncate_statement: /* truncate_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).delete_statement_t)!=NULL)((*yyvaluep).delete_statement_t)->deep_delete(); }
#line 3180 "bison_parser.cpp"
        break;

    case YYSYMBOL_insert_statement: /* insert_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).insert_statement_t)!=NULL)((*yyvaluep).insert_statement_t)->deep_delete(); }
#line 3186 "bison_parser.cpp"
        break;

    case YYSYMBOL_super_list: /* super_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).super_list_t)!=NULL)((*yyvaluep).super_list_t)->deep_delete(); }
#line 3192 "bison_parser.cpp"
        break;

    case YYSYMBOL_insert_type: /* insert_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).insert_type_t)!=NULL)((*yyvaluep).insert_type_t)->deep_delete(); }
#line 3198 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_column_list: /* opt_column_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_column_list_t)!=NULL)((*yyvaluep).opt_column_list_t)->deep_delete(); }
#line 3204 "bison_parser.cpp"
        break;

    case YYSYMBOL_update_statement: /* update_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).update_statement_t)!=NULL)((*yyvaluep).update_statement_t)->deep_delete(); }
#line 3210 "bison_parser.cpp"
        break;

    case YYSYMBOL_update_clause_commalist: /* update_clause_commalist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).update_clause_commalist_t)!=NULL)((*yyvaluep).update_clause_commalist_t)->deep_delete(); }
#line 3216 "bison_parser.cpp"
        break;

    case YYSYMBOL_update_clause: /* update_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).update_clause_t)!=NULL)((*yyvaluep).update_clause_t)->deep_delete(); }
#line 3222 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_statement: /* select_statement  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_statement_t)!=NULL)((*yyvaluep).select_statement_t)->deep_delete(); }
#line 3228 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_with_paren: /* select_with_paren  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_with_paren_t)!=NULL)((*yyvaluep).select_with_paren_t)->deep_delete(); }
#line 3234 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_paren_or_clause: /* select_paren_or_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_paren_or_clause_t)!=NULL)((*yyvaluep).select_paren_or_clause_t)->deep_delete(); }
#line 3240 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_no_paren: /* select_no_paren  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_no_paren_t)!=NULL)((*yyvaluep).select_no_paren_t)->deep_delete(); }
#line 3246 "bison_parser.cpp"
        break;

    case YYSYMBOL_set_operator: /* set_operator  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).set_operator_t)!=NULL)((*yyvaluep).set_operator_t)->deep_delete(); }
#line 3252 "bison_parser.cpp"
        break;

    case YYSYMBOL_set_type: /* set_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).set_type_t)!=NULL)((*yyvaluep).set_type_t)->deep_delete(); }
#line 3258 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_all: /* opt_all  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_all_t)!=NULL)((*yyvaluep).opt_all_t)->deep_delete(); }
#line 3264 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_clause: /* select_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_clause_t)!=NULL)((*yyvaluep).select_clause_t)->deep_delete(); }
#line 3270 "bison_parser.cpp"
        break;

    case YYSYMBOL_window_clause: /* window_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_clause_t)!=NULL)((*yyvaluep).window_clause_t)->deep_delete(); }
#line 3276 "bison_parser.cpp"
        break;

    case YYSYMBOL_windowdefn_list: /* windowdefn_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_defn_list_t)!=NULL)((*yyvaluep).window_defn_list_t)->deep_delete(); }
#line 3282 "bison_parser.cpp"
        break;

    case YYSYMBOL_windowdefn: /* windowdefn  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_defn_t)!=NULL)((*yyvaluep).window_defn_t)->deep_delete(); }
#line 3288 "bison_parser.cpp"
        break;

    case YYSYMBOL_window: /* window  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_t)!=NULL)((*yyvaluep).window_t)->deep_delete(); }
#line 3294 "bison_parser.cpp"
        break;

    case YYSYMBOL_window_with_order: /* window_with_order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_with_order_t)!=NULL)((*yyvaluep).window_with_order_t)->deep_delete(); }
#line 3300 "bison_parser.cpp"
        break;

    case YYSYMBOL_window_no_order: /* window_no_order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_no_order_t)!=NULL)((*yyvaluep).window_no_order_t)->deep_delete(); }
#line 3306 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_base_window_name: /* opt_base_window_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_base_window_name_t)!=NULL)((*yyvaluep).opt_base_window_name_t)->deep_delete(); }
#line 3312 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_frame: /* opt_frame  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_frame_t)!=NULL)((*yyvaluep).opt_frame_t)->deep_delete(); }
#line 3318 "bison_parser.cpp"
        break;

    case YYSYMBOL_range_or_rows: /* range_or_rows  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).range_or_rows_t)!=NULL)((*yyvaluep).range_or_rows_t)->deep_delete(); }
#line 3324 "bison_parser.cpp"
        break;

    case YYSYMBOL_frame_bound_s: /* frame_bound_s  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).frame_bound_s_t)!=NULL)((*yyvaluep).frame_bound_s_t)->deep_delete(); }
#line 3330 "bison_parser.cpp"
        break;

    case YYSYMBOL_frame_bound_e: /* frame_bound_e  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).frame_bound_e_t)!=NULL)((*yyvaluep).frame_bound_e_t)->deep_delete(); }
#line 3336 "bison_parser.cpp"
        break;

    case YYSYMBOL_frame_bound: /* frame_bound  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).frame_bound_t)!=NULL)((*yyvaluep).frame_bound_t)->deep_delete(); }
#line 3342 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_frame_exclude: /* opt_frame_exclude  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_frame_exclude_t)!=NULL)((*yyvaluep).opt_frame_exclude_t)->deep_delete(); }
#line 3348 "bison_parser.cpp"
        break;

    case YYSYMBOL_frame_exclude: /* frame_exclude  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).frame_exclude_t)!=NULL)((*yyvaluep).frame_exclude_t)->deep_delete(); }
#line 3354 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_distinct: /* opt_distinct  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_distinct_t)!=NULL)((*yyvaluep).opt_distinct_t)->deep_delete(); }
#line 3360 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_list: /* select_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_list_t)!=NULL)((*yyvaluep).select_list_t)->deep_delete(); }
#line 3366 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_from_clause: /* opt_from_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_from_clause_t)!=NULL)((*yyvaluep).opt_from_clause_t)->deep_delete(); }
#line 3372 "bison_parser.cpp"
        break;

    case YYSYMBOL_from_clause: /* from_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).from_clause_t)!=NULL)((*yyvaluep).from_clause_t)->deep_delete(); }
#line 3378 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_where: /* opt_where  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_where_t)!=NULL)((*yyvaluep).opt_where_t)->deep_delete(); }
#line 3384 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_group: /* opt_group  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_group_t)!=NULL)((*yyvaluep).opt_group_t)->deep_delete(); }
#line 3390 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_having: /* opt_having  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_having_t)!=NULL)((*yyvaluep).opt_having_t)->deep_delete(); }
#line 3396 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_order: /* opt_order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_order_t)!=NULL)((*yyvaluep).opt_order_t)->deep_delete(); }
#line 3402 "bison_parser.cpp"
        break;

    case YYSYMBOL_order: /* order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).order_t)!=NULL)((*yyvaluep).order_t)->deep_delete(); }
#line 3408 "bison_parser.cpp"
        break;

    case YYSYMBOL_order_list: /* order_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).order_list_t)!=NULL)((*yyvaluep).order_list_t)->deep_delete(); }
#line 3414 "bison_parser.cpp"
        break;

    case YYSYMBOL_order_desc: /* order_desc  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).order_desc_t)!=NULL)((*yyvaluep).order_desc_t)->deep_delete(); }
#line 3420 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_order_type: /* opt_order_type  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_order_type_t)!=NULL)((*yyvaluep).opt_order_type_t)->deep_delete(); }
#line 3426 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_top: /* opt_top  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_top_t)!=NULL)((*yyvaluep).opt_top_t)->deep_delete(); }
#line 3432 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_limit: /* opt_limit  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_limit_t)!=NULL)((*yyvaluep).opt_limit_t)->deep_delete(); }
#line 3438 "bison_parser.cpp"
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).expr_list_t)!=NULL)((*yyvaluep).expr_list_t)->deep_delete(); }
#line 3444 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_literal_list: /* opt_literal_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_literal_list_t)!=NULL)((*yyvaluep).opt_literal_list_t)->deep_delete(); }
#line 3450 "bison_parser.cpp"
        break;

    case YYSYMBOL_literal_list: /* literal_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).literal_list_t)!=NULL)((*yyvaluep).literal_list_t)->deep_delete(); }
#line 3456 "bison_parser.cpp"
        break;

    case YYSYMBOL_expr_alias: /* expr_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).expr_alias_t)!=NULL)((*yyvaluep).expr_alias_t)->deep_delete(); }
#line 3462 "bison_parser.cpp"
        break;

    case YYSYMBOL_expr: /* expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).expr_t)!=NULL)((*yyvaluep).expr_t)->deep_delete(); }
#line 3468 "bison_parser.cpp"
        break;

    case YYSYMBOL_operand: /* operand  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).operand_t)!=NULL)((*yyvaluep).operand_t)->deep_delete(); }
#line 3474 "bison_parser.cpp"
        break;

    case YYSYMBOL_json_expr: /* json_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).json_expr_t)!=NULL)((*yyvaluep).json_expr_t)->deep_delete(); }
#line 3480 "bison_parser.cpp"
        break;

    case YYSYMBOL_Jsonexpr_all: /* Jsonexpr_all  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Jsonexpr_all_t)!=NULL)((*yyvaluep).Jsonexpr_all_t)->deep_delete(); }
#line 3486 "bison_parser.cpp"
        break;

    case YYSYMBOL_Jsondata: /* Jsondata  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Jsondata_t)!=NULL)((*yyvaluep).Jsondata_t)->deep_delete(); }
#line 3492 "bison_parser.cpp"
        break;

    case YYSYMBOL_Jsonpath: /* Jsonpath  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).Jsonpath_t)!=NULL)((*yyvaluep).Jsonpath_t)->deep_delete(); }
#line 3498 "bison_parser.cpp"
        break;

    case YYSYMBOL_cast_expr: /* cast_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).cast_expr_t)!=NULL)((*yyvaluep).cast_expr_t)->deep_delete(); }
#line 3504 "bison_parser.cpp"
        break;

    case YYSYMBOL_scalar_expr: /* scalar_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).scalar_expr_t)!=NULL)((*yyvaluep).scalar_expr_t)->deep_delete(); }
#line 3510 "bison_parser.cpp"
        break;

    case YYSYMBOL_unary_expr: /* unary_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).unary_expr_t)!=NULL)((*yyvaluep).unary_expr_t)->deep_delete(); }
#line 3516 "bison_parser.cpp"
        break;

    case YYSYMBOL_binary_expr: /* binary_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).binary_expr_t)!=NULL)((*yyvaluep).binary_expr_t)->deep_delete(); }
#line 3522 "bison_parser.cpp"
        break;

    case YYSYMBOL_fts_query_literal: /* fts_query_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).fts_query_literal_t)!=NULL)((*yyvaluep).fts_query_literal_t)->deep_delete(); }
#line 3528 "bison_parser.cpp"
        break;

    case YYSYMBOL_logic_expr: /* logic_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).logic_expr_t)!=NULL)((*yyvaluep).logic_expr_t)->deep_delete(); }
#line 3534 "bison_parser.cpp"
        break;

    case YYSYMBOL_in_expr: /* in_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).in_expr_t)!=NULL)((*yyvaluep).in_expr_t)->deep_delete(); }
#line 3540 "bison_parser.cpp"
        break;

    case YYSYMBOL_case_expr: /* case_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).case_expr_t)!=NULL)((*yyvaluep).case_expr_t)->deep_delete(); }
#line 3546 "bison_parser.cpp"
        break;

    case YYSYMBOL_case_list: /* case_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).case_list_t)!=NULL)((*yyvaluep).case_list_t)->deep_delete(); }
#line 3552 "bison_parser.cpp"
        break;

    case YYSYMBOL_exists_expr: /* exists_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).exists_expr_t)!=NULL)((*yyvaluep).exists_expr_t)->deep_delete(); }
#line 3558 "bison_parser.cpp"
        break;

    case YYSYMBOL_comp_expr: /* comp_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).comp_expr_t)!=NULL)((*yyvaluep).comp_expr_t)->deep_delete(); }
#line 3564 "bison_parser.cpp"
        break;

    case YYSYMBOL_function_expr: /* function_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).function_expr_t)!=NULL)((*yyvaluep).function_expr_t)->deep_delete(); }
#line 3570 "bison_parser.cpp"
        break;

    case YYSYMBOL_aggregation_func: /* aggregation_func  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).aggregation_func_t)!=NULL)((*yyvaluep).aggregation_func_t)->deep_delete(); }
#line 3576 "bison_parser.cpp"
        break;

    case YYSYMBOL_window_func_no_arg: /* window_func_no_arg  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_func_no_arg_t)!=NULL)((*yyvaluep).window_func_no_arg_t)->deep_delete(); }
#line 3582 "bison_parser.cpp"
        break;

    case YYSYMBOL_window_func: /* window_func  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).window_func_t)!=NULL)((*yyvaluep).window_func_t)->deep_delete(); }
#line 3588 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_over_clause: /* opt_over_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_over_clause_t)!=NULL)((*yyvaluep).opt_over_clause_t)->deep_delete(); }
#line 3594 "bison_parser.cpp"
        break;

    case YYSYMBOL_over_clause: /* over_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).over_clause_t)!=NULL)((*yyvaluep).over_clause_t)->deep_delete(); }
#line 3600 "bison_parser.cpp"
        break;

    case YYSYMBOL_over_clause_with_order: /* over_clause_with_order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).over_clause_with_order_t)!=NULL)((*yyvaluep).over_clause_with_order_t)->deep_delete(); }
#line 3606 "bison_parser.cpp"
        break;

    case YYSYMBOL_over_clause_no_order: /* over_clause_no_order  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).over_clause_no_order_t)!=NULL)((*yyvaluep).over_clause_no_order_t)->deep_delete(); }
#line 3612 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_filter_clause: /* opt_filter_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_filter_clause_t)!=NULL)((*yyvaluep).opt_filter_clause_t)->deep_delete(); }
#line 3618 "bison_parser.cpp"
        break;

    case YYSYMBOL_extract_expr: /* extract_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).extract_expr_t)!=NULL)((*yyvaluep).extract_expr_t)->deep_delete(); }
#line 3624 "bison_parser.cpp"
        break;

    case YYSYMBOL_datetime_field: /* datetime_field  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).datetime_field_t)!=NULL)((*yyvaluep).datetime_field_t)->deep_delete(); }
#line 3630 "bison_parser.cpp"
        break;

    case YYSYMBOL_array_expr: /* array_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).array_expr_t)!=NULL)((*yyvaluep).array_expr_t)->deep_delete(); }
#line 3636 "bison_parser.cpp"
        break;

    case YYSYMBOL_array_index: /* array_index  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).array_index_t)!=NULL)((*yyvaluep).array_index_t)->deep_delete(); }
#line 3642 "bison_parser.cpp"
        break;

    case YYSYMBOL_between_expr: /* between_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).between_expr_t)!=NULL)((*yyvaluep).between_expr_t)->deep_delete(); }
#line 3648 "bison_parser.cpp"
        break;

    case YYSYMBOL_column_name: /* column_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).column_name_t)!=NULL)((*yyvaluep).column_name_t)->deep_delete(); }
#line 3654 "bison_parser.cpp"
        break;

    case YYSYMBOL_literal: /* literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).literal_t)!=NULL)((*yyvaluep).literal_t)->deep_delete(); }
#line 3660 "bison_parser.cpp"
        break;

    case YYSYMBOL_string_literal: /* string_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).string_literal_t)!=NULL)((*yyvaluep).string_literal_t)->deep_delete(); }
#line 3666 "bison_parser.cpp"
        break;

    case YYSYMBOL_json_literal: /* json_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).json_literal_t)!=NULL)((*yyvaluep).json_literal_t)->deep_delete(); }
#line 3672 "bison_parser.cpp"
        break;

    case YYSYMBOL_json_pathliteral: /* json_pathliteral  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).json_pathliteral_t)!=NULL)((*yyvaluep).json_pathliteral_t)->deep_delete(); }
#line 3678 "bison_parser.cpp"
        break;

    case YYSYMBOL_bool_literal: /* bool_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).bool_literal_t)!=NULL)((*yyvaluep).bool_literal_t)->deep_delete(); }
#line 3684 "bison_parser.cpp"
        break;

    case YYSYMBOL_num_literal: /* num_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).num_literal_t)!=NULL)((*yyvaluep).num_literal_t)->deep_delete(); }
#line 3690 "bison_parser.cpp"
        break;

    case YYSYMBOL_int_literal: /* int_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).int_literal_t)!=NULL)((*yyvaluep).int_literal_t)->deep_delete(); }
#line 3696 "bison_parser.cpp"
        break;

    case YYSYMBOL_null_literal: /* null_literal  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).null_literal_t)!=NULL)((*yyvaluep).null_literal_t)->deep_delete(); }
#line 3702 "bison_parser.cpp"
        break;

    case YYSYMBOL_param_expr: /* param_expr  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).param_expr_t)!=NULL)((*yyvaluep).param_expr_t)->deep_delete(); }
#line 3708 "bison_parser.cpp"
        break;

    case YYSYMBOL_table_ref: /* table_ref  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).table_ref_t)!=NULL)((*yyvaluep).table_ref_t)->deep_delete(); }
#line 3714 "bison_parser.cpp"
        break;

    case YYSYMBOL_table_prefix: /* table_prefix  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).table_prefix_t)!=NULL)((*yyvaluep).table_prefix_t)->deep_delete(); }
#line 3720 "bison_parser.cpp"
        break;

    case YYSYMBOL_join_op: /* join_op  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).join_op_t)!=NULL)((*yyvaluep).join_op_t)->deep_delete(); }
#line 3726 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_index: /* opt_index  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_index_t)!=NULL)((*yyvaluep).opt_index_t)->deep_delete(); }
#line 3732 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_on: /* opt_on  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_on_t)!=NULL)((*yyvaluep).opt_on_t)->deep_delete(); }
#line 3738 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_using: /* opt_using  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_using_t)!=NULL)((*yyvaluep).opt_using_t)->deep_delete(); }
#line 3744 "bison_parser.cpp"
        break;

    case YYSYMBOL_table_ref_name_no_alias: /* table_ref_name_no_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).table_ref_name_no_alias_t)!=NULL)((*yyvaluep).table_ref_name_no_alias_t)->deep_delete(); }
#line 3750 "bison_parser.cpp"
        break;

    case YYSYMBOL_table_name: /* table_name  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).table_name_t)!=NULL)((*yyvaluep).table_name_t)->deep_delete(); }
#line 3756 "bison_parser.cpp"
        break;

    case YYSYMBOL_alias: /* alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).alias_t)!=NULL)((*yyvaluep).alias_t)->deep_delete(); }
#line 3762 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_alias: /* opt_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_alias_t)!=NULL)((*yyvaluep).opt_alias_t)->deep_delete(); }
#line 3768 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_with_clause: /* opt_with_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_with_clause_t)!=NULL)((*yyvaluep).opt_with_clause_t)->deep_delete(); }
#line 3774 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_clause: /* with_clause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_clause_t)!=NULL)((*yyvaluep).with_clause_t)->deep_delete(); }
#line 3780 "bison_parser.cpp"
        break;

    case YYSYMBOL_WithRecursiveClause: /* WithRecursiveClause  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).WithRecursiveClause_t)!=NULL)((*yyvaluep).WithRecursiveClause_t)->deep_delete(); }
#line 3786 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_recursive_description_list: /* with_recursive_description_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_rec_desc_list_t)!=NULL)((*yyvaluep).with_rec_desc_list_t)->deep_delete(); }
#line 3792 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_recursive_description: /* with_recursive_description  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_recursive_description_t)!=NULL)((*yyvaluep).with_recursive_description_t)->deep_delete(); }
#line 3798 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_recursive_select: /* with_recursive_select  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_recursive_select_t)!=NULL)((*yyvaluep).with_recursive_select_t)->deep_delete(); }
#line 3804 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_recursive_select: /* opt_recursive_select  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_recursive_select_t)!=NULL)((*yyvaluep).opt_recursive_select_t)->deep_delete(); }
#line 3810 "bison_parser.cpp"
        break;

    case YYSYMBOL_init_select: /* init_select  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).init_select_t)!=NULL)((*yyvaluep).init_select_t)->deep_delete(); }
#line 3816 "bison_parser.cpp"
        break;

    case YYSYMBOL_select_list_essential_alias: /* select_list_essential_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).select_list_essential_alias_t)!=NULL)((*yyvaluep).select_list_essential_alias_t)->deep_delete(); }
#line 3822 "bison_parser.cpp"
        break;

    case YYSYMBOL_expr_list_essential_alias: /* expr_list_essential_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).expr_list_essential_alias_t)!=NULL)((*yyvaluep).expr_list_essential_alias_t)->deep_delete(); }
#line 3828 "bison_parser.cpp"
        break;

    case YYSYMBOL_expr_essential_alias: /* expr_essential_alias  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).expr_essential_alias_t)!=NULL)((*yyvaluep).expr_essential_alias_t)->deep_delete(); }
#line 3834 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_description_list: /* with_description_list  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_description_list_t)!=NULL)((*yyvaluep).with_description_list_t)->deep_delete(); }
#line 3840 "bison_parser.cpp"
        break;

    case YYSYMBOL_with_description: /* with_description  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).with_description_t)!=NULL)((*yyvaluep).with_description_t)->deep_delete(); }
#line 3846 "bison_parser.cpp"
        break;

    case YYSYMBOL_join_kw: /* join_kw  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).join_kw_t)!=NULL)((*yyvaluep).join_kw_t)->deep_delete(); }
#line 3852 "bison_parser.cpp"
        break;

    case YYSYMBOL_opt_semicolon: /* opt_semicolon  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).opt_semicolon_t)!=NULL)((*yyvaluep).opt_semicolon_t)->deep_delete(); }
#line 3858 "bison_parser.cpp"
        break;

    case YYSYMBOL_ident_commalist: /* ident_commalist  */
#line 629 "bison_parser.y"
            { if(((*yyvaluep).ident_commalist_t)!=NULL)((*yyvaluep).ident_commalist_t)->deep_delete(); }
#line 3864 "bison_parser.cpp"
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (Program * result, yyscan_t scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = SQL_HSQL_EMPTY; /* Cause a token to be read.  */


/* User initialization code.  */
#line 70 "bison_parser.y"
{
    // Initialize
    yylloc.first_column = 0;
    yylloc.last_column = 0;
    yylloc.first_line = 0;
    yylloc.last_line = 0;
    yylloc.total_column = 0;
    yylloc.string_length = 0;
}

#line 3972 "bison_parser.cpp"

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == SQL_HSQL_EMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= SQL_YYEOF)
    {
      yychar = SQL_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == SQL_HSQL_error)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = SQL_HSQL_UNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = SQL_HSQL_EMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* input: statement_list opt_semicolon  */
#line 666 "bison_parser.y"
                                     {
            (yyval.program_t) = NULL;
            result->statement_list_ = (yyvsp[-1].statement_list_t);
            result->opt_semicolon_ = (yyvsp[0].opt_semicolon_t);
        }
#line 4189 "bison_parser.cpp"
    break;

  case 3: /* statement_list: statement  */
#line 675 "bison_parser.y"
                  {
            (yyval.statement_list_t) = new StatementList();
            (yyval.statement_list_t)->v_statement_list_.push_back((yyvsp[0].statement_t));
            
        }
#line 4199 "bison_parser.cpp"
    break;

  case 4: /* statement_list: statement_list ';' statement  */
#line 680 "bison_parser.y"
                                     {
            (yyvsp[-2].statement_list_t)->v_statement_list_.push_back((yyvsp[0].statement_t));
            (yyval.statement_list_t) = (yyvsp[-2].statement_list_t);
        }
#line 4208 "bison_parser.cpp"
    break;

  case 5: /* statement: prepare_statement opt_hints  */
#line 687 "bison_parser.y"
                                    {
            (yyval.statement_t) = new Statement();
            (yyval.statement_t)->sub_type_ = CASE1;
            (yyval.statement_t)->prepare_statement_ = (yyvsp[-1].prepare_statement_t);
            (yyval.statement_t)->optional_hints_ = (yyvsp[0].optional_hints_t);
        }
#line 4219 "bison_parser.cpp"
    break;

  case 6: /* statement: preparable_statement opt_hints  */
#line 693 "bison_parser.y"
                                       {
            (yyval.statement_t) = new Statement();
            (yyval.statement_t)->sub_type_ = CASE0;
            (yyval.statement_t)->preparable_statement_ = (yyvsp[-1].preparable_statement_t);
            (yyval.statement_t)->optional_hints_ = (yyvsp[0].optional_hints_t);
        }
#line 4230 "bison_parser.cpp"
    break;

  case 7: /* statement: show_statement  */
#line 699 "bison_parser.y"
                       {
            (yyval.statement_t) = new Statement();
            (yyval.statement_t)->sub_type_ = CASE2;
            (yyval.statement_t)->show_statement_ = (yyvsp[0].show_statement_t);
        }
#line 4240 "bison_parser.cpp"
    break;

  case 8: /* statement: cmd  */
#line 705 "bison_parser.y"
            {
            (yyval.statement_t) = new Statement();
            (yyval.statement_t)->sub_type_ = CASE3;
            (yyval.statement_t)->cmd_ = (yyvsp[0].cmd_t);
    }
#line 4250 "bison_parser.cpp"
    break;

  case 9: /* cmd: cmd_pragma  */
#line 714 "bison_parser.y"
                   {(yyval.cmd_t) = (yyvsp[0].cmd_pragma_t);}
#line 4256 "bison_parser.cpp"
    break;

  case 10: /* cmd: cmd_reindex  */
#line 715 "bison_parser.y"
                    {(yyval.cmd_t) = (yyvsp[0].cmd_reindex_t);}
#line 4262 "bison_parser.cpp"
    break;

  case 11: /* cmd: cmd_analyze  */
#line 716 "bison_parser.y"
                    {(yyval.cmd_t) = (yyvsp[0].cmd_analyze_t);}
#line 4268 "bison_parser.cpp"
    break;

  case 12: /* cmd: cmd_attach  */
#line 717 "bison_parser.y"
                    {(yyval.cmd_t) = (yyvsp[0].cmd_attach_t);}
#line 4274 "bison_parser.cpp"
    break;

  case 13: /* cmd: cmd_detach  */
#line 718 "bison_parser.y"
                    {(yyval.cmd_t) = (yyvsp[0].cmd_detach_t);}
#line 4280 "bison_parser.cpp"
    break;

  case 14: /* cmd: cmd_release  */
#line 719 "bison_parser.y"
                    {(yyval.cmd_t) = (yyvsp[0].cmd_release_t);}
#line 4286 "bison_parser.cpp"
    break;

  case 15: /* cmd: rollback_statement  */
#line 720 "bison_parser.y"
                           {(yyval.cmd_t) = (yyvsp[0].rollback_statement_t);}
#line 4292 "bison_parser.cpp"
    break;

  case 16: /* cmd: vacuum_statement  */
#line 721 "bison_parser.y"
                         {(yyval.cmd_t) = (yyvsp[0].vacuum_statement_t);}
#line 4298 "bison_parser.cpp"
    break;

  case 17: /* cmd: begin_statement  */
#line 722 "bison_parser.y"
                        {(yyval.cmd_t) = (yyvsp[0].begin_statement_t);}
#line 4304 "bison_parser.cpp"
    break;

  case 18: /* cmd: commit_statement  */
#line 723 "bison_parser.y"
                         {(yyval.cmd_t) = (yyvsp[0].commit_statement_t);}
#line 4310 "bison_parser.cpp"
    break;

  case 19: /* cmd_release: RELEASE SAVEPOINT savepoint_name  */
#line 727 "bison_parser.y"
                                         {
            (yyval.cmd_release_t) = new CmdRelease();
            (yyval.cmd_release_t)->sub_type_ = CASE0;
            (yyval.cmd_release_t)->savepoint_name_ = (yyvsp[0].savepoint_name_t);
        }
#line 4320 "bison_parser.cpp"
    break;

  case 20: /* cmd_release: RELEASE savepoint_name  */
#line 732 "bison_parser.y"
                               {
            (yyval.cmd_release_t) = new CmdRelease();
            (yyval.cmd_release_t)->sub_type_ = CASE1;
            (yyval.cmd_release_t)->savepoint_name_ = (yyvsp[0].savepoint_name_t);
        }
#line 4330 "bison_parser.cpp"
    break;

  case 21: /* savepoint_name: IDENTIFIER  */
#line 740 "bison_parser.y"
                   {
            (yyval.savepoint_name_t) = new SavepointName();
            (yyval.savepoint_name_t)->id_ = new Identifier((yyvsp[0].sval), id_savepoint_name);
            free((yyvsp[0].sval));
        }
#line 4340 "bison_parser.cpp"
    break;

  case 22: /* cmd_pragma: PRAGMA pragma_key  */
#line 748 "bison_parser.y"
                         {
            (yyval.cmd_pragma_t) = new CmdPragma();
            (yyval.cmd_pragma_t)->sub_type_ = CASE0;
            (yyval.cmd_pragma_t)->pragma_key_ = (yyvsp[0].pragma_key_t);
        }
#line 4350 "bison_parser.cpp"
    break;

  case 23: /* cmd_pragma: PRAGMA pragma_key '=' pragma_value  */
#line 753 "bison_parser.y"
                                           {
            (yyval.cmd_pragma_t) = new CmdPragma();
            (yyval.cmd_pragma_t)->sub_type_ = CASE1;
            (yyval.cmd_pragma_t)->pragma_key_ = (yyvsp[-2].pragma_key_t);
            (yyval.cmd_pragma_t)->pragma_value_ = (yyvsp[0].pragma_value_t);
    }
#line 4361 "bison_parser.cpp"
    break;

  case 24: /* cmd_pragma: PRAGMA pragma_key '(' pragma_value ')'  */
#line 759 "bison_parser.y"
                                               {
            (yyval.cmd_pragma_t) = new CmdPragma();
            (yyval.cmd_pragma_t)->sub_type_ = CASE2;
            (yyval.cmd_pragma_t)->pragma_key_ = (yyvsp[-3].pragma_key_t);
            (yyval.cmd_pragma_t)->pragma_value_ = (yyvsp[-1].pragma_value_t);
    }
#line 4372 "bison_parser.cpp"
    break;

  case 25: /* cmd_reindex: REINDEX  */
#line 768 "bison_parser.y"
               {(yyval.cmd_reindex_t) = new CmdReindex(); (yyval.cmd_reindex_t)->sub_type_ = CASE0;}
#line 4378 "bison_parser.cpp"
    break;

  case 26: /* cmd_reindex: REINDEX table_name  */
#line 769 "bison_parser.y"
                           {(yyval.cmd_reindex_t) = new CmdReindex(); (yyval.cmd_reindex_t)->sub_type_ = CASE1; (yyval.cmd_reindex_t)->table_name_ = (yyvsp[0].table_name_t); (yyval.cmd_reindex_t)->table_name_->table_name_->id_type_ = id_top_table_name;}
#line 4384 "bison_parser.cpp"
    break;

  case 27: /* cmd_analyze: ANALYZE  */
#line 773 "bison_parser.y"
               {(yyval.cmd_analyze_t) = new CmdAnalyze(); (yyval.cmd_analyze_t)->sub_type_ = CASE0;}
#line 4390 "bison_parser.cpp"
    break;

  case 28: /* cmd_analyze: ANALYZE table_name  */
#line 774 "bison_parser.y"
                           {(yyval.cmd_analyze_t) = new CmdAnalyze(); (yyval.cmd_analyze_t)->sub_type_ = CASE1; (yyval.cmd_analyze_t)->table_name_ = (yyvsp[0].table_name_t); (yyval.cmd_analyze_t)->table_name_->table_name_->id_type_ = id_top_table_name;}
#line 4396 "bison_parser.cpp"
    break;

  case 29: /* cmd_attach: ATTACH expr AS schema_name  */
#line 778 "bison_parser.y"
                                  {
            (yyval.cmd_attach_t) = new CmdAttach();
            (yyval.cmd_attach_t)->sub_type_ = CASE0;
            (yyval.cmd_attach_t)->expr_ = (yyvsp[-2].expr_t);
            (yyval.cmd_attach_t)->schema_name_ = (yyvsp[0].schema_name_t);
        }
#line 4407 "bison_parser.cpp"
    break;

  case 30: /* cmd_attach: ATTACH DATABASE expr AS schema_name  */
#line 784 "bison_parser.y"
                                           {
            (yyval.cmd_attach_t) = new CmdAttach();
            (yyval.cmd_attach_t)->sub_type_ = CASE1;
            (yyval.cmd_attach_t)->expr_ = (yyvsp[-2].expr_t);
            (yyval.cmd_attach_t)->schema_name_ = (yyvsp[0].schema_name_t);
        }
#line 4418 "bison_parser.cpp"
    break;

  case 31: /* cmd_detach: DETACH schema_name  */
#line 793 "bison_parser.y"
                           {
            (yyval.cmd_detach_t) = new CmdDetach();
            (yyval.cmd_detach_t)->sub_type_ = CASE0;
            (yyval.cmd_detach_t)->schema_name_ = (yyvsp[0].schema_name_t);
        }
#line 4428 "bison_parser.cpp"
    break;

  case 32: /* cmd_detach: DETACH DATABASE schema_name  */
#line 798 "bison_parser.y"
                                   {
            (yyval.cmd_detach_t) = new CmdDetach();
            (yyval.cmd_detach_t)->sub_type_ = CASE1;
            (yyval.cmd_detach_t)->schema_name_ = (yyvsp[0].schema_name_t);
    }
#line 4438 "bison_parser.cpp"
    break;

  case 33: /* pragma_key: pragma_name  */
#line 806 "bison_parser.y"
                    {(yyval.pragma_key_t) = new PragmaKey(); (yyval.pragma_key_t)->sub_type_ = CASE0; (yyval.pragma_key_t)->pragma_name_ = (yyvsp[0].pragma_name_t);}
#line 4444 "bison_parser.cpp"
    break;

  case 34: /* pragma_key: schema_name '.' pragma_name  */
#line 807 "bison_parser.y"
                                    { (yyval.pragma_key_t) = new PragmaKey(); (yyval.pragma_key_t)->sub_type_ = CASE1; (yyval.pragma_key_t)->schema_name_ = (yyvsp[-2].schema_name_t); (yyval.pragma_key_t)->pragma_name_ = (yyvsp[0].pragma_name_t);}
#line 4450 "bison_parser.cpp"
    break;

  case 35: /* pragma_value: num_literal  */
#line 811 "bison_parser.y"
                    {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE0; (yyval.pragma_value_t)->num_literal_ = (yyvsp[0].num_literal_t);}
#line 4456 "bison_parser.cpp"
    break;

  case 36: /* pragma_value: string_literal  */
#line 812 "bison_parser.y"
                       {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE1; (yyval.pragma_value_t)->string_literal_ = (yyvsp[0].string_literal_t);}
#line 4462 "bison_parser.cpp"
    break;

  case 37: /* pragma_value: IDENTIFIER  */
#line 813 "bison_parser.y"
                   {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE2; (yyval.pragma_value_t)->id_ = new Identifier((yyvsp[0].sval), id_pragma_value); free((yyvsp[0].sval));}
#line 4468 "bison_parser.cpp"
    break;

  case 38: /* pragma_value: ON  */
#line 814 "bison_parser.y"
           {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE2; (yyval.pragma_value_t)->id_ = new Identifier("ON", id_pragma_value); }
#line 4474 "bison_parser.cpp"
    break;

  case 39: /* pragma_value: DELETE  */
#line 815 "bison_parser.y"
               {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE2; (yyval.pragma_value_t)->id_ = new Identifier("DELETE", id_pragma_value); }
#line 4480 "bison_parser.cpp"
    break;

  case 40: /* pragma_value: DEFAULT  */
#line 816 "bison_parser.y"
                {(yyval.pragma_value_t) = new PragmaValue(); (yyval.pragma_value_t)->sub_type_ = CASE2; (yyval.pragma_value_t)->id_ = new Identifier("DEFAULT", id_pragma_value); }
#line 4486 "bison_parser.cpp"
    break;

  case 41: /* schema_name: IDENTIFIER  */
#line 820 "bison_parser.y"
                   {
            (yyval.schema_name_t) = new SchemaName(); (yyval.schema_name_t)->id_ = new Identifier((yyvsp[0].sval), id_schema_name); free((yyvsp[0].sval));
            }
#line 4494 "bison_parser.cpp"
    break;

  case 42: /* pragma_name: IDENTIFIER  */
#line 826 "bison_parser.y"
                   {(yyval.pragma_name_t) = new PragmaName(); (yyval.pragma_name_t)->id_ = new Identifier((yyvsp[0].sval), id_pragma_name); free((yyvsp[0].sval));}
#line 4500 "bison_parser.cpp"
    break;

  case 43: /* preparable_statement: select_statement  */
#line 832 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].select_statement_t); }
#line 4506 "bison_parser.cpp"
    break;

  case 44: /* preparable_statement: import_statement  */
#line 833 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].import_statement_t); }
#line 4512 "bison_parser.cpp"
    break;

  case 45: /* preparable_statement: create_statement  */
#line 834 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].create_statement_t); }
#line 4518 "bison_parser.cpp"
    break;

  case 46: /* preparable_statement: insert_statement  */
#line 835 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].insert_statement_t); }
#line 4524 "bison_parser.cpp"
    break;

  case 47: /* preparable_statement: delete_statement  */
#line 836 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].delete_statement_t); }
#line 4530 "bison_parser.cpp"
    break;

  case 48: /* preparable_statement: truncate_statement  */
#line 837 "bison_parser.y"
                           { (yyval.preparable_statement_t) = (yyvsp[0].delete_statement_t); }
#line 4536 "bison_parser.cpp"
    break;

  case 49: /* preparable_statement: update_statement  */
#line 838 "bison_parser.y"
                         { (yyval.preparable_statement_t) = (yyvsp[0].update_statement_t); }
#line 4542 "bison_parser.cpp"
    break;

  case 50: /* preparable_statement: drop_statement  */
#line 839 "bison_parser.y"
                       { (yyval.preparable_statement_t) = (yyvsp[0].drop_statement_t); }
#line 4548 "bison_parser.cpp"
    break;

  case 51: /* preparable_statement: execute_statement  */
#line 840 "bison_parser.y"
                          { (yyval.preparable_statement_t) = (yyvsp[0].execute_statement_t); }
#line 4554 "bison_parser.cpp"
    break;

  case 52: /* preparable_statement: alter_statement  */
#line 841 "bison_parser.y"
                        {(yyval.preparable_statement_t) = (yyvsp[0].alter_statement_t);}
#line 4560 "bison_parser.cpp"
    break;

  case 53: /* rollback_statement: ROLLBACK opt_transaction opt_to_savepoint  */
#line 845 "bison_parser.y"
                                                  {
            (yyval.rollback_statement_t) = new RollbackStatement();
            (yyval.rollback_statement_t)->opt_transaction_ = (yyvsp[-1].opt_transaction_t);
            (yyval.rollback_statement_t)->opt_to_savepoint_ = (yyvsp[0].opt_to_savepoint_t);
        }
#line 4570 "bison_parser.cpp"
    break;

  case 54: /* opt_transaction: TRANSACTION  */
#line 853 "bison_parser.y"
                    {
            (yyval.opt_transaction_t) = new OptTransaction();
            (yyval.opt_transaction_t)->sub_type_ = CASE0;
            (yyval.opt_transaction_t)->str_val_ = string("TRANSACTION");
        }
#line 4580 "bison_parser.cpp"
    break;

  case 55: /* opt_transaction: %empty  */
#line 858 "bison_parser.y"
                   {
            (yyval.opt_transaction_t) = new OptTransaction();
            (yyval.opt_transaction_t)->sub_type_ = CASE1;
            (yyval.opt_transaction_t)->str_val_ = string("");
        }
#line 4590 "bison_parser.cpp"
    break;

  case 56: /* opt_to_savepoint: TO savepoint_name  */
#line 866 "bison_parser.y"
                          {
            (yyval.opt_to_savepoint_t) = new OptToSavepoint();
            (yyval.opt_to_savepoint_t)->sub_type_ = CASE0;
            (yyval.opt_to_savepoint_t)->savepoint_name_ = (yyvsp[0].savepoint_name_t);
        }
#line 4600 "bison_parser.cpp"
    break;

  case 57: /* opt_to_savepoint: TO SAVEPOINT savepoint_name  */
#line 871 "bison_parser.y"
                                    {
            (yyval.opt_to_savepoint_t) = new OptToSavepoint();
            (yyval.opt_to_savepoint_t)->sub_type_ = CASE1;
            (yyval.opt_to_savepoint_t)->savepoint_name_ = (yyvsp[0].savepoint_name_t);
        }
#line 4610 "bison_parser.cpp"
    break;

  case 58: /* opt_to_savepoint: %empty  */
#line 876 "bison_parser.y"
                   {
            (yyval.opt_to_savepoint_t) = new OptToSavepoint();
            (yyval.opt_to_savepoint_t)->sub_type_ = CASE2;
        }
#line 4619 "bison_parser.cpp"
    break;

  case 59: /* vacuum_statement: VACUUM opt_schema_name INTO file_path  */
#line 884 "bison_parser.y"
                                             {
            (yyval.vacuum_statement_t) = new VacuumStatement();
            (yyval.vacuum_statement_t)->sub_type_ = CASE0;
            (yyval.vacuum_statement_t)->opt_schema_name_ = (yyvsp[-2].opt_schema_name_t);
            (yyval.vacuum_statement_t)->file_path_ = (yyvsp[0].file_path_t);
        }
#line 4630 "bison_parser.cpp"
    break;

  case 60: /* vacuum_statement: VACUUM opt_schema_name  */
#line 890 "bison_parser.y"
                              {
            (yyval.vacuum_statement_t) = new VacuumStatement();
            (yyval.vacuum_statement_t)->sub_type_ = CASE1;
            (yyval.vacuum_statement_t)->opt_schema_name_ = (yyvsp[0].opt_schema_name_t);
        }
#line 4640 "bison_parser.cpp"
    break;

  case 61: /* opt_schema_name: schema_name  */
#line 898 "bison_parser.y"
                    {
            (yyval.opt_schema_name_t) = new OptSchemaName();
            (yyval.opt_schema_name_t)->sub_type_ = CASE0;
            (yyval.opt_schema_name_t)->schema_name_ = (yyvsp[0].schema_name_t);
        }
#line 4650 "bison_parser.cpp"
    break;

  case 62: /* opt_schema_name: %empty  */
#line 903 "bison_parser.y"
                  {
            (yyval.opt_schema_name_t) = new OptSchemaName();
            (yyval.opt_schema_name_t)->sub_type_ = CASE1;
        }
#line 4659 "bison_parser.cpp"
    break;

  case 63: /* begin_statement: BEGIN opt_transaction  */
#line 910 "bison_parser.y"
                              {
            (yyval.begin_statement_t) = new BeginStatement();
            (yyval.begin_statement_t)->sub_type_ = CASE0;
            (yyval.begin_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4669 "bison_parser.cpp"
    break;

  case 64: /* begin_statement: BEGIN DEFFERED opt_transaction  */
#line 915 "bison_parser.y"
                                       {
            (yyval.begin_statement_t) = new BeginStatement();
            (yyval.begin_statement_t)->sub_type_ = CASE1;
            (yyval.begin_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4679 "bison_parser.cpp"
    break;

  case 65: /* begin_statement: BEGIN IMEDIATE opt_transaction  */
#line 920 "bison_parser.y"
                                       {
            (yyval.begin_statement_t) = new BeginStatement();
            (yyval.begin_statement_t)->sub_type_ = CASE2;
            (yyval.begin_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4689 "bison_parser.cpp"
    break;

  case 66: /* begin_statement: BEGIN EXCLUSIVE opt_transaction  */
#line 925 "bison_parser.y"
                                        {
            (yyval.begin_statement_t) = new BeginStatement();
            (yyval.begin_statement_t)->sub_type_ = CASE3;
            (yyval.begin_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4699 "bison_parser.cpp"
    break;

  case 67: /* commit_statement: COMMIT opt_transaction  */
#line 933 "bison_parser.y"
                               {
            (yyval.commit_statement_t) = new CommitStatement();
            (yyval.commit_statement_t)->sub_type_ = CASE0;
            (yyval.commit_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4709 "bison_parser.cpp"
    break;

  case 68: /* commit_statement: END opt_transaction  */
#line 938 "bison_parser.y"
                            {
            (yyval.commit_statement_t) = new CommitStatement();
            (yyval.commit_statement_t)->sub_type_ = CASE1;
            (yyval.commit_statement_t)->opt_transaction_ = (yyvsp[0].opt_transaction_t);
        }
#line 4719 "bison_parser.cpp"
    break;

  case 69: /* opt_upsert_clause: upsert_clause  */
#line 947 "bison_parser.y"
                      {(yyval.opt_upsert_clause_t) = new OptUpsertClause(); (yyval.opt_upsert_clause_t)->sub_type_ = CASE0; (yyval.opt_upsert_clause_t)->upsert_clause_ = (yyvsp[0].upsert_clause_t);}
#line 4725 "bison_parser.cpp"
    break;

  case 70: /* opt_upsert_clause: %empty  */
#line 948 "bison_parser.y"
                    {(yyval.opt_upsert_clause_t) = new OptUpsertClause(); (yyval.opt_upsert_clause_t)->sub_type_ = CASE1;}
#line 4731 "bison_parser.cpp"
    break;

  case 71: /* upsert_clause: ON CONFLICT DO NOTHING  */
#line 951 "bison_parser.y"
                               {
            (yyval.upsert_clause_t) = new UpsertClause();
            (yyval.upsert_clause_t)->sub_type_ = CASE0;
        }
#line 4740 "bison_parser.cpp"
    break;

  case 72: /* upsert_clause: ON CONFLICT DO UPDATE SET assign_list opt_where  */
#line 955 "bison_parser.y"
                                                        {
            (yyval.upsert_clause_t) = new UpsertClause();
            (yyval.upsert_clause_t)->sub_type_ = CASE1;
            (yyval.upsert_clause_t)->assign_list_ = (yyvsp[-1].assign_list_t);
            (yyval.upsert_clause_t)->opt_where1_ = (yyvsp[0].opt_where_t);
        }
#line 4751 "bison_parser.cpp"
    break;

  case 73: /* upsert_clause: ON CONFLICT '(' indexed_column_list ')' opt_where DO NOTHING  */
#line 961 "bison_parser.y"
                                                                     {
            (yyval.upsert_clause_t) = new UpsertClause();
            (yyval.upsert_clause_t)->sub_type_ = CASE2;
            (yyval.upsert_clause_t)->indexed_column_list_ = (yyvsp[-4].indexed_column_list_t);
            (yyval.upsert_clause_t)->opt_where1_ = (yyvsp[-2].opt_where_t);
        }
#line 4762 "bison_parser.cpp"
    break;

  case 74: /* upsert_clause: ON CONFLICT '(' indexed_column_list ')' opt_where DO UPDATE SET assign_list opt_where  */
#line 967 "bison_parser.y"
                                                                                              {
            (yyval.upsert_clause_t) = new UpsertClause();
            (yyval.upsert_clause_t)->sub_type_ = CASE3;
            (yyval.upsert_clause_t)->indexed_column_list_ = (yyvsp[-7].indexed_column_list_t);
            (yyval.upsert_clause_t)->opt_where1_ = (yyvsp[-5].opt_where_t);
            (yyval.upsert_clause_t)->assign_list_ = (yyvsp[-1].assign_list_t);
            (yyval.upsert_clause_t)->opt_where2_ = (yyvsp[0].opt_where_t);
        }
#line 4775 "bison_parser.cpp"
    break;

  case 75: /* indexed_column_list: indexed_column  */
#line 979 "bison_parser.y"
                       {
            (yyval.indexed_column_list_t) = new IndexedColumnList();
            (yyval.indexed_column_list_t)->v_indexed_column_list_.push_back((yyvsp[0].indexed_column_t));
        }
#line 4784 "bison_parser.cpp"
    break;

  case 76: /* indexed_column_list: indexed_column_list ',' indexed_column  */
#line 983 "bison_parser.y"
                                               {
            (yyvsp[-2].indexed_column_list_t)->v_indexed_column_list_.push_back((yyvsp[0].indexed_column_t));
            (yyval.indexed_column_list_t) = (yyvsp[-2].indexed_column_list_t);
        }
#line 4793 "bison_parser.cpp"
    break;

  case 77: /* indexed_column: expr opt_collate opt_order_type  */
#line 990 "bison_parser.y"
                                        {
            (yyval.indexed_column_t) = new IndexedColumn();
            (yyval.indexed_column_t)->expr_ = (yyvsp[-2].expr_t);
            (yyval.indexed_column_t)->opt_collate_ = (yyvsp[-1].opt_collate_t);
            (yyval.indexed_column_t)->opt_order_type_ = (yyvsp[0].opt_order_type_t);
        }
#line 4804 "bison_parser.cpp"
    break;

  case 78: /* opt_collate: COLLATE collation_name  */
#line 999 "bison_parser.y"
                               {
            (yyval.opt_collate_t) = new OptCollate();
            (yyval.opt_collate_t)->sub_type_ = CASE0;
            (yyval.opt_collate_t)->collation_name_ = (yyvsp[0].collation_name_t);
        }
#line 4814 "bison_parser.cpp"
    break;

  case 79: /* opt_collate: %empty  */
#line 1004 "bison_parser.y"
                   {
            (yyval.opt_collate_t) = new OptCollate();
            (yyval.opt_collate_t)->sub_type_ = CASE1;
            (yyval.opt_collate_t)->str_val_ = string("");
        }
#line 4824 "bison_parser.cpp"
    break;

  case 80: /* assign_list: assign_clause  */
#line 1013 "bison_parser.y"
                      {
            (yyval.assign_list_t) = new AssignList();
            (yyval.assign_list_t)->v_assign_list_.push_back((yyvsp[0].assign_clause_t));

        }
#line 4834 "bison_parser.cpp"
    break;

  case 81: /* assign_list: assign_list ',' assign_clause  */
#line 1018 "bison_parser.y"
                                      {
            (yyvsp[-2].assign_list_t)->v_assign_list_.push_back((yyvsp[0].assign_clause_t));
            (yyval.assign_list_t) = (yyvsp[-2].assign_list_t);
        }
#line 4843 "bison_parser.cpp"
    break;

  case 82: /* opt_null: NULLS FIRST  */
#line 1026 "bison_parser.y"
                    {
            (yyval.opt_null_t) = new OptNull();
            (yyval.opt_null_t)->str_val_ = string("NULLS FIRST");
        }
#line 4852 "bison_parser.cpp"
    break;

  case 83: /* opt_null: NULLS LAST  */
#line 1030 "bison_parser.y"
                   {
            (yyval.opt_null_t) = new OptNull();
            (yyval.opt_null_t)->str_val_ = string("NULLS LAST");
        }
#line 4861 "bison_parser.cpp"
    break;

  case 84: /* opt_null: %empty  */
#line 1034 "bison_parser.y"
        {
            (yyval.opt_null_t) = new OptNull();
            (yyval.opt_null_t)->str_val_ = string("");
        }
#line 4870 "bison_parser.cpp"
    break;

  case 85: /* assign_clause: column_name_list '=' expr  */
#line 1041 "bison_parser.y"
                                  {
            (yyval.assign_clause_t) = new AssignClause();
            (yyval.assign_clause_t)->column_name_list_ = (yyvsp[-2].column_name_list_t);
            (yyval.assign_clause_t)->expr_ = (yyvsp[0].expr_t);
        }
#line 4880 "bison_parser.cpp"
    break;

  case 86: /* column_name_list: column_name  */
#line 1049 "bison_parser.y"
                    {
            (yyval.column_name_list_t) = new ColumnNameList();
            (yyval.column_name_list_t)->v_column_name_list_.push_back((yyvsp[0].column_name_t));
        }
#line 4889 "bison_parser.cpp"
    break;

  case 87: /* column_name_list: column_name_list ',' column_name  */
#line 1053 "bison_parser.y"
                                         {
            (yyvsp[-2].column_name_list_t)->v_column_name_list_.push_back((yyvsp[0].column_name_t));
            (yyval.column_name_list_t) = (yyvsp[-2].column_name_list_t);
        }
#line 4898 "bison_parser.cpp"
    break;

  case 88: /* collation_name: IDENTIFIER  */
#line 1060 "bison_parser.y"
                   {
            (yyval.collation_name_t) = new CollationName(); 
            (yyval.collation_name_t)->id_ = new Identifier((yyvsp[0].sval), id_collation_name); 
            free((yyvsp[0].sval));
        }
#line 4908 "bison_parser.cpp"
    break;

  case 89: /* opt_hints: WITH HINT '(' hint_list ')'  */
#line 1072 "bison_parser.y"
                                { 
        (yyval.optional_hints_t) = new OptionalHints();
        (yyval.optional_hints_t)->sub_type_ = CASE0;
        (yyval.optional_hints_t)->hint_list_ = (yyvsp[-1].hint_list_t); 
        }
#line 4918 "bison_parser.cpp"
    break;

  case 90: /* opt_hints: %empty  */
#line 1077 "bison_parser.y"
                { (yyval.optional_hints_t) = new OptionalHints(); (yyval.optional_hints_t)->sub_type_ = CASE1;}
#line 4924 "bison_parser.cpp"
    break;

  case 91: /* hint_list: hint  */
#line 1082 "bison_parser.y"
           { 
          (yyval.hint_list_t) = new HintList();
          (yyval.hint_list_t)->v_hint_list_.push_back((yyvsp[0].hint_t)); 
          }
#line 4933 "bison_parser.cpp"
    break;

  case 92: /* hint_list: hint_list ',' hint  */
#line 1086 "bison_parser.y"
                         { (yyvsp[-2].hint_list_t)->v_hint_list_.push_back((yyvsp[0].hint_t)); (yyval.hint_list_t) = (yyvsp[-2].hint_list_t); }
#line 4939 "bison_parser.cpp"
    break;

  case 93: /* hint: IDENTIFIER  */
#line 1090 "bison_parser.y"
                   {
            (yyval.hint_t) = new Hint();
            (yyval.hint_t)->sub_type_ = CASE1;
            (yyval.hint_t)->id_ = new Identifier((yyvsp[0].sval));
            free((yyvsp[0].sval));
        }
#line 4950 "bison_parser.cpp"
    break;

  case 94: /* hint: IDENTIFIER '(' literal_list ')'  */
#line 1096 "bison_parser.y"
                                      {
            (yyval.hint_t) = new Hint();
            (yyval.hint_t)->sub_type_ = CASE0;
            (yyval.hint_t)->id_ = new Identifier((yyvsp[-3].sval));
            (yyval.hint_t)->literal_list_ = (yyvsp[-1].literal_list_t);
            free((yyvsp[-3].sval));
        }
#line 4962 "bison_parser.cpp"
    break;

  case 95: /* prepare_statement: PREPARE IDENTIFIER FROM prepare_target_query  */
#line 1110 "bison_parser.y"
                                                     {
            (yyval.prepare_statement_t) = new PrepareStatement();
            (yyval.prepare_statement_t)->id_ = new Identifier((yyvsp[-2].sval));
            (yyval.prepare_statement_t)->prep_target_que_ = (yyvsp[0].prepare_target_query_t);
            free((yyvsp[-2].sval));
        }
#line 4973 "bison_parser.cpp"
    break;

  case 96: /* prepare_target_query: STRING  */
#line 1119 "bison_parser.y"
        {
            (yyval.prepare_target_query_t) = new PrepareTargetQuery();
            (yyval.prepare_target_query_t)->prep_target_que_ = "'" + string((yyvsp[0].sval)) + "'"; 
            free((yyvsp[0].sval));
        }
#line 4983 "bison_parser.cpp"
    break;

  case 97: /* execute_statement: EXECUTE IDENTIFIER  */
#line 1127 "bison_parser.y"
                           {
            (yyval.execute_statement_t) = new ExecuteStatement();
            (yyval.execute_statement_t)->sub_type_ = CASE0;
            (yyval.execute_statement_t)->id_ = new Identifier((yyvsp[0].sval));
            free((yyvsp[0].sval));
        }
#line 4994 "bison_parser.cpp"
    break;

  case 98: /* execute_statement: EXECUTE IDENTIFIER '(' opt_literal_list ')'  */
#line 1133 "bison_parser.y"
                                                    {
            (yyval.execute_statement_t) = new ExecuteStatement();
            (yyval.execute_statement_t)->sub_type_ = CASE1;
            (yyval.execute_statement_t)->id_ = new Identifier((yyvsp[-3].sval));
            (yyval.execute_statement_t)->opt_literal_list_ = (yyvsp[-1].opt_literal_list_t);
            free((yyvsp[-3].sval));
        }
#line 5006 "bison_parser.cpp"
    break;

  case 99: /* import_statement: IMPORT FROM import_file_type FILE file_path INTO table_name  */
#line 1147 "bison_parser.y"
                                                                    {
            (yyval.import_statement_t) = new ImportStatement();
            (yyval.import_statement_t)->import_file_type_ = (yyvsp[-4].import_file_type_t);
            (yyval.import_statement_t)->file_path_ = (yyvsp[-2].file_path_t);
            (yyval.import_statement_t)->table_name_ = (yyvsp[0].table_name_t);
        }
#line 5017 "bison_parser.cpp"
    break;

  case 100: /* import_file_type: CSV  */
#line 1156 "bison_parser.y"
            { (yyval.import_file_type_t) = new ImportFileType(); (yyval.import_file_type_t)->str_val_ = "CSV"; }
#line 5023 "bison_parser.cpp"
    break;

  case 101: /* file_path: string_literal  */
#line 1160 "bison_parser.y"
                       { 
            (yyval.file_path_t) = new FilePath();
            (yyval.file_path_t)->str_val_ = (yyvsp[0].string_literal_t)->str_val_;
            delete((yyvsp[0].string_literal_t));
         }
#line 5033 "bison_parser.cpp"
    break;

  case 102: /* show_statement: SHOW TABLES  */
#line 1174 "bison_parser.y"
                    {
            (yyval.show_statement_t) = new ShowStatement();
            (yyval.show_statement_t)->sub_type_ = CASE0;
        }
#line 5042 "bison_parser.cpp"
    break;

  case 103: /* show_statement: SHOW COLUMNS table_name  */
#line 1178 "bison_parser.y"
                                {
            (yyval.show_statement_t) = new ShowStatement();
            (yyval.show_statement_t)->sub_type_ = CASE1;
            (yyval.show_statement_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.show_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
        }
#line 5053 "bison_parser.cpp"
    break;

  case 104: /* show_statement: DESCRIBE table_name  */
#line 1184 "bison_parser.y"
                            {
            (yyval.show_statement_t) = new ShowStatement();
            (yyval.show_statement_t)->sub_type_ = CASE2;
            (yyval.show_statement_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.show_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
        }
#line 5064 "bison_parser.cpp"
    break;

  case 105: /* alter_statement: ALTER TABLE table_name RENAME TO table_name  */
#line 1199 "bison_parser.y"
                                                    {
		(yyval.alter_statement_t) = new AlterStatement();
		(yyval.alter_statement_t)->sub_type_ = CASE0;
        (yyval.alter_statement_t)->table_name1_ = (yyvsp[-3].table_name_t);
        (yyval.alter_statement_t)->table_name2_ = (yyvsp[0].table_name_t);
	}
#line 5075 "bison_parser.cpp"
    break;

  case 106: /* alter_statement: ALTER TABLE table_name RENAME opt_column column_name TO column_name  */
#line 1205 "bison_parser.y"
                                                                            {
		(yyval.alter_statement_t) = new AlterStatement();
		(yyval.alter_statement_t)->sub_type_ = CASE1;
        (yyval.alter_statement_t)->table_name1_ = (yyvsp[-5].table_name_t);
        (yyval.alter_statement_t)->opt_column_ = (yyvsp[-3].opt_column_t);
        (yyval.alter_statement_t)->column_name1_ = (yyvsp[-2].column_name_t);
        (yyval.alter_statement_t)->column_name2_ = (yyvsp[0].column_name_t);
	}
#line 5088 "bison_parser.cpp"
    break;

  case 107: /* alter_statement: ALTER TABLE table_name ADD opt_column column_def  */
#line 1213 "bison_parser.y"
                                                         {
		(yyval.alter_statement_t) = new AlterStatement();
		(yyval.alter_statement_t)->sub_type_ = CASE2;
        (yyval.alter_statement_t)->table_name1_ = (yyvsp[-3].table_name_t);
        (yyval.alter_statement_t)->opt_column_ = (yyvsp[-1].opt_column_t);
        (yyval.alter_statement_t)->column_def_ = (yyvsp[0].column_def_t);
	}
#line 5100 "bison_parser.cpp"
    break;

  case 108: /* opt_column: COLUMN  */
#line 1223 "bison_parser.y"
               {
		(yyval.opt_column_t) = new OptColumn();
		(yyval.opt_column_t)->sub_type_ = CASE0;
        (yyval.opt_column_t)->str_val_ = string("COLUMN");
	}
#line 5110 "bison_parser.cpp"
    break;

  case 109: /* opt_column: %empty  */
#line 1228 "bison_parser.y"
                   {
		(yyval.opt_column_t) = new OptColumn();
		(yyval.opt_column_t)->sub_type_ = CASE1;
        (yyval.opt_column_t)->str_val_ = string("");
	}
#line 5120 "bison_parser.cpp"
    break;

  case 110: /* create_statement: CREATE opt_tmp TABLE opt_not_exists table_name FROM TBL FILE file_path  */
#line 1242 "bison_parser.y"
                                                                               {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE0;
            (yyval.create_statement_t)->OptTmp_ = (yyvsp[-7].opt_tmp_t);
            (yyval.create_statement_t)->opt_not_exists_ = (yyvsp[-5].opt_not_exists_t);
            (yyval.create_statement_t)->table_name_ = (yyvsp[-4].table_name_t);
            (yyval.create_statement_t)->file_path_ = (yyvsp[0].file_path_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
        }
#line 5134 "bison_parser.cpp"
    break;

  case 111: /* create_statement: CREATE opt_tmp TABLE opt_not_exists table_name '(' CreateInparan ')'  */
#line 1251 "bison_parser.y"
                                                                             {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE1;
            (yyval.create_statement_t)->OptTmp_ = (yyvsp[-6].opt_tmp_t);
            (yyval.create_statement_t)->opt_not_exists_ = (yyvsp[-4].opt_not_exists_t);
            (yyval.create_statement_t)->table_name_ = (yyvsp[-3].table_name_t);
            (yyval.create_statement_t)->CreateInparan_ = (yyvsp[-1].CreateInparan_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
        }
#line 5148 "bison_parser.cpp"
    break;

  case 112: /* create_statement: CREATE opt_tmp TABLE opt_not_exists table_name AS select_statement  */
#line 1260 "bison_parser.y"
                                                                           {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE2;
            (yyval.create_statement_t)->OptTmp_ = (yyvsp[-5].opt_tmp_t);
            (yyval.create_statement_t)->opt_not_exists_ = (yyvsp[-3].opt_not_exists_t);
            (yyval.create_statement_t)->table_name_ = (yyvsp[-2].table_name_t);
            (yyval.create_statement_t)->select_statement_ = (yyvsp[0].select_statement_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
        }
#line 5162 "bison_parser.cpp"
    break;

  case 113: /* create_statement: CREATE VIEW table_name opt_column_list AS select_statement  */
#line 1269 "bison_parser.y"
                                                                   {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE3;
            (yyval.create_statement_t)->table_name_ = (yyvsp[-3].table_name_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
            (yyval.create_statement_t)->opt_column_list_ = (yyvsp[-2].opt_column_list_t);
            if((yyval.create_statement_t)->opt_column_list_->sub_type_ == CASE0)
                for(auto &i: (yyval.create_statement_t)->opt_column_list_->ident_comma_list_->v_iden_comma_list_){
                    i->id_type_ = id_create_column_name;
                }
            (yyval.create_statement_t)->select_statement_ = (yyvsp[0].select_statement_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
        }
#line 5180 "bison_parser.cpp"
    break;

  case 114: /* create_statement: CREATE opt_unique INDEX opt_not_exists index_name ON table_name '(' ident_commalist ')' opt_where  */
#line 1282 "bison_parser.y"
                                                                                                          {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE4;
            (yyval.create_statement_t)->opt_unique_ = (yyvsp[-9].opt_unique_t);
            (yyval.create_statement_t)->opt_not_exists_ = (yyvsp[-7].opt_not_exists_t);
            (yyval.create_statement_t)->index_name_ = (yyvsp[-6].index_name_t);   
            (yyval.create_statement_t)->table_name_ = (yyvsp[-4].table_name_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.create_statement_t)->ident_commalist_ = (yyvsp[-2].ident_commalist_t);
            for(auto &i: (yyval.create_statement_t)->ident_commalist_->v_iden_comma_list_){
                i->id_type_ = id_column_name;
            }
            (yyval.create_statement_t)->opt_where_ = (yyvsp[0].opt_where_t);
        }
#line 5199 "bison_parser.cpp"
    break;

  case 115: /* create_statement: CREATE VIRTUAL TABLE opt_not_exists table_name USING module_name '(' column_def_list_no_type ')'  */
#line 1296 "bison_parser.y"
                                                                                                          {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE6;
            (yyval.create_statement_t)->opt_not_exists_ = (yyvsp[-6].opt_not_exists_t);
            (yyval.create_statement_t)->table_name_ = (yyvsp[-5].table_name_t);
            (yyval.create_statement_t)->module_name_ = (yyvsp[-3].module_name_t);
            (yyval.create_statement_t)->table_name_->table_name_->id_type_ = id_create_table_name;
            (yyval.create_statement_t)->ColumnDefListNoType_ = (yyvsp[-1].column_def_list_no_type_t);
        }
#line 5213 "bison_parser.cpp"
    break;

  case 116: /* create_statement: CREATE trigger_declare BEGIN trigger_cmd_list END  */
#line 1305 "bison_parser.y"
                                                          {
            (yyval.create_statement_t) = new CreateStatement();
            (yyval.create_statement_t)->sub_type_ = CASE7;
            (yyval.create_statement_t)->trigger_declare_ = (yyvsp[-3].trigger_declare_t);
            (yyval.create_statement_t)->trigger_cmd_list_ = (yyvsp[-1].trigger_cmd_list_t);
        }
#line 5224 "bison_parser.cpp"
    break;

  case 117: /* column_def_list_no_type: column_def_no_type  */
#line 1313 "bison_parser.y"
                           { 
            (yyval.column_def_list_no_type_t) = new ColumnDefListNoType(); 
            (yyval.column_def_list_no_type_t)->v_column_def_no_type_list_.push_back((yyvsp[0].column_def_no_type_t));
        }
#line 5233 "bison_parser.cpp"
    break;

  case 118: /* column_def_list_no_type: column_def_list_no_type ',' column_def_no_type  */
#line 1317 "bison_parser.y"
                                                       { 
            (yyvsp[-2].column_def_list_no_type_t)->v_column_def_no_type_list_.push_back((yyvsp[0].column_def_no_type_t));
            (yyval.column_def_list_no_type_t) = (yyvsp[-2].column_def_list_no_type_t);
        }
#line 5242 "bison_parser.cpp"
    break;

  case 119: /* column_def_no_type: IDENTIFIER  */
#line 1324 "bison_parser.y"
                   {
            (yyval.column_def_no_type_t) = new ColumnDefNoType();
			(yyval.column_def_no_type_t)->id_ = new Identifier((yyvsp[0].sval), id_create_column_name);
            free((yyvsp[0].sval)); 
        }
#line 5252 "bison_parser.cpp"
    break;

  case 120: /* opt_tmp: TEMPORARY  */
#line 1332 "bison_parser.y"
                  { (yyval.opt_tmp_t) = new OptTmp(); (yyval.opt_tmp_t)->str_val_ = string("TEMPORARY"); }
#line 5258 "bison_parser.cpp"
    break;

  case 121: /* opt_tmp: TEMP  */
#line 1333 "bison_parser.y"
                 { (yyval.opt_tmp_t) = new OptTmp(); (yyval.opt_tmp_t)->str_val_ = string("TEMP"); }
#line 5264 "bison_parser.cpp"
    break;

  case 122: /* opt_tmp: %empty  */
#line 1334 "bison_parser.y"
                        { (yyval.opt_tmp_t) = new OptTmp(); (yyval.opt_tmp_t)->str_val_ = string(""); }
#line 5270 "bison_parser.cpp"
    break;

  case 123: /* CreateInparan: column_def_commalist opt_ForeignKeylist  */
#line 1338 "bison_parser.y"
                                            {
        (yyval.CreateInparan_t) = new CreateInparan(); (yyval.CreateInparan_t)->column_def_commalist_ = (yyvsp[-1].column_def_comma_list_t); (yyval.CreateInparan_t)->opt_ForeignKeylist_ = (yyvsp[0].opt_ForeignKeylist_t); }
#line 5277 "bison_parser.cpp"
    break;

  case 124: /* opt_ForeignKeylist: ',' ForeignKeylist  */
#line 1343 "bison_parser.y"
                           {(yyval.opt_ForeignKeylist_t) = new opt_ForeignKeylist(); (yyval.opt_ForeignKeylist_t)->sub_type_ = CASE0; (yyval.opt_ForeignKeylist_t)->ForeignKeylist_ = (yyvsp[0].ForeignKeylist_t);}
#line 5283 "bison_parser.cpp"
    break;

  case 125: /* opt_ForeignKeylist: %empty  */
#line 1344 "bison_parser.y"
                    {(yyval.opt_ForeignKeylist_t) = new opt_ForeignKeylist(); (yyval.opt_ForeignKeylist_t)->sub_type_ = CASE1;}
#line 5289 "bison_parser.cpp"
    break;

  case 126: /* ForeignKeylist: ForeignKeylist ',' ForeignKey  */
#line 1348 "bison_parser.y"
                                      {
            (yyvsp[-2].ForeignKeylist_t)->v_ForeignKey.push_back((yyvsp[0].ForeignKey_t)); 
            (yyval.ForeignKeylist_t) = (yyvsp[-2].ForeignKeylist_t);
        }
#line 5298 "bison_parser.cpp"
    break;

  case 127: /* ForeignKeylist: ForeignKey  */
#line 1352 "bison_parser.y"
                   {
        (yyval.ForeignKeylist_t) = new ForeignKeylist(); 
        (yyval.ForeignKeylist_t)->v_ForeignKey.push_back((yyvsp[0].ForeignKey_t));
        }
#line 5307 "bison_parser.cpp"
    break;

  case 128: /* ForeignKey: FkNoOptstmt opt_Actiontypelist  */
#line 1359 "bison_parser.y"
                                      {
            (yyval.ForeignKey_t) = new ForeignKey();
            (yyval.ForeignKey_t)->FkNoOptstmt_ = (yyvsp[-1].FkNoOptstmt_t);
            (yyval.ForeignKey_t)->opt_Actiontypelist_ = (yyvsp[0].opt_Actiontypelist_t);
    }
#line 5317 "bison_parser.cpp"
    break;

  case 129: /* FkNoOptstmt: ForeignKeyColumn ForeignKeyRef  */
#line 1367 "bison_parser.y"
                                   {
        (yyval.FkNoOptstmt_t) = new FkNoOptstmt();
        (yyval.FkNoOptstmt_t)->ForeignKeyColumn_ = (yyvsp[-1].ForeignKeyColumn_t);
        (yyval.FkNoOptstmt_t)->ForeignKeyRef_ = (yyvsp[0].ForeignKeyRef_t);
    }
#line 5327 "bison_parser.cpp"
    break;

  case 130: /* ForeignKeyColumn: FOREIGN KEY ColumnInParen_ForeignKey  */
#line 1375 "bison_parser.y"
                                         {
        (yyval.ForeignKeyColumn_t) = new ForeignKeyColumn();
        (yyval.ForeignKeyColumn_t)->column_name_ForeignKey_ = (yyvsp[0].Column_In_Paren_ForeignKey_t);
    }
#line 5336 "bison_parser.cpp"
    break;

  case 131: /* ForeignKeyRef: REFERENCES table_name ColumnInParen_References  */
#line 1382 "bison_parser.y"
                                                   {
        (yyval.ForeignKeyRef_t) = new ForeignKeyRef();
        (yyval.ForeignKeyRef_t)->table_name_ = (yyvsp[-1].table_name_t);
        (yyval.ForeignKeyRef_t)->column_name_References_ = (yyvsp[0].Column_In_Paren_References_t);
        (yyval.ForeignKeyRef_t)->table_name_->table_name_->id_type_ = id_references_table_name;
    }
#line 5347 "bison_parser.cpp"
    break;

  case 132: /* opt_Actiontypelist: Action_typelist  */
#line 1391 "bison_parser.y"
                        {(yyval.opt_Actiontypelist_t) = new opt_Actiontypelist(); (yyval.opt_Actiontypelist_t)->sub_type_ = CASE0; (yyval.opt_Actiontypelist_t)->Action_typelist_ = (yyvsp[0].Action_typelist_t);}
#line 5353 "bison_parser.cpp"
    break;

  case 133: /* opt_Actiontypelist: %empty  */
#line 1392 "bison_parser.y"
                    {(yyval.opt_Actiontypelist_t) = new opt_Actiontypelist(); (yyval.opt_Actiontypelist_t)->sub_type_ = CASE1;}
#line 5359 "bison_parser.cpp"
    break;

  case 134: /* Action_typelist: Action_type  */
#line 1396 "bison_parser.y"
                    {
        (yyval.Action_typelist_t) = new Action_typelist(); 
        (yyval.Action_typelist_t)->v_Action_type.push_back((yyvsp[0].Action_type_t));
        }
#line 5368 "bison_parser.cpp"
    break;

  case 135: /* Action_type: ON DELETE CASCADE  */
#line 1403 "bison_parser.y"
                      { 
        (yyval.Action_type_t) = new Action_type(); 
        (yyval.Action_type_t)->str_val_ = string("ON DELETE CASCADE"); 
    }
#line 5377 "bison_parser.cpp"
    break;

  case 136: /* Action_type: ON DELETE SET NULL  */
#line 1407 "bison_parser.y"
                         { 
        (yyval.Action_type_t) = new Action_type(); 
        (yyval.Action_type_t)->str_val_ = string("ON DELETE SET NULL"); 
    }
#line 5386 "bison_parser.cpp"
    break;

  case 137: /* Action_type: ON DELETE NO ACTION  */
#line 1411 "bison_parser.y"
                          { 
        (yyval.Action_type_t) = new Action_type(); 
        (yyval.Action_type_t)->str_val_ = string("ON DELETE NO ACTION"); 
    }
#line 5395 "bison_parser.cpp"
    break;

  case 138: /* ColumnInParen_ForeignKey: '(' ColumnNameList_ForeignKey ')'  */
#line 1419 "bison_parser.y"
                                         {
        (yyval.Column_In_Paren_ForeignKey_t) = new ColumnInParen_ForeignKey();
        (yyval.Column_In_Paren_ForeignKey_t)->column_name_list_ForeignKey_ = (yyvsp[-1].ColumnNameList_ForeignKey_t);
    }
#line 5404 "bison_parser.cpp"
    break;

  case 139: /* ColumnNameList_ForeignKey: ColumnName_ForeignKey  */
#line 1426 "bison_parser.y"
                              {
            (yyval.ColumnNameList_ForeignKey_t) = new ColumnNameList_ForeignKey();
            (yyval.ColumnNameList_ForeignKey_t)->v_column_name_list_ForeignKey_.push_back((yyvsp[0].ColumnName_ForeignKey_t));
        }
#line 5413 "bison_parser.cpp"
    break;

  case 140: /* ColumnNameList_ForeignKey: ColumnNameList_ForeignKey ',' ColumnName_ForeignKey  */
#line 1430 "bison_parser.y"
                                                            {
            (yyvsp[-2].ColumnNameList_ForeignKey_t)->v_column_name_list_ForeignKey_.push_back((yyvsp[0].ColumnName_ForeignKey_t));
            (yyval.ColumnNameList_ForeignKey_t) = (yyvsp[-2].ColumnNameList_ForeignKey_t);
        }
#line 5422 "bison_parser.cpp"
    break;

  case 141: /* ColumnName_ForeignKey: IDENTIFIER  */
#line 1437 "bison_parser.y"
                   { (yyval.ColumnName_ForeignKey_t) = new ColumnName_ForeignKey(); (yyval.ColumnName_ForeignKey_t)->sub_type_=CASE0; (yyval.ColumnName_ForeignKey_t)->identifier_=new Identifier((yyvsp[0].sval), id_foreignkey_column_name); free((yyvsp[0].sval));}
#line 5428 "bison_parser.cpp"
    break;

  case 142: /* ColumnInParen_References: '(' ColumnNameList_References ')'  */
#line 1442 "bison_parser.y"
                                         {
        (yyval.Column_In_Paren_References_t) = new ColumnInParen_References();
        (yyval.Column_In_Paren_References_t)->column_name_list_References_ = (yyvsp[-1].ColumnNameList_References_t);
    }
#line 5437 "bison_parser.cpp"
    break;

  case 143: /* ColumnNameList_References: ColumnName_References  */
#line 1449 "bison_parser.y"
                              {
            (yyval.ColumnNameList_References_t) = new ColumnNameList_References();
            (yyval.ColumnNameList_References_t)->v_column_name_list_References_.push_back((yyvsp[0].ColumnName_References_t));
        }
#line 5446 "bison_parser.cpp"
    break;

  case 144: /* ColumnNameList_References: ColumnNameList_References ',' ColumnName_References  */
#line 1453 "bison_parser.y"
                                                            {
            (yyvsp[-2].ColumnNameList_References_t)->v_column_name_list_References_.push_back((yyvsp[0].ColumnName_References_t));
            (yyval.ColumnNameList_References_t) = (yyvsp[-2].ColumnNameList_References_t);
        }
#line 5455 "bison_parser.cpp"
    break;

  case 145: /* ColumnName_References: IDENTIFIER  */
#line 1460 "bison_parser.y"
                   { (yyval.ColumnName_References_t) = new ColumnName_References(); (yyval.ColumnName_References_t)->sub_type_=CASE0; (yyval.ColumnName_References_t)->identifier_=new Identifier((yyvsp[0].sval), id_references_column_name); free((yyvsp[0].sval));}
#line 5461 "bison_parser.cpp"
    break;

  case 146: /* opt_unique: UNIQUE  */
#line 1465 "bison_parser.y"
               {(yyval.opt_unique_t) = new OptUnique(); (yyval.opt_unique_t)->str_val_ = string("UNIQUE");}
#line 5467 "bison_parser.cpp"
    break;

  case 147: /* opt_unique: %empty  */
#line 1466 "bison_parser.y"
                  {(yyval.opt_unique_t) = new OptUnique(); (yyval.opt_unique_t)->str_val_ = string("");}
#line 5473 "bison_parser.cpp"
    break;

  case 148: /* index_name: IDENTIFIER  */
#line 1470 "bison_parser.y"
                   {(yyval.index_name_t) = new IndexName(); (yyval.index_name_t)->id_ = new Identifier((yyvsp[0].sval), id_index_name); free((yyvsp[0].sval));}
#line 5479 "bison_parser.cpp"
    break;

  case 149: /* trigger_declare: opt_tmp TRIGGER opt_not_exists trigger_name opt_trigger_time trigger_event ON table_name opt_for_each opt_when  */
#line 1474 "bison_parser.y"
                                                                                                                       {
            (yyval.trigger_declare_t) = new TriggerDeclare();
            (yyval.trigger_declare_t)->opt_tmp_ = (yyvsp[-9].opt_tmp_t);
            (yyval.trigger_declare_t)->opt_not_exists_ = (yyvsp[-7].opt_not_exists_t);
            (yyval.trigger_declare_t)->trigger_name_ = (yyvsp[-6].trigger_name_t);
            (yyval.trigger_declare_t)->opt_trigger_time_ = (yyvsp[-5].opt_trigger_time_t);
            (yyval.trigger_declare_t)->trigger_event_ = (yyvsp[-4].trigger_event_t);
            (yyval.trigger_declare_t)->table_name_ = (yyvsp[-2].table_name_t);
            (yyval.trigger_declare_t)->opt_for_each_ = (yyvsp[-1].opt_for_each_t);
            (yyval.trigger_declare_t)->opt_when_ = (yyvsp[0].opt_when_t);
        }
#line 5495 "bison_parser.cpp"
    break;

  case 150: /* trigger_name: IDENTIFIER  */
#line 1488 "bison_parser.y"
                   {(yyval.trigger_name_t) = new TriggerName(); (yyval.trigger_name_t)->id_ = new Identifier((yyvsp[0].sval), id_trigger_name); free((yyvsp[0].sval));}
#line 5501 "bison_parser.cpp"
    break;

  case 151: /* opt_trigger_time: BEFORE  */
#line 1492 "bison_parser.y"
               {(yyval.opt_trigger_time_t) = new OptTriggerTime(); (yyval.opt_trigger_time_t)->str_val_ = string("BEFORE");}
#line 5507 "bison_parser.cpp"
    break;

  case 152: /* opt_trigger_time: AFTER  */
#line 1493 "bison_parser.y"
              {(yyval.opt_trigger_time_t) = new OptTriggerTime(); (yyval.opt_trigger_time_t)->str_val_ = string("AFTER");}
#line 5513 "bison_parser.cpp"
    break;

  case 153: /* opt_trigger_time: INSTEAD OF  */
#line 1494 "bison_parser.y"
                   {(yyval.opt_trigger_time_t) = new OptTriggerTime(); (yyval.opt_trigger_time_t)->str_val_ = string("INSTEAD OF");}
#line 5519 "bison_parser.cpp"
    break;

  case 154: /* opt_trigger_time: %empty  */
#line 1495 "bison_parser.y"
                    {(yyval.opt_trigger_time_t) = new OptTriggerTime(); (yyval.opt_trigger_time_t)->str_val_ = string("");}
#line 5525 "bison_parser.cpp"
    break;

  case 155: /* trigger_event: DELETE  */
#line 1499 "bison_parser.y"
               {(yyval.trigger_event_t) = new TriggerEvent(); (yyval.trigger_event_t)->sub_type_ = CASE0;}
#line 5531 "bison_parser.cpp"
    break;

  case 156: /* trigger_event: INSERT  */
#line 1500 "bison_parser.y"
               {(yyval.trigger_event_t) = new TriggerEvent(); (yyval.trigger_event_t)->sub_type_ = CASE1;}
#line 5537 "bison_parser.cpp"
    break;

  case 157: /* trigger_event: UPDATE opt_of_column_list  */
#line 1501 "bison_parser.y"
                                  {(yyval.trigger_event_t) = new TriggerEvent(); (yyval.trigger_event_t)->sub_type_ = CASE2; (yyval.trigger_event_t)->opt_of_column_list_ = (yyvsp[0].opt_of_column_list_t);}
#line 5543 "bison_parser.cpp"
    break;

  case 158: /* opt_of_column_list: OF ident_commalist  */
#line 1505 "bison_parser.y"
                           {(yyval.opt_of_column_list_t) = new OptOfColumnList(); (yyval.opt_of_column_list_t)->sub_type_ = CASE0; (yyval.opt_of_column_list_t)->ident_commalist_ = (yyvsp[0].ident_commalist_t);}
#line 5549 "bison_parser.cpp"
    break;

  case 159: /* opt_of_column_list: %empty  */
#line 1506 "bison_parser.y"
                    {(yyval.opt_of_column_list_t) = new OptOfColumnList(); (yyval.opt_of_column_list_t)->sub_type_ = CASE1;}
#line 5555 "bison_parser.cpp"
    break;

  case 160: /* opt_for_each: FOR EACH ROW  */
#line 1510 "bison_parser.y"
                     {(yyval.opt_for_each_t) = new OptForEach(); (yyval.opt_for_each_t)->str_val_ = string("FOR EACH ROW");}
#line 5561 "bison_parser.cpp"
    break;

  case 161: /* opt_for_each: %empty  */
#line 1511 "bison_parser.y"
                    {(yyval.opt_for_each_t) = new OptForEach(); (yyval.opt_for_each_t)->str_val_ = string("");}
#line 5567 "bison_parser.cpp"
    break;

  case 162: /* opt_when: WHEN expr  */
#line 1515 "bison_parser.y"
                  {(yyval.opt_when_t) = new OptWhen(); (yyval.opt_when_t)->sub_type_ = CASE0; (yyval.opt_when_t)->expr_ = (yyvsp[0].expr_t);}
#line 5573 "bison_parser.cpp"
    break;

  case 163: /* opt_when: %empty  */
#line 1516 "bison_parser.y"
                    {(yyval.opt_when_t) = new OptWhen(); (yyval.opt_when_t)->sub_type_ = CASE1;}
#line 5579 "bison_parser.cpp"
    break;

  case 164: /* trigger_cmd_list: trigger_cmd ';'  */
#line 1520 "bison_parser.y"
                        {(yyval.trigger_cmd_list_t) = new TriggerCmdList(); (yyval.trigger_cmd_list_t)->v_trigger_cmd_list_.push_back((yyvsp[-1].trigger_cmd_t));}
#line 5585 "bison_parser.cpp"
    break;

  case 165: /* trigger_cmd_list: trigger_cmd_list trigger_cmd ';'  */
#line 1521 "bison_parser.y"
                                         {(yyvsp[-2].trigger_cmd_list_t)->v_trigger_cmd_list_.push_back((yyvsp[-1].trigger_cmd_t)); (yyval.trigger_cmd_list_t) = (yyvsp[-2].trigger_cmd_list_t);}
#line 5591 "bison_parser.cpp"
    break;

  case 166: /* trigger_cmd: select_statement  */
#line 1525 "bison_parser.y"
                         {(yyval.trigger_cmd_t) = new TriggerCmd(); (yyval.trigger_cmd_t)->stmt_ = (yyvsp[0].select_statement_t);}
#line 5597 "bison_parser.cpp"
    break;

  case 167: /* trigger_cmd: update_statement  */
#line 1526 "bison_parser.y"
                         {(yyval.trigger_cmd_t) = new TriggerCmd(); (yyval.trigger_cmd_t)->stmt_ = (yyvsp[0].update_statement_t);}
#line 5603 "bison_parser.cpp"
    break;

  case 168: /* trigger_cmd: insert_statement  */
#line 1527 "bison_parser.y"
                         {(yyval.trigger_cmd_t) = new TriggerCmd(); (yyval.trigger_cmd_t)->stmt_ = (yyvsp[0].insert_statement_t);}
#line 5609 "bison_parser.cpp"
    break;

  case 169: /* trigger_cmd: delete_statement  */
#line 1528 "bison_parser.y"
                         {(yyval.trigger_cmd_t) = new TriggerCmd(); (yyval.trigger_cmd_t)->stmt_ = (yyvsp[0].delete_statement_t);}
#line 5615 "bison_parser.cpp"
    break;

  case 170: /* module_name: IDENTIFIER  */
#line 1532 "bison_parser.y"
                   {(yyval.module_name_t) = new ModuleName(); (yyval.module_name_t)->id_ = new Identifier((yyvsp[0].sval)); free((yyvsp[0].sval));}
#line 5621 "bison_parser.cpp"
    break;

  case 171: /* opt_not_exists: IF NOT EXISTS  */
#line 1537 "bison_parser.y"
                      { (yyval.opt_not_exists_t) = new OptNotExists(); (yyval.opt_not_exists_t)->sub_type_ = CASE0; }
#line 5627 "bison_parser.cpp"
    break;

  case 172: /* opt_not_exists: %empty  */
#line 1538 "bison_parser.y"
                    { (yyval.opt_not_exists_t) = new OptNotExists(); (yyval.opt_not_exists_t)->sub_type_ = CASE1; }
#line 5633 "bison_parser.cpp"
    break;

  case 173: /* column_def_commalist: column_def  */
#line 1542 "bison_parser.y"
                   { 
            (yyval.column_def_comma_list_t) = new ColumnDefCommaList(); 
            (yyval.column_def_comma_list_t)->v_column_def_comma_list_.push_back((yyvsp[0].column_def_t));
        }
#line 5642 "bison_parser.cpp"
    break;

  case 174: /* column_def_commalist: column_def_commalist ',' column_def  */
#line 1546 "bison_parser.y"
                                            { 
            (yyvsp[-2].column_def_comma_list_t)->v_column_def_comma_list_.push_back((yyvsp[0].column_def_t));
            (yyval.column_def_comma_list_t) = (yyvsp[-2].column_def_comma_list_t);
        }
#line 5651 "bison_parser.cpp"
    break;

  case 175: /* column_def: IDENTIFIER column_type opt_column_arglist  */
#line 1553 "bison_parser.y"
                                                  {
            (yyval.column_def_t) = new ColumnDef();
			(yyval.column_def_t)->id_ = new Identifier((yyvsp[-2].sval), id_create_column_name);
            (yyval.column_def_t)->column_type_ = (yyvsp[-1].column_type_t);
            (yyval.column_def_t)->opt_column_arglist_ = (yyvsp[0].opt_column_arglist_t);
            free((yyvsp[-2].sval)); 
        }
#line 5663 "bison_parser.cpp"
    break;

  case 176: /* opt_column_arglist: column_arglist  */
#line 1564 "bison_parser.y"
                       {(yyval.opt_column_arglist_t) = new OptColumnArglist(); (yyval.opt_column_arglist_t)->sub_type_ = CASE0; (yyval.opt_column_arglist_t)->column_arglist_ = (yyvsp[0].column_arglist_t);}
#line 5669 "bison_parser.cpp"
    break;

  case 177: /* opt_column_arglist: %empty  */
#line 1565 "bison_parser.y"
                    {(yyval.opt_column_arglist_t) = new OptColumnArglist(); (yyval.opt_column_arglist_t)->sub_type_ = CASE1;}
#line 5675 "bison_parser.cpp"
    break;

  case 178: /* column_arglist: column_arglist column_arg  */
#line 1569 "bison_parser.y"
                                  {
            (yyvsp[-1].column_arglist_t)->v_column_arg_.push_back((yyvsp[0].column_arg_t)); 
            (yyval.column_arglist_t) = (yyvsp[-1].column_arglist_t);
        }
#line 5684 "bison_parser.cpp"
    break;

  case 179: /* column_arglist: column_arg  */
#line 1573 "bison_parser.y"
                   {
        (yyval.column_arglist_t) = new ColumnArglist(); 
        (yyval.column_arglist_t)->v_column_arg_.push_back((yyvsp[0].column_arg_t));
        }
#line 5693 "bison_parser.cpp"
    break;

  case 180: /* column_arg: NULL opt_on_conflict  */
#line 1580 "bison_parser.y"
                             {(yyval.column_arg_t) = new ColumnArg(); (yyval.column_arg_t)->sub_type_ = CASE0; (yyval.column_arg_t)->opt_on_conflict_ = (yyvsp[0].opt_on_conflict_t);}
#line 5699 "bison_parser.cpp"
    break;

  case 181: /* column_arg: NOT NULL opt_on_conflict  */
#line 1581 "bison_parser.y"
                                 {(yyval.column_arg_t) = new ColumnArg(); (yyval.column_arg_t)->sub_type_ = CASE1; (yyval.column_arg_t)->opt_on_conflict_ = (yyvsp[0].opt_on_conflict_t);}
#line 5705 "bison_parser.cpp"
    break;

  case 182: /* column_arg: PRIMARY KEY opt_order_type opt_on_conflict opt_autoinc  */
#line 1582 "bison_parser.y"
                                                               {
                (yyval.column_arg_t) = new ColumnArg(); 
                (yyval.column_arg_t)->sub_type_ = CASE2; 
                (yyval.column_arg_t)->opt_order_type_ = (yyvsp[-2].opt_order_type_t);
                (yyval.column_arg_t)->opt_on_conflict_ = (yyvsp[-1].opt_on_conflict_t);
                (yyval.column_arg_t)->opt_autoinc_ = (yyvsp[0].opt_autoinc_t);
        }
#line 5717 "bison_parser.cpp"
    break;

  case 183: /* column_arg: UNIQUE opt_on_conflict  */
#line 1589 "bison_parser.y"
                               {(yyval.column_arg_t) = new ColumnArg(); (yyval.column_arg_t)->sub_type_ = CASE3; (yyval.column_arg_t)->opt_on_conflict_ = (yyvsp[0].opt_on_conflict_t);}
#line 5723 "bison_parser.cpp"
    break;

  case 184: /* column_arg: GENERATED ALWAYS AS '(' expr ')' opt_generatedarg  */
#line 1590 "bison_parser.y"
                                                          {
                (yyval.column_arg_t) = new ColumnArg(); 
                (yyval.column_arg_t)->sub_type_ = CASE4; 
                (yyval.column_arg_t)->expr_ = (yyvsp[-2].expr_t);
                (yyval.column_arg_t)->opt_generatedarg_ = (yyvsp[0].opt_generatedarg_t);
        }
#line 5734 "bison_parser.cpp"
    break;

  case 185: /* column_arg: CHECK '(' expr ')'  */
#line 1597 "bison_parser.y"
                           {(yyval.column_arg_t) = new ColumnArg(); (yyval.column_arg_t)->sub_type_ = CASE6; (yyval.column_arg_t)->expr_ = (yyvsp[-1].expr_t);}
#line 5740 "bison_parser.cpp"
    break;

  case 186: /* opt_generatedarg: STORED  */
#line 1601 "bison_parser.y"
               { (yyval.opt_generatedarg_t) = new opt_generatedarg(); (yyval.opt_generatedarg_t)->sub_type_ = CASE0; (yyval.opt_generatedarg_t)->str_val_ = string("STORED"); }
#line 5746 "bison_parser.cpp"
    break;

  case 187: /* opt_generatedarg: VIRTUAL  */
#line 1602 "bison_parser.y"
                { (yyval.opt_generatedarg_t) = new opt_generatedarg(); (yyval.opt_generatedarg_t)->sub_type_ = CASE1; (yyval.opt_generatedarg_t)->str_val_ = string("VIRTUAL"); }
#line 5752 "bison_parser.cpp"
    break;

  case 188: /* opt_generatedarg: %empty  */
#line 1603 "bison_parser.y"
                    { (yyval.opt_generatedarg_t) = new opt_generatedarg(); (yyval.opt_generatedarg_t)->sub_type_ = CASE2; (yyval.opt_generatedarg_t)->str_val_ = string(""); }
#line 5758 "bison_parser.cpp"
    break;

  case 189: /* opt_on_conflict: ON CONFLICT resolve_type  */
#line 1606 "bison_parser.y"
                                 {(yyval.opt_on_conflict_t) = new OptOnConflict(); (yyval.opt_on_conflict_t)->sub_type_ = CASE0; (yyval.opt_on_conflict_t)->resolve_type_ = (yyvsp[0].resolve_type_t);}
#line 5764 "bison_parser.cpp"
    break;

  case 190: /* opt_on_conflict: %empty  */
#line 1607 "bison_parser.y"
                    {(yyval.opt_on_conflict_t) = new OptOnConflict(); (yyval.opt_on_conflict_t)->sub_type_ = CASE1;}
#line 5770 "bison_parser.cpp"
    break;

  case 191: /* resolve_type: IGNORE  */
#line 1611 "bison_parser.y"
               {(yyval.resolve_type_t) = new ResolveType(); (yyval.resolve_type_t)->str_val_ = string("IGNORE");}
#line 5776 "bison_parser.cpp"
    break;

  case 192: /* resolve_type: REPLACE  */
#line 1612 "bison_parser.y"
                {(yyval.resolve_type_t) = new ResolveType(); (yyval.resolve_type_t)->str_val_ = string("REPLACE");}
#line 5782 "bison_parser.cpp"
    break;

  case 193: /* resolve_type: ROLLBACK  */
#line 1613 "bison_parser.y"
                 {(yyval.resolve_type_t) = new ResolveType(); (yyval.resolve_type_t)->str_val_ = string("ROLLBACK");}
#line 5788 "bison_parser.cpp"
    break;

  case 194: /* resolve_type: ABORT  */
#line 1614 "bison_parser.y"
              {(yyval.resolve_type_t) = new ResolveType(); (yyval.resolve_type_t)->str_val_ = string("ABORT");}
#line 5794 "bison_parser.cpp"
    break;

  case 195: /* resolve_type: FAIL  */
#line 1615 "bison_parser.y"
             {(yyval.resolve_type_t) = new ResolveType(); (yyval.resolve_type_t)->str_val_ = string("FAIL");}
#line 5800 "bison_parser.cpp"
    break;

  case 196: /* opt_autoinc: AUTOINCR  */
#line 1619 "bison_parser.y"
                 {(yyval.opt_autoinc_t) = new OptAutoinc(); (yyval.opt_autoinc_t)->str_val_ = string("AUTOINCR");}
#line 5806 "bison_parser.cpp"
    break;

  case 197: /* opt_autoinc: %empty  */
#line 1620 "bison_parser.y"
                    {(yyval.opt_autoinc_t) = new OptAutoinc(); (yyval.opt_autoinc_t)->str_val_ = string("");}
#line 5812 "bison_parser.cpp"
    break;

  case 198: /* column_type: INT  */
#line 1625 "bison_parser.y"
            { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("INT"); }
#line 5818 "bison_parser.cpp"
    break;

  case 199: /* column_type: INTEGER  */
#line 1626 "bison_parser.y"
                { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("INTEGER"); }
#line 5824 "bison_parser.cpp"
    break;

  case 200: /* column_type: FLOAT  */
#line 1628 "bison_parser.y"
              { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("FLOAT"); }
#line 5830 "bison_parser.cpp"
    break;

  case 201: /* column_type: DOUBLE  */
#line 1629 "bison_parser.y"
               { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("DOUBLE"); }
#line 5836 "bison_parser.cpp"
    break;

  case 202: /* column_type: VARCHAR '(' INTVAL ')'  */
#line 1630 "bison_parser.y"
                               { 
            (yyval.column_type_t) = new ColumnType();
            (yyval.column_type_t)->str_val_ = string("VARCHAR(") + to_string((yyvsp[-1].ival)) + ")"; 
            }
#line 5845 "bison_parser.cpp"
    break;

  case 203: /* column_type: CHAR '(' INTVAL ')'  */
#line 1634 "bison_parser.y"
                            { (yyval.column_type_t) = new ColumnType(); 
            (yyval.column_type_t)->str_val_ = string("CHAR(") + to_string((yyvsp[-1].ival)) + ")"; 
            }
#line 5853 "bison_parser.cpp"
    break;

  case 204: /* column_type: TEXT  */
#line 1637 "bison_parser.y"
             { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("TEXT"); }
#line 5859 "bison_parser.cpp"
    break;

  case 205: /* column_type: JSON  */
#line 1638 "bison_parser.y"
             { (yyval.column_type_t) = new ColumnType(); (yyval.column_type_t)->str_val_ = string("JSON"); }
#line 5865 "bison_parser.cpp"
    break;

  case 206: /* drop_statement: DROP TABLE opt_exists table_name  */
#line 1649 "bison_parser.y"
                                         {
            (yyval.drop_statement_t) = new DropStatement();
            (yyval.drop_statement_t)->sub_type_ = CASE0;
            (yyval.drop_statement_t)->opt_exists_ = (yyvsp[-1].opt_exists_t);
            (yyval.drop_statement_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.drop_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.drop_statement_t)->id_ = NULL;
        }
#line 5878 "bison_parser.cpp"
    break;

  case 207: /* drop_statement: DROP VIEW opt_exists table_name  */
#line 1657 "bison_parser.y"
                                        {
            (yyval.drop_statement_t) = new DropStatement();
            (yyval.drop_statement_t)->sub_type_ = CASE1;
            (yyval.drop_statement_t)->opt_exists_ = (yyvsp[-1].opt_exists_t);
            (yyval.drop_statement_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.drop_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.drop_statement_t)->id_ = NULL;
        }
#line 5891 "bison_parser.cpp"
    break;

  case 208: /* drop_statement: DEALLOCATE PREPARE IDENTIFIER  */
#line 1665 "bison_parser.y"
                                      {
            (yyval.drop_statement_t) = new DropStatement();
            (yyval.drop_statement_t)->sub_type_ = CASE2;
            (yyval.drop_statement_t)->id_ = new Identifier((yyvsp[0].sval));
            free((yyvsp[0].sval));
        }
#line 5902 "bison_parser.cpp"
    break;

  case 209: /* drop_statement: DROP TRIGGER opt_exists schema_name '.' trigger_name  */
#line 1671 "bison_parser.y"
                                                           {
            (yyval.drop_statement_t) = new DropStatement();
            (yyval.drop_statement_t)->sub_type_ = CASE3;
            (yyval.drop_statement_t)->opt_exists_ = (yyvsp[-3].opt_exists_t);
            (yyval.drop_statement_t)->schema_name_ = (yyvsp[-2].schema_name_t);
            (yyval.drop_statement_t)->trigger_name_ = (yyvsp[0].trigger_name_t);
    }
#line 5914 "bison_parser.cpp"
    break;

  case 210: /* drop_statement: DROP TRIGGER opt_exists trigger_name  */
#line 1679 "bison_parser.y"
                                           {
            (yyval.drop_statement_t) = new DropStatement();
            (yyval.drop_statement_t)->sub_type_ = CASE4;
            (yyval.drop_statement_t)->opt_exists_ = (yyvsp[-1].opt_exists_t);
            (yyval.drop_statement_t)->trigger_name_ = (yyvsp[0].trigger_name_t);
    }
#line 5925 "bison_parser.cpp"
    break;

  case 211: /* opt_exists: IF EXISTS  */
#line 1688 "bison_parser.y"
                    { (yyval.opt_exists_t) = new OptExists(); (yyval.opt_exists_t)->str_val_=string("IF EXISTS"); }
#line 5931 "bison_parser.cpp"
    break;

  case 212: /* opt_exists: %empty  */
#line 1689 "bison_parser.y"
                    { (yyval.opt_exists_t) = new OptExists(); (yyval.opt_exists_t)->str_val_=string(""); }
#line 5937 "bison_parser.cpp"
    break;

  case 213: /* delete_statement: DELETE FROM table_name opt_where  */
#line 1698 "bison_parser.y"
                                         {
            (yyval.delete_statement_t) = new DeleteStatement();
            (yyval.delete_statement_t)->sub_type_ = CASE0;
            (yyval.delete_statement_t)->table_name_ = (yyvsp[-1].table_name_t);
            (yyval.delete_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.delete_statement_t)->opt_where_ = (yyvsp[0].opt_where_t);
        }
#line 5949 "bison_parser.cpp"
    break;

  case 214: /* truncate_statement: TRUNCATE table_name  */
#line 1708 "bison_parser.y"
                            {
            (yyval.delete_statement_t) = new DeleteStatement();
            (yyval.delete_statement_t)->sub_type_ = CASE1;
            (yyval.delete_statement_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.delete_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;

        }
#line 5961 "bison_parser.cpp"
    break;

  case 215: /* insert_statement: insert_type INTO table_name opt_column_list VALUES super_list opt_upsert_clause  */
#line 1723 "bison_parser.y"
                                                                                       {
            (yyval.insert_statement_t) = new InsertStatement();
            (yyval.insert_statement_t)->sub_type_ = CASE0;
            (yyval.insert_statement_t)->insert_type_ = (yyvsp[-6].insert_type_t);
            (yyval.insert_statement_t)->table_name_ = (yyvsp[-4].table_name_t);
            (yyval.insert_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.insert_statement_t)->opt_column_list_ = (yyvsp[-3].opt_column_list_t);
            (yyval.insert_statement_t)->super_list_ = (yyvsp[-1].super_list_t);
            (yyval.insert_statement_t)->opt_upsert_clause_ = (yyvsp[0].opt_upsert_clause_t);
            if((yyval.insert_statement_t)->opt_column_list_->sub_type_ == CASE0){
                for(auto &cname: (yyval.insert_statement_t)->opt_column_list_->ident_comma_list_->v_iden_comma_list_){
                    cname->id_type_ = id_column_name;
                }    
            }
        }
#line 5981 "bison_parser.cpp"
    break;

  case 216: /* insert_statement: insert_type INTO table_name opt_column_list select_no_paren opt_upsert_clause  */
#line 1738 "bison_parser.y"
                                                                                     {
            (yyval.insert_statement_t) = new InsertStatement();
            (yyval.insert_statement_t)->sub_type_ = CASE1;
            (yyval.insert_statement_t)->insert_type_ = (yyvsp[-5].insert_type_t);
            (yyval.insert_statement_t)->table_name_ = (yyvsp[-3].table_name_t);
            (yyval.insert_statement_t)->table_name_->table_name_->id_type_ = id_top_table_name;
            (yyval.insert_statement_t)->opt_column_list_ = (yyvsp[-2].opt_column_list_t);
            (yyval.insert_statement_t)->select_no_paren_ = (yyvsp[-1].select_no_paren_t);
            (yyval.insert_statement_t)->opt_upsert_clause_ = (yyvsp[0].opt_upsert_clause_t);
            if((yyval.insert_statement_t)->opt_column_list_->sub_type_ == CASE0){
                for(auto &cname: (yyval.insert_statement_t)->opt_column_list_->ident_comma_list_->v_iden_comma_list_){
                    cname->id_type_ = id_column_name;
                }    
            }
        }
#line 6001 "bison_parser.cpp"
    break;

  case 217: /* super_list: '(' literal_list ')'  */
#line 1756 "bison_parser.y"
                            {
            (yyval.super_list_t) = new SuperList(); (yyval.super_list_t)->v_super_list_.push_back((yyvsp[-1].literal_list_t));
        }
#line 6009 "bison_parser.cpp"
    break;

  case 218: /* super_list: super_list ',' '(' literal_list ')'  */
#line 1759 "bison_parser.y"
                                           {
            (yyvsp[-4].super_list_t)->v_super_list_.push_back((yyvsp[-1].literal_list_t));
            (yyval.super_list_t) = (yyvsp[-4].super_list_t);
        }
#line 6018 "bison_parser.cpp"
    break;

  case 219: /* insert_type: INSERT  */
#line 1766 "bison_parser.y"
               { (yyval.insert_type_t) = new InsertType(); (yyval.insert_type_t)->sub_type_ = CASE0; (yyval.insert_type_t)->str_val_ = string("INSERT"); }
#line 6024 "bison_parser.cpp"
    break;

  case 220: /* insert_type: REPLACE  */
#line 1767 "bison_parser.y"
                  {(yyval.insert_type_t) = new InsertType(); (yyval.insert_type_t)->sub_type_ = CASE1; (yyval.insert_type_t)->str_val_  = string("REPLACE");}
#line 6030 "bison_parser.cpp"
    break;

  case 221: /* insert_type: INSERT OR resolve_type  */
#line 1768 "bison_parser.y"
                                 {(yyval.insert_type_t) = new InsertType(); (yyval.insert_type_t)->sub_type_ = CASE2; (yyval.insert_type_t)->resolve_type_ = (yyvsp[0].resolve_type_t);}
#line 6036 "bison_parser.cpp"
    break;

  case 222: /* opt_column_list: '(' ident_commalist ')'  */
#line 1772 "bison_parser.y"
                                { (yyval.opt_column_list_t) = new OptColumnList(); (yyval.opt_column_list_t)->sub_type_ = CASE0; (yyval.opt_column_list_t)->ident_comma_list_ = (yyvsp[-1].ident_commalist_t); }
#line 6042 "bison_parser.cpp"
    break;

  case 223: /* opt_column_list: %empty  */
#line 1773 "bison_parser.y"
                    { (yyval.opt_column_list_t) = new OptColumnList(); (yyval.opt_column_list_t)->sub_type_ = CASE1; }
#line 6048 "bison_parser.cpp"
    break;

  case 224: /* update_statement: UPDATE table_ref_name_no_alias SET update_clause_commalist opt_where  */
#line 1783 "bison_parser.y"
                                                                         {
        (yyval.update_statement_t) = new UpdateStatement();
        (yyval.update_statement_t)->table_ref_name_no_alias_ = (yyvsp[-3].table_ref_name_no_alias_t); //had set id_top_table_name in table_ref_name_no_alias
        (yyval.update_statement_t)->update_clause_comma_list_ = (yyvsp[-1].update_clause_commalist_t);
        (yyval.update_statement_t)->opt_where_ = (yyvsp[0].opt_where_t);
    }
#line 6059 "bison_parser.cpp"
    break;

  case 225: /* update_clause_commalist: update_clause  */
#line 1792 "bison_parser.y"
                      { 
            (yyval.update_clause_commalist_t) = new UpdateClauseCommalist(); 
            (yyval.update_clause_commalist_t)->v_update_clause_list_.push_back((yyvsp[0].update_clause_t)); 
            }
#line 6068 "bison_parser.cpp"
    break;

  case 226: /* update_clause_commalist: update_clause_commalist ',' update_clause  */
#line 1796 "bison_parser.y"
                                                  { 
        (yyvsp[-2].update_clause_commalist_t)->v_update_clause_list_.push_back((yyvsp[0].update_clause_t)); 
        (yyval.update_clause_commalist_t) = (yyvsp[-2].update_clause_commalist_t); }
#line 6076 "bison_parser.cpp"
    break;

  case 227: /* update_clause: IDENTIFIER '=' expr  */
#line 1802 "bison_parser.y"
                            {
            (yyval.update_clause_t) = new UpdateClause();
            (yyval.update_clause_t)->id_ = new Identifier((yyvsp[-2].sval), id_column_name);
            (yyval.update_clause_t)->expr_ = (yyvsp[0].expr_t);
            free((yyvsp[-2].sval));
        }
#line 6087 "bison_parser.cpp"
    break;

  case 228: /* select_statement: opt_with_clause select_with_paren  */
#line 1816 "bison_parser.y"
                                          {
            (yyval.select_statement_t) = new SelectStatement();
            (yyval.select_statement_t)->sub_type_ = CASE0;
            (yyval.select_statement_t)->opt_with_clause_ = (yyvsp[-1].opt_with_clause_t);
            (yyval.select_statement_t)->select_with_paren_ = (yyvsp[0].select_with_paren_t);
        }
#line 6098 "bison_parser.cpp"
    break;

  case 229: /* select_statement: opt_with_clause select_no_paren  */
#line 1822 "bison_parser.y"
                                        {
            (yyval.select_statement_t) = new SelectStatement();
            (yyval.select_statement_t)->sub_type_ = CASE1;
            (yyval.select_statement_t)->opt_with_clause_ = (yyvsp[-1].opt_with_clause_t);
            (yyval.select_statement_t)->select_no_paren_ = (yyvsp[0].select_no_paren_t);
        }
#line 6109 "bison_parser.cpp"
    break;

  case 230: /* select_statement: opt_with_clause select_with_paren set_operator select_paren_or_clause opt_order opt_limit  */
#line 1828 "bison_parser.y"
                                                                                                  {
            (yyval.select_statement_t) = new SelectStatement();
            (yyval.select_statement_t)->sub_type_ = CASE2;
            (yyval.select_statement_t)->opt_with_clause_ = (yyvsp[-5].opt_with_clause_t);
            (yyval.select_statement_t)->select_with_paren_ = (yyvsp[-4].select_with_paren_t);
            (yyval.select_statement_t)->set_operator_ = (yyvsp[-3].set_operator_t);
            (yyval.select_statement_t)->select_paren_or_clause_ = (yyvsp[-2].select_paren_or_clause_t);
            (yyval.select_statement_t)->opt_order_ = (yyvsp[-1].opt_order_t);
            (yyval.select_statement_t)->opt_limit_ = (yyvsp[0].opt_limit_t);
            
        }
#line 6125 "bison_parser.cpp"
    break;

  case 231: /* select_with_paren: '(' select_no_paren ')'  */
#line 1842 "bison_parser.y"
                                 { (yyval.select_with_paren_t) = new SelectWithParen(); (yyval.select_with_paren_t)->sub_type_ = CASE0; (yyval.select_with_paren_t)->select_no_paren_=(yyvsp[-1].select_no_paren_t);}
#line 6131 "bison_parser.cpp"
    break;

  case 232: /* select_with_paren: '(' select_with_paren ')'  */
#line 1843 "bison_parser.y"
                                  { (yyval.select_with_paren_t) = new SelectWithParen(); (yyval.select_with_paren_t)->sub_type_ = CASE1; (yyval.select_with_paren_t)->select_with_paren_=(yyvsp[-1].select_with_paren_t);}
#line 6137 "bison_parser.cpp"
    break;

  case 233: /* select_paren_or_clause: select_with_paren  */
#line 1847 "bison_parser.y"
                          {(yyval.select_paren_or_clause_t) = new SelectParenOrClause(); (yyval.select_paren_or_clause_t)->sub_type_=CASE0; (yyval.select_paren_or_clause_t)->select_with_paren_=(yyvsp[0].select_with_paren_t);}
#line 6143 "bison_parser.cpp"
    break;

  case 234: /* select_paren_or_clause: select_clause  */
#line 1848 "bison_parser.y"
                      {(yyval.select_paren_or_clause_t)=new SelectParenOrClause(); (yyval.select_paren_or_clause_t)->sub_type_=CASE1; (yyval.select_paren_or_clause_t)->select_clause_=(yyvsp[0].select_clause_t);}
#line 6149 "bison_parser.cpp"
    break;

  case 235: /* select_no_paren: select_clause opt_order opt_limit  */
#line 1852 "bison_parser.y"
                                          {
            (yyval.select_no_paren_t) = new SelectNoParen();
            (yyval.select_no_paren_t)->sub_type_ = CASE0;
            (yyval.select_no_paren_t)->select_clause_ = (yyvsp[-2].select_clause_t);
            (yyval.select_no_paren_t)->opt_order_ = (yyvsp[-1].opt_order_t);
            (yyval.select_no_paren_t)->opt_limit_ = (yyvsp[0].opt_limit_t);
        }
#line 6161 "bison_parser.cpp"
    break;

  case 236: /* select_no_paren: select_clause set_operator select_paren_or_clause opt_order opt_limit  */
#line 1859 "bison_parser.y"
                                                                              {
            (yyval.select_no_paren_t) = new SelectNoParen();
            (yyval.select_no_paren_t)->sub_type_ = CASE1;
            (yyval.select_no_paren_t)->select_clause_ = (yyvsp[-4].select_clause_t);
            (yyval.select_no_paren_t)->set_operator_ = (yyvsp[-3].set_operator_t);
            (yyval.select_no_paren_t)->select_paren_or_clause_ = (yyvsp[-2].select_paren_or_clause_t);
            (yyval.select_no_paren_t)->opt_order_ = (yyvsp[-1].opt_order_t);
            (yyval.select_no_paren_t)->opt_limit_ = (yyvsp[0].opt_limit_t);    
        }
#line 6175 "bison_parser.cpp"
    break;

  case 237: /* set_operator: set_type opt_all  */
#line 1871 "bison_parser.y"
                         {
            (yyval.set_operator_t) = new SetOperator();
            (yyval.set_operator_t)->set_type_ = (yyvsp[-1].set_type_t);
            (yyval.set_operator_t)->opt_all_ = (yyvsp[0].opt_all_t);
            }
#line 6185 "bison_parser.cpp"
    break;

  case 238: /* set_type: UNION  */
#line 1879 "bison_parser.y"
                {(yyval.set_type_t) = new SetType(); (yyval.set_type_t)->str_val_ = string("UNION");}
#line 6191 "bison_parser.cpp"
    break;

  case 239: /* set_type: INTERSECT  */
#line 1880 "bison_parser.y"
                  {(yyval.set_type_t) = new SetType(); (yyval.set_type_t)->str_val_ = string("INTERSECT");}
#line 6197 "bison_parser.cpp"
    break;

  case 240: /* set_type: EXCEPT  */
#line 1881 "bison_parser.y"
                {(yyval.set_type_t) = new SetType(); (yyval.set_type_t)->str_val_ = string("EXCEPT");}
#line 6203 "bison_parser.cpp"
    break;

  case 241: /* opt_all: ALL  */
#line 1885 "bison_parser.y"
            {(yyval.opt_all_t) = new OptAll(); (yyval.opt_all_t)->str_val_ = string("ALL");}
#line 6209 "bison_parser.cpp"
    break;

  case 242: /* opt_all: %empty  */
#line 1886 "bison_parser.y"
                    {(yyval.opt_all_t) = new OptAll(); (yyval.opt_all_t)->str_val_ = string("");}
#line 6215 "bison_parser.cpp"
    break;

  case 243: /* select_clause: SELECT opt_top opt_distinct select_list opt_from_clause opt_where opt_group  */
#line 1890 "bison_parser.y"
                                                                                    {
            (yyval.select_clause_t) = new SelectClause();
            (yyval.select_clause_t)->sub_type_ = CASE0;
            (yyval.select_clause_t)->opt_top_ = (yyvsp[-5].opt_top_t);
            (yyval.select_clause_t)->opt_distinct_ = (yyvsp[-4].opt_distinct_t);
            (yyval.select_clause_t)->select_list_ = (yyvsp[-3].select_list_t);
            (yyval.select_clause_t)->opt_from_clause_ = (yyvsp[-2].opt_from_clause_t);
            (yyval.select_clause_t)->opt_where_ = (yyvsp[-1].opt_where_t);
            (yyval.select_clause_t)->opt_group_ = (yyvsp[0].opt_group_t);
        }
#line 6230 "bison_parser.cpp"
    break;

  case 244: /* select_clause: SELECT opt_top opt_distinct select_list opt_from_clause opt_where opt_group window_clause  */
#line 1901 "bison_parser.y"
                                                                                                  {
            (yyval.select_clause_t) = new SelectClause();
            (yyval.select_clause_t)->sub_type_ = CASE1;
            (yyval.select_clause_t)->opt_top_ = (yyvsp[-6].opt_top_t);
            (yyval.select_clause_t)->opt_distinct_ = (yyvsp[-5].opt_distinct_t);
            (yyval.select_clause_t)->select_list_ = (yyvsp[-4].select_list_t);
            (yyval.select_clause_t)->opt_from_clause_ = (yyvsp[-3].opt_from_clause_t);
            (yyval.select_clause_t)->opt_where_ = (yyvsp[-2].opt_where_t);
            (yyval.select_clause_t)->opt_group_ = (yyvsp[-1].opt_group_t);
            (yyval.select_clause_t)->window_clause_ = (yyvsp[0].window_clause_t);
        }
#line 6246 "bison_parser.cpp"
    break;

  case 245: /* window_clause: WINDOW windowdefn_list  */
#line 1915 "bison_parser.y"
                               {(yyval.window_clause_t) = new WindowClause(); (yyval.window_clause_t)->windowdefn_list_ = (yyvsp[0].window_defn_list_t);}
#line 6252 "bison_parser.cpp"
    break;

  case 246: /* windowdefn_list: windowdefn  */
#line 1919 "bison_parser.y"
                   {(yyval.window_defn_list_t) = new WindowDefnList(); (yyval.window_defn_list_t)->v_windowdefn_list_.push_back((yyvsp[0].window_defn_t));}
#line 6258 "bison_parser.cpp"
    break;

  case 247: /* windowdefn_list: windowdefn_list ',' windowdefn  */
#line 1920 "bison_parser.y"
                                       {(yyvsp[-2].window_defn_list_t)->v_windowdefn_list_.push_back((yyvsp[0].window_defn_t)); (yyval.window_defn_list_t) = (yyvsp[-2].window_defn_list_t);}
#line 6264 "bison_parser.cpp"
    break;

  case 248: /* windowdefn: IDENTIFIER AS '(' window ')'  */
#line 1924 "bison_parser.y"
                                     {(yyval.window_defn_t) = new WindowDefn(); (yyval.window_defn_t)->id_ = new Identifier((yyvsp[-4].sval)); (yyval.window_defn_t)->window_ = (yyvsp[-1].window_t); free((yyvsp[-4].sval));}
#line 6270 "bison_parser.cpp"
    break;

  case 249: /* window: window_with_order  */
#line 1928 "bison_parser.y"
                          { (yyval.window_t) = new Window(); (yyval.window_t)->sub_type_ = CASE0; (yyval.window_t)->WindowWithOrder_ = (yyvsp[0].window_with_order_t); }
#line 6276 "bison_parser.cpp"
    break;

  case 250: /* window: window_no_order  */
#line 1929 "bison_parser.y"
                       { (yyval.window_t) = new Window(); (yyval.window_t)->sub_type_ = CASE1; (yyval.window_t)->WindowNoOrder_ = (yyvsp[0].window_no_order_t); }
#line 6282 "bison_parser.cpp"
    break;

  case 251: /* window_with_order: opt_base_window_name PARTITION BY expr_list order opt_frame  */
#line 1933 "bison_parser.y"
                                                                    {
            (yyval.window_with_order_t) = new WindowWithOrder();
            (yyval.window_with_order_t)->sub_type_ = CASE0;
            (yyval.window_with_order_t)->opt_base_window_name_ = (yyvsp[-5].opt_base_window_name_t);
            (yyval.window_with_order_t)->expr_list_ = (yyvsp[-2].expr_list_t);
            (yyval.window_with_order_t)->order_ = (yyvsp[-1].order_t);
            (yyval.window_with_order_t)->opt_frame_ = (yyvsp[0].opt_frame_t);
        }
#line 6295 "bison_parser.cpp"
    break;

  case 252: /* window_with_order: opt_base_window_name order opt_frame  */
#line 1941 "bison_parser.y"
                                             {
            (yyval.window_with_order_t) = new WindowWithOrder();
            (yyval.window_with_order_t)->sub_type_ = CASE1;
            (yyval.window_with_order_t)->opt_base_window_name_ = (yyvsp[-2].opt_base_window_name_t);
            (yyval.window_with_order_t)->order_ = (yyvsp[-1].order_t);
            (yyval.window_with_order_t)->opt_frame_ = (yyvsp[0].opt_frame_t);
        }
#line 6307 "bison_parser.cpp"
    break;

  case 253: /* window_no_order: opt_base_window_name PARTITION BY expr_list opt_frame  */
#line 1951 "bison_parser.y"
                                                              {
            (yyval.window_no_order_t) = new WindowNoOrder();
            (yyval.window_no_order_t)->sub_type_ = CASE0;
            (yyval.window_no_order_t)->opt_base_window_name_ = (yyvsp[-4].opt_base_window_name_t);
            (yyval.window_no_order_t)->expr_list_ = (yyvsp[-1].expr_list_t);
            (yyval.window_no_order_t)->opt_frame_ = (yyvsp[0].opt_frame_t);
        }
#line 6319 "bison_parser.cpp"
    break;

  case 254: /* window_no_order: opt_base_window_name opt_frame  */
#line 1958 "bison_parser.y"
                                       {
            (yyval.window_no_order_t) = new WindowNoOrder();
            (yyval.window_no_order_t)->sub_type_ = CASE1;
            (yyval.window_no_order_t)->opt_base_window_name_ = (yyvsp[-1].opt_base_window_name_t);
            (yyval.window_no_order_t)->opt_frame_ = (yyvsp[0].opt_frame_t);
        }
#line 6330 "bison_parser.cpp"
    break;

  case 255: /* opt_base_window_name: IDENTIFIER  */
#line 1967 "bison_parser.y"
                   {(yyval.opt_base_window_name_t) = new OptBaseWindowName(); (yyval.opt_base_window_name_t)->sub_type_ = CASE0; (yyval.opt_base_window_name_t)->id_ = new Identifier((yyvsp[0].sval)); free((yyvsp[0].sval));}
#line 6336 "bison_parser.cpp"
    break;

  case 256: /* opt_base_window_name: %empty  */
#line 1968 "bison_parser.y"
                  {(yyval.opt_base_window_name_t) = new OptBaseWindowName(); (yyval.opt_base_window_name_t)->sub_type_ = CASE1;}
#line 6342 "bison_parser.cpp"
    break;

  case 257: /* opt_frame: range_or_rows frame_bound_s opt_frame_exclude  */
#line 1972 "bison_parser.y"
                                                      {
            (yyval.opt_frame_t) = new OptFrame(); 
            (yyval.opt_frame_t)->sub_type_ = CASE0; 
            (yyval.opt_frame_t)->range_or_rows_ = (yyvsp[-2].range_or_rows_t);
            (yyval.opt_frame_t)->frame_bound_s_ = (yyvsp[-1].frame_bound_s_t);
            (yyval.opt_frame_t)->opt_frame_exclude_ = (yyvsp[0].opt_frame_exclude_t);
        }
#line 6354 "bison_parser.cpp"
    break;

  case 258: /* opt_frame: range_or_rows BETWEEN frame_bound_s AND frame_bound_e opt_frame_exclude  */
#line 1979 "bison_parser.y"
                                                                                {
            (yyval.opt_frame_t) = new OptFrame();
            (yyval.opt_frame_t)->sub_type_ = CASE1;
            (yyval.opt_frame_t)->range_or_rows_ = (yyvsp[-5].range_or_rows_t);
            (yyval.opt_frame_t)->frame_bound_s_ = (yyvsp[-3].frame_bound_s_t);
            (yyval.opt_frame_t)->frame_bound_e_ = (yyvsp[-1].frame_bound_e_t);
            (yyval.opt_frame_t)->opt_frame_exclude_ = (yyvsp[0].opt_frame_exclude_t);
        }
#line 6367 "bison_parser.cpp"
    break;

  case 259: /* opt_frame: %empty  */
#line 1987 "bison_parser.y"
                  {(yyval.opt_frame_t) = new OptFrame(); (yyval.opt_frame_t)->sub_type_ = CASE2;}
#line 6373 "bison_parser.cpp"
    break;

  case 260: /* range_or_rows: RANGE  */
#line 1991 "bison_parser.y"
              {(yyval.range_or_rows_t) = new RangeOrRows(); (yyval.range_or_rows_t)->str_val_ = string("RANGE");}
#line 6379 "bison_parser.cpp"
    break;

  case 261: /* range_or_rows: ROWS  */
#line 1992 "bison_parser.y"
             {(yyval.range_or_rows_t) = new RangeOrRows(); (yyval.range_or_rows_t)->str_val_ = string("ROWS");}
#line 6385 "bison_parser.cpp"
    break;

  case 262: /* frame_bound_s: frame_bound  */
#line 1997 "bison_parser.y"
                    {(yyval.frame_bound_s_t) = new FrameBoundS(); (yyval.frame_bound_s_t)->sub_type_ = CASE0; (yyval.frame_bound_s_t)->frame_bound_ = (yyvsp[0].frame_bound_t);}
#line 6391 "bison_parser.cpp"
    break;

  case 263: /* frame_bound_s: UNBOUNDED PRECEDING  */
#line 1998 "bison_parser.y"
                            {(yyval.frame_bound_s_t) = new FrameBoundS(); (yyval.frame_bound_s_t)->sub_type_ = CASE1;}
#line 6397 "bison_parser.cpp"
    break;

  case 264: /* frame_bound_e: frame_bound  */
#line 2002 "bison_parser.y"
                    {(yyval.frame_bound_e_t) = new FrameBoundE(); (yyval.frame_bound_e_t)->sub_type_ = CASE0; (yyval.frame_bound_e_t)->frame_bound_ = (yyvsp[0].frame_bound_t);}
#line 6403 "bison_parser.cpp"
    break;

  case 265: /* frame_bound_e: UNBOUNDED FOLLOWING  */
#line 2003 "bison_parser.y"
                            {(yyval.frame_bound_e_t) = new FrameBoundE(); (yyval.frame_bound_e_t)->sub_type_ = CASE1;}
#line 6409 "bison_parser.cpp"
    break;

  case 266: /* frame_bound: expr PRECEDING  */
#line 2007 "bison_parser.y"
                       {(yyval.frame_bound_t) = new FrameBound(); (yyval.frame_bound_t)->sub_type_ = CASE0; (yyval.frame_bound_t)->expr_ = (yyvsp[-1].expr_t);}
#line 6415 "bison_parser.cpp"
    break;

  case 267: /* frame_bound: expr FOLLOWING  */
#line 2008 "bison_parser.y"
                       {(yyval.frame_bound_t) = new FrameBound(); (yyval.frame_bound_t)->sub_type_ = CASE1; (yyval.frame_bound_t)->expr_ = (yyvsp[-1].expr_t);}
#line 6421 "bison_parser.cpp"
    break;

  case 268: /* frame_bound: CURRENT ROW  */
#line 2009 "bison_parser.y"
                    {(yyval.frame_bound_t) = new FrameBound(); (yyval.frame_bound_t)->sub_type_ = CASE2;}
#line 6427 "bison_parser.cpp"
    break;

  case 269: /* opt_frame_exclude: EXCLUDE frame_exclude  */
#line 2013 "bison_parser.y"
                              {(yyval.opt_frame_exclude_t) = new OptFrameExclude(); (yyval.opt_frame_exclude_t)->sub_type_ = CASE0; (yyval.opt_frame_exclude_t)->frame_exclude_ = (yyvsp[0].frame_exclude_t);}
#line 6433 "bison_parser.cpp"
    break;

  case 270: /* opt_frame_exclude: %empty  */
#line 2014 "bison_parser.y"
                    {(yyval.opt_frame_exclude_t) = new OptFrameExclude(); (yyval.opt_frame_exclude_t)->sub_type_ = CASE1; }
#line 6439 "bison_parser.cpp"
    break;

  case 271: /* frame_exclude: NO OTHERS  */
#line 2018 "bison_parser.y"
                  {(yyval.frame_exclude_t) = new FrameExclude(); (yyval.frame_exclude_t)->str_val_ = string("NO OTHERS");}
#line 6445 "bison_parser.cpp"
    break;

  case 272: /* frame_exclude: CURRENT ROW  */
#line 2019 "bison_parser.y"
                    {(yyval.frame_exclude_t) = new FrameExclude(); (yyval.frame_exclude_t)->str_val_ = string("CURRENT ROW");}
#line 6451 "bison_parser.cpp"
    break;

  case 273: /* frame_exclude: GROUP  */
#line 2020 "bison_parser.y"
              {(yyval.frame_exclude_t) = new FrameExclude(); (yyval.frame_exclude_t)->str_val_ = string("GROUP");}
#line 6457 "bison_parser.cpp"
    break;

  case 274: /* frame_exclude: TIES  */
#line 2021 "bison_parser.y"
             {(yyval.frame_exclude_t) = new FrameExclude(); (yyval.frame_exclude_t)->str_val_ = string("TIES");}
#line 6463 "bison_parser.cpp"
    break;

  case 275: /* opt_distinct: DISTINCT  */
#line 2026 "bison_parser.y"
                 { (yyval.opt_distinct_t) = new OptDistinct();  (yyval.opt_distinct_t)->str_val_ = string("DISTINCT");}
#line 6469 "bison_parser.cpp"
    break;

  case 276: /* opt_distinct: %empty  */
#line 2027 "bison_parser.y"
                    { (yyval.opt_distinct_t) = new OptDistinct();  (yyval.opt_distinct_t)->str_val_ = string("");}
#line 6475 "bison_parser.cpp"
    break;

  case 277: /* select_list: expr_list  */
#line 2031 "bison_parser.y"
                  {
            (yyval.select_list_t) = new SelectList();
            (yyval.select_list_t)->expr_list_ = (yyvsp[0].expr_list_t);
        }
#line 6484 "bison_parser.cpp"
    break;

  case 278: /* opt_from_clause: from_clause  */
#line 2038 "bison_parser.y"
                     { (yyval.opt_from_clause_t) = new OptFromClause(); (yyval.opt_from_clause_t)->sub_type_ = CASE0; (yyval.opt_from_clause_t)->from_clause_ = (yyvsp[0].from_clause_t);}
#line 6490 "bison_parser.cpp"
    break;

  case 279: /* opt_from_clause: %empty  */
#line 2039 "bison_parser.y"
                     { (yyval.opt_from_clause_t) = new OptFromClause(); (yyval.opt_from_clause_t)->sub_type_ = CASE1;}
#line 6496 "bison_parser.cpp"
    break;

  case 280: /* from_clause: FROM table_ref  */
#line 2043 "bison_parser.y"
                       { (yyval.from_clause_t) = new FromClause(); (yyval.from_clause_t)->table_ref_ = (yyvsp[0].table_ref_t);}
#line 6502 "bison_parser.cpp"
    break;

  case 281: /* opt_where: WHERE expr  */
#line 2048 "bison_parser.y"
                   { (yyval.opt_where_t) = new OptWhere(); (yyval.opt_where_t)->sub_type_ = CASE0; (yyval.opt_where_t)->expr_ = (yyvsp[0].expr_t); }
#line 6508 "bison_parser.cpp"
    break;

  case 282: /* opt_where: %empty  */
#line 2049 "bison_parser.y"
                    { (yyval.opt_where_t) = new OptWhere(); (yyval.opt_where_t)->sub_type_ = CASE1;}
#line 6514 "bison_parser.cpp"
    break;

  case 283: /* opt_group: GROUP BY expr_list opt_having  */
#line 2053 "bison_parser.y"
                                      {
            (yyval.opt_group_t) = new OptGroup();
            (yyval.opt_group_t)->sub_type_ = CASE0;
            (yyval.opt_group_t)->expr_list_ = (yyvsp[-1].expr_list_t);
            (yyval.opt_group_t)->opt_having_ = (yyvsp[0].opt_having_t);
        }
#line 6525 "bison_parser.cpp"
    break;

  case 284: /* opt_group: %empty  */
#line 2059 "bison_parser.y"
                    { (yyval.opt_group_t) = new OptGroup(); (yyval.opt_group_t)->sub_type_ = CASE1;}
#line 6531 "bison_parser.cpp"
    break;

  case 285: /* opt_having: HAVING expr  */
#line 2063 "bison_parser.y"
                    { (yyval.opt_having_t) = new OptHaving(); (yyval.opt_having_t)->sub_type_ = CASE0; (yyval.opt_having_t)->expr_ = (yyvsp[0].expr_t); }
#line 6537 "bison_parser.cpp"
    break;

  case 286: /* opt_having: %empty  */
#line 2064 "bison_parser.y"
                    { (yyval.opt_having_t) = new OptHaving(); (yyval.opt_having_t)->sub_type_ = CASE1;}
#line 6543 "bison_parser.cpp"
    break;

  case 287: /* opt_order: order  */
#line 2067 "bison_parser.y"
              { (yyval.opt_order_t) = new OptOrder(); (yyval.opt_order_t)->sub_type_ = CASE0; (yyval.opt_order_t)->order_ = (yyvsp[0].order_t); }
#line 6549 "bison_parser.cpp"
    break;

  case 288: /* opt_order: %empty  */
#line 2068 "bison_parser.y"
                    {  (yyval.opt_order_t) = new OptOrder(); (yyval.opt_order_t)->sub_type_ = CASE1; }
#line 6555 "bison_parser.cpp"
    break;

  case 289: /* order: ORDER BY order_list  */
#line 2072 "bison_parser.y"
                            { (yyval.order_t) = new Order(); (yyval.order_t)->order_list_ = (yyvsp[0].order_list_t); }
#line 6561 "bison_parser.cpp"
    break;

  case 290: /* order_list: order_desc  */
#line 2076 "bison_parser.y"
                   { (yyval.order_list_t) = new OrderList(); (yyval.order_list_t)->v_order_desc_.push_back((yyvsp[0].order_desc_t)); }
#line 6567 "bison_parser.cpp"
    break;

  case 291: /* order_list: order_list ',' order_desc  */
#line 2077 "bison_parser.y"
                                  { (yyvsp[-2].order_list_t)->v_order_desc_.push_back((yyvsp[0].order_desc_t)); (yyval.order_list_t) = (yyvsp[-2].order_list_t); }
#line 6573 "bison_parser.cpp"
    break;

  case 292: /* order_desc: expr opt_order_type opt_null  */
#line 2081 "bison_parser.y"
                                    { (yyval.order_desc_t) = new OrderDesc(); (yyval.order_desc_t)->expr_ = (yyvsp[-2].expr_t); (yyval.order_desc_t)->opt_order_type_ = (yyvsp[-1].opt_order_type_t); (yyval.order_desc_t)->opt_null_ = (yyvsp[0].opt_null_t);}
#line 6579 "bison_parser.cpp"
    break;

  case 293: /* opt_order_type: ASC  */
#line 2085 "bison_parser.y"
            { (yyval.opt_order_type_t) = new OptOrderType(); (yyval.opt_order_type_t)->str_val_ = string("ASC"); }
#line 6585 "bison_parser.cpp"
    break;

  case 294: /* opt_order_type: DESC  */
#line 2086 "bison_parser.y"
             { (yyval.opt_order_type_t) = new OptOrderType(); (yyval.opt_order_type_t)->str_val_ = string("DESC"); }
#line 6591 "bison_parser.cpp"
    break;

  case 295: /* opt_order_type: %empty  */
#line 2087 "bison_parser.y"
                    { (yyval.opt_order_type_t) = new OptOrderType(); (yyval.opt_order_type_t)->str_val_ = string(""); }
#line 6597 "bison_parser.cpp"
    break;

  case 296: /* opt_top: TOP int_literal  */
#line 2092 "bison_parser.y"
                        { 
            (yyval.opt_top_t) = new OptTop(); 
            (yyval.opt_top_t)->sub_type_ = CASE0;
            (yyval.opt_top_t)->int_literal_ = (yyvsp[0].int_literal_t);
            }
#line 6607 "bison_parser.cpp"
    break;

  case 297: /* opt_top: %empty  */
#line 2097 "bison_parser.y"
                    { 
            (yyval.opt_top_t) = new OptTop(); 
            (yyval.opt_top_t)->sub_type_ = CASE1;
            }
#line 6616 "bison_parser.cpp"
    break;

  case 298: /* opt_limit: LIMIT expr  */
#line 2104 "bison_parser.y"
                   { (yyval.opt_limit_t) = new OptLimit(); (yyval.opt_limit_t)->sub_type_ = CASE0; (yyval.opt_limit_t)->expr1_ = (yyvsp[0].expr_t);}
#line 6622 "bison_parser.cpp"
    break;

  case 299: /* opt_limit: OFFSET expr  */
#line 2105 "bison_parser.y"
                    { (yyval.opt_limit_t) = new OptLimit(); (yyval.opt_limit_t)->sub_type_ = CASE1; (yyval.opt_limit_t)->expr1_ = (yyvsp[0].expr_t);}
#line 6628 "bison_parser.cpp"
    break;

  case 300: /* opt_limit: LIMIT expr OFFSET expr  */
#line 2106 "bison_parser.y"
                               { (yyval.opt_limit_t) = new OptLimit(); (yyval.opt_limit_t)->sub_type_ = CASE2; (yyval.opt_limit_t)->expr1_ = (yyvsp[-2].expr_t); (yyval.opt_limit_t)->expr2_ = (yyvsp[0].expr_t);}
#line 6634 "bison_parser.cpp"
    break;

  case 301: /* opt_limit: LIMIT ALL  */
#line 2107 "bison_parser.y"
                  { (yyval.opt_limit_t) = new OptLimit(); (yyval.opt_limit_t)->sub_type_ = CASE3;}
#line 6640 "bison_parser.cpp"
    break;

  case 302: /* opt_limit: LIMIT ALL OFFSET expr  */
#line 2108 "bison_parser.y"
                              { (yyval.opt_limit_t) = new OptLimit(); (yyval.opt_limit_t)->sub_type_ = CASE4; (yyval.opt_limit_t)->expr1_ = (yyvsp[0].expr_t);}
#line 6646 "bison_parser.cpp"
    break;

  case 303: /* opt_limit: %empty  */
#line 2109 "bison_parser.y"
                    { (yyval.opt_limit_t) = nullptr; }
#line 6652 "bison_parser.cpp"
    break;

  case 304: /* expr_list: expr_alias  */
#line 2116 "bison_parser.y"
                   { 
            (yyval.expr_list_t) = new ExprList(); 
            (yyval.expr_list_t)->v_expr_list_.push_back((yyvsp[0].expr_alias_t)); 
            }
#line 6661 "bison_parser.cpp"
    break;

  case 305: /* expr_list: expr_list ',' expr_alias  */
#line 2120 "bison_parser.y"
                                 { 
        (yyvsp[-2].expr_list_t)->v_expr_list_.push_back((yyvsp[0].expr_alias_t)); 
        (yyval.expr_list_t) = (yyvsp[-2].expr_list_t); }
#line 6669 "bison_parser.cpp"
    break;

  case 306: /* opt_literal_list: literal_list  */
#line 2126 "bison_parser.y"
                     { 
            (yyval.opt_literal_list_t) = new OptLiteralList();
            (yyval.opt_literal_list_t)->sub_type_ = CASE0;
            (yyval.opt_literal_list_t)->literal_list_ = (yyvsp[0].literal_list_t);
            }
#line 6679 "bison_parser.cpp"
    break;

  case 307: /* opt_literal_list: %empty  */
#line 2131 "bison_parser.y"
                    { 
            (yyval.opt_literal_list_t) = new OptLiteralList();
            (yyval.opt_literal_list_t)->sub_type_ = CASE1; }
#line 6687 "bison_parser.cpp"
    break;

  case 308: /* literal_list: literal  */
#line 2137 "bison_parser.y"
                { 
            (yyval.literal_list_t) = new LiteralList(); 
            (yyval.literal_list_t)->v_literal_list_.push_back((yyvsp[0].literal_t)); 
            }
#line 6696 "bison_parser.cpp"
    break;

  case 309: /* literal_list: literal_list ',' literal  */
#line 2141 "bison_parser.y"
                                 { 
        (yyvsp[-2].literal_list_t)->v_literal_list_.push_back((yyvsp[0].literal_t)); 
        (yyval.literal_list_t) = (yyvsp[-2].literal_list_t); 
        }
#line 6705 "bison_parser.cpp"
    break;

  case 310: /* expr_alias: expr opt_alias  */
#line 2148 "bison_parser.y"
                       {
            (yyval.expr_alias_t) = new ExprAlias();
            (yyval.expr_alias_t)->expr_ = (yyvsp[-1].expr_t);
            (yyval.expr_alias_t)->opt_alias_ = (yyvsp[0].opt_alias_t);
        }
#line 6715 "bison_parser.cpp"
    break;

  case 311: /* expr: operand  */
#line 2156 "bison_parser.y"
                {(yyval.expr_t) = (yyvsp[0].operand_t);}
#line 6721 "bison_parser.cpp"
    break;

  case 312: /* expr: between_expr  */
#line 2157 "bison_parser.y"
                     {(yyval.expr_t) = (yyvsp[0].between_expr_t);}
#line 6727 "bison_parser.cpp"
    break;

  case 313: /* expr: logic_expr  */
#line 2158 "bison_parser.y"
                   {(yyval.expr_t) = (yyvsp[0].logic_expr_t);}
#line 6733 "bison_parser.cpp"
    break;

  case 314: /* expr: exists_expr  */
#line 2159 "bison_parser.y"
                    {(yyval.expr_t) = (yyvsp[0].exists_expr_t);}
#line 6739 "bison_parser.cpp"
    break;

  case 315: /* expr: in_expr  */
#line 2160 "bison_parser.y"
                {(yyval.expr_t) = (yyvsp[0].in_expr_t);}
#line 6745 "bison_parser.cpp"
    break;

  case 316: /* expr: cast_expr  */
#line 2161 "bison_parser.y"
                  {(yyval.expr_t) = (yyvsp[0].cast_expr_t);}
#line 6751 "bison_parser.cpp"
    break;

  case 317: /* operand: '(' expr ')'  */
#line 2165 "bison_parser.y"
                     { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE0; (yyval.operand_t)->expr_ = (yyvsp[-1].expr_t); }
#line 6757 "bison_parser.cpp"
    break;

  case 318: /* operand: array_index  */
#line 2166 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].array_index_t); }
#line 6763 "bison_parser.cpp"
    break;

  case 319: /* operand: scalar_expr  */
#line 2167 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].scalar_expr_t); }
#line 6769 "bison_parser.cpp"
    break;

  case 320: /* operand: unary_expr  */
#line 2168 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].unary_expr_t); }
#line 6775 "bison_parser.cpp"
    break;

  case 321: /* operand: binary_expr  */
#line 2169 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].binary_expr_t); }
#line 6781 "bison_parser.cpp"
    break;

  case 322: /* operand: case_expr  */
#line 2170 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].case_expr_t); }
#line 6787 "bison_parser.cpp"
    break;

  case 323: /* operand: function_expr  */
#line 2171 "bison_parser.y"
                        { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].function_expr_t); }
#line 6793 "bison_parser.cpp"
    break;

  case 324: /* operand: extract_expr  */
#line 2172 "bison_parser.y"
                        { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].extract_expr_t); }
#line 6799 "bison_parser.cpp"
    break;

  case 325: /* operand: array_expr  */
#line 2173 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].array_expr_t); }
#line 6805 "bison_parser.cpp"
    break;

  case 326: /* operand: '(' select_no_paren ')'  */
#line 2174 "bison_parser.y"
                                { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE2; (yyval.operand_t)->select_no_paren_ = (yyvsp[-1].select_no_paren_t); }
#line 6811 "bison_parser.cpp"
    break;

  case 327: /* operand: json_expr  */
#line 2175 "bison_parser.y"
                    { (yyval.operand_t) = new Operand(); (yyval.operand_t)->sub_type_ = CASE1; (yyval.operand_t)->expr_ = (yyvsp[0].json_expr_t); }
#line 6817 "bison_parser.cpp"
    break;

  case 328: /* json_expr: Jsonexpr_all  */
#line 2179 "bison_parser.y"
                    {
            (yyval.json_expr_t) = new JsonExpr();
            (yyval.json_expr_t)->sub_type_ = CASE2;
            (yyval.json_expr_t)->Jsonexpr_all_ = (yyvsp[0].Jsonexpr_all_t);
        }
#line 6827 "bison_parser.cpp"
    break;

  case 329: /* Jsonexpr_all: Jsondata Jsonpath  */
#line 2187 "bison_parser.y"
                          {
            (yyval.Jsonexpr_all_t) = new Jsonexpr_all();
            (yyval.Jsonexpr_all_t)->Jsondata_ = (yyvsp[-1].Jsondata_t);
            (yyval.Jsonexpr_all_t)->Jsonpath_ = (yyvsp[0].Jsonpath_t);
        }
#line 6837 "bison_parser.cpp"
    break;

  case 330: /* Jsondata: json_literal  */
#line 2195 "bison_parser.y"
                     {
            (yyval.Jsondata_t) = new Jsondata();
            (yyval.Jsondata_t)->sub_type_ = CASE0; 
            (yyval.Jsondata_t)->json_literal_ = (yyvsp[0].json_literal_t);
        }
#line 6847 "bison_parser.cpp"
    break;

  case 331: /* Jsondata: column_name  */
#line 2200 "bison_parser.y"
                    {
            (yyval.Jsondata_t) = new Jsondata();
            (yyval.Jsondata_t)->sub_type_ = CASE1; 
            (yyval.Jsondata_t)->column_name_ = (yyvsp[0].column_name_t);
        }
#line 6857 "bison_parser.cpp"
    break;

  case 332: /* Jsonpath: json_pathliteral  */
#line 2208 "bison_parser.y"
                         {    
            (yyval.Jsonpath_t) = new Jsonpath();
            (yyval.Jsonpath_t)->json_pathliteral_ = (yyvsp[0].json_pathliteral_t);
        }
#line 6866 "bison_parser.cpp"
    break;

  case 333: /* cast_expr: CAST '(' expr AS column_type ')'  */
#line 2215 "bison_parser.y"
                                             {
		    (yyval.cast_expr_t) = new CastExpr();
		    (yyval.cast_expr_t)->expr_ = (yyvsp[-3].expr_t);
            (yyval.cast_expr_t)->column_type_ = (yyvsp[-1].column_type_t);
	    }
#line 6876 "bison_parser.cpp"
    break;

  case 334: /* scalar_expr: column_name  */
#line 2223 "bison_parser.y"
                    {(yyval.scalar_expr_t) = new ScalarExpr(); (yyval.scalar_expr_t)->sub_type_=CASE0; (yyval.scalar_expr_t)->column_name_ = (yyvsp[0].column_name_t);}
#line 6882 "bison_parser.cpp"
    break;

  case 335: /* scalar_expr: literal  */
#line 2224 "bison_parser.y"
                {(yyval.scalar_expr_t) = new ScalarExpr(); (yyval.scalar_expr_t)->sub_type_=CASE1; (yyval.scalar_expr_t)->literal_ = (yyvsp[0].literal_t);}
#line 6888 "bison_parser.cpp"
    break;

  case 336: /* unary_expr: '-' operand  */
#line 2228 "bison_parser.y"
                    { 
            (yyval.unary_expr_t) =new UnaryExpr(); 
            (yyval.unary_expr_t)->sub_type_ = CASE0;
            (yyval.unary_expr_t)->operand_ = (yyvsp[0].operand_t);
            (yyval.unary_expr_t)->operator_ = string("-");
            }
#line 6899 "bison_parser.cpp"
    break;

  case 337: /* unary_expr: NOT operand  */
#line 2234 "bison_parser.y"
                    { 
        (yyval.unary_expr_t) =new UnaryExpr(); 
            (yyval.unary_expr_t)->sub_type_ = CASE1;
            (yyval.unary_expr_t)->operand_ = (yyvsp[0].operand_t);
            (yyval.unary_expr_t)->operator_ = string("NOT");
        }
#line 6910 "bison_parser.cpp"
    break;

  case 338: /* unary_expr: operand ISNULL  */
#line 2240 "bison_parser.y"
                       { 
            (yyval.unary_expr_t) =new UnaryExpr(); 
            (yyval.unary_expr_t)->sub_type_ = CASE2;
            (yyval.unary_expr_t)->operand_ = (yyvsp[-1].operand_t);
            (yyval.unary_expr_t)->operator_ = string("ISNULL");
        }
#line 6921 "bison_parser.cpp"
    break;

  case 339: /* unary_expr: operand IS NULL  */
#line 2246 "bison_parser.y"
                        { 
            (yyval.unary_expr_t) =new UnaryExpr(); 
            (yyval.unary_expr_t)->sub_type_ = CASE3;
            (yyval.unary_expr_t)->operand_ = (yyvsp[-2].operand_t);
            (yyval.unary_expr_t)->operator_ = string("IS NULL");
        }
#line 6932 "bison_parser.cpp"
    break;

  case 340: /* unary_expr: operand IS NOT NULL  */
#line 2252 "bison_parser.y"
                            { 
            (yyval.unary_expr_t) =new UnaryExpr(); 
            (yyval.unary_expr_t)->sub_type_ = CASE4;
            (yyval.unary_expr_t)->operand_ = (yyvsp[-3].operand_t);
            (yyval.unary_expr_t)->operator_ = string("IS NOT NULL");
        }
#line 6943 "bison_parser.cpp"
    break;

  case 341: /* binary_expr: comp_expr  */
#line 2261 "bison_parser.y"
                  {(yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE0; (yyval.binary_expr_t)->comp_expr_ = (yyvsp[0].comp_expr_t);}
#line 6949 "bison_parser.cpp"
    break;

  case 342: /* binary_expr: operand '-' operand  */
#line 2262 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("-");}
#line 6955 "bison_parser.cpp"
    break;

  case 343: /* binary_expr: operand '+' operand  */
#line 2263 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("+");}
#line 6961 "bison_parser.cpp"
    break;

  case 344: /* binary_expr: operand '/' operand  */
#line 2264 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("/");}
#line 6967 "bison_parser.cpp"
    break;

  case 345: /* binary_expr: operand '*' operand  */
#line 2265 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("*");}
#line 6973 "bison_parser.cpp"
    break;

  case 346: /* binary_expr: operand '%' operand  */
#line 2266 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("%");}
#line 6979 "bison_parser.cpp"
    break;

  case 347: /* binary_expr: operand '^' operand  */
#line 2267 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("^");}
#line 6985 "bison_parser.cpp"
    break;

  case 348: /* binary_expr: operand LIKE operand  */
#line 2268 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("LIKE");}
#line 6991 "bison_parser.cpp"
    break;

  case 349: /* binary_expr: operand NOT LIKE operand  */
#line 2269 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-3].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("NOT LIKE");}
#line 6997 "bison_parser.cpp"
    break;

  case 350: /* binary_expr: operand ILIKE operand  */
#line 2270 "bison_parser.y"
                                    { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("ILIKE");}
#line 7003 "bison_parser.cpp"
    break;

  case 351: /* binary_expr: operand CONCAT operand  */
#line 2271 "bison_parser.y"
                                { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("||");}
#line 7009 "bison_parser.cpp"
    break;

  case 352: /* binary_expr: operand GLOB operand  */
#line 2272 "bison_parser.y"
                                { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE2; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("GLOB");}
#line 7015 "bison_parser.cpp"
    break;

  case 353: /* binary_expr: column_name MATCH fts_query_literal  */
#line 2273 "bison_parser.y"
                                              {
            (yyval.binary_expr_t) = new BinaryExpr(); 
            (yyval.binary_expr_t)->sub_type_ = CASE2; 
            (yyval.binary_expr_t)->column_name_ = (yyvsp[-2].column_name_t); 
            (yyval.binary_expr_t)->FtsQueryLiteral_ = (yyvsp[0].fts_query_literal_t);
            (yyval.binary_expr_t)->operator_ = string("MATCH");
        }
#line 7027 "bison_parser.cpp"
    break;

  case 354: /* binary_expr: operand REGEX operand  */
#line 2280 "bison_parser.y"
                               { (yyval.binary_expr_t) = new BinaryExpr(); (yyval.binary_expr_t)->sub_type_ = CASE1; (yyval.binary_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.binary_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.binary_expr_t)->operator_ = string("REGEX");}
#line 7033 "bison_parser.cpp"
    break;

  case 355: /* fts_query_literal: STRING  */
#line 2284 "bison_parser.y"
               { (yyval.fts_query_literal_t) = new FtsQueryLiteral(); (yyval.fts_query_literal_t)->str_val_=(yyvsp[0].sval); free((yyvsp[0].sval));}
#line 7039 "bison_parser.cpp"
    break;

  case 356: /* logic_expr: expr AND expr  */
#line 2288 "bison_parser.y"
                        { (yyval.logic_expr_t) = new LogicExpr(); (yyval.logic_expr_t)->expr1_=(yyvsp[-2].expr_t); (yyval.logic_expr_t)->expr2_=(yyvsp[0].expr_t); (yyval.logic_expr_t)->operator_=string("AND"); }
#line 7045 "bison_parser.cpp"
    break;

  case 357: /* logic_expr: expr OR expr  */
#line 2289 "bison_parser.y"
                        { (yyval.logic_expr_t) = new LogicExpr(); (yyval.logic_expr_t)->expr1_=(yyvsp[-2].expr_t); (yyval.logic_expr_t)->expr2_=(yyvsp[0].expr_t); (yyval.logic_expr_t)->operator_=string("OR"); }
#line 7051 "bison_parser.cpp"
    break;

  case 358: /* in_expr: operand IN '(' expr_list ')'  */
#line 2293 "bison_parser.y"
                                                { (yyval.in_expr_t) = new InExpr(); (yyval.in_expr_t)->sub_type_=CASE0; (yyval.in_expr_t)->operand_=(yyvsp[-4].operand_t); (yyval.in_expr_t)->expr_list_=(yyvsp[-1].expr_list_t);}
#line 7057 "bison_parser.cpp"
    break;

  case 359: /* in_expr: operand NOT IN '(' expr_list ')'  */
#line 2294 "bison_parser.y"
                                                { (yyval.in_expr_t) = new InExpr(); (yyval.in_expr_t)->sub_type_=CASE1; (yyval.in_expr_t)->operand_=(yyvsp[-5].operand_t); (yyval.in_expr_t)->expr_list_=(yyvsp[-1].expr_list_t);}
#line 7063 "bison_parser.cpp"
    break;

  case 360: /* in_expr: operand IN '(' select_no_paren ')'  */
#line 2295 "bison_parser.y"
                                                { (yyval.in_expr_t) = new InExpr(); (yyval.in_expr_t)->sub_type_=CASE2; (yyval.in_expr_t)->operand_=(yyvsp[-4].operand_t); (yyval.in_expr_t)->select_no_paren_=(yyvsp[-1].select_no_paren_t);}
#line 7069 "bison_parser.cpp"
    break;

  case 361: /* in_expr: operand NOT IN '(' select_no_paren ')'  */
#line 2296 "bison_parser.y"
                                                { (yyval.in_expr_t) = new InExpr(); (yyval.in_expr_t)->sub_type_=CASE3; (yyval.in_expr_t)->operand_=(yyvsp[-5].operand_t); (yyval.in_expr_t)->select_no_paren_=(yyvsp[-1].select_no_paren_t);}
#line 7075 "bison_parser.cpp"
    break;

  case 362: /* case_expr: CASE expr case_list END  */
#line 2302 "bison_parser.y"
                                            { (yyval.case_expr_t) = new CaseExpr(); (yyval.case_expr_t)->sub_type_=CASE0; (yyval.case_expr_t)->case_expr_=(yyvsp[-2].expr_t); (yyval.case_expr_t)->case_list_=(yyvsp[-1].case_list_t); }
#line 7081 "bison_parser.cpp"
    break;

  case 363: /* case_expr: CASE expr case_list ELSE expr END  */
#line 2303 "bison_parser.y"
                                            { (yyval.case_expr_t) = new CaseExpr(); (yyval.case_expr_t)->sub_type_=CASE1; (yyval.case_expr_t)->case_expr_=(yyvsp[-4].expr_t); (yyval.case_expr_t)->case_list_=(yyvsp[-3].case_list_t); (yyval.case_expr_t)->else_expr_=(yyvsp[-1].expr_t);}
#line 7087 "bison_parser.cpp"
    break;

  case 364: /* case_expr: CASE case_list END  */
#line 2304 "bison_parser.y"
                                            { (yyval.case_expr_t) = new CaseExpr(); (yyval.case_expr_t)->sub_type_=CASE2; (yyval.case_expr_t)->case_list_=(yyvsp[-1].case_list_t); }
#line 7093 "bison_parser.cpp"
    break;

  case 365: /* case_expr: CASE case_list ELSE expr END  */
#line 2305 "bison_parser.y"
                                            { (yyval.case_expr_t) = new CaseExpr(); (yyval.case_expr_t)->sub_type_=CASE3; (yyval.case_expr_t)->else_expr_=(yyvsp[-1].expr_t); (yyval.case_expr_t)->case_list_=(yyvsp[-3].case_list_t); }
#line 7099 "bison_parser.cpp"
    break;

  case 366: /* case_list: WHEN expr THEN expr  */
#line 2309 "bison_parser.y"
                                         { (yyval.case_list_t) = new CaseList(); (yyval.case_list_t)->v_case_list_.push_back(new CaseClause((yyvsp[-2].expr_t),(yyvsp[0].expr_t))); }
#line 7105 "bison_parser.cpp"
    break;

  case 367: /* case_list: case_list WHEN expr THEN expr  */
#line 2310 "bison_parser.y"
                                         { (yyval.case_list_t)->v_case_list_.push_back(new CaseClause((yyvsp[-2].expr_t), (yyvsp[0].expr_t))); (yyval.case_list_t) = (yyvsp[-4].case_list_t); }
#line 7111 "bison_parser.cpp"
    break;

  case 368: /* exists_expr: EXISTS '(' select_no_paren ')'  */
#line 2314 "bison_parser.y"
                                       { (yyval.exists_expr_t) = new ExistsExpr(); (yyval.exists_expr_t)->sub_type_=CASE0; (yyval.exists_expr_t)->select_no_paren_=(yyvsp[-1].select_no_paren_t);}
#line 7117 "bison_parser.cpp"
    break;

  case 369: /* exists_expr: NOT EXISTS '(' select_no_paren ')'  */
#line 2315 "bison_parser.y"
                                           { (yyval.exists_expr_t) = new ExistsExpr(); (yyval.exists_expr_t)->sub_type_=CASE1; (yyval.exists_expr_t)->select_no_paren_=(yyvsp[-1].select_no_paren_t);}
#line 7123 "bison_parser.cpp"
    break;

  case 370: /* comp_expr: operand '=' operand  */
#line 2319 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string("="); }
#line 7129 "bison_parser.cpp"
    break;

  case 371: /* comp_expr: operand EQUALS operand  */
#line 2320 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string("=="); }
#line 7135 "bison_parser.cpp"
    break;

  case 372: /* comp_expr: operand NOTEQUALS operand  */
#line 2321 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string("!="); }
#line 7141 "bison_parser.cpp"
    break;

  case 373: /* comp_expr: operand '<' operand  */
#line 2322 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string("<"); }
#line 7147 "bison_parser.cpp"
    break;

  case 374: /* comp_expr: operand '>' operand  */
#line 2323 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string(">"); }
#line 7153 "bison_parser.cpp"
    break;

  case 375: /* comp_expr: operand LESSEQ operand  */
#line 2324 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string("<="); }
#line 7159 "bison_parser.cpp"
    break;

  case 376: /* comp_expr: operand GREATEREQ operand  */
#line 2325 "bison_parser.y"
                                    { (yyval.comp_expr_t) = new CompExpr(); (yyval.comp_expr_t)->operand1_ = (yyvsp[-2].operand_t); (yyval.comp_expr_t)->operand2_ = (yyvsp[0].operand_t); (yyval.comp_expr_t)->operator_ = string(">="); }
#line 7165 "bison_parser.cpp"
    break;

  case 377: /* function_expr: IDENTIFIER '(' ')' opt_filter_clause  */
#line 2329 "bison_parser.y"
                                                                   {
            (yyval.function_expr_t) = new FunctionExpr(); 
            (yyval.function_expr_t)->sub_type_ = CASE0; 
            (yyval.function_expr_t)->id_ = new Identifier((yyvsp[-3].sval)); 
            (yyval.function_expr_t)->opt_filter_clause_ = (yyvsp[0].opt_filter_clause_t);
            /* $$->opt_over_clause_ = $5; */
            free((yyvsp[-3].sval));
        }
#line 7178 "bison_parser.cpp"
    break;

  case 378: /* function_expr: IDENTIFIER '(' opt_distinct expr_list ')' opt_filter_clause  */
#line 2337 "bison_parser.y"
                                                                                          {
            (yyval.function_expr_t) = new FunctionExpr(); 
            (yyval.function_expr_t)->sub_type_ = CASE1; 
            (yyval.function_expr_t)->id_ = new Identifier((yyvsp[-5].sval)); 
            (yyval.function_expr_t)->opt_distinct_ = (yyvsp[-3].opt_distinct_t);
            (yyval.function_expr_t)->expr_list_ = (yyvsp[-2].expr_list_t);
            (yyval.function_expr_t)->opt_filter_clause_ = (yyvsp[0].opt_filter_clause_t);
            /* $$->opt_over_clause_ = $7; */
            free((yyvsp[-5].sval));
        }
#line 7193 "bison_parser.cpp"
    break;

  case 379: /* function_expr: aggregation_func '(' ')' opt_filter_clause opt_over_clause  */
#line 2347 "bison_parser.y"
                                                                   {
            (yyval.function_expr_t) = new FunctionExpr(); 
            (yyval.function_expr_t)->sub_type_ = CASE4; 
            (yyval.function_expr_t)->AggregationFunc_ = (yyvsp[-4].aggregation_func_t);
            (yyval.function_expr_t)->opt_filter_clause_ = (yyvsp[-1].opt_filter_clause_t);
            (yyval.function_expr_t)->opt_over_clause_ = (yyvsp[0].opt_over_clause_t);
        }
#line 7205 "bison_parser.cpp"
    break;

  case 380: /* function_expr: aggregation_func '(' opt_distinct expr_list ')' opt_filter_clause opt_over_clause  */
#line 2354 "bison_parser.y"
                                                                                          {
            (yyval.function_expr_t) = new FunctionExpr(); 
            (yyval.function_expr_t)->sub_type_ = CASE5; 
            (yyval.function_expr_t)->AggregationFunc_ = (yyvsp[-6].aggregation_func_t);
            (yyval.function_expr_t)->opt_distinct_ = (yyvsp[-4].opt_distinct_t);
            (yyval.function_expr_t)->expr_list_ = (yyvsp[-3].expr_list_t);
            (yyval.function_expr_t)->opt_filter_clause_ = (yyvsp[-1].opt_filter_clause_t);
            (yyval.function_expr_t)->opt_over_clause_ = (yyvsp[0].opt_over_clause_t);
        }
#line 7219 "bison_parser.cpp"
    break;

  case 381: /* function_expr: window_func_no_arg '(' ')' over_clause_with_order  */
#line 2363 "bison_parser.y"
                                                          {
            (yyval.function_expr_t) = new FunctionExpr();
            (yyval.function_expr_t)->sub_type_ = CASE2;
            (yyval.function_expr_t)->WindowFuncNoArg_ = (yyvsp[-3].window_func_no_arg_t);
            (yyval.function_expr_t)->OverClauseWithOrder_ = (yyvsp[0].over_clause_with_order_t);
        }
#line 7230 "bison_parser.cpp"
    break;

  case 382: /* function_expr: window_func '(' expr_list ')' over_clause  */
#line 2369 "bison_parser.y"
                                                  {
            (yyval.function_expr_t) = new FunctionExpr();
            (yyval.function_expr_t)->sub_type_ = CASE3;
            (yyval.function_expr_t)->WindowFunc_ = (yyvsp[-4].window_func_t);
            (yyval.function_expr_t)->expr_list_ = (yyvsp[-2].expr_list_t);
            (yyval.function_expr_t)->OverClause_ = (yyvsp[0].over_clause_t);
        }
#line 7242 "bison_parser.cpp"
    break;

  case 383: /* aggregation_func: AVG  */
#line 2397 "bison_parser.y"
            { (yyval.aggregation_func_t) = new AggregationFunc(); (yyval.aggregation_func_t)->str_val_ = string("AVG"); }
#line 7248 "bison_parser.cpp"
    break;

  case 384: /* aggregation_func: MAX  */
#line 2398 "bison_parser.y"
            { (yyval.aggregation_func_t) = new AggregationFunc(); (yyval.aggregation_func_t)->str_val_ = string("MAX"); }
#line 7254 "bison_parser.cpp"
    break;

  case 385: /* aggregation_func: MIN  */
#line 2399 "bison_parser.y"
            { (yyval.aggregation_func_t) = new AggregationFunc(); (yyval.aggregation_func_t)->str_val_ = string("MIN"); }
#line 7260 "bison_parser.cpp"
    break;

  case 386: /* aggregation_func: SUM  */
#line 2400 "bison_parser.y"
            { (yyval.aggregation_func_t) = new AggregationFunc(); (yyval.aggregation_func_t)->str_val_ = string("SUM"); }
#line 7266 "bison_parser.cpp"
    break;

  case 387: /* aggregation_func: COUNT  */
#line 2401 "bison_parser.y"
              { (yyval.aggregation_func_t) = new AggregationFunc(); (yyval.aggregation_func_t)->str_val_ = string("COUNT"); }
#line 7272 "bison_parser.cpp"
    break;

  case 388: /* window_func_no_arg: CUME_DIST  */
#line 2405 "bison_parser.y"
                  { (yyval.window_func_no_arg_t) = new WindowFuncNoArg(); (yyval.window_func_no_arg_t)->str_val_ = string("CUME_DIST"); }
#line 7278 "bison_parser.cpp"
    break;

  case 389: /* window_func_no_arg: DENSE_RANK  */
#line 2406 "bison_parser.y"
                   { (yyval.window_func_no_arg_t) = new WindowFuncNoArg(); (yyval.window_func_no_arg_t)->str_val_ = string("DENSE_RANK"); }
#line 7284 "bison_parser.cpp"
    break;

  case 390: /* window_func_no_arg: PERCENT_RANK  */
#line 2407 "bison_parser.y"
                     { (yyval.window_func_no_arg_t) = new WindowFuncNoArg(); (yyval.window_func_no_arg_t)->str_val_ = string("PERCENT_RANK"); }
#line 7290 "bison_parser.cpp"
    break;

  case 391: /* window_func_no_arg: RANK  */
#line 2408 "bison_parser.y"
             { (yyval.window_func_no_arg_t) = new WindowFuncNoArg(); (yyval.window_func_no_arg_t)->str_val_ = string("RANK"); }
#line 7296 "bison_parser.cpp"
    break;

  case 392: /* window_func_no_arg: ROW_NUMBER  */
#line 2409 "bison_parser.y"
                   { (yyval.window_func_no_arg_t) = new WindowFuncNoArg(); (yyval.window_func_no_arg_t)->str_val_ = string("ROW_NUMBER"); }
#line 7302 "bison_parser.cpp"
    break;

  case 393: /* window_func: LAG  */
#line 2413 "bison_parser.y"
            { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("LAG"); }
#line 7308 "bison_parser.cpp"
    break;

  case 394: /* window_func: LEAD  */
#line 2414 "bison_parser.y"
             { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("LEAD"); }
#line 7314 "bison_parser.cpp"
    break;

  case 395: /* window_func: NTILE  */
#line 2415 "bison_parser.y"
              { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("NTILE"); }
#line 7320 "bison_parser.cpp"
    break;

  case 396: /* window_func: FIRST_VALUE  */
#line 2416 "bison_parser.y"
                    { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("FIRST_VALUE"); }
#line 7326 "bison_parser.cpp"
    break;

  case 397: /* window_func: LAST_VALUE  */
#line 2417 "bison_parser.y"
                   { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("LAST_VALUE"); }
#line 7332 "bison_parser.cpp"
    break;

  case 398: /* window_func: NTH_VALUE  */
#line 2418 "bison_parser.y"
                  { (yyval.window_func_t) = new WindowFunc(); (yyval.window_func_t)->str_val_ = string("NTH_VALUE"); }
#line 7338 "bison_parser.cpp"
    break;

  case 399: /* opt_over_clause: over_clause  */
#line 2424 "bison_parser.y"
                    { (yyval.opt_over_clause_t) = new OptOverClause(); (yyval.opt_over_clause_t)->sub_type_ = CASE0; (yyval.opt_over_clause_t)->OverClause_ = (yyvsp[0].over_clause_t); }
#line 7344 "bison_parser.cpp"
    break;

  case 400: /* opt_over_clause: %empty  */
#line 2425 "bison_parser.y"
                    {(yyval.opt_over_clause_t) = new OptOverClause(); (yyval.opt_over_clause_t)->sub_type_ = CASE1; }
#line 7350 "bison_parser.cpp"
    break;

  case 401: /* over_clause: over_clause_with_order  */
#line 2429 "bison_parser.y"
                               {
            (yyval.over_clause_t) = new OverClause();
            (yyval.over_clause_t)->sub_type_ = CASE0;
            (yyval.over_clause_t)->OverClauseWithOrder_ = (yyvsp[0].over_clause_with_order_t);
        }
#line 7360 "bison_parser.cpp"
    break;

  case 402: /* over_clause: over_clause_no_order  */
#line 2434 "bison_parser.y"
                             {
            (yyval.over_clause_t) = new OverClause();
            (yyval.over_clause_t)->sub_type_ = CASE1;
            (yyval.over_clause_t)->OverClauseNoOrder_ = (yyvsp[0].over_clause_no_order_t);
        }
#line 7370 "bison_parser.cpp"
    break;

  case 403: /* over_clause: OVER IDENTIFIER  */
#line 2439 "bison_parser.y"
                                               {
        (yyval.over_clause_t) = new OverClause(); 
        (yyval.over_clause_t)->sub_type_ = CASE2;
        (yyval.over_clause_t)->id_ = new Identifier((yyvsp[0].sval), id_window_name);
        free((yyvsp[0].sval));
    }
#line 7381 "bison_parser.cpp"
    break;

  case 404: /* over_clause_with_order: OVER '(' window_with_order ')'  */
#line 2448 "bison_parser.y"
                                       {(yyval.over_clause_with_order_t) = new OverClauseWithOrder(); (yyval.over_clause_with_order_t)->WindowWithOrder_ = (yyvsp[-1].window_with_order_t);}
#line 7387 "bison_parser.cpp"
    break;

  case 405: /* over_clause_no_order: OVER '(' window_no_order ')'  */
#line 2452 "bison_parser.y"
                                     {(yyval.over_clause_no_order_t) = new OverClauseNoOrder(); (yyval.over_clause_no_order_t)->WindowNoOrder_ = (yyvsp[-1].window_no_order_t);}
#line 7393 "bison_parser.cpp"
    break;

  case 406: /* opt_filter_clause: FILTER '(' WHERE expr ')'  */
#line 2456 "bison_parser.y"
                                  {(yyval.opt_filter_clause_t) = new OptFilterClause(); (yyval.opt_filter_clause_t)->sub_type_ = CASE0; (yyval.opt_filter_clause_t)->expr_ = (yyvsp[-1].expr_t);}
#line 7399 "bison_parser.cpp"
    break;

  case 407: /* opt_filter_clause: %empty  */
#line 2457 "bison_parser.y"
                  {(yyval.opt_filter_clause_t) = new OptFilterClause(); (yyval.opt_filter_clause_t)->sub_type_ = CASE1;}
#line 7405 "bison_parser.cpp"
    break;

  case 408: /* extract_expr: EXTRACT '(' datetime_field FROM expr ')'  */
#line 2462 "bison_parser.y"
                                                     { 
             (yyval.extract_expr_t) = new ExtractExpr();
             (yyval.extract_expr_t)->datetime_field_ = (yyvsp[-3].datetime_field_t);
             (yyval.extract_expr_t)->expr_ = (yyvsp[-1].expr_t); 
             (yyval.extract_expr_t)->sub_type_ = CASE0;
             }
#line 7416 "bison_parser.cpp"
    break;

  case 409: /* datetime_field: SECOND  */
#line 2471 "bison_parser.y"
               { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("SECOND"); }
#line 7422 "bison_parser.cpp"
    break;

  case 410: /* datetime_field: MINUTE  */
#line 2472 "bison_parser.y"
               { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("MINUTE"); }
#line 7428 "bison_parser.cpp"
    break;

  case 411: /* datetime_field: HOUR  */
#line 2473 "bison_parser.y"
             { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("HOUR"); }
#line 7434 "bison_parser.cpp"
    break;

  case 412: /* datetime_field: DAY  */
#line 2474 "bison_parser.y"
            { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("DAY"); }
#line 7440 "bison_parser.cpp"
    break;

  case 413: /* datetime_field: MONTH  */
#line 2475 "bison_parser.y"
              { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("MONTH"); }
#line 7446 "bison_parser.cpp"
    break;

  case 414: /* datetime_field: YEAR  */
#line 2476 "bison_parser.y"
             { (yyval.datetime_field_t) = new DatetimeField(); (yyval.datetime_field_t)->str_val_ = string("YEAR"); }
#line 7452 "bison_parser.cpp"
    break;

  case 415: /* array_expr: ARRAY '[' expr_list ']'  */
#line 2480 "bison_parser.y"
                                { (yyval.array_expr_t) = new ArrayExpr(); (yyval.array_expr_t)->expr_list_=(yyvsp[-1].expr_list_t); }
#line 7458 "bison_parser.cpp"
    break;

  case 416: /* array_index: operand '[' int_literal ']'  */
#line 2484 "bison_parser.y"
                                    { (yyval.array_index_t) = new ArrayIndex(); (yyval.array_index_t)->operand_ = (yyvsp[-3].operand_t); (yyval.array_index_t)->int_literal_ = (yyvsp[-1].int_literal_t);}
#line 7464 "bison_parser.cpp"
    break;

  case 417: /* between_expr: operand BETWEEN operand AND operand  */
#line 2488 "bison_parser.y"
                                            { (yyval.between_expr_t) = new BetweenExpr(); (yyval.between_expr_t)->operand1_=(yyvsp[-4].operand_t); (yyval.between_expr_t)->operand2_=(yyvsp[-2].operand_t); (yyval.between_expr_t)->operand3_=(yyvsp[0].operand_t);}
#line 7470 "bison_parser.cpp"
    break;

  case 418: /* column_name: IDENTIFIER  */
#line 2492 "bison_parser.y"
                   { (yyval.column_name_t) = new ColumnName(); (yyval.column_name_t)->sub_type_=CASE0; (yyval.column_name_t)->identifier1_=new Identifier((yyvsp[0].sval), id_column_name); free((yyvsp[0].sval));}
#line 7476 "bison_parser.cpp"
    break;

  case 419: /* column_name: IDENTIFIER '.' IDENTIFIER  */
#line 2493 "bison_parser.y"
                                  { (yyval.column_name_t) = new ColumnName(); (yyval.column_name_t)->sub_type_=CASE1; (yyval.column_name_t)->identifier1_=new Identifier((yyvsp[-2].sval), id_table_name); (yyval.column_name_t)->identifier2_=new Identifier((yyvsp[0].sval), id_column_name); free((yyvsp[-2].sval)); free((yyvsp[0].sval));}
#line 7482 "bison_parser.cpp"
    break;

  case 420: /* column_name: '*'  */
#line 2494 "bison_parser.y"
            { (yyval.column_name_t) = new ColumnName(); (yyval.column_name_t)->sub_type_=CASE2; }
#line 7488 "bison_parser.cpp"
    break;

  case 421: /* column_name: IDENTIFIER '.' '*'  */
#line 2495 "bison_parser.y"
                           { (yyval.column_name_t) = new ColumnName(); (yyval.column_name_t)->sub_type_=CASE3; (yyval.column_name_t)->identifier1_=new Identifier((yyvsp[-2].sval), id_table_name); free((yyvsp[-2].sval));}
#line 7494 "bison_parser.cpp"
    break;

  case 422: /* literal: string_literal  */
#line 2499 "bison_parser.y"
                        {(yyval.literal_t)=(yyvsp[0].string_literal_t);}
#line 7500 "bison_parser.cpp"
    break;

  case 423: /* literal: json_literal  */
#line 2500 "bison_parser.y"
                      {(yyval.literal_t)=(yyvsp[0].json_literal_t);}
#line 7506 "bison_parser.cpp"
    break;

  case 424: /* literal: json_pathliteral  */
#line 2501 "bison_parser.y"
                         {(yyval.literal_t)=(yyvsp[0].json_pathliteral_t);}
#line 7512 "bison_parser.cpp"
    break;

  case 425: /* literal: bool_literal  */
#line 2502 "bison_parser.y"
                      {(yyval.literal_t)=(yyvsp[0].bool_literal_t);}
#line 7518 "bison_parser.cpp"
    break;

  case 426: /* literal: num_literal  */
#line 2503 "bison_parser.y"
                     {(yyval.literal_t)=(yyvsp[0].num_literal_t);}
#line 7524 "bison_parser.cpp"
    break;

  case 427: /* literal: null_literal  */
#line 2504 "bison_parser.y"
                      {(yyval.literal_t)=(yyvsp[0].null_literal_t);}
#line 7530 "bison_parser.cpp"
    break;

  case 428: /* literal: param_expr  */
#line 2505 "bison_parser.y"
                    {(yyval.literal_t)=(yyvsp[0].param_expr_t);}
#line 7536 "bison_parser.cpp"
    break;

  case 429: /* string_literal: STRING  */
#line 2509 "bison_parser.y"
               { (yyval.string_literal_t) = new StringLiteral(); (yyval.string_literal_t)->str_val_ = (yyvsp[0].sval); free((yyvsp[0].sval));}
#line 7542 "bison_parser.cpp"
    break;

  case 430: /* json_literal: ESCAPED_CURLY_LITERAL  */
#line 2513 "bison_parser.y"
                              { (yyval.json_literal_t) = new json_literal(); (yyval.json_literal_t)->str_val_ = (yyvsp[0].sval); free((yyvsp[0].sval)); }
#line 7548 "bison_parser.cpp"
    break;

  case 431: /* json_literal: ESCAPED_BRACKET_LITERAL  */
#line 2514 "bison_parser.y"
                                { (yyval.json_literal_t) = new json_literal(); (yyval.json_literal_t)->str_val_ = (yyvsp[0].sval); free((yyvsp[0].sval)); }
#line 7554 "bison_parser.cpp"
    break;

  case 432: /* json_pathliteral: ARROW JSONPATH_STRING  */
#line 2518 "bison_parser.y"
                              {  (yyval.json_pathliteral_t) = new json_pathliteral(); (yyval.json_pathliteral_t)->str_val_ = (yyvsp[0].sval); free((yyvsp[0].sval));  }
#line 7560 "bison_parser.cpp"
    break;

  case 433: /* bool_literal: TRUE  */
#line 2522 "bison_parser.y"
             { (yyval.bool_literal_t) = new BoolLiteral(); (yyval.bool_literal_t)->b_val_=true; }
#line 7566 "bison_parser.cpp"
    break;

  case 434: /* bool_literal: FALSE  */
#line 2523 "bison_parser.y"
              { (yyval.bool_literal_t) = new BoolLiteral(); (yyval.bool_literal_t)->b_val_=false; }
#line 7572 "bison_parser.cpp"
    break;

  case 435: /* num_literal: FLOATVAL  */
#line 2527 "bison_parser.y"
                 { (yyval.num_literal_t) = new NumLiteral(); (yyval.num_literal_t)->sub_type_=CASE0; (yyval.num_literal_t)->f_val_ = (yyvsp[0].fval); }
#line 7578 "bison_parser.cpp"
    break;

  case 436: /* num_literal: int_literal  */
#line 2528 "bison_parser.y"
                    {(yyval.num_literal_t) = new NumLiteral(); (yyval.num_literal_t)->sub_type_=CASE1; (yyval.num_literal_t)->int_literal_ = (yyvsp[0].int_literal_t);}
#line 7584 "bison_parser.cpp"
    break;

  case 437: /* int_literal: INTVAL  */
#line 2532 "bison_parser.y"
               {(yyval.int_literal_t) = new IntLiteral(); (yyval.int_literal_t)->int_val_=(yyvsp[0].ival); }
#line 7590 "bison_parser.cpp"
    break;

  case 438: /* null_literal: NULL  */
#line 2536 "bison_parser.y"
             { (yyval.null_literal_t) = new NullLiteral(); }
#line 7596 "bison_parser.cpp"
    break;

  case 439: /* param_expr: '?'  */
#line 2540 "bison_parser.y"
            {
            (yyval.param_expr_t) = new ParamExpr();
        }
#line 7604 "bison_parser.cpp"
    break;

  case 440: /* table_ref: table_prefix table_name opt_alias opt_index opt_on opt_using  */
#line 2552 "bison_parser.y"
                                                                    {
            (yyval.table_ref_t) = new TableRef();
            (yyval.table_ref_t)->sub_type_ = CASE0;
            (yyval.table_ref_t)->table_prefix_ = (yyvsp[-5].table_prefix_t);
            (yyval.table_ref_t)->table_name_ = (yyvsp[-4].table_name_t);
            (yyval.table_ref_t)->opt_alias_ = (yyvsp[-3].opt_alias_t);
            (yyval.table_ref_t)->opt_index_ = (yyvsp[-2].opt_index_t);
            (yyval.table_ref_t)->opt_on_ = (yyvsp[-1].opt_on_t);
            (yyval.table_ref_t)->opt_using_ = (yyvsp[0].opt_using_t);
            (yyval.table_ref_t)->table_name_->table_name_->id_type_ = id_top_table_name;
        }
#line 7620 "bison_parser.cpp"
    break;

  case 441: /* table_ref: table_prefix table_name '(' expr_list ')' opt_alias opt_on opt_using  */
#line 2563 "bison_parser.y"
                                                                            {
            (yyval.table_ref_t) = new TableRef();
            (yyval.table_ref_t)->sub_type_ = CASE1;
            (yyval.table_ref_t)->table_prefix_ = (yyvsp[-7].table_prefix_t);
            (yyval.table_ref_t)->table_name_ = (yyvsp[-6].table_name_t);
            (yyval.table_ref_t)->expr_list_ = (yyvsp[-4].expr_list_t);
            (yyval.table_ref_t)->opt_alias_  = (yyvsp[-2].opt_alias_t);
            (yyval.table_ref_t)->opt_on_ = (yyvsp[-1].opt_on_t);
            (yyval.table_ref_t)->opt_using_ = (yyvsp[0].opt_using_t);
            (yyval.table_ref_t)->table_name_->table_name_->id_type_ = id_top_table_name;
    }
#line 7636 "bison_parser.cpp"
    break;

  case 442: /* table_ref: table_prefix '(' select_no_paren ')' opt_alias opt_on opt_using  */
#line 2574 "bison_parser.y"
                                                                        {
            (yyval.table_ref_t) = new TableRef();
            (yyval.table_ref_t)->sub_type_ = CASE2;
            (yyval.table_ref_t)->table_prefix_ = (yyvsp[-6].table_prefix_t);
            (yyval.table_ref_t)->select_no_paren_ = (yyvsp[-4].select_no_paren_t);
            (yyval.table_ref_t)->opt_alias_ = (yyvsp[-2].opt_alias_t);
            (yyval.table_ref_t)->opt_on_ = (yyvsp[-1].opt_on_t);
            (yyval.table_ref_t)->opt_using_ = (yyvsp[0].opt_using_t);
    }
#line 7650 "bison_parser.cpp"
    break;

  case 443: /* table_ref: table_prefix '(' table_ref ')' opt_alias opt_on opt_using  */
#line 2583 "bison_parser.y"
                                                                 {
            (yyval.table_ref_t) = new TableRef();
            (yyval.table_ref_t)->sub_type_ = CASE3;
            (yyval.table_ref_t)->table_prefix_ = (yyvsp[-6].table_prefix_t);
            (yyval.table_ref_t)->table_ref_ = (yyvsp[-4].table_ref_t);
            (yyval.table_ref_t)->opt_alias_ = (yyvsp[-2].opt_alias_t);
            (yyval.table_ref_t)->opt_on_ = (yyvsp[-1].opt_on_t);
            (yyval.table_ref_t)->opt_using_ = (yyvsp[0].opt_using_t);
    }
#line 7664 "bison_parser.cpp"
    break;

  case 444: /* table_prefix: table_ref join_op  */
#line 2595 "bison_parser.y"
                         {
            (yyval.table_prefix_t) = new TablePrefix();
            (yyval.table_prefix_t)->sub_type_ = CASE0;
            (yyval.table_prefix_t)->table_ref_ = (yyvsp[-1].table_ref_t);
            (yyval.table_prefix_t)->join_op_ = (yyvsp[0].join_op_t);
        }
#line 7675 "bison_parser.cpp"
    break;

  case 445: /* table_prefix: %empty  */
#line 2601 "bison_parser.y"
                  {
            (yyval.table_prefix_t) = new TablePrefix();
            (yyval.table_prefix_t)->sub_type_ = CASE1;
        }
#line 7684 "bison_parser.cpp"
    break;

  case 446: /* join_op: ','  */
#line 2607 "bison_parser.y"
            {(yyval.join_op_t) = new JoinOp(); (yyval.join_op_t)->sub_type_ = CASE0; }
#line 7690 "bison_parser.cpp"
    break;

  case 447: /* join_op: JOIN  */
#line 2608 "bison_parser.y"
             {(yyval.join_op_t) = new JoinOp(); (yyval.join_op_t)->sub_type_ = CASE1; }
#line 7696 "bison_parser.cpp"
    break;

  case 448: /* join_op: join_kw JOIN  */
#line 2609 "bison_parser.y"
                     {(yyval.join_op_t) = new JoinOp(); (yyval.join_op_t)->sub_type_ = CASE2; (yyval.join_op_t)->join_kw_ = (yyvsp[-1].join_kw_t);}
#line 7702 "bison_parser.cpp"
    break;

  case 449: /* join_op: join_kw IDENTIFIER JOIN  */
#line 2610 "bison_parser.y"
                                {
            (yyval.join_op_t) = new JoinOp(); 
            (yyval.join_op_t)->sub_type_ = CASE3; 
            (yyval.join_op_t)->id1_ = new Identifier((yyvsp[-1].sval), id_top_table_name); 
            (yyval.join_op_t)->join_kw_ = (yyvsp[-2].join_kw_t); 
            free((yyvsp[-1].sval));}
#line 7713 "bison_parser.cpp"
    break;

  case 450: /* join_op: join_kw IDENTIFIER IDENTIFIER JOIN  */
#line 2616 "bison_parser.y"
                                           {
            (yyval.join_op_t) = new JoinOp(); 
            (yyval.join_op_t)->sub_type_ = CASE4; 
            (yyval.join_op_t)->id1_ = new Identifier((yyvsp[-2].sval));
            (yyval.join_op_t)->id2_ = new Identifier((yyvsp[-1].sval));
            (yyval.join_op_t)->join_kw_ = (yyvsp[-3].join_kw_t);
            free((yyvsp[-2].sval));
            free((yyvsp[-1].sval));
        }
#line 7727 "bison_parser.cpp"
    break;

  case 451: /* opt_index: INDEXED BY column_name  */
#line 2628 "bison_parser.y"
                               {(yyval.opt_index_t) = new OptIndex(); (yyval.opt_index_t)->sub_type_ = CASE0; (yyval.opt_index_t)->column_name_ = (yyvsp[0].column_name_t); }
#line 7733 "bison_parser.cpp"
    break;

  case 452: /* opt_index: NOT INDEXED  */
#line 2629 "bison_parser.y"
                    {(yyval.opt_index_t) = new OptIndex(); (yyval.opt_index_t)->sub_type_ = CASE1; }
#line 7739 "bison_parser.cpp"
    break;

  case 453: /* opt_index: %empty  */
#line 2630 "bison_parser.y"
                  {(yyval.opt_index_t) = new OptIndex(); (yyval.opt_index_t)->sub_type_ = CASE2; }
#line 7745 "bison_parser.cpp"
    break;

  case 454: /* opt_on: ON expr  */
#line 2634 "bison_parser.y"
               {(yyval.opt_on_t) = new OptOn(); (yyval.opt_on_t)->sub_type_ = CASE0; (yyval.opt_on_t)->expr_ = (yyvsp[0].expr_t); }
#line 7751 "bison_parser.cpp"
    break;

  case 455: /* opt_on: %empty  */
#line 2635 "bison_parser.y"
                  {(yyval.opt_on_t) = new OptOn(); (yyval.opt_on_t)->sub_type_ = CASE1; }
#line 7757 "bison_parser.cpp"
    break;

  case 456: /* opt_using: USING '(' ident_commalist ')'  */
#line 2639 "bison_parser.y"
                                      {(yyval.opt_using_t) = new OptUsing(); (yyval.opt_using_t)->sub_type_ = CASE0; (yyval.opt_using_t)->ident_commalist_ = (yyvsp[-1].ident_commalist_t); }
#line 7763 "bison_parser.cpp"
    break;

  case 457: /* opt_using: %empty  */
#line 2640 "bison_parser.y"
                  {(yyval.opt_using_t) = new OptUsing(); (yyval.opt_using_t)->sub_type_ = CASE1; }
#line 7769 "bison_parser.cpp"
    break;

  case 458: /* table_ref_name_no_alias: table_name  */
#line 2645 "bison_parser.y"
                   {
            (yyval.table_ref_name_no_alias_t) = new TableRefNameNoAlias();
            (yyval.table_ref_name_no_alias_t)->table_name_ = (yyvsp[0].table_name_t);
            (yyval.table_ref_name_no_alias_t)->table_name_->table_name_->id_type_ = id_top_table_name;
        }
#line 7779 "bison_parser.cpp"
    break;

  case 459: /* table_name: IDENTIFIER  */
#line 2652 "bison_parser.y"
                                  { (yyval.table_name_t) = new TableName(); (yyval.table_name_t)->sub_type_ = CASE0; (yyval.table_name_t)->table_name_ = new Identifier((yyvsp[0].sval), id_table_name); (yyval.table_name_t)->database_name_ = NULL; free((yyvsp[0].sval));}
#line 7785 "bison_parser.cpp"
    break;

  case 460: /* table_name: IDENTIFIER '.' IDENTIFIER  */
#line 2653 "bison_parser.y"
                                  { 
			(yyval.table_name_t) = new TableName(); 
			(yyval.table_name_t)->sub_type_ = CASE1; 
			(yyval.table_name_t)->database_name_ = new Identifier((yyvsp[-2].sval),id_database_name); 
			(yyval.table_name_t)->table_name_ = new Identifier((yyvsp[0].sval), id_table_name);
            free((yyvsp[-2].sval));
            free((yyvsp[0].sval));
		}
#line 7798 "bison_parser.cpp"
    break;

  case 461: /* alias: AS IDENTIFIER  */
#line 2664 "bison_parser.y"
                      { (yyval.alias_t) = new Alias(); (yyval.alias_t)->sub_type_ = CASE0; (yyval.alias_t)->id_ = new Identifier((yyvsp[0].sval)); free((yyvsp[0].sval)); }
#line 7804 "bison_parser.cpp"
    break;

  case 462: /* opt_alias: alias  */
#line 2669 "bison_parser.y"
              { (yyval.opt_alias_t) = new OptAlias(); (yyval.opt_alias_t)->sub_type_ = CASE0; (yyval.opt_alias_t)->alias_=(yyvsp[0].alias_t);}
#line 7810 "bison_parser.cpp"
    break;

  case 463: /* opt_alias: %empty  */
#line 2670 "bison_parser.y"
                    { (yyval.opt_alias_t) = new OptAlias(); (yyval.opt_alias_t)->sub_type_ = CASE1; }
#line 7816 "bison_parser.cpp"
    break;

  case 464: /* opt_with_clause: with_clause  */
#line 2678 "bison_parser.y"
                    { (yyval.opt_with_clause_t) = new OptWithClause(); (yyval.opt_with_clause_t)->sub_type_ = CASE0; (yyval.opt_with_clause_t)->with_clause_=(yyvsp[0].with_clause_t);}
#line 7822 "bison_parser.cpp"
    break;

  case 465: /* opt_with_clause: WithRecursiveClause  */
#line 2679 "bison_parser.y"
                            { (yyval.opt_with_clause_t) = new OptWithClause(); (yyval.opt_with_clause_t)->sub_type_ = CASE1; (yyval.opt_with_clause_t)->WithRecursiveClause_ =(yyvsp[0].WithRecursiveClause_t); }
#line 7828 "bison_parser.cpp"
    break;

  case 466: /* opt_with_clause: %empty  */
#line 2680 "bison_parser.y"
                    { (yyval.opt_with_clause_t) = new OptWithClause(); (yyval.opt_with_clause_t)->sub_type_ = CASE2; }
#line 7834 "bison_parser.cpp"
    break;

  case 467: /* with_clause: WITH with_description_list  */
#line 2684 "bison_parser.y"
                                   { (yyval.with_clause_t) = new WithClause(); (yyval.with_clause_t)->with_description_list_ = (yyvsp[0].with_description_list_t); }
#line 7840 "bison_parser.cpp"
    break;

  case 468: /* WithRecursiveClause: WITH RECURSIVE with_recursive_description_list  */
#line 2688 "bison_parser.y"
                                                       { (yyval.WithRecursiveClause_t) = new WithRecursiveClause(); (yyval.WithRecursiveClause_t)->with_rec_desc_list = (yyvsp[0].with_rec_desc_list_t); }
#line 7846 "bison_parser.cpp"
    break;

  case 469: /* with_recursive_description_list: with_recursive_description  */
#line 2692 "bison_parser.y"
                                   {
            (yyval.with_rec_desc_list_t) = new WithRecDescList();
            (yyval.with_rec_desc_list_t)->v_with_rec_desc_list.push_back((yyvsp[0].with_recursive_description_t));
        }
#line 7855 "bison_parser.cpp"
    break;

  case 470: /* with_recursive_description_list: with_recursive_description_list ',' with_recursive_description  */
#line 2697 "bison_parser.y"
     {
            (yyvsp[-2].with_rec_desc_list_t)->v_with_rec_desc_list.push_back((yyvsp[0].with_recursive_description_t));
            (yyval.with_rec_desc_list_t) = (yyvsp[-2].with_rec_desc_list_t);
    }
#line 7864 "bison_parser.cpp"
    break;

  case 471: /* with_recursive_description: IDENTIFIER AS with_recursive_select  */
#line 2704 "bison_parser.y"
                                            {
            (yyval.with_recursive_description_t) = new WithRecDesc();
            (yyval.with_recursive_description_t)->id_ = new Identifier((yyvsp[-2].sval));
            (yyval.with_recursive_description_t)->with_recursive_select_ = (yyvsp[0].with_recursive_select_t);
            free((yyvsp[-2].sval));
        }
#line 7875 "bison_parser.cpp"
    break;

  case 472: /* with_recursive_select: '(' init_select opt_recursive_select ')'  */
#line 2713 "bison_parser.y"
                                                 {
            (yyval.with_recursive_select_t) = new WithRecursiveSelect();
            (yyval.with_recursive_select_t)->init_select_ = (yyvsp[-2].init_select_t);
            (yyval.with_recursive_select_t)->opt_recursive_select_ = (yyvsp[-1].opt_recursive_select_t);
        }
#line 7885 "bison_parser.cpp"
    break;

  case 473: /* opt_recursive_select: UNION ALL SELECT opt_distinct select_list opt_from_clause opt_where opt_group opt_order LIMIT INTVAL  */
#line 2721 "bison_parser.y"
                                                                                                             {
            (yyval.opt_recursive_select_t) = new OptRecursiveSelect();
            (yyval.opt_recursive_select_t)->sub_type_ = CASE0;
            (yyval.opt_recursive_select_t)->opt_distinct_ = (yyvsp[-7].opt_distinct_t);
            (yyval.opt_recursive_select_t)->select_list_ = (yyvsp[-6].select_list_t);
            (yyval.opt_recursive_select_t)->opt_from_clause_ = (yyvsp[-5].opt_from_clause_t);
            (yyval.opt_recursive_select_t)->opt_where_ = (yyvsp[-4].opt_where_t);
            (yyval.opt_recursive_select_t)->opt_group_ = (yyvsp[-3].opt_group_t);
            (yyval.opt_recursive_select_t)->opt_order_ = (yyvsp[-2].opt_order_t);
            (void)(yyvsp[0].ival);
            // free($11);
        }
#line 7902 "bison_parser.cpp"
    break;

  case 474: /* opt_recursive_select: %empty  */
#line 2733 "bison_parser.y"
                     {(yyval.opt_recursive_select_t) = new OptRecursiveSelect(); (yyval.opt_recursive_select_t)->sub_type_ = CASE1;}
#line 7908 "bison_parser.cpp"
    break;

  case 475: /* init_select: SELECT opt_distinct select_list_essential_alias opt_from_clause opt_where opt_group  */
#line 2737 "bison_parser.y"
                                                                                            {
            (yyval.init_select_t) = new InitSelect();
            (yyval.init_select_t)->opt_distinct_ = (yyvsp[-4].opt_distinct_t);
            (yyval.init_select_t)->select_list_essential_alias_ = (yyvsp[-3].select_list_essential_alias_t);
            (yyval.init_select_t)->opt_from_clause_ = (yyvsp[-2].opt_from_clause_t);
            (yyval.init_select_t)->opt_where_ = (yyvsp[-1].opt_where_t);
            (yyval.init_select_t)->opt_group_ = (yyvsp[0].opt_group_t);
        }
#line 7921 "bison_parser.cpp"
    break;

  case 476: /* select_list_essential_alias: expr_list_essential_alias  */
#line 2748 "bison_parser.y"
                                  {
            (yyval.select_list_essential_alias_t) = new SelListAlias();
            (yyval.select_list_essential_alias_t)->expr_list_essential_alias_ = (yyvsp[0].expr_list_essential_alias_t);
        }
#line 7930 "bison_parser.cpp"
    break;

  case 477: /* expr_list_essential_alias: expr_essential_alias  */
#line 2755 "bison_parser.y"
                             { 
            (yyval.expr_list_essential_alias_t) = new ExprListAlias(); 
            (yyval.expr_list_essential_alias_t)->v_expr_list_essential_alias_.push_back((yyvsp[0].expr_essential_alias_t)); 
            }
#line 7939 "bison_parser.cpp"
    break;

  case 478: /* expr_list_essential_alias: expr_list_essential_alias ',' expr_essential_alias  */
#line 2759 "bison_parser.y"
                                                           { 
        (yyvsp[-2].expr_list_essential_alias_t)->v_expr_list_essential_alias_.push_back((yyvsp[0].expr_essential_alias_t)); 
        (yyval.expr_list_essential_alias_t) = (yyvsp[-2].expr_list_essential_alias_t); }
#line 7947 "bison_parser.cpp"
    break;

  case 479: /* expr_essential_alias: expr alias  */
#line 2765 "bison_parser.y"
                   {
            (yyval.expr_essential_alias_t) = new ExprEssentialAlias();
            (yyval.expr_essential_alias_t)->expr_ = (yyvsp[-1].expr_t);
            (yyval.expr_essential_alias_t)->alias_ = (yyvsp[0].alias_t);
        }
#line 7957 "bison_parser.cpp"
    break;

  case 480: /* with_description_list: with_description  */
#line 2775 "bison_parser.y"
                         {
            (yyval.with_description_list_t) = new WithDescriptionList();
            (yyval.with_description_list_t)->v_with_description_list_.push_back((yyvsp[0].with_description_t));
        }
#line 7966 "bison_parser.cpp"
    break;

  case 481: /* with_description_list: with_description_list ',' with_description  */
#line 2779 "bison_parser.y"
                                                   {
            (yyvsp[-2].with_description_list_t)->v_with_description_list_.push_back((yyvsp[0].with_description_t));
            (yyval.with_description_list_t) = (yyvsp[-2].with_description_list_t);
        }
#line 7975 "bison_parser.cpp"
    break;

  case 482: /* with_description: IDENTIFIER AS select_with_paren  */
#line 2786 "bison_parser.y"
                                        {
            (yyval.with_description_t) = new WithDescription();
            (yyval.with_description_t)->id_ = new Identifier((yyvsp[-2].sval));
            (yyval.with_description_t)->select_with_paren_ = (yyvsp[0].select_with_paren_t);
            free((yyvsp[-2].sval));
        }
#line 7986 "bison_parser.cpp"
    break;

  case 483: /* join_kw: INNER  */
#line 2800 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("INNER"); }
#line 7992 "bison_parser.cpp"
    break;

  case 484: /* join_kw: LEFT OUTER  */
#line 2801 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("LEFT OUTER"); }
#line 7998 "bison_parser.cpp"
    break;

  case 485: /* join_kw: LEFT  */
#line 2802 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("LEFT"); }
#line 8004 "bison_parser.cpp"
    break;

  case 486: /* join_kw: RIGHT OUTER  */
#line 2803 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("RIGHT OUTER"); }
#line 8010 "bison_parser.cpp"
    break;

  case 487: /* join_kw: RIGHT  */
#line 2804 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("RIGHT"); }
#line 8016 "bison_parser.cpp"
    break;

  case 488: /* join_kw: CROSS  */
#line 2808 "bison_parser.y"
                    { (yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("CROSS"); }
#line 8022 "bison_parser.cpp"
    break;

  case 489: /* join_kw: NATURAL  */
#line 2809 "bison_parser.y"
                    {(yyval.join_kw_t) = new JoinKw(); (yyval.join_kw_t)->str_val_ = string("NATURAL");}
#line 8028 "bison_parser.cpp"
    break;

  case 490: /* opt_semicolon: ';'  */
#line 2824 "bison_parser.y"
            {(yyval.opt_semicolon_t) = new OptSemicolon(); (yyval.opt_semicolon_t)->str_val_ = string(";");}
#line 8034 "bison_parser.cpp"
    break;

  case 491: /* opt_semicolon: %empty  */
#line 2825 "bison_parser.y"
                   {(yyval.opt_semicolon_t) = new OptSemicolon(); (yyval.opt_semicolon_t)->str_val_ = string("");}
#line 8040 "bison_parser.cpp"
    break;

  case 492: /* ident_commalist: IDENTIFIER  */
#line 2830 "bison_parser.y"
                   { (yyval.ident_commalist_t) = new IdentCommaList(); (yyval.ident_commalist_t)->v_iden_comma_list_.push_back(new Identifier((yyvsp[0].sval))); free((yyvsp[0].sval));}
#line 8046 "bison_parser.cpp"
    break;

  case 493: /* ident_commalist: ident_commalist ',' IDENTIFIER  */
#line 2831 "bison_parser.y"
                                       { (yyvsp[-2].ident_commalist_t)->v_iden_comma_list_.push_back(new Identifier((yyvsp[0].sval))); (yyval.ident_commalist_t) = (yyvsp[-2].ident_commalist_t); free((yyvsp[0].sval));}
#line 8052 "bison_parser.cpp"
    break;


#line 8056 "bison_parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == SQL_HSQL_EMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= SQL_YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == SQL_YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, result, scanner);
          yychar = SQL_HSQL_EMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != SQL_HSQL_EMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 2834 "bison_parser.y"

/*********************************
 ** Section 4: Additional C code
 *********************************/

 /* empty */
 int yyerror(YYLTYPE* llocp, Program* result, yyscan_t scanner, const char* msg) {
    // std::cerr << "[Bison Error] " << msg << std::endl;
    // if (llocp) {
    //     std::cerr << "At line " << llocp->first_line << ", column " << llocp->first_column << std::endl;
    // }
    return 1;
}
