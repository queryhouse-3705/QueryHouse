# Inconsistency 7

### `LENGTH` on `JSON` Data

The `LENGTH` function behaves inconsistently when applied to `JSON` data across DBMSs. Documentation is often vague or lacks any mention of how `JSON` values are handled, leading to potential confusion.

## Behavior by DBMS

### SQLite
- Returns the character length of the string.
- Documentation describes `JSON` as stored in text form and explains `LENGTH` behavior on text, which implies this behavior.

### MySQL
- Returns the byte length of the textual representation, despite `JSON` being stored in an internal binary format.
- Documentation explains `LENGTH` for strings, but does not mention behavior with `JSON`.

### MariaDB
- Returns the byte length of the string.
- `JSON` is stored as `LONGTEXT`, and general `LENGTH` behavior applies. Documentation implies this behavior.

### PostgreSQL
- Applying `LENGTH` to either `JSON` (text) or `JSONB` (binary) raises a type error.
- Documentation defines `length(text)`, but does not mention `JSON`, so lack of support is implied rather than explicitly stated.

### OracleDB
- Returns the byte length of the internal binary representation.
- Documentation defines `LENGTH` support for types like `VARCHAR2` and `CLOB`, but does not address behavior with native `JSON` types.
