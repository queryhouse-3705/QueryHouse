#include "common.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>


/***************************************
 * Target
 ***************************************/

TargetsMask to_flag(std::vector<Target> targets) {
  TargetsMask mask = 0;
  for (const auto &target : targets) {
    mask |= TARGET(static_cast<uint8_t>(target));
  }
  return mask;
}

std::vector<Target> to_targets(TargetsMask targets) {
  std::vector<Target> res;
  for (uint8_t i = TargetStart; i <= TargetEnd; i++)
    if (targets & TARGET(i)) res.push_back(static_cast<Target>(i));
  return res;
}

/***************************************
 * TestGroup
 ***************************************/

// TestGroup::TestGroup(Raw *r)
//      Decode Raw into TestGroup
TestGroup::TestGroup(TestGroup::Raw *r) {
  if (r == NULL) {
    return;
  }
  base_query = std::string(r->buf_queries);
  targets = r->targets;
  for (auto &t : to_targets(targets)) {
    adapted_queries[t] = std::string(r->buf_queries + r->query_offset[static_cast<uint8_t>(t)]);
  }
}

// TestGroup::encode()
//      Encode TestGroup into Raw
TestGroup::Raw *TestGroup::encode() {
  if (!is_valid()) return nullptr;

  TestGroup::Raw *r = (TestGroup::Raw *)malloc(MAX_TESTGROUP_RAW_SIZE);
  if (!r) return nullptr;
  memset(r, 0, MAX_TESTGROUP_RAW_SIZE);

  // Copy targets
  r->targets = targets;

  // Copy base query
  char *cur = r->buf_queries;
  strcpy(cur, base_query.c_str());
  cur += base_query.length() + 1;

  // Copy adapted queries, deliminated by NULL
  for (auto &t : to_targets(targets)) {
    r->query_offset[static_cast<uint8_t>(t)] = cur - r->buf_queries;
    strcpy(cur, adapted_queries[t].c_str());
    cur += adapted_queries[t].length() + 1;
  }

  return r;
}

// TestGroup::is_valid()
//      Validate if TestGroup has everything ready to be encoded into Raw
bool TestGroup::is_valid() {
  if (base_query.empty()) return false;
  for (auto &t : to_targets(targets)) {
    if (adapted_queries.find(t) == adapted_queries.end()) return false;
  }
  for (auto &q : adapted_queries) {
    if (q.second.empty()) return false;
  }
  return true;
}


// TestGroup::to_string()
//      Returns a string for printing all contents of TestGroup
std::string TestGroup::to_string() {
  std::stringstream ss;
  ss << "------------------------------------------------------------\n";
  ss << "Base Query: " << base_query << "\n";

  ss << "Adapted Queries:\n";
  for (auto &t : to_targets(targets)) {
    ss << "\tTarget: " << target_to_string(t) << "\n"
       << "\tQuery:\n" << adapted_queries[t] << "\n";
  }

  return ss.str();
}

std::string target_to_string(Target target) {
  switch (target) {
    case Target::SQLite:
      return "SQLite";
    case Target::MySQL:
      return "MySQL";
    case Target::PostgreSQL:
      return "PostgreSQL";
    case Target::Oracle:
      return "Oracle";
    case Target::MariaDB:
      return "MariaDB";
    default:
      return "Unknown Target";
  }
}
