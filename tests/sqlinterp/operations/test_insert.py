
import unittest
from database.database import Database
from database.row import Row
from database.table import Table
from sqlinterp.operations import InsertInto


class TestInsertOperation(unittest.TestCase):
    def test_insert_data(self):
        # Create a sample table
        table = Table("TestTable")
        table.add_column("Name", "text")
        table.add_column("Age", "integer")
        table.add_column("Active", "boolean")

        # Create an instance of the InsertInto operation

        # Define the data to insert
        data_to_insert = [
            {"column-name": "Name", "value": "John"},
            {"column-name": "Age", "value": 30},
            {"column-name": "Active", "value": True},
        ]
        insert_operation = InsertInto(data_to_insert)

        # Execute the insert operation
        result = insert_operation.execute(table)

        # Check if the data was inserted correctly
        self.assertTrue(result)
        self.assertEqual(len(table.columns[0]), 1)

        inserted_row: Row = table.get_rows()[0]
        self.assertEqual(inserted_row.row_elements[0].value, "John")
        self.assertEqual(inserted_row.row_elements[1].value, 30)
        self.assertEqual(inserted_row.row_elements[2].value, True)


if __name__ == '__main__':
    unittest.main()
