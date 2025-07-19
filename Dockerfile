FROM ubuntu:22.04

ARG TIMEZONE=UTC
RUN ln -sf /usr/share/zoneinfo/${TIMEZONE} /etc/localtime
RUN echo "TZ='${TIMEZONE}'; export TZ" >> ~/.profile

RUN apt update && apt install -y \
    make cmake build-essential vim sudo git \
    clang libmysqlclient-dev ninja-build pkg-config clang-format \
    libpq-dev libyaml-cpp-dev lld llvm bison apt-transport-https \
    curl software-properties-common gnutls-dev ltrace tcl-dev nlohmann-json3-dev

RUN apt update && apt install -y make cmake build-essential vim git \
    clang ninja-build pkg-config clang-format libpq-dev llvm libyaml-cpp-dev zlib1g-dev \
    libreadline8 libreadline-dev bison flex python3 python3-pip python3-fire nano


RUN apt update && apt install -y \
    build-essential bison libgnutls28-dev \
    software-properties-common devscripts equivs cmake \
    ninja-build pkg-config libaio-dev libncurses-dev

# add user Fuzz
RUN useradd -m -s /bin/bash fuzz
RUN echo "fuzz ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers

USER fuzz
WORKDIR /home/fuzz
RUN mkdir QueryHouse
WORKDIR /home/fuzz/QueryHouse

# Clone DBMS
RUN git clone https://github.com/sqlite/sqlite.git sqlite
RUN cd sqlite && git checkout version-3.47.0
RUN git clone https://github.com/mysql/mysql-server.git mysql
RUN cd mysql && git checkout mysql-9.1.0
RUN git clone https://github.com/postgres/postgres.git postgres
RUN cd postgres && git checkout REL_17_0
RUN git clone https://github.com/MariaDB/server.git mariadb
RUN cd mariadb && git checkout mariadb-11.6.2


#
# Build SQLite
#
RUN mkdir sqlite_bld
WORKDIR /home/fuzz/QueryHouse/sqlite_bld
RUN ../sqlite/configure --enable-all
RUN make -j$(nproc)
RUN sudo make install

#
# Build MySQL
#
WORKDIR /home/fuzz/QueryHouse
RUN mkdir mysql_bld
WORKDIR /home/fuzz/QueryHouse/mysql_bld
RUN cmake ../mysql/ -DDOWNLOAD_BOOST=1 -DWITH_BOOST=../boost 
RUN make -j$(nproc)

RUN sudo cmake --install . --prefix=/usr/local/mysql/
RUN sudo chown -R fuzz:fuzz /usr/local/mysql/

WORKDIR /usr/local/mysql/

RUN mkdir mysql-files
RUN chmod 750 mysql-files

RUN bin/mysqld --initialize-insecure --user=fuzz

#
# Build Postgres
#
WORKDIR /home/fuzz/QueryHouse
RUN mkdir postgres_bld
WORKDIR /home/fuzz/QueryHouse/postgres_bld

RUN ../postgres/configure --prefix=/usr/local/pgsql
RUN make -j$(nproc)
RUN sudo make install

RUN sudo chown -R fuzz:fuzz /usr/local/pgsql/

RUN sudo mkdir /usr/local/pgsql/data
RUN sudo chown fuzz:fuzz /usr/local/pgsql/data

RUN /usr/local/pgsql/bin/initdb -D /usr/local/pgsql/data

#
# Install OracleDB
#
WORKDIR /home/fuzz/QueryHouse

ENV ORACLE_SID=FREE
ENV ORAENV_ASK=NO

USER root

# Install necessary packages
RUN apt-get install -y alien libaio1 wget unzip && \
    apt-get clean && rm -rf /var/lib/apt/lists/*

# Create oracle user and group
RUN groupadd oinstall && \
    useradd -r -g oinstall oracle

# Kernel parameter configuration
# COPY docker/97-oracle-database-sysctl.conf /etc/sysctl.d/
# RUN sysctl -p /etc/sysctl.d/97-oracle-database-sysctl.conf

# Shared memory setup script
RUN echo '#!/bin/sh\n' > /etc/rc.local && \
    echo 'mkdir -p /var/lock/subsys' >> /etc/rc.local && \
    echo 'rm -rf /dev/shm && mkdir /dev/shm && mount -t tmpfs shmfs -o size=4096m /dev/shm' >> /etc/rc.local && \
    chmod +x /etc/rc.local

# Download and convert Oracle Database RPM to DEB
WORKDIR /tmp
RUN wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" \
    https://download.oracle.com/otn-pub/otn_software/db-free/oracle-database-free-23ai-1.0-1.el9.x86_64.rpm && \
    alien --scripts -d oracle-database-free-23ai-1.0-1.el9.x86_64.rpm && \
    dpkg -i oracle-database-free-23ai_1.0-2_amd64.deb

# Configure Oracle Database
RUN mkdir -p /opt/oracle && \
    chown oracle:oinstall /opt/oracle
RUN /opt/oracle/product/23ai/dbhomeFree/bin/oraenv && \
    (echo "password"; echo "password";)  | /etc/init.d/oracle-free-23ai configure; \
    (echo "password"; echo "password";)  | /etc/init.d/oracle-free-23ai configure

# Download Oracle Instant Client packages
RUN wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" \
    https://download.oracle.com/otn_software/linux/instantclient/2350000/instantclient-basic-linux.x64-23.5.0.24.07.zip -O /tmp/OCI.zip && \
    wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" \
    https://download.oracle.com/otn_software/linux/instantclient/2350000/instantclient-sdk-linux.x64-23.5.0.24.07.zip -O /tmp/SDK.zip && \
    unzip /tmp/OCI.zip -d /opt/oracle/product/23ai/dbhomeFree/lib/OCI && \
    unzip /tmp/SDK.zip -d /opt/oracle/product/23ai/dbhomeFree/lib/SDK && \
    rm -f /tmp/*.zip

# Set up environment variables for Oracle
ENV PATH=$PATH:/opt/oracle/product/23ai/dbhomeFree/bin
ENV LD_LIBRARY_PATH=/opt/oracle/product/23ai/dbhomeFree/lib

# Clean up large unnecessary files
RUN rm -f \
    /tmp/oracle-database-free-23ai-1.0-1.el9.x86_64.rpm \
    /tmp/oracle-database-free-23ai_1.0-2_amd64.deb


#
# MariaDB Build
#

RUN mkdir -p /etc/apt/keyrings
RUN curl -fsSL https://mariadb.org/mariadb_release_signing_key.asc | gpg --dearmor | tee /etc/apt/keyrings/mariadb.gpg > /dev/null
RUN chmod 644 /etc/apt/keyrings/mariadb.gpg

RUN cat <<'EOF' | tee /etc/apt/sources.list.d/mariadb.sources
# MariaDB 11.8 repository list - created 2025-04-01 14:27 UTC
# https://mariadb.org/download/
X-Repolib-Name: MariaDB
Types: deb deb-src
# deb.mariadb.org is a dynamic mirror if your preferred mirror goes offline. See https://mariadb.org/mirrorbits/ for details.
# URIs: https://deb.mariadb.org/11.rc/ubuntu
URIs: https://mirrors.xtom.jp/mariadb/repo/11.8/ubuntu
Suites: jammy
Components: main main/debug
Signed-By: /etc/apt/keyrings/mariadb.gpg
EOF
RUN apt update && apt build-dep mariadb -y

ENV MARIADB_SRC=/home/fuzz/QueryHouse/mariadb
ENV MARIADB_BLD=/home/fuzz/QueryHouse/mariadb_bld
ENV MARIADB_DATA=/usr/local/mariadb/data
ENV MARIADB_PREFIX=/usr/local/mariadb
ENV MARIADB_PORT=3307
ENV MARIADB_SOCK=/usr/local/mariadb/data/mariadb.sock

RUN mkdir -p $MARIADB_BLD
RUN mkdir -p $MARIADB_DATA

WORKDIR /home/fuzz/QueryHouse/mariadb
RUN git config --global --add safe.directory '*'
RUN git submodule update --init --recursive

RUN apt update && apt install -y \
  libssl-dev \
  libjemalloc-dev \
  libnuma-dev \
  libzstd-dev \
  libedit-dev \
  libreadline-dev \
  libncurses5-dev \
  libncursesw5-dev \
  libxml2-dev \
  libxslt1-dev \
  libssl-dev \
  libpam0g-dev \
  libcurl4-openssl-dev   libbz2-dev   liblz4-dev   liblzma-dev   liblzo2-dev   libsnappy-dev   libboost-all-dev \
  libcrack2-dev

RUN cmake "$MARIADB_SRC" -DBUILD_CONFIG=mysql_release -G Ninja \
    -DFORCE_INSOURCE_BUILD=OFF \
    -DDEFAULT_CHARSET=utf8mb4 \
    -DDEFAULT_COLLATION=utf8mb4_bin

RUN cmake --build . --parallel $(nproc)

RUN cmake --install . --prefix $MARIADB_PREFIX

RUN chown -R fuzz:fuzz $MARIADB_DATA

RUN $MARIADB_PREFIX/scripts/mariadb-install-db --user=fuzz --datadir=$MARIADB_DATA

# RUN sleep 5

# RUN $MARIADB_PREFIX/bin/mariadb -u root --socket=$MARIADB_SOCK <<EOF
# FLUSH PRIVILEGES;
# UPDATE mysql.user SET authentication_string='', plugin=''
# WHERE user
#     UPDATE mysql.user SET password=PASSWORD('') WHERE user='root';
#     DELETE FROM mysql.user WHERE User='' OR Password='';
#     GRANT ALL PRIVILEGES ON *.* TO 'root'
#     @'localhost' IDENTIFIED BY '' WITH GRANT OPTION;
#     FLUSH PRIVILEGES;
# EOF

# RUN killall mariadbd-safe
# RUN sleep 5

# RUN $MARIADB_PREFIX/bin/mariadbd-safe --user=fuzz --datadir=$MARIADB_DATA --port=$MARIADB_PORT --socket=$MARIADB_SOCK &

#
# Build AFL
#
USER fuzz
WORKDIR /home/fuzz/QueryHouse
RUN git clone https://github.com/AFLplusplus/AFLplusplus.git
RUN cd AFLplusplus && git checkout 16cc444ae576da9c8c7ef45f55984507b3cf6004

COPY docker/afl /home/fuzz/QueryHouse/afl
RUN cp -r afl/* AFLplusplus/src/

RUN mkdir afl_bld
WORKDIR /home/fuzz/QueryHouse/afl_bld

RUN cp -r ../AFLplusplus/* .
RUN LLVM_CONFIG=llvm-config-14 make -j$(nproc)

#
# Build SQLite with AFL
#
WORKDIR /home/fuzz/QueryHouse

RUN mkdir sqlite_afl_bld
WORKDIR /home/fuzz/QueryHouse/sqlite_afl_bld
RUN CC=/home/fuzz/QueryHouse/afl_bld/afl-clang-fast CXX=/home/fuzz/QueryHouse/afl_bld/afl-clang-fast++ CFLAGS="-DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_LOAD_EXTENSION=0 -DSQLITE_NO_SYNC -DSQLITE_DEBUG -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_RTREE -DSQLITE_OMIT_RANDOMNESS -fsanitize=address" /home/fuzz/QueryHouse/sqlite/configure --enable-all --disable-shared --disable-static && \
    CC=/home/fuzz/QueryHouse/afl_bld/afl-clang-fast CXX=/home/fuzz/QueryHouse/afl_bld/afl-clang-fast++ make -j$(nproc) && \
    sudo make install

RUN sudo chmod 777 /tmp

#
# Build SQLGlot
#
WORKDIR /home/fuzz/QueryHouse
RUN git clone https://github.com/queryhouse-3705/QueryHouse-sqlglot
RUN pip install --upgrade pip setuptools

# Patch for muting SQLGlot
WORKDIR /home/fuzz/QueryHouse/QueryHouse-sqlglot
COPY --chown=fuzz:fuzz mute_sqlglot.patch /home/fuzz/QueryHouse/QueryHouse-sqlglot/mute_sqlglot.patch
RUN git apply mute_sqlglot.patch && make install

#
# LLM requirements
#
RUN pip install openai

#
# Build fuzzer
#
WORKDIR /home/fuzz/QueryHouse

# Prepare sources & data
COPY --chown=fuzz:fuzz docker /home/fuzz/QueryHouse

# Default values in CMakeLists.txt are used unless overridden
ARG BATCH_SIZE
ARG ENABLE_TRANSPILER
ARG LOG_KWCOV
ARG LOG_INSTANT_KWCOV
ARG LOG_LLM
ARG LOG_INPUT
ARG LOG_TRANSPILE_FAIL

# Multi core (default) / Single core mode
ARG MULTI_CORE=1
RUN if [ "$MULTI_CORE" = "1" ]; then \
    mv run-multi.py run.py; \
    else \
    mv run-single.py run.py; \
    fi

# Build
RUN cd srcs/internal/sqlite/parser && make
RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -Wno-dev \
    ${BATCH_SIZE:+-DBATCH_SIZE=${BATCH_SIZE}} \
    ${ENABLE_TRANSPILER:+-DENABLE_TRANSPILER=${ENABLE_TRANSPILER}} \
    ${LOG_KWCOV:+-DLOG_KWCOV=${LOG_KWCOV}} \
    ${LOG_INSTANT_KWCOV:+-DLOG_INSTANT_KWCOV=${LOG_INSTANT_KWCOV}} \
    ${LOG_LLM:+-DLOG_LLM=${LOG_LLM}} \
    ${LOG_INPUT:+-DLOG_INPUT=${LOG_INPUT}} \
    ${LOG_TRANSPILE_FAIL:+-DLOG_TRANSPILE_FAIL=${LOG_TRANSPILE_FAIL}}
RUN cmake --build build -j$(nproc)

# Format initial seeds
RUN cd build && ./seed_formatter

CMD ["/home/fuzz/QueryHouse/afl_run.sh"]
