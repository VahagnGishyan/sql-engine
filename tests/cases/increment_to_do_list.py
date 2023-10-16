import unittest
# Import the Database class and the 'table' alias from the 'database' module
from database import database as db
from database import table as tb
from database import file_manager as fm
from database import constraints as cstr
from utility import file as utfile
import re

# Step 0: Set data names
db_path = fm.FileManager.get_work_dir()
db_name = "to-do-list-inc-db"
table_name_pattern = "to-do-list"


class DatabaseConnectionState(unittest.TestCase):
    def test_to_do_list_db(self):
        # Step 1: Create a database
        todo_db = db.Database.create(db_name, db_path, connect=True)

        self.assertTrue(todo_db.is_connected())

        self.assertEqual(len(todo_db.list_tables()), 1)
        table_name = todo_db.list_tables(table_name)[0]
        table = todo_db.get_table(table_name)
        if not isinstance(table, tb.Table):
            raise ValueError("Table must be instance of class Table.")
        self.assertEqual(len(table), 4)

        text = "to-do-list-42"
        pattern = r'\d+'
        match = re.search(pattern, text)

        number = None
        if match:
            # Extract the matched number and convert it to an integer
            number = int(match.group())
        if number is None:
            raise ValueError("No number found in the name of table.")

        new_index = number + 1
        new_table_name = f"{table_name_pattern}-{number}"
        new_table = todo_db.create_table(new_table_name)
        self.assertEqual(len(todo_db.list_tables()), 2)

        rows = table.get_rows()
        new_table.insert_rows(rows)
        self.assertEqual(len(new_table), 4)
        self.assertEqual(len(todo_db.list_tables()), 2)

        todo_db.drop_table(table_name)
        self.assertEqual(len(todo_db.list_tables()), 1)


if __name__ == '__main__':
    unittest.main()
