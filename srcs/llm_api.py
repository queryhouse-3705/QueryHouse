from openai import OpenAI
client = OpenAI()

def query_chatgpt(input_query):

    completion = client.chat.completions.create(
        model="gpt-4o-2024-08-06",
        messages=[
            {
                "role": "system",
                "content": """You are an innovative SQL query generator for DBMS fuzz testing. Given a previously executed query, produce a single-line, complex, diverse SQLite query that satisfies the following requirements:

1. Syntactic and semantic correctness under SQLite.
2. Starting from an empty database, include multiple statements for:
  - Schema creation
  - Data population
  - Schema and data manipulation
  - Data retrieval
3. Use only these data types: TEXT, VARCHAR, CHAR, INTEGER, FLOAT, DOUBLE, JSON.
4. Output format: one line of plain text, without comments, explanations, code blocks, or formatting tags.
5. Exclude these keywords and features:
  - LENGTH(), RANDOM()
  - Referential actions: ON UPDATE ..., SET DEFAULT, RESTRICT
  - FULL OUTER JOIN, OUTER JOIN, FULL JOIN
  - JSON related operations other than ->'$.'
  - DCL, TCL statements
6. Prohibited patterns:
  - GENERATED columns in ALTER or UPDATE
  - GENERATED JSON columns or those with UNIQUE constraints
  - Indexes on TEXT or JSON columns
  - JSON columns as FOREIGN KEY
  - ORDER BY on JSON columns
  - Table aliases for joined tables
7. Validity constraints:
  - Every referenced key must be UNIQUE or PRIMARY KEY.
  - [INNER] JOIN and LEFT/RIGHT [OUTER] JOIN clauses must include join conditions using ON or USING. CROSS JOIN and NATURAL JOIN clauses must not include any join conditions.
  - WITH and WITH RECURSIVE clauses:
    - Only before SELECT, with no column list after the CTE name.
    - WITH RECURSIVE must define column aliases in its first SELECT, use UNION ALL at most once, and include LIMIT n in the recursive part.
    - Example: WITH RECURSIVE cte1 AS (SELECT 1 AS y UNION ALL SELECT y+1 FROM cte1 WHERE y<10 LIMIT 10) SELECT y FROM cte1;

Generate a query that strictly complies with all of the above."""
            },
            {
                "role": "user",
                "content": f"""{input_query}"""
            }
        ]
    )
    
    message_content = completion.choices[0].message.content

    message_content = message_content.replace("\n", "")
    message_content = message_content.replace("```sql", "").replace("```", "")
    message_content = message_content.strip()

    return message_content

