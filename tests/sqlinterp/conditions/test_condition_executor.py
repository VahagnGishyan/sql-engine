import unittest
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import ConditionExecutor
from sqlinterp.conditions import GreaterThan, LessThan, GreaterThanOrEqualTo, LessThanOrEqualTo
from database.database import Database
from database.file_manager import FileManager

db_path = FileManager.get_work_dir() + '/' + "test-dbase-dir"
db_name = "TestDB"
table_name = "TestConditionExecutor"


class TestConditionExecutor(unittest.TestCase):
    def setUp(self):
        todo_db = Database.create(db_name, db_path, connect=True)

        # Create a test table with columns
        self.table = todo_db.create_table(table_name)

        self.age_column = self.table.add_column("Age", "integer")
        self.salary_column = self.table.add_column("Salary", "real")
        self.name_column = self.table.add_column("Name", "text")

        # Insert data into the table
        age_data = [25,  30,  30, 35,  30]
        salary_data = [50000.0,  60000.0, 60000.0,  75000.0,  60000.0]
        name_data = ["Alice",  "Bob", "Charlie",  "David",  "Eva"]

        for element in age_data:
            self.age_column.add_element(element)
        for element in salary_data:
            self.salary_column.add_element(element)
        for element in name_data:
            self.name_column.add_element(element)

    def test_equal_condition(self):
        equal_condition = Equal(30)
        executor = ConditionExecutor("Age", equal_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [1, 2, 4])

    def test_not_equal_condition(self):
        not_equal_condition = NotEqual(30)
        executor = ConditionExecutor("Age", not_equal_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [0, 3])

    def test_greater_than_condition(self):
        greater_than_condition = GreaterThan(30)
        executor = ConditionExecutor("Age", greater_than_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [3])

    def test_greater_than_or_equal_condition(self):
        greater_than_or_equal_condition = GreaterThanOrEqualTo(30)
        executor = ConditionExecutor("Age", greater_than_or_equal_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [1, 2, 3, 4])

    def test_less_than_condition(self):
        less_than_condition = LessThan(35)
        executor = ConditionExecutor("Age", less_than_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [0, 1, 2, 4])

    def test_less_than_or_equal_condition(self):
        less_than_or_equal_condition = LessThanOrEqualTo(35)
        executor = ConditionExecutor("Age", less_than_or_equal_condition)
        result = executor.execute(self.table)
        self.assertEqual(result, [0, 1, 2, 3, 4])


if __name__ == '__main__':
    unittest.main()
