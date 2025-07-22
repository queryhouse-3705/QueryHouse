# Inconsistency 5

### Precision of Real Numbers in `JSON`

DBMSs handle floating-point precision in JSON differently. In many cases, the default behavior for representing and preserving real-number precision is not clearly specified.

## Behavior by DBMS

### SQLite
- Works as the SQL `REAL`.
- Official documentation only states that `JSON_TYPE` returns `real`, and `JSON_EXTRACT` produces a `REAL` value.

### MySQL
- Works as the SQL `DOUBLE`.
- Documentation refers to JSON `DOUBLE` as "approximate-value numbers" and notes general issues with floating-point types, but lacks precise information about default precision.

### MariaDB
- Serialized as strings; precision depends on conversion routines.
- Documentation defines JSON `DOUBLE` loosely as *"a number with at least one floating point decimal,"* without specifying precision guarantees.

### PostgreSQL
- Maps JSON numeric values to the SQL `NUMERIC` type, as documented.
- `JSONB` rejects out-of-range numbers; `JSON` stores as text verbatim. This behavior implies more deterministic handling of precision.

### OracleDB
- Maps JSON numeric values to the SQL `BINARY_FLOAT`, `BINARY_DOUBLE`, or `NUMBER`.
- Documentation clearly outlines these mappings, which indirectly clarify how precision is handled.