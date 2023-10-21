import unittest
from database.table import Table
from sqlinterp.parser import SQLQuerySimpleParser


class TestSQLQueryParser(unittest.TestCase):
    def setUp(self):
        # Create an instance of the SQLQueryParser
        self.parser = SQLQuerySimpleParser()
        # Create a table for testing
        self.large_table = Table("large_table")

        # Add columns to the table
        self.large_table.add_column("column1", "text")
        self.large_table.add_column("column2", "int")
        self.large_table.add_column("column3", "text")

        # Populate the table with data
        taskList = [
            [
                {"column-name": "column1", "value": "value1"},
                {"column-name": "column2", "value": 42},
                {"column-name": "column3", "value": "foo"}
            ],
            [
                {"column-name": "column1", "value": "value2"},
                {"column-name": "column2", "value": 99},
                {"column-name": "column3", "value": "foo"}
            ],
            [
                {"column-name": "column1", "value": "value3"},
                {"column-name": "column2", "value": 123},
                {"column-name": "column3", "value": "bar"}
            ],
            [
                {"column-name": "column1", "value": "value4"},
                {"column-name": "column2", "value": 54},
                {"column-name": "column3", "value": "bar"}
            ]
        ]

        for row in taskList:
            self.large_table.insert_data(row)

    def test_delete_query(self):

        # Generate a SELECT SQL query
        query = "DELETE FROM employees WHERE column3 == 'bar' AND column2 > 62;"

        # Parse the query using the parser
        # return ({"table-name": result["table-name"], "operation": operation})
        parsed_query = self.parser.parse(query)
        operation = parsed_query["operation"]

        # Execute the parsed operation on the large table
        result = operation.execute(self.large_table)

        # Check the result using assertions
        self.assertIsNotNone(result)  # Ensure the result is not None

        # Check that the result is of the correct type, e.g., a Table
        self.assertIsInstance(result, Table)

        # Check the number of columns in the result
        self.assertEqual(len(result.columns), 3)

        # Check the number of rows in the result
        self.assertGreaterEqual(len(result.get_rows()), 0)

        # Add more specific assertions based on your expectations
        # For example, check if the rows in the result meet your conditions

        # Example: Check if all rows meet the condition column2 > 54
        for row in result.get_rows():
            column2_value = row.row_elements[1].get_value()
            self.assertLessEqual(column2_value, 62)  # Modify as needed

        # Add more assertions based on your specific query and expectations


if __name__ == '__main__':
    unittest.main()
