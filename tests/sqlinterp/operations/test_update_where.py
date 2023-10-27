import unittest
from database.database import Database
from sqlinterp.operations import Update
from database.table import Table
from database.row import Row
from sqlinterp.parser import Equal, NotEqual
from sqlinterp.parser import GreaterThan, LessThan
from sqlinterp.parser import GreaterThanOrEqualTo, LessThanOrEqualTo
from utility import console


class TestUpdateOperation(unittest.TestCase):
    def get_table(self):
        db = Database.create("MyDatabase")
        table = db.create_table("MyTable")
        table.add_column("Name", "text")
        table.add_column("Age", "integer")
        table.add_column("Active", "boolean")

        taskList = [
            [
                {"column-name": "Name", "value": "John"},
                {"column-name": "Age", "value": 30},
                {"column-name": "Active", "value": True},
            ],
            [
                {"column-name": "Name", "value": "Alice"},
                {"column-name": "Age", "value": 25},
                {"column-name": "Active", "value": False},
            ],
            [
                {"column-name": "Name", "value": "Bob"},
                {"column-name": "Age", "value": 35},
                {"column-name": "Active", "value": True}
            ]
        ]

        for task in taskList:
            table.insert_data(task)
        return table

    def test_update_completed_true(self):
        table = self.get_table()
        # Test updating rows where Completed is True
        condition = Equal("Name", "John")

        data_to_update = [
            {"column-name": "Age", "value": 35},
            {"column-name": "Active", "value": False},
        ]

        # Create an instance of the Update operation
        update_operation = Update(data_to_update, condition)

        row_column_before = len(table.columns)
        row_count_before = len(table.columns[0])

        # Execute the update operation
        update_operation.execute(table)

        row_column_after = len(table.columns)
        row_count_after = len(table.columns[0])

        self.assertEqual(row_column_before, row_column_after)
        self.assertEqual(row_count_before, row_count_after)

        updated_table = table
        # Check that rows where Completed is True have been updated
        for row in updated_table.get_rows():
            if row.elements[2] is False:
                self.assertEqual(row.elements[1], 35)

    def test_update_age_greater_than(self):
        table = self.get_table()

        data_to_update = [
            {"column-name": "Active", "value": False},
        ]
        condition = GreaterThan("Age", 18)
        update_operation = Update(data_to_update, condition)
        update_operation.execute(table)
        updated_table = table
        # Check that rows with DueDate greater than "2023-10-16" have been updated
        for row in updated_table.get_rows():
            if row.elements[1].get_value() > 18:
                self.assertEqual(row.elements[2].get_value(), False)

    def test_update_age_less_than(self):
        table = self.get_table()
        data_to_update = [
            {"column-name": "Name", "value": "Taron"},
        ]
        condition = LessThan("Age", 35)
        update_operation = Update(data_to_update, condition)
        update_operation.execute(table)
        updated_table = table
        # Check that rows with Name less than "Task 3" have been updated
        for row in updated_table.get_rows():
            if row.elements[1].get_value() < 35:
                self.assertEqual(row.elements[0].get_value(), "Taron")


if __name__ == '__main__':
    unittest.main()
