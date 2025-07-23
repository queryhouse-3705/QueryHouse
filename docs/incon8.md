# Inconsistency 8

### Index Access on Non-Array `JSON` Data

Accessing a non-array `JSON` value using an array-style selector (e.g., `$[0]`) results in inconsistent behavior across DBMSs. Behavior varies depending on the input format (e.g., JSON types vs. SQL types) and whether implicit coercion is applied. Documentation is generally insufficient, and many systems do not explicitly describe this edge case.

Example of non-array JSON values (SQLite syntax):
```sql
SELECT '{ "x" : 100 }' -> '$[0]';       -- JSON object
SELECT '100' -> '$[0]';                 -- JSON integer
```

## Behavior by DBMS

### SQLite
- Returns `NULL` for non-array `JSON` values.
- Documentation states that `NULL` is returned if the specified subcomponent does not exist.

### MySQL
- For index `0` on non-array `JSON` values, returns the entire value.
- For non-zero indices, returns `NULL`, though this is not documented.
- Only the case of index `0` returning the full value is described in the documentation.

### MariaDB
- Index `0` on non-array values returns the full value.
- Non-zero indices return `NULL`.
- This applies even to non-JSON values.
- Documentation mentions returning `NULL` when the path does not match, but does not explicitly define this specific behavior.

### PostgreSQL
- Returns `NULL` when indexing into non-array `JSON` values.
- Documentation explicitly states that unmatched paths return `NULL`.


### OracleDB
- For index `0`, returns the full value from non-array `JSON` inputs.
- Returns `NULL` for other unmatched indices.
- Documentation states that unmatched paths return `NULL`, but does not specifically address this selector case.
