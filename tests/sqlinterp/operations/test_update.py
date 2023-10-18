import unittest
from sqlinterp.operations import Update
from database.table import Table
from database.row import Row
from sqlinterp.conditions import Equal, ConditionExecutor


class TestUpdateOperation(unittest.TestCase):
    def test_update_data(self):
        # Create a sample table
        table = Table("TestTable")
        table.add_column("Name", "text")
        table.add_column("Age", "integer")
        table.add_column("Active", "boolean")

        # Insert data into the table
        data_to_insert = [
            {"column-name": "Name", "value": "John"},
            {"column-name": "Age", "value": 30},
            {"column-name": "Active", "value": True},
        ]
        table.insert_data(data_to_insert)

        # Define the data to update
        data_to_update = [
            {"column-name": "Age", "value": 35},
            {"column-name": "Active", "value": False},
        ]

        # Create an instance of the Update operation
        update_operation = Update(data_to_update, [
                                  ConditionExecutor("Name", Equal("John"))])

        # Execute the update operation
        update_operation.execute(table)

        updated_row: Row = table.get_rows()[0]
        self.assertEqual(updated_row.row_elements[0].get_value(), "John")
        self.assertEqual(updated_row.row_elements[1].get_value(), 35)
        self.assertEqual(updated_row.row_elements[2].get_value(), False)


if __name__ == '__main__':
    unittest.main()
