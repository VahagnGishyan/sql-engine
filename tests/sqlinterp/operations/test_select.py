
import unittest
from database.database import Database
from database.table import Table
from sqlinterp.operations import Select


class TestSelect(unittest.TestCase):
    def setUp(self):
        self.db = Database.create("MyDatabase")
        self.table = self.db.create_table("ToDoList")
        self.table.add_column("Name", "text")
        self.table.add_column("Description", "text")
        self.table.add_column("DueDate", "date")
        self.table.add_column("Completed", "boolean")

        taskList = [
            [
                {"column-name": "Name", "value": "Task 1"},
                {"column-name": "Description", "value": "Description 1"},
                {"column-name": "DueDate", "value": "2023-10-15"},
                {"column-name": "Completed", "value": False},
            ],
            [
                {"column-name": "Name", "value": "Task 2"},
                {"column-name": "Description", "value": "Description 2"},
                {"column-name": "DueDate", "value": "2023-10-16"},
                {"column-name": "Completed", "value": True},
            ],
            [
                {"column-name": "Name", "value": "Task 3"},
                {"column-name": "Description", "value": "Description 3"},
                {"column-name": "DueDate", "value": "2023-10-17"},
                {"column-name": "Completed", "value": False},
            ],
            [
                {"column-name": "Name", "value": "Task 4"},
                {"column-name": "Description", "value": "Description 4"},
                {"column-name": "DueDate", "value": "2023-10-18"},
                {"column-name": "Completed", "value": True}
            ]
        ]

        for task in taskList:
            self.table.insert_data(task)

    def test_select_all_columns(self):
        query = Select(["Name", "Description", "DueDate", "Completed"])
        result = query.execute(self.table)
        self.assertEqual(len(result.list_columns()),
                         len(self.table.list_columns()))
        self.assertEqual(len(result.get_rows()), 4)

    def test_select_specific_columns(self):
        query = Select(["Name", "Completed"])
        result = query.execute(self.table)
        self.assertEqual(len(result.list_columns()), 2)
        self.assertEqual(len(result.get_rows()), 4)


if __name__ == '__main__':
    unittest.main()
