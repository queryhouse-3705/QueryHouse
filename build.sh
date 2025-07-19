#!/bin/bash

#
# Prerequisite
#

BASE_DIR=$(git rev-parse --show-toplevel)
NCORES=$(( $(nproc) <= 20 ? $(nproc) : 20))

START_TIME=$(date +%s)

#
# Dependencies
#

sudo apt-get update && \
sudo apt-get install -y \
    make cmake build-essential vim sudo git \
    clang libmysqlclient-dev ninja-build pkg-config clang-format \
    libpq-dev libyaml-cpp-dev lld llvm bison python3-fire apt-transport-https \
    curl software-properties-common gnutls-dev ltrace libsqlite3-dev \
    zlib1g-dev libreadline8 libreadline-dev flex lcov nlohmann-json3-dev libsasl2-dev python3-dev python3-pybind11

APT_END_TIME=$(date +%s)

#
# MySQL Build & Install
#

if [ ! -d "$BASE_DIR/mysql_bld" ]; then
    mkdir -p $BASE_DIR/mysql_bld
fi

cd $BASE_DIR/mysql_bld
cmake $BASE_DIR/mysql/ -DDOWNLOAD_BOOST=1 -DWITH_BOOST=../boost 
make -j$NCORES

sudo cmake --install . --prefix /usr/local/mysql/
sudo chown $USER:$USER /usr/local/mysql/ -R

cd /usr/local/mysql/
if [ ! -d "mysql-files" ]; then
    mkdir mysql-files
    chmod 750 mysql-files
fi

sudo rm -rf /usr/local/mysql/data

bin/mysqld --initialize-insecure --user=$USER
MYSQL_END_TIME=$(date +%s)

#
# PostgreSQL Build & Install
#

PG_SRC=$BASE_DIR/postgres
PG_BLD=$BASE_DIR/postgres_bld
PG_PATH=/usr/local/pgsql    # =PG_ROOT in config.sh : postgres install path
#PG_PATH=$PG_BLD/pgsql
PG_DATA=$PG_PATH/data
PG_PORT=5432                # =PG_PORT in config.sh : default port number for server and clients
PG_LOG=/tmp/postgres_log    # =PG_LOG in config.sh : postgres log filename

# Uninstall if needed
kill $(ps aux | grep 'postgres -D ${PG_DATA}' | awk '{print $2}')
sudo rm -rf $PG_DATA

# Initialize directories
mkdir -p $PG_BLD
sudo mkdir -p $PG_PATH
sudo mkdir -p $PG_DATA
cd $PG_BLD && make coverage-clean

# Config & Build
cd $PG_BLD
$PG_SRC/configure \
    --prefix=$PG_PATH --with-pgport=$PG_PORT \
    CFLAGS='-g -O0' LDFLAGS='-L/usr/lib/' \
    --with-llvm --enable-debug --enable-coverage --enable-cassert
wait
sudo rm a-conftest.gcno -f
sudo make -j$NCORES
sudo make install -j$NCORES

# Initialize Database
sudo chown -R $USER:$USER $PG_BLD
sudo chown -R $USER:$USER $PG_PATH
$PG_PATH/bin/initdb -D $PG_DATA \
    -E UTF8 --lc-collate=C.UTF-8 --lc-ctype=C.UTF-8 \
    > $PG_LOG 2>&1 &  

wait
POSTGRES_END_TIME=$(date +%s)

#
# SQLite Build & Install
#

SQLITE_SRC=$BASE_DIR/sqlite
SQLITE_BLD=$BASE_DIR/sqlite_bld

# Initialize directories
mkdir -p $SQLITE_BLD
cd $SQLITE_BLD && rm -rf *.gcda *.gcov conftest__.gcno a-conftest.gcno

# Config & Build
CFLAGS="-fPIC -DSQLITE_THREADSAFE=0 -DSQLITE_ENABLE_LOAD_EXTENSION=0 -DSQLITE_NO_SYNC -DSQLITE_DEBUG -DSQLITE_ENABLE_FTS4 -DSQLITE_ENABLE_RTREE -DSQLITE_OMIT_RANDOMNESS -DSQLITE_ENABLE_SELECTTRACE -DSQLITE_ENABLE_WHERETRACE -g -O0 --coverage" \
    $SQLITE_SRC/configure --enable-all --disable-shared --disable-static
make -j$NCORES
sudo make install

wait
SQLITE_END_TIME=$(date +%s)


#
# Mariadb Build & Install
#

# Required packages
sudo apt update && sudo apt install -y \
    build-essential bison libgnutls28-dev \
    software-properties-common devscripts equivs cmake \
    ninja-build pkg-config libaio-dev libncurses-dev

# Add MariaDB GPG key
sudo mkdir -p /etc/apt/keyrings
curl -fsSL https://mariadb.org/mariadb_release_signing_key.asc | gpg --dearmor | sudo tee /etc/apt/keyrings/mariadb.gpg > /dev/null
sudo chmod 644 /etc/apt/keyrings/mariadb.gpg

# Remove the old repository file if it exists
sudo rm -f /etc/apt/sources.list.d/mariadb.list

# Add MariaDB repository with both binary and source entries
cat <<'EOF' | sudo tee /etc/apt/sources.list.d/mariadb.sources
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

# Install MariaDB build dependencies
sudo apt update
sudo apt build-dep mariadb -y

# Set base directories
MARIADB_SRC=$BASE_DIR/mariaDB
MARIADB_BLD=$BASE_DIR/mariaDB_bld
MARIADB_DATA=/usr/local/mariadb/data
MARIADB_PREFIX=/usr/local/mariadb
MARIADB_PORT=3307
MARIADB_SOCK=$MARIADB_DATA/mariadb.sock

# Create necessary directories
mkdir -p "$MARIADB_BLD" "$MARIADB_DATA"
cd "$MARIADB_BLD"

# Build MariaDB
cmake "$MARIADB_SRC" -DBUILD_CONFIG=mysql_release -G Ninja \
    -DFORCE_INSOURCE_BUILD=OFF \
    -DDEFAULT_CHARSET=utf8mb4 \
    -DDEFAULT_COLLATION=utf8mb4_bin

cmake --build . --parallel=$(nproc)

# Install MariaDB
sudo cmake --install . --prefix="$MARIADB_PREFIX"

# Ensure database directory exists
sudo chown -R "$USER":"$USER" "$MARIADB_DATA"

# Initialize MariaDB Data Directory
sudo "$MARIADB_PREFIX"/scripts/mariadb-install-db --user="$USER" --datadir="$MARIADB_DATA"

# Start MariaDB without access control
sudo "$MARIADB_PREFIX"/bin/mariadbd-safe --user="$USER" --datadir="$MARIADB_DATA" --port="$MARIADB_PORT" --socket="$MARIADB_SOCK" --skip-grant-tables --skip-networking &

# Wait for the server to start
sleep 5

# Secure MariaDB installation
sudo "$MARIADB_PREFIX"/bin/mariadb -u root --socket="$MARIADB_SOCK" <<EOF
FLUSH PRIVILEGES;
UPDATE mysql.user SET authentication_string='', plugin='' WHERE user='root';
UPDATE mysql.user SET password=PASSWORD('') WHERE user='root';
DELETE FROM mysql.user WHERE User='' OR Password='';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'localhost' IDENTIFIED BY '' WITH GRANT OPTION;
FLUSH PRIVILEGES;
EOF

# Stop MariaDB Server
sudo killall mariadbd-safe
sleep 5

# Start MariaDB normally
sudo "$MARIADB_PREFIX"/bin/mariadbd-safe --user="$USER" --datadir="$MARIADB_DATA" --port="$MARIADB_PORT" --socket="$MARIADB_SOCK" &

# Output instructions
echo "MariaDB installation complete."
echo "Root user has no password. Data directory: $MARIADB_DATA"
echo "To start the server: $MARIADB_PREFIX/bin/mariadbd-safe --datadir=\"$MARIADB_DATA\" --port=$MARIADB_PORT --socket=$MARIADB_SOCK &"
echo "To stop the server: killall mariadbd-safe"
echo "To log in as root: $MARIADB_PREFIX/bin/mariadb -u root --socket=$MARIADB_SOCK"
echo "Try: $MARIADB_PREFIX/bin/mariadb -u root --socket=$MARIADB_SOCK -e \"SHOW VARIABLES LIKE 'character_set_server';\""

wait
MARIADB_END_TIME=$(date +%s)

#
# SQLGLOT Build & Install
#

pip3 install --upgrade pip setuptools
pushd $BASE_DIR/QueryHouse-sqlglot && make install && popd
wait
SQLGLOT_END_TIME=$(date +%s)

#
# mutator & db_driver build
#

cd $BASE_DIR
pushd srcs/internal/sqlite/parser && make && popd
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -Wno-dev
cmake --build build #-j
wait
DRIVER_END_TIME=$(date +%s)

#
# Build Time
#

echo "APT: $((APT_END_TIME - START_TIME))s"
echo "MYSQL: $((MYSQL_END_TIME - APT_END_TIME))s"
echo "POSTGRES: $((POSTGRES_END_TIME - MYSQL_END_TIME))s"
echo "SQLITE: $((SQLITE_END_TIME - POSTGRES_END_TIME))s"
echo "MARIADB: $((MARIADB_END_TIME - SQLITE_END_TIME))s"
echo "SQLGLOT: $((SQLGLOT_END_TIME - MARIADB_END_TIME))s"
echo "DRIVER: $((DRIVER_END_TIME - SQLGLOT_END_TIME))s"
echo "TOTAL: $((DRIVER_END_TIME - START_TIME))s"
