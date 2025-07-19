#ifndef __POSTPROCESS_H__
#define __POSTPROCESS_H__
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>  // for smart pointers
#include <string>
#include <vector>
#include <iomanip>

#include "common.h"

// extern std::ofstream outfile;
// extern std::ofstream errfile;

// #define DIFF2_NONE 0

// #define DIFF2_SQLITE_PRAGMA 1
// #define DIFF2_SQLite_WITHOUT_ROWID 2
// #define DIFF2_SQLITE_INDEX_ASC 4
// #define DIFF2_SQLITE_INDEX_DESC 8
// #define DIFF2_SQLITE_PARTIAL_INDEX 16
// #define DIFF2_SQLITE_VACUUM 32
// #define DIFF2_SQLITE_MATERIALIZED_CTE 64

// #define DIFF2_MYSQL_CREATE_INVISIBLE_INDEX 1
// #define DIFF2_MYSQL_ALTER_INVISIBLE_INDEX 2
// #define DIFF2_MYSQL_TYPE_BTREE 4
// #define DIFF2_MYSQL_TYPE_HASH 8
// #define DIFF2_MYSQL_INDEX_PREFIX 16
// #define DIFF2_MYSQL_INDEX_ASC 32
// #define DIFF2_MYSQL_INDEX_DESC 64
// #define DIFF2_MYSQL_STORAGE_ENGINE 128
// #define DIFF2_MYSQL_OPTIMIZE_TABLE 256
// #define DIFF2_MYSQL_INDEX_ALGORITHM_LOCK 512
// #define DIFF2_MYSQL_TABLE_ALGORITHM_LOCK 1024
// #define DIFF2_MYSQL_PAGE_COMPRESSION 2048
// #define DIFF2_MYSQL_TABLE_COMPRESSION 4096
// #define DIFF2_MYSQL_OPTIMIZER_HINTS 8192
// #define DIFF2_MYSQL_TABLE_OPTIONS 16384

// #define DIFF2_PSQL_TYPE_BTREE 1
// #define DIFF2_PSQL_TYPE_HASH 2
// #define DIFF2_PSQL_JIT 4
// #define DIFF2_PSQL_INDEX_ASC 8
// #define DIFF2_PSQL_INDEX_DESC 16
// #define DIFF2_PSQL_PARTIAL_INDEX 32
// #define DIFF2_PSQL_VACUUM 64
// #define DIFF2_PSQL_STORAGE_OPTION 128
// #define DIFF2_PSQL_MATERIALIZED_CTE 256

// #define DIFF2_ORACLE_CREATE_INVISIBLE_INDEX 1
// #define DIFF2_ORACLE_ALTER_INVISIBLE_INDEX 2
// #define DIFF2_ORACLE_BITMAP_INDEX 4
// #define DIFF2_ORACLE_CREATE_UNUSABLE_INDEX 8
// #define DIFF2_ORACLE_INDEX_ASC 16
// #define DIFF2_ORACLE_INDEX_DESC 32
// #define DIFF2_ORACLE_ADVANCED_COMPRESSION 64

// Probability
#define PROB(p) ((rand() % 100) < p)
#define PROB_VERY_LOW()     PROB(1)
#define PROB_LOW()          PROB(5)
#define PROB_MEDIUM()       PROB(10)
#define PROB_HIGH()         PROB(25)
#define PROB_VERY_HIGH()    PROB(50)

// helpers
std::vector<std::string> splitQuery(const std::string& query);
size_t findOppositeParentheses(const std::string& query, int start);
std::string strip(const std::string& str);
std::vector<std::string> strip_vector(const std::vector<std::string>& vec);
bool isInt(const std::string& str);
bool isFloat(const std::string& str);
std::string roundFromFloat(const std::string& str);
bool createInfo(const std::string& query, std::string& tablename, std::vector<std::pair<std::string, std::string>>& columnnames);
bool indexInfo(const std::string& query, std::string& tablename, std::vector<std::string>& columnnames);
bool insertInfo(const std::string& query, std::string& tablename, std::vector<std::string>& columnnames, std::vector<std::vector<std::string>>& columnvalues);
bool whereInfo(const std::string& query, std::string& where);

void extractTableNameAndColumns(const std::string& statement, std::string& current_table_name, std::vector<std::string>& table_columns);

/*
 * postprocess()
 *
 * Post-processing on each adapted query, including:
 *   - Add type-2 diff test scneario
 */
// core postprocess
void sqliteEnableForeignKey_Postprocess(TestGroup& tg);
void mysqlIndexSize_Postprocess(TestGroup& tg);
void checkTypeViolation_Postprocess(TestGroup& tg);

// SQLite
void sqliteAddPragmaCommands(std::string& query);
void sqliteProcessWithoutRowId(std::string& statement);
void sqliteProcessAscDescColumns(std::string& statement, std::string& first_column_name);
void sqliteProcessPartialIndex(std::string& statement, const std::string& first_column_name);
// void sqliteAddVacuumCommand(std::string& statement);
// void sqliteCleanUpVacuumFile();
void sqliteAddMaterializedToCTE(std::string& statement);
void ProcessSQLite(std::string& query);

// MySQL
void mysqlIdentifyCharTypeColumns(
    const std::string& query,
    std::vector<std::pair<std::string, int>>& char_type_columns);
void mysqlAddSizeToIndexColumns(
    std::string& statement,
    const std::vector<std::pair<std::string, int>>& char_type_columns);
void mysqlAddOrderToIndexColumns(std::string& statement, bool& add_order);
void mysqlAddUsingClauseToIndex(std::string& statement, const bool& add_order);
void mysqlAddInvisibleToIndex(std::string& statement);
void mysqlAddInvisibleToAlterIndex(std::string& statement);
void mysqlIdentifyForeignKeyAndTextBlob(const std::string& query,
                                        bool& has_foreign_key,
                                        bool& has_text_or_blob);
void mysqlAddEngineAndRowFormat(std::string& statement, bool has_foreign_key,
                                bool has_text_or_blob);
void mysqlExtractTableName(const std::string& statement, std::string& table_name);
void mysqlAddOptimizeTableIfOracleSkip(std::string& query,
                                       const std::string& table_name);
void mysqlAddAlgorithmAndLockToIndex(std::string& statement);
void mysqlAddRandomAlterTableStatements(std::string& new_query,
                                        const std::string& table_name);
void mysqlAddCompressionToCreateTable(std::string& statement);
void mysqlAddCompressionAndOptimizeAlterTable(std::string& new_query,
                                              const std::string& table_name);
std::string mysqlExtractIndexName(const std::string& statement,
                                  size_t create_index_pos);
std::string generateRandomHint(
    const std::vector<std::string>& table_names,
    const std::map<std::string, std::vector<std::string>>& index_names);
void mysqlExtractIndexAndTableNames(
    const std::string& statement,
    std::map<std::string, std::vector<std::string>>& index_names,
    std::vector<std::string>& table_names);
void mysqlAddHintsToSQLStatement(
    std::string& statement, const std::vector<std::string>& table_names,
    const std::map<std::string, std::vector<std::string>>& index_names);
void mysqlIdentifyJSONColumns(const std::string& query,
                              std::vector<std::string>& json_columns);
std::string mysqlGenerateRandomString(size_t length);
void mysqlAddTableOptions(std::string& statement);
void processMySQL(std::string& query);

// PostgreSQL
std::string psqlAddJitSettings(const std::string& query);
void psqlModifyCreateIndexStatement(std::string& statement);
void psqlAddIndexOrdering(std::string& statement);
void psqlAddPartialIndexCondition(std::string& statement);
void psqlAddNewIndexIfMissing(std::string& statement,
                              const std::string& current_table_name,
                              const std::vector<std::string>& table_columns,
                              int& index_counter);
void psqlAddVacuumDatabaseStats(std::string& statement);
void psqlAddVacuumWithOptions(std::string& statement);
void psqlAddVacuumAnalyzeTable(std::string& statement,
                               const std::string& table_name,
                               const std::vector<std::string>& columns);
int getRandomInt(int min, int max);
double getRandomDouble(double min, double max);
void psqlAddWithClauseStorageOption(std::string& statement);

void psqlAddMaterializedToCTE(std::string& statement);
void processPostgreSQL(std::string& query);

// Oracle
std::string extractIndexName(const std::string& statement);
void oracleConvertToBitmapIndex(std::string& statement);
void oracleAddInvisibleOrUnusable(std::string& statement);
void oracleAddColumnOrdering(std::string& statement);
void oracleAddAlterIndexStatements(std::string& statement,
                                   const std::vector<std::string>& index_names);
void oracleProcessCreateIndexStatement(std::string& statement);
void oracleProcessAlterIndexStatement(std::string& statement);
std::string oracleGetRandomCompressionOption();
void oracleAddCompressionOption(std::string& statement);
void oracleAddAlterTableCompressionOption(std::string& statement, const std::vector<std::string>& table_names);
void oracleAddCreateBitmapIndex(std::string& statement,
                                const std::map<std::string, std::vector<std::string>>& table_columns,
                                int& index_counter);
void processOracle(std::string& query);

void postprocess_core(TestGroup& tg);
void postprocess(TestGroup& tg);

#endif  // __POSTPROCESS_H__