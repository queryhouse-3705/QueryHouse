#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <chrono>

#include "common.h"
#include "internal/client/client.h"


/***************************************
 * Result Analyzer (Normalizer)
 ***************************************/

// Determining if it's json or not
bool isJSON(const std::string &data);

// Converting a semantically equivalent json to a common string for alignment
std::string formatJSON(std::string &data);

// Helper function to trim quotation marks from strings
std::string trimQuotes(const std::string &str);

std::string normalizeScientificNotation(const std::string &num);

// Function to format a float string into a fixed-length string with leading
// zeros
std::string formatFloat(const std::string &floatStr);

// Function to normalize values before sorting by trimming quotes and formatting
// floats
std::vector<std::vector<std::string>> normalizeValues(
    const std::vector<std::vector<std::string>> &result);

/***************************************
 * Result Analyzer (Comparator)
 ***************************************/

bool checkFloatEqual(const std::string &, const std::string &);
/*
 * compare_row_num()
 *
 * Compares the number of rows between two query results and prints an
 * explanation if they differ.
 */
bool compare_row_num(const std::vector<Result> &results);

/*
 * compare_row()
 *
 * Compares the content of each row between two query results and prints an
 * explanation if they differ.
 */
bool compare_row(const std::vector<Result> &results);

/***************************************
 * Executor
 ***************************************/

bool execute_testgroup(
    TestGroup &testgroup,
    const std::map<Target, std::unique_ptr<client::DBClient>> &db_clients,
    std::vector<Result> &results,
    unsigned long batch_number,
    int index_in_batch);

    
/***************************************
 * Reporter
 ***************************************/

/*
 * report()
 *
 * Reports a bug on wrong results.
 *  - Log on file
 *  - Prints OraclePlan, which DBMS is buggy on which piece of queries
 */
void report(TestGroup &testgroup, std::vector<Result> &results,
            unsigned long batch_number, int index_in_batch);
void log_result_one(const Result &result);

void log_stats(
    size_t base_query_count, size_t base_statement_count, size_t dbms_statement_count,
    std::map<Target, size_t> &dbms_valid_query_count,
    std::map<int, size_t> &validity_score_distribution);
#ifdef LOG_INPUT
void log_input(TestGroup *tg);
#endif  // LOG_INPUT
#ifdef LOG_TRANSPILE_FAIL
void log_transpile_fail(std::vector<Result> &results);
#endif  // LOG_TRANSPILE_FAIL
#endif  // __EXECUTOR_H__
