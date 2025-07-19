# QueryHouse

QueryHouse is a fuzzer that conducts Cross-DBMS differential testing with LLM and transpiler.

Our work is based on [Squirrel](https://github.com/s3team/Squirrel).

## How to build

### Docker build (recommended)

```bash
git clone https://github.com/queryhouse-3705/QueryHouse-sqlglot.git
cd QueryHouse
./single_docker_run.sh
```
It will build and run the QueryHouse as `test_qh`.

To run multiple instances with docker swarm:
```bash
./opti_swarm_run.py
```
> This will build another image for docker swarm.


### Local build

```bash
git clone https://github.com/queryhouse-3705/QueryHouse-sqlglot.git
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

## Bugs

For list of bugs and inconsistencies found by QueryHouse, see [here](./BUGLIST).

## Seeds

- **SQL Queries:** Stored in `data/fuzz_root/sql_input` as plain text SQL queries.
- **Formatted Seeds (Initial Corpus):** Automatically converted from SQL queries into the built-in format before fuzzing. Stored in `data/fuzz_root/input`.

To add new queries, place them in the SQL Queries directory. The `seed_formatter` tool automatically encodes plain SQL queries into the required format before executing the fuzzer.
