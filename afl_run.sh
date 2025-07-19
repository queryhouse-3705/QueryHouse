#!/bin/bash

./oracle_run.sh

# Configure configs
./config.sh
echo "Configureation done"
echo "Note: If your oracle hostname seems incorrect,"
echo "      check if /tmp/run_oracle_find_hostname.sh returns the hostname correctly."
echo "      If not, modify config.sh either to create the correct script."
echo "      You can also simply hardcode it to your template and disable the replacement,"
echo "      but please make sure not to push them to repo in that case."


# Format initial seeds
rm data/fuzz_root/input/*
pushd build
./seed_formatter
popd

AFL_IGNORE_PROBLEMS=1 AFL_MAP_SIZE=65536 python3 run.py sqlite data/fuzz_root/input
