# Inconsistency 2

### Behavior of `CAST(... AS INT)`

DBMSs differ in how they handle casting values to integers. Some truncate toward zero, others round half-up or round-to-even. Overflow handling and support for various numeric types also vary. Documentation is often incomplete or vague, especially regarding rounding rules and overflow behavior.

## Behavior by DBMS

### SQLite
- Always truncates toward zero (`1.9 → 1`, `-1.9 → -1`).
- Clamps values outside 64-bit signed range to INT64 bounds.
- Behavior is explicitly documented.

### MySQL
- Uses `CAST(... AS SIGNED)` syntax.
- Rounds half-up (`0.5` → `1`).
- Target type is `BIGINT` (64-bit signed integer).
- Overflow behavior:
  - Floats: aLways clamped to `BIGINT` limits with a warning.
  - Negative integers: always clamped to `BIGINT` limits with a warning.
  - Positive integers: 
    - Up to `9223372036854775807`: accepted.
    - `9223372036854775808` to `18446744073709551615`: wraps via two's complement.
    - Greater than `18446744073709551615`: clamps to `BIGINT` limits with a warning.
- Documentation only states: *"Produces a signed `BIGINT` value."* 

### MariaDB
- Matches MySQL:
  - Rounds half-up.
  - Target type is `BIGINT`.
  - Overflow follows the same clamping and wrapping behavior.
- Documentation lacks any detailed explanation of rounding or overflow behavior.

### PostgreSQL
- For literals, `NUMERIC`, and `DECIMAL`: rounds half-up.
- For `REAL` (`FLOAT`) and `DOUBLE PRECISION`: uses IEEE 754 round-to-even.
- Uses 4 byte signed integers.
- Overflow raises an error.
- Documentation only provides general descriptions (e.g., supported types), and lacks specific information on rounding behavior, range, and overflow handling.

### OracleDB
- Rounds half-up.
- Supports dynamic integer range.
- Overflow triggers an error.
- Documentation offers general casting behavior but lacks detailed coverage of rounding rules and overflow handling.
