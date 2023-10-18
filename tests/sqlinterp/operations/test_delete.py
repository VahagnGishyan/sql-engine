import unittest
from sqlinterp.operations import Delete
from database.table import Table
from sqlinterp.conditions import Equal, ConditionExecutor


class TestDeleteOperation(unittest.TestCase):
    def test_delete_data(self):
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

        # Create an instance of the Delete operation
        delete_operation = Delete([ConditionExecutor("Name", Equal("John"))])

        # Execute the delete operation
        delete_operation.execute(table)

        # Verify that the row with "Name" equal to "John" was deleted
        rows = table.get_rows()
        self.assertEqual(len(rows), 0)


if __name__ == '__main__':
    unittest.main()
