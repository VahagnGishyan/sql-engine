
import unittest
from database.database import Database
from database.table import Table
from database.column import Column, ColumnElement
from sqlinterp.operations import InsertInto


class TestInsert(unittest.TestCase):
    def setUp(self):
        # Create a table and insert data
        self.table = Table("MyTable")
        self.table.add_column("Name", "text")
        self.table.add_column("Age", "integer")
        self.table.add_column("City", "date")
        self.table.add_column("Completed", "boolean")
        data_to_insert = [
            [
                {"column-name": "Name", "value": "John"},
                {"column-name": "Age", "value": 25},
                {"column-name": "City", "value": "New York"},
                {"column-name": "Completed", "value": True}
            ],
            [
                {"column-name": "Name", "value": "Alice"},
                {"column-name": "Age", "value": 30},
                {"column-name": "City", "value": "Los Angeles"},
                {"column-name": "Completed", "value": False}
            ],
            [
                {"column-name": "Name", "value": "Bob"},
                {"column-name": "Age", "value": 35},
                {"column-name": "City", "value": "Chicago"},
                {"column-name": "Completed", "value": True}
            ]
        ]
        for row in data_to_insert:
            self.table.insert_data(row)


if __name__ == '__main__':
    unittest.main()
