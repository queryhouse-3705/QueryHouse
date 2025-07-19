#!/bin/bash

#if fail, hardcoded dir
BASE_DIR=$(git rev-parse --show-toplevel)

START_TIME=$(date +%s)

sudo apt-get update && \
sudo apt-get -y install make cmake build-essential vim sudo git \
    clang libmysqlclient-dev ninja-build pkg-config clang-format gcc-11-plugin-dev \
    libpq-dev libyaml-cpp-dev lld llvm bison python3-fire apt-transport-https \
    curl software-properties-common gnutls-dev ltrace

sudo apt-get -y install make cmake build-essential vim sudo git \
    clang ninja-build pkg-config clang-format libpq-dev llvm libyaml-cpp-dev zlib1g-dev \
    libreadline8 libreadline-dev bison flex python3-fire lcov

APT_END_TIME=$(date +%s)

# AFL build
if [ ! -d "$BASE_DIR/afl_bld" ]; then
    mkdir -p $BASE_DIR/afl_bld
    cp -r AFLplusplus/* afl_bld/
fi

cd $BASE_DIR/afl_bld
cp -r ../AFLplusplus/src/* ./src
LLVM_CONFIG=llvm-config-14 make -j20

AFL_END_TIME=$(date +%s)

# Build & Install time
echo "APT: $((APT_END_TIME - START_TIME))s"
echo "AFL: $((AFL_END_TIME - APT_END_TIME))s"
echo "TOTAL: $((AFL_END_TIME - START_TIME))s"
