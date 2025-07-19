#!/bin/bash

declare -A MODULES=(
    ["sqlite"]="https://github.com/sqlite/sqlite.git"
    ["postgres"]="https://github.com/postgres/postgres.git"
    ["mysql"]="https://github.com/mysql/mysql-server.git"
    ["AFLplusplus"]="https://github.com/AFLplusplus/AFLplusplus.git"
    ["QueryHouse-sqlglot"]="https://github.com/queryhouse-3705/QueryHouse-sqlglot.git"
    ["mariaDB"]="https://github.com/MariaDB/server.git"
)

declare -A TAGS=(
    ["sqlite"]="version-3.47.0"
    ["postgres"]="REL_17_0"
    ["mysql"]="mysql-9.1.0"
    ["mariaDB"]="mariadb-11.6.2"
)

for submodule in "${!MODULES[@]}"; do
    if [ -d "$submodule" ]; then
        echo "$submodule already exists, skipping clone."
    else
        echo -n "Cloning $submodule..."
        git clone "${MODULES[$submodule]}" "$submodule"
        echo "  Done"
    fi
    
    echo -n "Updating $submodule..."
    cd "$submodule" || exit 1

    if [ -z "${TAGS[$submodule]}" ]; then
        echo -n "(main)"
        git fetch origin
        git pull origin main
    else
        echo -n "(tag: ${TAGS[$submodule]})"
        git fetch origin tag "${TAGS[$submodule]}"
        git checkout "tags/${TAGS[$submodule]}"
    fi

    cd .. || exit 1
    echo "  Done"
done

# Backup for .gitmodules
#[submodule "postgres"]
	#path = postgres
	#url = https://github.com/postgres/postgres.git
#[submodule "mysql"]
	#path = mysql
	#url = https://github.com/mysql/mysql-server.git
#[submodule "AFLplusplus"]
	#path = AFLplusplus
	#url = https://github.com/AFLplusplus/AFLplusplus.git
#[submodule "sqlite"]
	#path = sqlite
	#url = https://github.com/sqlite/sqlite
#[submodule "QueryHouse-sqlglot"]
	#path = QueryHouse-sqlglot
	#url = https://github.com/queryhouse-3705/QueryHouse-sqlglot.git

## Should add for mariaDB