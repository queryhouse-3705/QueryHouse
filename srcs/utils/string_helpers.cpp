#include "string_helpers.h"

#include <string>
#include <cctype>

namespace utils {
    std::string strip(const std::string& str) {
        auto start = std::find_if_not(str.begin(), str.end(), ::isspace);
        auto end = std::find_if_not(str.rbegin(), str.rend(), ::isspace).base();
        return std::string(start, end);
    }

    std::string str_tolower(const std::string& str) {
        std::string res = str;
        for (char& c : res) {
            c = std::tolower(c);
        }
        return res;
    }

    std::string str_toupper(const std::string& str) {
        std::string res = str;
        for (char& c : res) {
            c = std::toupper(c);
        }
        return res;
    }
};  // namespace utils

