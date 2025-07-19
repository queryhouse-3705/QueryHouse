#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// afl headers
#include "config.h"
#include "types.h"

#include <filesystem>
#include <iostream>
#include <vector>

#include "yaml-cpp/yaml.h"
#include "client.h"
#include "common.h"
#include "executor.h"
#include "utils/string_helpers.h"

// Batch size (default: 100)
#ifndef BATCH_SIZE
#define BATCH_SIZE 100
#endif

using namespace std;

//ofstream outfile("/tmp/output.Fuzzlog");
//ofstream errfile("/tmp/error_log.Fuzzlog");

u8 *__afl_area_ptr;

__thread u32 __afl_map_size = MAP_SIZE;

/* Error reporting to forkserver controller */

void send_forkserver_error(int error) {
  u32 status;
  if (!error || error > 0xffff) return;
  status = (FS_OPT_ERROR | FS_OPT_SET_ERROR(error));
  if (write(FORKSRV_FD + 1, (char *)&status, 4) != 4) return;
}

/* SHM setup. */

static void __afl_map_shm(void) {
  char *id_str = getenv(SHM_ENV_VAR);
  char *ptr;

  /* NOTE TODO BUG FIXME: if you want to supply a variable sized map then
   * uncomment the following: */

  if ((ptr = getenv("AFL_MAP_SIZE")) != NULL) {
    u32 val = atoi(ptr);
    if (val > 0) __afl_map_size = val;
  }

  if (__afl_map_size > MAP_SIZE) {
    if (__afl_map_size > FS_OPT_MAX_MAPSIZE) {
      fprintf(stderr,
              "Error: AFL++ tools *require* to set AFL_MAP_SIZE to %u to "
              "be able to run this instrumented program!\n",
              __afl_map_size);
      if (id_str) {
        send_forkserver_error(FS_ERROR_MAP_SIZE);
        exit(-1);
      }

    } else {
      fprintf(stderr,
              "Warning: AFL++ tools will need to set AFL_MAP_SIZE to %u to "
              "be able to run this instrumented program!\n",
              __afl_map_size);
    }
  }

  if (id_str) {
#ifdef USEMMAP
    const char *shm_file_path = id_str;
    int shm_fd = -1;
    unsigned char *shm_base = NULL;

    /* create the shared memory segment as if it was a file */
    shm_fd = shm_open(shm_file_path, O_RDWR, 0600);
    if (shm_fd == -1) {
      fprintf(stderr, "shm_open() failed\n");
      send_forkserver_error(FS_ERROR_SHM_OPEN);
      exit(1);
    }

    /* map the shared memory segment to the address space of the process */
    shm_base =
        mmap(0, __afl_map_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    if (shm_base == MAP_FAILED) {
      close(shm_fd);
      shm_fd = -1;

      fprintf(stderr, "mmap() failed\n");
      send_forkserver_error(FS_ERROR_MMAP);
      exit(2);
    }

    __afl_area_ptr = shm_base;
#else
    u32 shm_id = atoi(id_str);

    __afl_area_ptr = (u8 *)shmat(shm_id, 0, 0);

#endif

    if (__afl_area_ptr == (void *)-1) {
      send_forkserver_error(FS_ERROR_SHMAT);
      exit(1);
    }

    /* Write something into the bitmap so that the parent doesn't give up */
    __afl_area_ptr[0] = 1;
  }
}

/* Fork server logic. */

static void __afl_start_forkserver(void) {
  u8 tmp[4] = {0, 0, 0, 0};
  u32 status = 0;

  if (__afl_map_size <= FS_OPT_MAX_MAPSIZE)
    status |= (FS_OPT_SET_MAPSIZE(__afl_map_size) | FS_OPT_MAPSIZE);
  if (status) status |= (FS_OPT_ENABLED);
  memcpy(tmp, &status, 4);

  /* Phone home and tell the parent that we're OK. */

  if (write(FORKSRV_FD + 1, tmp, 4) != 4) return;
}

static u32 __afl_next_testcase(u8 *buf, u32 max_len) {
  s32 status, res = 0xffffff;

  /* Wait for parent by reading from the pipe. Abort if read fails. */
  if (read(FORKSRV_FD, &status, 4) != 4) return 0;      // return 0

  /* we have a testcase - read it */
  status = read(0, buf, max_len);

  /* report that we are starting the target */
  if (write(FORKSRV_FD + 1, &res, 4) != 4) return 0;
  return status;
}

static void __afl_end_testcase(client::ExecutionStatus status) {
  int waitpid_status = 0xffffff;
  if (status == client::kServerCrash) {
    waitpid_status = 0x6;  // raise.
  }

  if (write(FORKSRV_FD + 1, &waitpid_status, 4) != 4) exit(1);
}

int main(int argc, char *argv[]) {
  string basedir = getenv("HOME");
  basedir += "/QueryHouse";
  string config_file_path = basedir + "/data/config/config_";
  vector<string> database = {"sqlite", "mysql", "postgresql", "oracle", "mariadb"};
  std::vector<Target> targets = {Target::SQLite, Target::MySQL, Target::PostgreSQL, Target::Oracle, Target::MariaDB};
  std::map<Target, string> db_names;
  std::map<Target, YAML::Node> configs;
  std::map<Target, unique_ptr<client::DBClient>> db_clients;
  std::map<Target, string> startup_cmds;

  for (const auto &target : targets) {
    db_names[target] = utils::str_tolower(target_to_string(target));
    configs[target] = YAML::LoadFile(config_file_path + db_names[target] + ".yml");
    db_clients[target] = std::unique_ptr<client::DBClient>(client::create_client(db_names[target], configs[target]));
    startup_cmds[target] = configs[target]["startup_cmd"].as<string>();
  }
  // outfile << YELLOW << "[Create DB clients]" << RESET << endl;

  // Batch execution variables
  vector<string> batch;           // queries within the current batch
  unsigned long batch_number = 0; // n'th batch
  int index_in_batch = 0;         // position within the current batch
  int last_buggy_index = -1;		  // -1 if the current batch is not buggy, otherwise the last index of the buggy query in the current batch
  std::filesystem::create_directories("/tmp/batch");
#ifdef LOG_INPUT
  std::filesystem::create_directories("/tmp/input");
#endif  // LOG_INPUT

  // Statistics variables
  size_t base_query_count = 0;
  size_t base_statement_count = 0; 
  size_t dbms_statement_count = 0;
  std::map<Target, size_t> dbms_valid_query_count = {
    {Target::SQLite, 0},
    {Target::MySQL, 0},
    {Target::PostgreSQL, 0},
    {Target::Oracle, 0},
    {Target::MariaDB, 0}
  };
  // Number of queries with each validity score
  std::map<int, size_t> validity_score_distribution = {
    {0, 0},
    {1, 0},
    {2, 0},
    {3, 0},
    {4, 0},
    {5, 0}
  };

  constexpr size_t kMaxInputSize = 0x10000;
  u8 *buf = (u8 *)malloc(kMaxInputSize);
  s32 len = 1;

  __afl_map_size = MAP_SIZE;  // default is 65536

  /* then we initialize the shared memory map and start the forkserver */

  // Start the database server. In case that the driver
  // is stopped and restarted, we should not start another server.
  __afl_map_shm();
  //outfile << YELLOW << "[afl_map_shm]" << RESET << endl;

  for (const auto &target : targets) {
    if (!db_clients[target]->check_alive()) {
      system(startup_cmds[target].c_str());
      sleep(5);
    }
  }
  //outfile << YELLOW << "[Start DB servers]" << RESET << endl;
  
  __afl_start_forkserver();

  //outfile << YELLOW << "[afl_start_forkserver]" << RESET << endl;
  while ((len = __afl_next_testcase(buf, kMaxInputSize)) > 0) {
    TestGroup *tg = new TestGroup((TestGroup::Raw *)buf);
    if (tg && tg->is_valid()) {
      // Batch execution initialization
      if ( index_in_batch == 0 ) { 
        for (const auto &target : targets) {
          db_clients[target]->prepare_env();
        }
      }
      batch.push_back(tg->to_string());

      vector<Result> results;
      if (!execute_testgroup(*tg, db_clients, results, batch_number, index_in_batch)){
        last_buggy_index = index_in_batch;
      }

	    // Statistics collection
      base_query_count++;
      base_statement_count += std::count(tg->base_query.begin(), tg->base_query.end(), ';');
      int validity_score = 0;
      for (const auto &result : results) {
        dbms_statement_count += std::count(result.executed_query.begin(), result.executed_query.end(), ';');
        if (result.status == client::kNormal) {
          dbms_valid_query_count[result.target]++;
          validity_score++;
        }
      }
      validity_score_distribution[validity_score]++;
      log_stats(base_query_count, base_statement_count, dbms_statement_count,
        dbms_valid_query_count, validity_score_distribution);
#ifdef LOG_TRANSPILE_FAIL
      log_transpile_fail(results);
#endif  // LOG_TRANSPILE_FAIL
#ifdef LOG_INPUT
      log_input(tg);
#endif  // LOG_INPUT

      for (const auto &result : results) {
	      // Restrart if DBMS server is crashed
        if (result.status == client::kConnectFailed) {
          system(startup_cmds[result.target].c_str());
          sleep(5);
        }
        // Report server crash
        else if (result.status == client::kServerCrash) {
          std::ofstream crash_logfile("/tmp/server_crash.Fuzzlog", std::ios::app);
          crash_logfile << "[CRASH] Server crashed for DBMS: "
                        << db_names[result.target] << "\n";
          crash_logfile << "        Query causing the crash: "
                        << result.executed_query << "\n";
          crash_logfile.close();
        }
      }

	    // Batch execution clean up
      if (index_in_batch >= BATCH_SIZE - 1) {
        for (const auto &target : targets) {
          db_clients[target]->clean_up_env();
        }
        
        if (last_buggy_index != -1) {
          string filename = "/tmp/batch/" + to_string(batch_number) + ".log";
          ofstream batch_log(filename);
          if (batch_log.is_open()) {
            for (int i = 0; i <= last_buggy_index; i++) {
              batch_log << batch[i] << "\n";
            }
            batch_log.close();
          }
        }
        
        batch_number++;
        index_in_batch = 0;
        last_buggy_index = -1;
        batch.clear();
      } else {
	      index_in_batch++;
	    }
    }
    delete tg;

    // remove this, this is just to make afl-fuzz not complain when run
    __afl_area_ptr[1] = 1;

    /* report the test case is done and wait for the next */
    __afl_end_testcase(client::kNormal);
  }
  std::cout << "\n\n\n\n\n\n\n __afl_next_testcase() does't have testcase!!!" << std::endl;
  free(buf);
  return 0;
}
