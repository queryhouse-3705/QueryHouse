#ifndef __TRANSPILE_H__
#define __TRANSPILE_H__

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "common.h"

/***************************************
 * Transpiler
 ***************************************/

/*
 * transpile()
 *
 * Transpiles a given `query` for DBMSs specified by the bitmask `targets`
 *
 * Returns the QueryQueue containing the transpilation result
 *
 * This is a wrapper for transpile_for()
 */
TestGroup transpile(const std::string &query, TargetsMask targets);

/*
 * transpile_for()
 *
 * Transpiles a given `query` for the specified DBMS `target`
 *
 * This is a actual worker of transpiler.
 */
std::string transpile_for(const std::string &query, Target target);
std::vector<std::string> split_query(const char *buf, size_t len);
#endif  // __TRANSPILE_H__
