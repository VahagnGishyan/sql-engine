import unittest
from database.table import Table
from sqlinterp.parser import SQLQuerySimpleParser
from utility import console


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
        sql_query = """
        INSERT INTO employees (column1, column2, column3)
        VALUES ('value5', 4, 'jar');
           """

        # Parse the query using the parser
        # return ({"table-name": result["table-name"], "operation": operation})
        parsed_query = self.parser.parse(sql_query)
        operation = parsed_query["operation"]

        row_column_before = len(self.large_table.columns)
        row_count_before = len(self.large_table.columns[0])

        # Execute the parsed operation on the large table
        operation.execute(self.large_table)

        row_column_after = len(self.large_table.columns)
        row_count_after = len(self.large_table.columns[0])

        self.assertEqual(row_column_before, row_column_after)
        self.assertEqual(row_count_before + 1, row_count_after)

        # Add more specific assertions based on your expectations
        # For example, check if the rows in the result meet your conditions

        # Example: Check if all rows meet the condition column2 > 54
        last_row = self.large_table.get_rows()[-1]
        column1 = last_row.elements[0].get_value()
        column2 = last_row.elements[1].get_value()
        column3 = last_row.elements[2].get_value()

        self.assertEqual(column1, "value5")
        self.assertEqual(column2, 4)
        self.assertEqual(column3, "jar")


if __name__ == '__main__':
    unittest.main()
