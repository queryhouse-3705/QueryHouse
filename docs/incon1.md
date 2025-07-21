# Inconsistency 1

### Implicit Comparison Between Textual and Numeric Data

Some DBMSs allow implicit comparisons between strings and numbers, while others raise errors. When permitted, the destination type and casting rules differ between systems. These behaviors are often poorly or ambiguously documented, making them prone to misinterpretation.

## Behavior by DBMS

### SQLite
- Strings are treated as greater than numbers in literal comparisons.
- Implicit casting depends on the column type, if one is defined.

### MySQL
- Strings are implicitly cast to `DOUBLE`.
- Only decimal-formatted strings are accepted.
- Invalid conversions of `VARCHAR` result in zero and a warning.
- Invalid conversions of `TEXT` result in zero but no warning.

### MariaDB
- Casts strings to `DECIMAL` if compared with integers, `DOUBLE` if compared with floats.
- Non-decimal strings are truncated to zero, triggering a warning.

### PostgreSQL
- Strings are cast to `INT`, supporting decimal, binary, and hexadecimal formats, but not floats.
- Invalid casts raise an error.

### OracleDB
- Strings are cast to a numeric type (decimal only).
- Invalid conversions result in an error.
