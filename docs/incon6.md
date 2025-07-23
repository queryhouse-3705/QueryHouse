# Inconsistency 6

### Sorting Behavior for `JSON` (`ORDER BY`)

DBMSs differ in how they handle ordering `JSON` values. In some cases, documentation is incomplete or inconsistent with actual behavior.

## Behavior by DBMS

### SQLite
- Stores `JSON` as plain text, resulting in lexicographical ordering.
- Behavior is consistent but not explicitly documented in JSON-specific references.

### MySQL
- Sorting non-scalar `JSON` values is not supported and triggers a warning.
- This limitation is clearly stated in the official documentation.

### MariaDB
- Sorting behaves like string comparison.
- The behavior is clearly documented.

### PostgreSQL
- Ordering rules for `JSONB` are explicitly documented.
- Sorting of `JSON` values is not supported and raises an error, but this is not specified in the documentation.

### OracleDB
- Documentation states that native `JSON` values cannot be used with comparison operators or `ORDER BY`.
- In practice, no error or warning is raised, and values appear to be ordered lexicographically.
- However, the documentation does not explain the actual behavior when sorting is attempted.
