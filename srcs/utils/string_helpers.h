#ifndef __UTILS_STRING_HELPERS_H__
#define __UTILS_STRING_HELPERS_H__
#include <string>

#include "yaml-cpp/yaml.h"
namespace utils {
    std::string strip(const std::string& str);
    std::string str_tolower(const std::string &str);
    std::string str_toupper(const std::string &str);
};  // namespace utils

#endif  // __UTILS_STRING_HELPERS_H__
