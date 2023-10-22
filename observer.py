
from sqlinterp.parser import SQLQueryParser, SQLQuerySimpleParser
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo
from sqlinterp.conditions import LessThan, LessThanOrEqualTo

# sql_query = "UPDATE employees SET salary = 75000, Active = true WHERE department = 'Engineering' and age >= 18;"
# sql_query = "DELETE FROM employees WHERE department == 'engineering' AND salary < 60000;"
# sql_query = """
# INSERT INTO employees (first_name, last_name, job_title, salary)
# VALUES ('John', 'Doe', 'Software Engineer', 75000);
#    """
parser = SQLQuerySimpleParser()

# sql_query = """
# INSERT INTO employees (first_name, last_name, job_title, salary)
# VALUES ('John', 'Doe', 'Software Engineer', 75000);
#    """
# sql_query = "UPDATE employees SET salary = 75000, Active = true WHERE department == 'Engineering' and age >= 18;"
sql_query = "DELETE FROM employees WHERE column3 == 'bar' AND column2 > 62;"

# print(f"sql-query: {sql_query}")
# sql_query = sql_query.lower()

# lexed_query = parser.lex(sql_query)
# print(f"lex-query: {lexed_query}")

# parsed_query_list = parser.get_parsed_insert_query(lexed_query)
# print(f"prs-query-list: {parsed_query_list}")

parsed_query = parser.parse(sql_query)
table = parsed_query["table-name"]
print(f"prs-query: table: {table}, oper: ", end="")
parsed_query["operation"].print()
