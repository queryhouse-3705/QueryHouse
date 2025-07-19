#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <stack>
#include <string>

#include "afl-fuzz.h"
#include "db.h"
#include "llm_api.h"
#include "common.h"
#include "cov/kwcov.h"
#include "utils/config_validate.h"
#include "yaml-cpp/yaml.h"

struct QHMutator {
  QHMutator(DataBase *db) : database(db) {}
  ~QHMutator() { delete database; }
  DataBase *database;
  TestGroup::Raw *current_input;
};

// LLM variables
static double last_coverage_level = -1.0;   // Previous coverage_level
static int stagnation_streak = 0;           // Num consecutive mutations with same coverage_level
static const int STREAK_THRESHOLD = 20;
static const double COVERAGE_THRESHOLD = 70.0;

extern "C" {
void *afl_custom_init(afl_state_t *afl, unsigned int seed) {
  std::string basedir = getenv("HOME");
  basedir += "/QueryHouse";
  std::string config_file_path = basedir + "/data/config/config_sqlite.yml";
  std::string config_file(config_file_path);
  YAML::Node config = YAML::LoadFile(config_file);
  if (!utils::validate_db_config(config)) {
  }
  auto *mutator = create_database(config);
  return new QHMutator(mutator);
}

void afl_custom_deinit(QHMutator *data) { delete data; }

u8 afl_custom_queue_new_entry(QHMutator *mutator,
                              const unsigned char *filename_new_queue,
                              const unsigned char *filename_orig_queue) {
  // Open the file in binary mode
  std::ifstream ifs((const char *)filename_new_queue, std::ios::binary);
  if (!ifs) {
    //std::cerr << "Error: Could not open file " << filename_new_queue
              //<< std::endl;
    return false;  // Failed to open file
  }

  // Read the file contents into a string (binary safe)
  std::string content((std::istreambuf_iterator<char>(ifs)),
                      std::istreambuf_iterator<char>());

  // Check that the file size matches the size of the Round structure
  if (content.size() < sizeof(TestGroup::Raw)) {
    //errfile << "Error: File content size does not match Round structure size."
            //<< std::endl;
    return false;  // File size mismatch
  }

  // Allocate memory for Round
  TestGroup::Raw *r = (TestGroup::Raw *)malloc(MAX_TESTGROUP_RAW_SIZE);
  // Copy the binary data from the string into the Round
  memcpy(r, content.data(), MAX_TESTGROUP_RAW_SIZE);

  // Extract the buffer queries from the Round structure
  std::string base_query = std::string(r->buf_queries);

  // Pass the queries to the mutator's database for saving
  mutator->database->save_interesting_query(base_query);

  // Clean up (free the dynamically allocated Round)
  delete r;

  return false;  // You can adjust this return value as per your needs
}

unsigned int afl_custom_fuzz_count(QHMutator *mutator,
                                   const unsigned char *buf, size_t buf_size) {
    TestGroup::Raw *raw = (TestGroup::Raw *)buf;

    //std::cerr << "afl_custom_fuzz_count:" << r->buf_queries << std::endl;

    // Coverage monitor
    double coverage_level = mutator->database->kwcov->get_global_kwcov();
    if (coverage_level == last_coverage_level) {
        stagnation_streak++;
    } else {
        stagnation_streak = 1;
        last_coverage_level = coverage_level;
    }

    // LLM invocation
    if (stagnation_streak >= STREAK_THRESHOLD && coverage_level >= COVERAGE_THRESHOLD) {
        //std::ofstream log_file("/tmp/llm_log.Fuzzlog", std::ios::app);
        //log_file << "Original Query: " << r->buf_queries << "\n";

        std::string llm_response = call_llm(raw->buf_queries);

        if (!llm_response.empty()) {
            //log_file << "LLM Response: " << llm_response << "\n";
            //log_file << "--------------------------------------\n";

            size_t max_query_size = buf_size - sizeof(TestGroup::Raw);
            strncpy(raw->buf_queries, llm_response.c_str(), max_query_size);
            raw->buf_queries[max_query_size - 1] = '\0';

        } //else {
            //log_file << "LLM Failed, Stay Original Query." << "\n";
            //return mutator->database->mutate(*r);
        //}

        // Reset keyword coverage and counter after LLM invocation
        stagnation_streak = 0;
        mutator->database->kwcov->reset_frequency();
    }

    // IR mutation
    return mutator->database->mutate(*raw);
}

size_t afl_custom_fuzz(QHMutator *mutator, uint8_t *buf, size_t buf_size,
                       u8 **out_buf, uint8_t *add_buf,
                       size_t add_buf_size,  // add_buf can be NULL
                       size_t max_size) {
  DataBase *db = mutator->database;
  assert(db->has_mutated_test_cases());
  mutator->current_input = db->get_next_mutated_query();
  *out_buf = (u8 *)mutator->current_input;
  return MAX_TESTGROUP_RAW_SIZE;
}
}
