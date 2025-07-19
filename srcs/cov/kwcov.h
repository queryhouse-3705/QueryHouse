#ifndef __KWCOV_H__
#define __KWCOV_H__

#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "yaml-cpp/yaml.h"
#include "utils/logging.h"

class KeywordCoverage {
public:
    KeywordCoverage();
    ~KeywordCoverage();
    void init(YAML::Node config);

    // Keyword Coverage
    double update_kwcov(const std::string& query);
    double get_global_kwcov();

    // Frequency
    void reset_frequency();

private:
    // List of keywords
    std::vector<std::string> keywords;
    // Keyword Frequency
    std::unordered_map<std::string, int> frequency;
#ifdef LOG_KWCOV
    // Coverage log
    std::ofstream covlog;
    // Cumulative keyword coverage
    double get_cummulated_kwcov();
    std::unordered_map<std::string, int> cummulated_frequency;  
#endif
#ifdef LOG_INSTANT_KWCOV
    // Instant coverage log
    std::ofstream instant_covlog;
#endif
};

#endif  // __KWCOV_H__
