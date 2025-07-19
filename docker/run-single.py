"""
Run a fuzzing instance.
"""
import os
import fire
import uuid
from pathlib import Path

DBMS = ["sqlite"]
ROOTPATH = Path(os.path.dirname(os.path.realpath(__file__)))


def get_mutator_so_path(database):
  return f"{ROOTPATH}/build/lib{database}_mutator.so"


def get_config_path(database):
  return f"{ROOTPATH}/data/config/config_{database}.yml"


def set_env(database):
  os.environ["AFL_CUSTOM_MUTATOR_ONLY"] = "1"
  os.environ["AFL_DISABLE_TRIM"] = "1"
  os.environ["AFL_FAST_CAL"] = "1"
  os.environ["AFL_CUSTOM_MUTATOR_LIBRARY"] = get_mutator_so_path(database)
  os.environ["QUERYHOUSE_CONFIG"] = get_config_path(database)
  os.environ["ORACLE_HOME"] = "/opt/oracle/product/23ai/dbhomeFree"
  os.environ["ORACLE_SID"] = "FREE"
  os.environ["ORACLE_BASE"] = "/opt/oracle"
  os.environ["LD_LIBRARY_PATH"] = os.environ["ORACLE_HOME"] + "/lib" + ":" + (os.environ["LD_LIBRARY_PATH"] if "LD_LIBRARY_PATH" in os.environ else "")
  os.environ["PATH"] = os.environ["ORACLE_HOME"] + "/bin" + ":" + os.environ["PATH"]
  os.environ["AFL_NO_AFFINITY"] = "1"
  os.environ["AFL_SKIP_CPUFREQ"] = "1"
  os.environ["AFL_NO_SYNC"] = "1"
  # os.environ["AFL_NO_UI"] = "1"
  if "OPENAI_API_KEY" not in os.environ or os.environ.get("OPENAI_API_KEY") == "":
    os.environ["OPENAI_API_KEY"] = input("OPENAI_API_KEY (Press Enter to skip): ").strip()


def run(database, input_dir, output_dir=None, config_file=None, fuzzer=None):
  # Precondition checks
  if database not in DBMS:
    print(f"Unsupported database. The supported ones are {DBMS}")
    return

  if not output_dir:
    output_dir = "/tmp/fuzz"

  if not config_file:
    config_file = get_config_path(database)
  if not fuzzer:
    fuzzer = f"{ROOTPATH}/afl_bld/afl-fuzz"
  if not os.path.exists(config_file):
    print("Invalid path for config file")
  if not os.path.exists(fuzzer):
    print("Invalid path for afl-fuzz")

  set_env(database)
  cpu = os.environ.get("CPU")

  output_id = str(uuid.uuid4())[:10]
  
  cmd = f"/usr/local/mysql/bin/mysqld --basedir=/usr/local/mysql --datadir=/usr/local/mysql/data --log-error=err_log.err --pid-file=server_pid.pid --max-execution-time=1000 &"
  os.system(cmd)
  cmd = f"/usr/local/pgsql/bin/pg_ctl start -D /usr/local/pgsql/data -l /tmp/postgres_log"
  os.system(cmd)
  cmd = f"/home/fuzz/QueryHouse/oracle_run.sh"
  os.system(cmd)
  cmd = f"/home/fuzz/QueryHouse/mariadb_run.sh"
  os.system(cmd)
  cmd = f"stty sane"
  os.system(cmd)
  # cmd = f"taskset -c {cpu} {fuzzer} -i {input_dir} -o {output_dir} -t 60000 -- {ROOTPATH}/build/db_driver"
  cmd = f"{fuzzer} -i {input_dir} -o {output_dir} -M {output_id} -t 60000 -- {ROOTPATH}/build/db_driver"
  print(cmd)
  os.system(cmd)


if __name__ == "__main__":
  fire.Fire(run)
