
import unittest
from database.database import Database
from database.table import Table
from database.column import Column, ColumnElement
from sqlinterp.operations import Select
from sqlinterp.conditions import ConditionExecutor
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import GreaterThan, GreaterThanOrEqualTo, LessThanOrEqualTo


class TestSelect(unittest.TestCase):
    def setUp(self):
        self.db = Database.create("MyDatabase")
        self.table = self.db.create_table("MyTable")
        self.table.add_column("Name", "text")
        self.table.add_column("Age", "integer")
        self.table.add_column("City", "date")
        self.table.add_column("Completed", "boolean")

        taskList = [
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

        for task in taskList:
            self.table.insert_data(task)

    def test_select_specific_columns(self):
        # Test for selecting specific columns with a condition
        query = Select(["Name", "City"], [
            ConditionExecutor("Name", Equal("John"))
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].get_value(), "John")
        self.assertEqual(result.get_column_by_name(
            "City").elements[0].get_value(), "New York")

    def test_select_age_greater_than_30(self):
        # Test for selecting rows with Age greater than 30
        query = Select(["Name", "Age"], [
            ConditionExecutor("Age", Equal(35))])
        result = query.execute(self.table)

        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        column: Column = result.get_column_by_name("Name")
        elements = column.elements
        element = elements[0]
        valueis = element.get_value()
        typeis = type(valueis)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].get_value(), "Bob")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].get_value(), 35)

    def test_select_completed_tasks(self):
        # Test for selecting rows where Completed is True
        query = Select(["Name", "Completed"], [
            ConditionExecutor("Completed", Equal(True))])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].get_value(), "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].get_value(), "Bob")
        self.assertEqual(result.get_column_by_name(
            "Completed").elements[0].get_value(), True)
        self.assertEqual(result.get_column_by_name(
            "Completed").elements[1].get_value(), True)

    def test_select_specific_columns(self):
        # Test for selecting specific columns with a condition
        query = Select(["Name", "City"], [
            ConditionExecutor("Name", Equal("John"))
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "City").elements[0].value, "New York")

    def test_select_age_greater_than_30(self):
        # Test for selecting rows with Age greater than 30
        query = Select(["Name", "Age"], [
            ConditionExecutor("Age", GreaterThan(30))
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Bob")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].value, 35)

    def test_select_completed_tasks(self):
        # Test for selecting rows where Completed is True
        query = Select(["Name", "Completed"], [
            ConditionExecutor("Completed", Equal(True))
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Bob")
        self.assertEqual(result.get_column_by_name(
            "Completed").elements[0].value, True)
        self.assertEqual(result.get_column_by_name(
            "Completed").elements[1].value, True)

    def test_select_age_between_25_and_35(self):
        # Test for selecting rows where Age is between 25 and 35
        query = Select(["Name", "Age"], [
            ConditionExecutor("Age", GreaterThanOrEqualTo(25)),
            ConditionExecutor("Age", LessThanOrEqualTo(35)),
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 3)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[2].value, "Bob")

    def test_select_city_not_chicago(self):
        # Test for selecting rows where City is not "Chicago"
        query = Select(["Name", "City"], [
            ConditionExecutor("City", NotEqual("Chicago"))
        ])
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")


if __name__ == '__main__':
    unittest.main()
