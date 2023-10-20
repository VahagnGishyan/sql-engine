
from sqlinterp.parser import SQLQueryParser, SQLQuerySimpleParser
from sqlinterp.conditions import ConditionExecutor
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo
from sqlinterp.conditions import LessThan, LessThanOrEqualTo

sql_query = "DELETE FROM employees WHERE department == 'engineering' AND salary < 60000;"
# sql_query = """
# INSERT INTO employees (first_name, last_name, job_title, salary)
# VALUES ('John', 'Doe', 'Software Engineer', 75000);
#    """
parser = SQLQuerySimpleParser()

parsed_query = parser.parse(sql_query)
table = parsed_query["table-name"]


print(f"sql-query: {sql_query}")
print(f"prs-query: table: {table}, oper: ", end="")
parsed_query["operation"].print()
