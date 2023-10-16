import unittest
# Import the Database class and the 'table' alias from the 'database' module
from database import database as db
from database import file_manager as fm
from database import constraints as cstr
from utility import file as utfile


# Step 0: Set data names
db_path = fm.FileManager.get_work_dir()
db_name = "ToDoListEmptyDB"
table_name = "ToDoList"


class CaseToDoListEmpty(unittest.TestCase):
    def test_to_do_list_db_empty(self):
        # Step 1: Create a database
        todo_db = db.Database.create(db_name, db_path, connect=True)

        self.assertTrue(todo_db.is_connected())
        self.assertEqual(len(todo_db.list_tables()), 0)

        # Step 2: Create a table for the to-do list tasks
        todo_table = todo_db.create_table(table_name)
        self.assertEqual(len(todo_db.list_tables()), 1)
        self.assertEqual(len(todo_table), 0)

        # Step 3: Define columns for the to-do list tasks
        todo_table.add_column("Name", "text", [cstr.ConstraintNotNull()])
        todo_table.add_column("Description", "text", [
                              cstr.ConstraintNotNull()])
        todo_table.add_column("DueDate", "date", [cstr.ConstraintNotNull()])
        todo_table.add_column("Completed", "boolean", [
            cstr.ConstraintDefault(False)])

        self.assertEqual(len(todo_table), 4)

        # Step 4: Add data to columns
        taskList = [
            [("Name", "Task 1"), ("Description", "Description 1"),
             ("DueDate", "2023-10-15"), ("Completed", False)],
            [("Name", "Task 2"), ("Description", "Description 2"),
             ("DueDate", "2023-10-16"), ("Completed", True)],
            [("Name", "Task 3"), ("Description", "Description 3"),
             ("DueDate", "2023-10-17"), ("Completed", False)],
            [("Name", "Task 4"), ("Description", "Description 4"),
             ("DueDate", "2023-10-18"), ("Completed", True)],
        ]
        for task in taskList:
            todo_table.insert_data(task)

        self.assertEqual(len(todo_table.get_rows()), 4)

        db_work_dir = todo_db.get_path()
        db_tables_dir = todo_db.get_tables_dir_path()
        todo_db.disconnect()
        self.assertFalse(utfile.is_dir_empty(db_tables_dir))
        # utfile.rmdir(db_work_dir)


if __name__ == '__main__':
    unittest.main()
