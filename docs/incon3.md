# Inconsistency 3

### Return Type of Division

When using the division operator (`/`), the result type varies across DBMSs. Some systems return an integer when both operands are integers, truncating the result, while others return a floating-point value. The behavior is inconsistent, and in some cases, the official documentation lacks clear guidance.

## Behavior by DBMS

### SQLite
- Returns an integer when both operands are integers.
- Integer division truncates toward zero.

### MySQL
- Returns a real number, even when dividing integers.
- Resulting precision can be configured.

### MariaDB
- Same as MySQL: returns a real number.
- Resulting precision can be configured.

### PostgreSQL
- Returns an integer when both operands are integers; otherwise, returns a real number.
- Integer division truncates toward zero.

### OracleDB
- Returns a real number in all cases.
- Performs implicit promotion based on operand types.
- Documentation is ambiguous: does not explicitly state that integer operands are promoted to `NUMBER`, even when both operands are integers.