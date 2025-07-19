#include "kwcov.h"
#include "../utils/string_helpers.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>           // C++17 or above required
// #include <algorithm>
#include "yaml-cpp/yaml.h"

namespace fs = std::filesystem;

// Constructor
KeywordCoverage::KeywordCoverage() { } 

// Initialize
void KeywordCoverage::init(YAML::Node config) {
    // Keywords, Frequency
    const std::string kw_path = config["keyword_path"].as<std::string>();
    
    if (fs::exists(kw_path) && fs::is_directory(kw_path)) {
        for (const auto& entry : fs::directory_iterator(kw_path)) {
            if (!fs::is_regular_file(entry.status())) continue;

            std::ifstream f(entry.path());
            if (!f) {
                continue;
            }

            std::string l;
            while (std::getline(f, l)) {
                std::string kw = utils::str_tolower(utils::strip(l));
                kw = kw.substr(0, kw.find_first_of("//"));

                if (!kw.empty() &&
                    std::find(keywords.begin(), keywords.end(), kw) == keywords.end()
                ) {
                    keywords.push_back(kw);
                    frequency[kw] = 0;
#ifdef LOG_KWCOV
                    cummulated_frequency[kw] = 0;
#endif
                }
            }
        }
    }

#ifdef LOG_KWCOV
    // Coverage log
    std::string path = config["log_path"].as<std::string>("/tmp/kwcov.log");
    covlog.open(path, std::ios::out);
#endif
#ifdef LOG_INSTANT_KWCOV
    // Instant coverage log
    instant_covlog.open("/tmp/instant_kwcov.log", std::ios::out);
#endif
}

KeywordCoverage::~KeywordCoverage() {
#ifdef LOG_KWCOV
    if (covlog.is_open()) {
        covlog.close();
    }
#endif
#ifdef LOG_INSTANT_KWCOV
    if (instant_covlog.is_open()) {
        instant_covlog.close();
    }
#endif
}

// Keyword Coverage
double KeywordCoverage::update_kwcov(const std::string& query) {
    std::string lowered_query = utils::str_tolower(query);
    int all = keywords.size();
    int cnt = 0;
    for (const auto& kw : keywords) {
        if (lowered_query.find(kw) != std::string::npos) {
            cnt++;
            frequency[kw]++;
#ifdef LOG_KWCOV
            cummulated_frequency[kw]++;
#endif
        }
    }
    
    double cov = static_cast<double>(cnt) / all * 100;

#ifdef LOG_KWCOV
    fLOGF(covlog, get_cummulated_kwcov());
#endif
#ifdef LOG_INSTANT_KWCOV
    fLOGF(instant_covlog, get_global_kwcov());
#endif
    return cov;
}

// used in custom_mutator.cc for LLM invocation
double KeywordCoverage::get_global_kwcov() {
    double cnt = 0;
    for (const auto& entry : frequency) {
        if (entry.second) cnt += 1;
    }
    return ( cnt / keywords.size()) * 100 ;
}

#ifdef LOG_KWCOV
// used in internal/sqlite/sqlite.cc > get_keyword_coverage() for logging
double KeywordCoverage::get_cummulated_kwcov() {
    double cnt = 0;
    for (const auto& entry : cummulated_frequency) {
        if (entry.second) cnt += 1;
    }
    return (cnt / keywords.size()) * 100;
}
#endif

// Frequency
void KeywordCoverage::reset_frequency() {
    for (auto& entry : frequency) {
        entry.second = 0;
    }
}

