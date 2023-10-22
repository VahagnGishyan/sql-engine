
import re
from sqlinterp import operations as op

from sqlinterp.conditions import Condition
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo
from sqlinterp.conditions import LessThan, LessThanOrEqualTo

from utility import console

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

    def parse(self, query: str) -> map:
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

    def parse(self, query: str) -> map:
        # Convert the query to lowercase
        # query = query.lower()

        # Split the SQL statement into words and remove extra whitespace
        tokens = self.lex(query)

        if tokens[-1] == ';':
            tokens = tokens[:-1]

        # Check if the query is empty or doesn't start with a recognized SQL operation
        if not tokens:
            raise ValueError("Empty SQL query")
        if tokens[0].lower() == "select":
            return self.parse_select_operation(tokens)
        if tokens[0].lower() == "insert":
            return self.parse_insert_operation(tokens)
        if tokens[0].lower() == "update":
            return self.parse_update_operation(tokens)
        if tokens[0].lower() == "delete":
            return self.parse_delete_operation(tokens)
        else:
            raise ValueError("Unsupported SQL operation")

    #########################################################

    def token_is_operator(self, token: str) -> bool:
        operators = ['==', '!=', '<', '>', '<=', '>=']
        return token in operators

    def token_is_logic_operator(self, token: str) -> bool:
        logic_operators = ['and', 'or']
        return token.lower() in logic_operators

    def lex_conds(self, conds: list[str]) -> map:
        info = {
            "operands": [],
            "operator": [],
            "logic-operator": []
        }

        for token in conds:
            if self.token_is_operator(token):
                info["operator"].append(token)
                continue
            if self.token_is_logic_operator(token):
                info["logic-operator"].append(token)
                continue
            info["operands"].append(token)

        return info

    def lex_sql_query(self, query):
        # Define regular expressions for various SQL components
        keywords = r'(SELECT|INSERT|UPDATE|DELETE|FROM|INTO|SET|VALUES|WHERE)'
        identifiers = r'(\w+)'
        strings = r"'(.*?)'"
        numbers = r'(\d+)'
        operators = r'([=<>]+)'
        punctuation = r'([(),;])'

        # Combine regular expressions into a single pattern
        pattern = f'{keywords}|{identifiers}|{strings}|{numbers}|{operators}|{punctuation}'

        if not isinstance(query, str):
            raise ValueError("The 'query' must be a string.")

        # Use re.findall to tokenize the query
        tokens = re.findall(pattern, query, re.IGNORECASE)

        # Flatten the list of tuples into a list of strings
        tokens = [token for group in tokens for token in group if token]

        return tokens

    def get_next_operation(self, parsed_conds: map) -> (map, list[str]):
        operands: list = parsed_conds["operands"]
        value = operands.pop()
        column_name = operands.pop()
        operators: list = parsed_conds["operator"]
        operator = operators.pop()
        return (parsed_conds, [value, column_name, operator])

    def parsed_conds_to_ast_list(self, parsed_conds: map) -> list[str]:
        ast_list: list[str]
        parsed_conds, ast_list = self.get_next_operation(parsed_conds)
        while parsed_conds["logic-operator"]:
            logic_operator = parsed_conds["logic-operator"].pop()
            parsed_conds, next_oper = self.get_next_operation(parsed_conds)
            ast_list = ast_list + next_oper
            ast_list.append(logic_operator)
        return ast_list

    def convert_value(self, param: str):
        if param.lower() == "true":
            return True
        elif param.lower() == "false":
            return False
        try:
            value = int(param)
            return value
        except ValueError:
            return param

    def get_next_condition_operands(self, tokens: list):
        column_name = tokens.pop()
        value = self.convert_value(tokens.pop())
        return (column_name, value, tokens)

    def get_next_condition(self, tokens: list[str]):
        token = tokens.pop()

        if token.lower() == 'and':
            tokens, condition = self.get_next_condition(tokens)
            tokens, second_condition = self.get_next_condition(tokens)
            return (tokens, And(condition, second_condition))
        elif token.lower() == 'or':
            tokens, condition = self.get_next_condition(tokens)
            tokens, second_condition = self.get_next_condition(tokens)
            return (tokens, Or(condition, second_condition))
        elif token.lower() == 'not':
            tokens, condition = self.get_next_condition(tokens)
            return (tokens, Not(condition))

        column_name, value, tokens = self.get_next_condition_operands(tokens)

        if token == '==':
            return (tokens, Equal(column_name, value))
        elif token == '!=':
            return (tokens, NotEqual(column_name, value))
        elif token == '>':
            return (tokens, GreaterThan(column_name, value))
        elif token == '>=':
            return (tokens, GreaterThanOrEqualTo(column_name, value))
        elif token == '<':
            return (tokens, LessThan(column_name, value))
        elif token == '<=':
            return (tokens, LessThanOrEqualTo(column_name, value))
        else:
            raise ValueError(f"Unsupported token: {token}")

    def get_condition(self, tokens: list):
        tokens, condition = self.get_next_condition(tokens)
        if tokens:
            raise Exception("tokens is not empty.")
        return condition

    def parse_condition(self, conds: list[str]) -> Condition:
        # console.PrintDebug("conds[list]:  " + " ".join(conds))
        parsed_conds = self.lex_conds(conds)
        # console.PrintDebug("parsed[list]")
        # console.PrintDebug("\toperands: " + " ".join(parsed_conds["operands"]))
        # console.PrintDebug("\toperator: " + " ".join(parsed_conds["operator"]))
        # console.PrintDebug("\tlogic-operator: " +
        #    " ".join(parsed_conds["logic-operator"]))
        ast_list = self.parsed_conds_to_ast_list(parsed_conds)
        # console.PrintDebug("ast[list]:    " + " ".join(ast_list))
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
            if token.lower() == 'select':
                operation = 'select'
                columns = []
                j = i + 1
                while j < len(tokens) and tokens[j].lower() != 'from':
                    if tokens[j] != ',':
                        columns.append(tokens[j])
                    j += 1
            elif token.lower() == 'from':
                table = tokens[i + 1]
            elif token.lower() == 'where':
                conditions = ' '.join(tokens[i + 1:])

        parsed_data = {
            'operation': operation,
            'columns': columns,
            'table': table,
            'conditions': conditions
        }
        return ({"table-name": table, "parsed-query":  parsed_data})

    def parse_select_operation(self, tokens: list[str]) -> map:
        result = self.get_parsed_select_query(tokens)
        conditionStr = result["parsed-query"]["conditions"]
        condition_tokens = self.lex_sql_query(conditionStr)
        condition = self.parse_condition(condition_tokens)
        operation = op.Select(result["parsed-query"]["columns"], condition)
        return ({"table-name": result["table-name"], "operation": operation})

    #########################################################

    def get_parsed_insert_query(self, tokens: list[str]) -> map:
        # Initialize variables
        operation = None
        table = None
        columns = []
        values = []

        # Iterate through tokens
        i = 0
        while i < len(tokens):
            token = tokens[i]

            if token.upper() == 'INSERT':
                operation = 'INSERT'
            elif token.upper() == 'INTO':
                # Next token should be the table name
                table = tokens[i + 1]
                i += 1
            elif token == '(':
                # Collect columns within parentheses
                i += 1
                while tokens[i] != ')':
                    if tokens[i] != ',':
                        columns.append(tokens[i])
                    i += 1
            elif token.upper() == 'VALUES':
                # Collect values within parentheses
                i += 2
                while tokens[i] != ')':
                    if tokens[i] != ',':
                        values.append(tokens[i])
                    i += 1
            i += 1

        column_value_list = []
        assert (len(columns) == len(values))
        for i in range(len(columns)):
            column_value_list.append(
                {"column-name": columns[i], "value": values[i]})

        # Create the parsed_data object
        parsed_data = {
            'operation': operation,
            'values': column_value_list
        }
        return ({"table-name": table, "parsed-query":  parsed_data})

    def parse_insert_operation(self, tokens: list[str]) -> map:
        result = self.get_parsed_insert_query(tokens)
        operation = op.InsertInto(result["parsed-query"]["values"])
        return ({"table-name": result["table-name"], "operation": operation})

    #########################################################

    def get_parsed_update_query(self, tokens: list[str]) -> map:
        # Initialize variables to store parsed information
        operation = None
        table = None
        values = []
        conditions = None

        # Iterate through the tokens to identify the operation and extract relevant information
        # console.PrintSignal("parse_update_operation")
        i = -1
        while i < len(tokens):
            i += 1
            token = tokens[i]
            if token.upper() == 'UPDATE':
                # console.PrintInfo(f"token: {token}, type-is: operation")
                operation = 'UPDATE'
                i += 1  # get the table name
                table = tokens[i]
                # console.PrintInfo(f"token: {table}, type-is: table")
                continue
            if token.upper() == 'SET':
                # console.PrintInfo(f"token: {token}, type-is: set")
                i += 1  # Skip 'SET' keyword
                # Parse the column-value pairs in the 'SET' clause
                while i < len(tokens):
                    column = tokens[i]
                    i += 2  # Skip column name and '='
                    value = tokens[i]
                    values.append({"column-name": column, "value": value})
                    # console.PrintInfo(f"column-name: {column}, value: {value}")
                    i += 1  # Move to the next token
                    token = tokens[i]
                    # console.PrintInfo(f"SET, next token is: {token}")
                    if token == ',':
                        i += 1  # Move to the next token
                    if tokens[i].upper() == 'WHERE':
                        i -= 1  # Move to the next token
                        break
                continue
            if token.upper() == 'WHERE':
                # console.PrintInfo(f"token: {token}, type-is: WHERE")
                conditions = ' '.join(tokens[i + 1:])
                break  # No need to continue parsing

            i += 1  # get the table name

            console.PrintInfo(f"token: {token}, unexpected token")
            raise Exception(f"token: {token}, unexpected token")

        return {
            'operation': operation,
            'table': table,
            'values': values,
            'conditions': conditions
        }

    def parse_update_operation(self, tokens: list[str]) -> map:
        result = self.get_parsed_update_query(tokens)
        conditionStr = result["conditions"]
        condition_tokens = self.lex_sql_query(conditionStr)
        condition = self.parse_condition(condition_tokens)
        operation = op.Update(result["values"],  condition)
        return ({"table-name": result["table"], "operation": operation})

    #########################################################

    def get_parsed_delete_query(self, tokens: list[str]) -> map:
        # Initialize variables to store parsed information
        operation = None
        table = None
        conditions = None

        # Iterate through the tokens to identify the operation and extract relevant information
        i = 0
        while i < len(tokens):
            token = tokens[i]
            if token.lower() == 'delete':
                operation = token

                # Check if the next token is 'FROM'
                if i + 1 < len(tokens) and tokens[i + 1].lower() == 'from':
                    i += 1  # Skip 'FROM' keyword

                    # The next token should be the table name
                    if i < len(tokens):
                        table = tokens[i + 1]
                    else:
                        raise ValueError(
                            'Invalid DELETE statement: Table name missing')
                    i += 1  # Move to the next token
                else:
                    raise ValueError(
                        'Invalid DELETE statement: "FROM" keyword missing')

            if token.lower() == 'where':
                # The rest of the tokens are part of the conditions
                conditions = ' '.join(tokens[i + 1:])
                break  # No need to continue parsing

            i += 1

        return {
            'operation': operation,
            'table': table,
            'conditions': conditions
        }

    def parse_delete_operation(self, tokens: list[str]) -> map:
        result = self.get_parsed_delete_query(tokens)
        # console.PrintSignal(f"tokens: {tokens}")
        # console.PrintSignal(f"result: {result}")
        conditionStr = result["conditions"]
        # console.PrintSignal(f"conditionStr: {conditionStr}")
        condition_tokens = self.lex_sql_query(conditionStr)
        # console.PrintSignal(f"condition_tokens: {condition_tokens}")
        condition = self.parse_condition(condition_tokens)
        # console.PrintSignal(f"condition: ")
        # condition.print()
        operation = op.Delete(condition)
        return ({"table-name": result["table"], "operation": operation})


#############################################################
#                                                           #
#############################################################
