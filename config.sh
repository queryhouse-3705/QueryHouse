#!/bin/bash

dbmss=("sqlite" "mysql" "postgresql" "oracle" "mariadb")

# Global replacement values
REPO_ROOT=$(git rev-parse --show-toplevel | echo "/home/fuzz/QueryHouse")
LOG_DIR="/tmp"
TMPFILE="$(mktemp)"

# Replace
for dbms in "${dbmss[@]}"; do
    TEMPLATE="${REPO_ROOT}/data/config/template_${dbms}.yml"
    OUT="${REPO_ROOT}/data/config/config_${dbms}.yml"
    echo "Configure $dbms"
    echo "  From template:    $TEMPLATE"
    touch "$OUT"
    if [ ! -w "$OUT" ]; then
        echo "Error: Cannot write to $OUT."
        exit 1
    fi

    # Global replacement
    sed "s|\${REPO_ROOT}|$REPO_ROOT|g" "$TEMPLATE" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
    sed "s|\${USER}|$USER|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
    sed "s|\${LOG_DIR}|$LOG_DIR|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"

    # Per-dbms replacement
    case "$dbms" in
        "sqlite")
            ;;
        "mysql")
            ;;
        "postgresql")
            PG_ROOT=/usr/local/pgsql
            #PG_ROOT=${REPO_ROOT}/postgres_bld/pgsql
            PG_PORT=5432
            PG_LOG=/tmp/postgres_log

            echo "  Postgres Path: $PG_ROOT"
            echo "  Postgres Port Number: $PG_PORT"
            echo "  Postgres Log: $PG_LOG"

            sed "s|\${PG_ROOT}|$PG_ROOT|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
            sed "s|\${PG_PORT}|$PG_PORT|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
            sed "s|\${PG_LOG}|$PG_LOG|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
            ;;
        "oracle")
            # Find Hostname of local OracleDB
            FINDSH="/tmp/run_oracle_find_hostname.sh"
cat <<EOF > "$FINDSH"
#!/bin/bash
export ORACLE_HOME=/opt/oracle/product/23ai/dbhomeFree
export ORACLE_SID=FREE
export ORACLE_BASE=/opt/oracle
export LD_LIBRARY_PATH=\$ORACLE_HOME/lib:\$LD_LIBRARY_PATH
export PATH=\$ORACLE_HOME/bin:\$PATH

lsnrctl start
sqlplus -S / as sysdba <<QUERY
SELECT SYS_CONTEXT('USERENV', 'HOST');
exit;
QUERY
EOF
            ORACLE_HOST=$(chmod +x $FINDSH && sudo su - oracle -c "sh $FINDSH" \
                | sed -n '/SYS_CONTEXT('\''USERENV'\'','\''HOST'\'')/{n; :a; n; /./{s/^[[:space:]]*//;s/[[:space:]]*$//;p;q}; ba}')

            # Try this if parsing hostname fails
            #ORACLE_HOST=$(chmod +x $FINDSH && sudo su - oracle -c "sh $FINDSH" \
                #| sed -n '/-------------/!b;n;p' | sed 's/^[[:space:]]*//;s/[[:space:]]*$//')

            ############# Backup for Oracle Docker users ####################
#cat <<EOF > $FINDSH
##!/bin/bash
#docker exec -i oracle-db sqlplus -S / as sysdba <<QUERY
#SELECT SYS_CONTEXT('USERENV', 'HOST');
#QUERY
#EOF
            #ORACLE_HOST=$(chmod +x $FINDSH && $FINDSH \
                #| sed -n '/SYS_CONTEXT('\''USERENV'\'','\''HOST'\'')/{n; :a; n; /./{s/^[[:space:]]*//;s/[[:space:]]*$//;p;q}; ba}')
            #################################################################

            echo "  Hostname: $ORACLE_HOST"
            sed "s|\${ORACLE_HOST}|$ORACLE_HOST|g" "$OUT" > "$TMPFILE" && mv "$TMPFILE" "$OUT"
            ;;
        *)
            ;;
    esac

    echo "  Generated config: $OUT"
done

#rm -f "$FINDSH"
rm -f "$TMPFILE"
