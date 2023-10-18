
import re

################################################################


def parse_select_operation(query_tokens):
    # Initialize variables to store parsed information
    operation = None
    columns = None
    table = None
    conditions = None

    # Loop through the tokens to identify the operation and extract relevant information
    for i, token in enumerate(query_tokens):
        if token == 'select':
            operation = 'select'
            columns = []
            j = i + 1
            while j < len(query_tokens) and query_tokens[j] != 'from':
                columns.append(query_tokens[j])
                j += 1
        elif token == 'from':
            table = query_tokens[i + 1]
        elif token == 'where':
            conditions = ' '.join(query_tokens[i + 1:])

    if operation == 'select':
        return {
            'operation': operation,
            'columns': columns,
            'table': table,
            'conditions': conditions
        }
    else:
        raise ValueError('Invalid SQL statement')


################################################################


def parse_insert_operation(query_tokens):
    operation = 'insert'
    table = None
    columns = None
    values = None

    # Find the table name
    table_index = query_tokens.index('into') + 1
    table = query_tokens[table_index]

    # Find the start and end positions of the column names
    columns_start = query_tokens.index('(')
    columns_end = query_tokens.index(')')

    # Extract column names from tokens
    columns = query_tokens[columns_start + 1:columns_end]

    # Find the start and end positions of the values
    values_start = query_tokens.index('values') + 1
    values_end = query_tokens.index(';')

    # Extract values from tokens
    values = query_tokens[values_start:values_end]

    return {
        'operation': operation,
        'table': table,
        'columns': columns,
        'values': values
    }

################################################################


def parse_update_operation(tokens):
    # Initialize variables to store parsed information
    operation = None
    table = None
    set_values = {}
    conditions = None

    # Iterate through the tokens to identify the operation and extract relevant information
    i = 0
    while i < len(tokens):
        token = tokens[i]

        if token.upper() == 'UPDATE':
            operation = 'UPDATE'
            table = tokens[i + 1]
            i += 2  # Skip the table name

        if token.upper() == 'SET':
            i += 1  # Skip 'SET' keyword

            # Parse the column-value pairs in the 'SET' clause
            while i < len(tokens) and tokens[i].upper() != 'WHERE':
                column = tokens[i]
                i += 2  # Skip column name and '='
                value = tokens[i]
                set_values[column] = value
                i += 1  # Move to the next token

        if token.upper() == 'WHERE':
            conditions = ' '.join(tokens[i + 1:])
            break  # No need to continue parsing

        i += 1

    if operation == 'UPDATE':
        return {
            'operation': operation,
            'table': table,
            'set_values': set_values,
            'conditions': conditions
        }
    else:
        raise ValueError('Invalid SQL UPDATE statement')


################################################################


def parse_delete_operation(tokens):
    # Initialize variables to store parsed information
    operation = None
    table = None
    conditions = None

    # Iterate through the tokens to identify the operation and extract relevant information
    i = 0
    while i < len(tokens):
        token = tokens[i]

        if token.upper() == 'DELETE':
            operation = 'DELETE'

            # Check if the next token is 'FROM'
            if i + 1 < len(tokens) and tokens[i + 1].upper() == 'FROM':
                i += 2  # Skip 'FROM' keyword

                # The next token should be the table name
                if i < len(tokens):
                    table = tokens[i]
                else:
                    raise ValueError(
                        'Invalid DELETE statement: Table name missing')
                i += 1  # Move to the next token
            else:
                raise ValueError(
                    'Invalid DELETE statement: "FROM" keyword missing')

        if token.upper() == 'WHERE':
            # The rest of the tokens are part of the conditions
            conditions = ' '.join(tokens[i + 1:])
            break  # No need to continue parsing

        i += 1

    if operation == 'DELETE':
        return {
            'operation': operation,
            'table': table,
            'conditions': conditions
        }
    else:
        raise ValueError('Invalid SQL DELETE statement')

################################################################


def lex_sql_query(query):
    # Define regular expressions for various SQL components
    keywords = r'(SELECT|INSERT|UPDATE|DELETE|FROM|INTO|SET|VALUES|WHERE)'
    identifiers = r'(\w+)'
    strings = r"'(.*?)'"
    numbers = r'(\d+)'
    operators = r'([=<>]+)'
    punctuation = r'([(),;])'

    # Combine regular expressions into a single pattern
    pattern = f'{keywords}|{identifiers}|{strings}|{numbers}|{operators}|{punctuation}'

    # Use re.findall to tokenize the query
    tokens = re.findall(pattern, query, re.IGNORECASE)

    # Flatten the list of tuples into a list of strings
    tokens = [token for group in tokens for token in group if token]

    return tokens


def parse_sql_query(query):
    # Convert the query to lowercase
    query = query.lower()

    # Remove semicolon if it exists
    if query.endswith(';'):
        query = query[:-1]

    # Split the SQL statement into words and remove extra whitespace
    tokens = lex_sql_query(query)

    # Check if the query is empty or doesn't start with a recognized SQL operation
    if not tokens:
        raise ValueError("Empty SQL query")
    if tokens[0] == "select":
        return parse_select_operation(tokens)
    if tokens[0] == "insert":
        return parse_insert_operation(tokens)
    if tokens[0] == "update":
        return parse_update_operation(tokens)
    if tokens[0] == "delete":
        return parse_delete_operation(tokens)
    else:
        raise ValueError("Unsupported SQL operation")


################################################################


# Example usage:
# sql_query = "SELECT column1, column2 FROM table1 WHERE column3 = 'value';"
# sql_query = """
# INSERT INTO employees (first_name, last_name, job_title, salary)
# VALUES ('John', 'Doe', 'Software Engineer', 75000),
#        ('Jane', 'Smith', 'Data Analyst', 60000),
#        ('Bob', 'Johnson', 'Project Manager', 85000);
#        """
# sql_query = "UPDATE employees SET salary = 75000 WHERE department = 'Engineering';"
sql_query = "DELETE FROM employees WHERE department = 'engineering' AND salary < 60000;"

parsed_data = parse_sql_query(sql_query)
print(parsed_data)
