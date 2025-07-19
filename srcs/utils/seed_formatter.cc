#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
// #include "ast.h"
// #include "mutator.h"
// #include "utils.h"
#include "common.h"
#include "transpile.h"
#include "postprocess.h"

#ifndef SQL_INPUT_DIR
#define SQL_INPUT_DIR "../data/fuzz_root/sql_input"
#endif

#ifndef SEED_OUTPUT_DIR
#define SEED_OUTPUT_DIR "../data/fuzz_root/input"
#endif

namespace fs = std::filesystem;

void save_testgroup_to_binary(TestGroup &tg, const std::string &filename) {
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    TestGroup::Raw *r = tg.encode();
    outfile.write(reinterpret_cast<const char*>(r), MAX_TESTGROUP_RAW_SIZE);
    delete r;
    outfile.close();

    if (outfile.fail()) {
        std::cerr << "Error writing to file: " << filename << std::endl;
    } else {
        std::cout << "TestGroup data successfully written to " << filename << std::endl;
    }
}

void format_query(const std::string &base_query, const std::string &filepath, TargetsMask targets) {
    TestGroup tg = transpile(base_query, targets);
    postprocess_core(tg);

    if (tg.is_valid()) {
        save_testgroup_to_binary(tg, filepath);
    } else {
        std::cerr << "Invalid TestGroup" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    // Source directory
    if (!fs::exists(SQL_INPUT_DIR) || !fs::is_directory(SQL_INPUT_DIR)) {
        std::cerr
            << "Error: Invalid directory path :" << SQL_INPUT_DIR << std::endl;
        return 1;
    }

    // Destination directory
    fs::create_directory(SEED_OUTPUT_DIR);

    // Targets
    TargetsMask targets = TARGET_NONE;
#ifdef __QUERYHOUSE_SQLITE__
    targets |= TARGET(Target::SQLite);
#endif
#ifdef __QUERYHOUSE_MYSQL__
    targets |= TARGET(Target::MySQL);
#endif
#ifdef __QUERYHOUSE_POSTGRESQL__
    targets |= TARGET(Target::PostgreSQL);
#endif
#ifdef __QUERYHOUSE_ORACLE__
    targets |= TARGET(Target::Oracle);
#endif
#ifdef __QUERYHOUSE_MARIADB__
    targets |= TARGET(Target::MariaDB);
#endif

    // Format each files in SQL_INPUT_DIR
    for (const auto &entry : fs::directory_iterator(SQL_INPUT_DIR)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::string file_path = entry.path().string();
            std::ifstream infile(file_path);
            if (!infile) {
                std::cerr << "Error opening file: " << file_path << std::endl;
                continue;
            }

            std::string sql_query((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
            infile.close();

            // extension to .bin
            std::string output_path = SEED_OUTPUT_DIR "/" + entry.path().stem().string() + ".bin";

            format_query(sql_query, output_path, targets);
        }
    }

    return 0;
}
