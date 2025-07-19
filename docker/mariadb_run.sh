#!/bin/bash

MARIADB_SRC=$BASE_DIR/mariaDB
MARIADB_BLD=$BASE_DIR/mariaDB_bld
MARIADB_DATA=/usr/local/mariadb/data
MARIADB_PREFIX=/usr/local/mariadb
MARIADB_PORT=3307
MARIADB_SOCK=$MARIADB_DATA/mariadb.sock
USER=fuzz

# Start MariaDB without access control
sudo "$MARIADB_PREFIX"/bin/mariadbd-safe --user="$USER" --datadir="$MARIADB_DATA" --port="$MARIADB_PORT" --socket="$MARIADB_SOCK" --skip-grant-tables --skip-networking &

# Wait for the server to start
sleep 15

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