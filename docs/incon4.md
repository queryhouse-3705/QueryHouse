# Inconsistency 4

### Support for `FULL JOIN` / `FULL OUTER JOIN`

`FULL [OUTER] JOIN` is part of the SQL standard, but its support varies across DBMSs. MySQL and MariaDB do not support this construct, and their documentation does not clearly state this limitation.

This can lead to silent issues when `FULL` is incorrectly interpreted as a table alias:
```SQL
SELECT ... FROM table1 FULL JOIN table2 ...;
```
- Intended: perform a `FULL JOIN` between `table1` and `table2`
- Actual: perform a `JOIN` between `table1` (aliased as `FULL`) and `table2`

## Behavior by DBMS

### MySQL
- Does not support `FULL JOIN` or `FULL OUTER JOIN`.
- The official documentation does not mention this limitation.

### MariaDB
- Does not support `FULL JOIN` or `FULL OUTER JOIN`.
- The official documentation also omits any mention of this.

### Others (SQLite, PostgreSQL, OracleDB)
- Support `FULL JOIN` and `FULL OUTER JOIN` per SQL standard.