# QueryHouse

A cross-DBMS differential testing framework that uses LLM and transpiler to find bugs and inconsistencies across database systems (SQLite, MySQL, PostgreSQL, Oracle, MariaDB).

Our work is based on [Squirrel](https://github.com/s3team/Squirrel).

## Quick Start

### Docker (Recommended)
```bash
git clone https://github.com/queryhouse-3705/QueryHouse.git
cd QueryHouse
./single_docker_run.sh
```
It will build and run the QueryHouse as `test_qh`.

For multiple instances:
```bash
./opti_swarm_run.py
```

### Local Build
```bash
git clone https://github.com/queryhouse-3705/QueryHouse.git
cd QueryHouse
./submodule_init.sh

# to install oracle
./scripts/install_oracle.sh
# to disable oracle
./oracle_enable_disable_compile.sh

./build.sh
./afl_build.sh
./afl_run.sh
```

## Usage

- **Input queries**: Add SQL queries to `data/fuzz_root/sql_input/`
- **Formatted seeds**: Automatically generated in `data/fuzz_root/input/` from input queries
- **Results**: Check reports in `/tmp/report.Fuzzlog`

## Bugs

See [here](./docs/BUGLIST.md) for the list of found bugs and inconsistencies by QueryHouse.
