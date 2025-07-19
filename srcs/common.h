#ifndef __COMMON_H__
#define __COMMON_H__

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <chrono>

#include "internal/client/client.h"

using std::uint32_t;
using std::uint8_t;

/***************************************
 * Target DBMS
 ***************************************/

/*
 *  Target DBMS
 */
#define MAX_TARGET 8

enum class Target : uint8_t {
  SQLite = 0,
  MySQL = 1,
  PostgreSQL = 2,
  Oracle = 3,
  MariaDB = 4,
};

constexpr uint8_t TargetStart = static_cast<uint8_t>(Target::SQLite);
constexpr uint8_t TargetEnd = static_cast<uint8_t>(Target::MariaDB);  // 4

std::string target_to_string(Target target);

// TargetsMask: Bitmask for Targets
using TargetsMask = uint8_t;

// Bitmask for each target
#define TARGET(db) (1 << static_cast<uint8_t>(db))
#define TARGET_NONE 0
#define TARGET_ALL                                  \
  (TARGET(Target::SQLite) | TARGET(Target::MySQL) | \
   TARGET(Target::PostgreSQL) | TARGET(Target::Oracle) | \
   TARGET(Target::MariaDB))

// Conversion between a vector of targets and bitmask for it
TargetsMask to_flag(std::vector<Target> targets);
std::vector<Target> to_targets(TargetsMask targets);

/***************************************
 * TestGroup
 ***************************************/

/*
 * TestGroup:
 *
 * A group of test cases for a single base query
 *
 *  base_query: The base query in SQLite syntax
 *  adapted_queries: A map from Target to its adapted query in the target DBMS syntax
 *
 *  to_string(): Returns a string for printing all contents of TestGroup
 *  is_valid(): Validate if TestGroup has everything ready to be encoded into Round
 *  encode(): Encode TestGroup into Round
 */
class TestGroup {
 public:
   struct Raw {
    // Targets bitmask
    TargetsMask targets;

    // Offsets: per-DBMS query offset from buf_queries, 0 for empty
    int query_offset[MAX_TARGET];

    // Deliminated by NULL (\0) (base_query, adapted_queries)
    char buf_queries[];
  };

  // Constructor
  TestGroup(std::string _base_query) : base_query(_base_query) {}
  // Constructor (decoder)
  TestGroup(Raw *r);

  // Members
  std::string base_query;
  TargetsMask targets;
  std::map<Target, std::string> adapted_queries;

  // Methods
  Raw *encode();
  bool is_valid();
  std::string to_string();
};

#define MAX_TESTGROUP_RAW_SIZE 0x10000

/***************************************
 * Oracle Executor (Result Analyzer)
 ***************************************/

// Result
typedef struct Result {
  Target target;
  std::vector<std::vector<std::string>> result;
  client::ExecutionStatus status;
  std::string executed_query;
} Result;

#endif  // __COMMON_H__
