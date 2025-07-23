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
| 2 | All | Behavior of `CAST(... AS INT)` | [🔗](./incon2.md) Behavior of casting to integers varies in terms of rounding, range, and overflow handling. |
| 3 | All | Return type of division | [🔗](./incon3.md) Integer division returns different types. |
| 4 | MySQL, MariaDB | `FULL JOIN` / `FULL OUTER JOIN` | [🔗](./incon4.md) Although part of the SQL standard, some systems do not support `FULL [OUTER] JOIN` and omit this in documentation. |
| 5 | All | Precision of real numbers in `JSON` | [🔗](./incon5.md) Precision for real numbers stored in JSON differs by system and is often underdocumented. |
| 6 | PostgreSQL, Oracle | Sorting behavior for `JSON` (`ORDER BY`) | [🔗](./incon6.md) Sorting behavior for `JSON` values differs across systems, and documentation is often incomplete. |
| 7 | All | `LENGTH` on `JSON` data | [🔗](./incon7.md) The `LENGTH` function behaves inconsistently on `JSON` values, with ambiguous or missing documentation in some cases. |
| 8 | All | Index access on non-array `JSON` data | [🔗](./incon8.md) Behavior differs when applying array selectors to non-array `JSON` values. |



## Statistics

- **Total Bugs Found**: 11
- **Verified/Fixed**: 11 / 6
- **Total Inconsistencies**: 8
