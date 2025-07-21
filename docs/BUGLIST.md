# Bug List

This document tracks bugs and inconsistencies discovered by QueryHouse..

## Bugs

| ID | DBMS | Description | Status | Report |
| --- | --- | --- | --- | --- |
| 1 | SQLite | `FILTER` not working in window function | Fixed | [🔗](https://sqlite.org/forum/forumpost/e9126d554a) |
| 2 | SQLite | `REAL` constant doubles | Fixed | [🔗](https://sqlite.org/forum/info/a81507e93557394e) |
| 3 | SQLite | `ROUND` function overflow | Fixed | [🔗](https://sqlite.org/forum/forumpost/170aeab92a) |
| 4 | SQLite | `SUBSTR` function overflow | Fixed | [🔗](https://sqlite.org/forum/forumpost/bfbb7d11c4) |
| 5 | MySQL | `BETWEEN` operator precedence mismatch | Verified | [🔗](http://bugs.mysql.com/116765) |
| 6 | MySQL | `IN` operator precedence mismatch | Verified | [🔗](http://bugs.mysql.com/117017) |
| 7 | MySQL | `MAX` as window aggregate returns `NULL` | Fixed | [🔗](http://bugs.mysql.com/117072) |
| 8 | MariaDB | `BETWEEN` operator precedence mismatch | Fixed | [🔗](https://jira.mariadb.org/browse/MDEV-35685) |
| 9 | Oracle | `LAG`/`LEAD` functon overflow | Verified | [🔗](https://forums.oracle.com/ords/apexds/post/bug-overflow-in-lag-value-expr-offset-window-function-3235) |
| 10 | Oracle | Incorrect result of multiple `NATURAL JOIN`s with ambiguous reference | Verified | [🔗](https://forums.oracle.com/ords/apexds/post/bug-report-multiple-natural-joins-with-ambiguous-reference-1406) |
| 11 | Oracle | `ROUND` function overflow | Verified | [🔗](https://forums.oracle.com/ords/apexds/post/bug-overflow-in-round-n-integer-function-4753) |

## Inconsistencies

> Note: Detailed descriptions of each inconsistency are currently being prepared.

| ID | DBMSs | Feature | Description |
| --- | --- | --- | --- |
| 1 | All | Comparison between textual and numeric data | [🔗](./incon1.md) Some DBMSs allow implicit comparison between strings and numbers, others throw errors. |
| 2 | All | Rounding in `CAST AS INT` | <!-- [🔗](./incon2.md) --> Behavior of casting floats to integers varies: some truncate, others round. |
| 3 | All | Return type of division | <!-- [🔗](./incon3.md) --> Integer division returns different types—float or integer—depending on the DBMS. |
| 4 | MySQL, MariaDB | `FULL JOIN`/`FULL OUTER JOIN` | <!-- [🔗](./incon4.md) --> MySQL does not support `FULL OUTER JOIN` natively unlike other DBMSs. |
| 5 | MySQL | Precision of `JSON DOUBLE` | <!-- [🔗](./incon5.md) --> `DOUBLE` values in JSON may lose precision when serialized or queried. |
| 6 | PostgreSQL, Oracle | Sorting `JSON` | <!-- [🔗](./incon6.md) --> Sorting behavior for `JSON` values varies and may raise errors or return unexpected order. |
| 7 | MySQL | `LENGTH` on `JSON` types | <!-- [🔗](./incon7.md) --> `LENGTH()` returns byte length of JSON text, not element count, unlike other DBMSs. |
| 8 | All | Index access on non-array `JSON` data types | <!-- [🔗](./incon8.md) --> Using numeric keys on non-array JSON types is accepted by some DBMSs, but not others. |


## Statistics

- **Total Bugs Found**: 11
- **Verified/Fixed**: 11 / 6
- **Total Inconsistencies**: 8
