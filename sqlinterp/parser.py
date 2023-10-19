
import re
from sqlinterp import operations as op

from sqlinterp.conditions import ConditionExecutor
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo
from sqlinterp.conditions import LessThan, LessThanOrEqualTo
#############################################################
#                                                           #
#############################################################

# Example usage:
# sql_query = "SELECT column1, column2 FROM table1 WHERE column3 = 'value';"
# sql_query = """
# INSERT INTO employees (first_name, last_name, job_title, salary)
# VALUES ('John', 'Doe', 'Software Engineer', 75000);
#    """
# sql_query = "UPDATE employees SET salary = 75000 WHERE department = 'Engineering';"
# sql_query = "DELETE FROM employees WHERE department = 'engineering' AND salary < 60000;"

#############################################################
#                                                           #
#############################################################


class SQLQueryParser:
    def lex(self, query: str) -> list[str]:
        pass

    def parse(self, query: str) -> op.Operation:
        pass


#############################################################
#                                                           #
#############################################################


class SQLQuerySimpleParser:
    def lex(self, query: str) -> list[str]:
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

        # Remove semicolon if it exists
        if tokens[:-1] == ';':
            tokens = tokens[:-1]

        return tokens

    def parse(self, query: str) -> op.Operation:
        # Convert the query to lowercase
        query = query.lower()

        # Split the SQL statement into words and remove extra whitespace
        tokens = self.lex(query)

        # Check if the query is empty or doesn't start with a recognized SQL operation
        if not tokens:
            raise ValueError("Empty SQL query")
        if tokens[0] == "select":
            return self.parse_select_operation(tokens)
        if tokens[0] == "insert":
            return self.parse_insert_operation(tokens)
        if tokens[0] == "update":
            return self.parse_update_operation(tokens)
        if tokens[0] == "delete":
            return self.parse_delete_operation(tokens)
        else:
            raise ValueError("Unsupported SQL operation")

    #########################################################

    def token_is_operator(self, token: str) -> bool:
        operators = ['==', '!=', '<', '>', '<=', '>=']
        return token in operators

    def token_is_logic_operator(self, token: str) -> bool:
        logic_operators = ['and', 'or']
        return token in logic_operators

    def lex_conds(self, conds: list[str]) -> list:
        info = {
            "operands": [],
            "operator": [],
            "logic-operator": []
        }

        for token in conds:
            print(f"token: {token} type: ", end="")
            if self.token_is_operator(token):
                print("operator")
                info["operator"].append(token)
                continue
            if self.token_is_logic_operator(token):
                print("logic-operator")
                info["logic-operator"].append(token)
                continue
            info["operands"].append(token)

        return info

    def get_operation(self, parsed_conds: map) -> (map, list[str]):
        operands: list = parsed_conds["operands"]
        value = operands.pop()
        column_name = operands.pop()
        operators: list = parsed_conds["operator"]
        operator = operators.pop()
        return [value, column_name, operator]

    def parsed_conds_to_ast_list(self, parsed_conds: map) -> list[str]:
        ast_list: list[str]
        parsed_conds, ast_list = self.get_operation(parsed_conds)
        while parsed_conds["logic-operator"]:
            logic_operator = parsed_conds["logic-operator"].pop()
            parsed_conds, next_oper = self.get_operation(parsed_conds)
            ast_list = ast_list + next_oper
            ast_list.append(logic_operator)
        return ast_list

    def get_next_condition_operands(self, tokens: list):
        column_name = tokens.pop()
        value = tokens.pop()
        return (column_name, value, tokens)

    def get_next_condition(self, tokens: list):
        token = tokens.pop()

        if token == 'and':
            tokens, condition = self.get_next_condition(tokens)
            tokens, second_condition = self.get_next_condition(tokens)
            return (tokens, And(condition, second_condition))
        elif token == 'or':
            tokens, condition = self.get_next_condition(tokens)
            tokens, second_condition = self.get_next_condition(tokens)
            return (tokens, Or(condition, second_condition))
        elif token == 'not':
            tokens, condition = self.get_next_condition(tokens)
            return (tokens, Not(condition))

        column_name, value, tokens = self.get_next_condition_operands(tokens)

        if token == '==':
            return (tokens, ConditionExecutor(column_name, Equal(value)))
        elif token == '!=':
            return (tokens, ConditionExecutor(column_name, NotEqual(value)))
        elif token == '>':
            return (tokens, ConditionExecutor(column_name, GreaterThan(value)))
        elif token == '>=':
            return (tokens, ConditionExecutor(column_name, GreaterThanOrEqualTo(value)))
        elif token == '<':
            return (tokens, ConditionExecutor(column_name, LessThan(value)))
        elif token == '<=':
            return (tokens, ConditionExecutor(column_name, LessThanOrEqualTo(value)))
        else:
            raise ValueError(f"Unsupported token: {token}")

    def get_condition(self, tokens: list):
        tokens, condition = self.get_next_condition(tokens)
        if tokens:
            raise Exception("tokens is not empty.")
        return condition

    def parse_conditions(self, conds: list[str]) -> list[ConditionExecutor]:
        parsed_conds = self.lex_conds(conds)
        ast_list = self.parsed_conds_to_ast_list(parsed_conds)
        condition = self.get_condition(ast_list)
        return condition

    #########################################################

    def get_parsed_select_query(self, tokens: list[str]) -> map:
        # Initialize variables to store parsed information
        operation = None
        columns = None
        table = None
        conditions = None

        # Loop through the tokens to identify the operation and extract relevant information
        for i, token in enumerate(tokens):
            if token == 'select':
                operation = 'select'
                columns = []
                j = i + 1
                while j < len(tokens) and tokens[j] != 'from':
                    if tokens[j] != ',':
                        columns.append(tokens[j])
                    j += 1
            elif token == 'from':
                table = tokens[i + 1]
            elif token == 'where':
                conditions = ' '.join(tokens[i + 1:])

        parsed_data = {
            'operation': operation,
            'columns': columns,
            'table': table,
            'conditions': conditions
        }
        return ({"table-name": table, "parsed-query":  parsed_data})

    def parse_select_operation(self, tokens: list[str]) -> op.Operation:
        result = self.get_parsed_select_query(tokens)
        condition = self.parse_conditions(result["conditions"])
        operation = op.Select(result["parsed-query"]["columns"], [condition])
        return ({"table-name": result["table-name"], "operation": operation})

    #########################################################

    def parse_insert_operation(self, tokens: list[str]) -> op.Operation:
        operation = 'insert'
        table = None
        columns = None
        values = None

        # Find the table name
        table_index = tokens.index('into') + 1
        table = tokens[table_index]

        # Find the start and end positions of the column names
        columns_start = tokens.index('(')
        columns_end = tokens.index(')')

        # Extract column names from tokens
        columns = tokens[columns_start + 1:columns_end]

        # Find the start and end positions of the values
        values_start = tokens.index('values') + 1
        values_end = tokens.index(';')

        # Extract values from tokens
        values = tokens[values_start:values_end]

        return {
            'operation': operation,
            'table': table,
            'columns': columns,
            'values': values
        }

    #########################################################

    def parse_update_operation(self, tokens: list[str]) -> op.Operation:
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

    #########################################################

    def parse_delete_operation(self, tokens: list[str]) -> op.Operation:
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

#############################################################
#                                                           #
#############################################################
