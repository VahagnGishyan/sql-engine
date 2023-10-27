
import unittest
from database.database import Database
from database.table import Table
from database.column import Column, ColumnElement
from sqlinterp.operations import Select
from sqlinterp.conditions import Equal, NotEqual
from sqlinterp.conditions import And, Or, Not
from sqlinterp.conditions import GreaterThan, LessThan
from sqlinterp.conditions import GreaterThanOrEqualTo, LessThanOrEqualTo
from utility import console


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

    def test_select_name_and_city_of_user_jhon(self):
        # Test for selecting specific columns with a condition
        query = Select(["Name", "City"], Equal("Name", "John"))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].get_value(), "John")
        self.assertEqual(result.get_column_by_name(
            "City").elements[0].get_value(), "New York")

    def test_select_age_greater_than_35(self):
        # Test for selecting rows with Age greater than 30
        query = Select(["Name", "Age"], Equal("Age", 35))
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
        query = Select(["Name", "Completed"], Equal("Completed", True))
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

    def test_select_age_equal_35(self):
        # Test for selecting rows with Age greater than 30
        query = Select(["Name", "Age"], Equal("Age", 35))
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

    def test_select_age_or_greater_than_equal_to_30(self):
        # Test for selecting rows with Age greater than or equal to 30
        query = Select(["Name", "Age"], Or(GreaterThan("Age", 30),
                                           Equal("Age", 30)))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Bob")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].value, 30)
        self.assertEqual(result.get_column_by_name(
            "Age").elements[1].value, 35)

    def test_select_age_greater_than_or_equal_to_30(self):
        # Test for selecting rows with Age greater than or equal to 30
        query = Select(["Name", "Age"], GreaterThanOrEqualTo("Age", 30))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Bob")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].value, 30)
        self.assertEqual(result.get_column_by_name(
            "Age").elements[1].value, 35)

    def test_select_age_less_than_30(self):
        # Test for selecting rows with Age less than 30
        query = Select(["Name", "Age"], LessThan("Age", 30))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].value, 25)

    def test_select_age_less_than_or_equal_to_30(self):
        # Test for selecting rows with Age less than or equal to 30
        query = Select(["Name", "Age"], LessThanOrEqualTo("Age", 30))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Age").elements[0].value, 25)
        self.assertEqual(result.get_column_by_name(
            "Age").elements[1].value, 30)

    def test_select_age_between_25_and_35(self):
        # Test for selecting rows where Age is between 25 and 35
        condition = And(GreaterThanOrEqualTo("Age", 25),
                        LessThanOrEqualTo("Age", 35))
        query = Select(["Name", "Age"], condition)
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 3)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[2].value, "Bob")

    def test_select_city_new_york_or_los_angeles(self):
        # Test for selecting rows where City is "New York" or "Los Angeles"
        query = Select(["Name", "City"], Or(
            Equal("City", "New York"), Equal("City", "Los Angeles")))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")

    def test_select_age_30_and_city_los_angeles(self):
        # Test for selecting rows where Age is 30 and City is "Los Angeles"
        query = Select(["Name", "Age", "City"], And(
            Equal("Age", 30), Equal("City", "Los Angeles")))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Alice")

    def test_select_not_chicago_or_not_completed(self):
        # Test for selecting rows where City is not "Chicago" or Completed is not True
        query = Select(["Name", "City", "Completed"], Or(
            NotEqual("City", "Chicago"), Not(Equal("Completed", True))))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")

    def test_select_city_not_equal_chicago(self):
        # Test for selecting rows where City is not "Chicago"
        query = Select(["Name", "City"], Not(Equal("City", "Chicago")))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")

    def test_select_age_not_25(self):
        # Test for selecting rows where Age is not 25
        query = Select(["Name", "Age"], Not(Equal("Age", 25)))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Alice")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Bob")

    def test_select_not_completed(self):
        # Test for selecting rows where Completed is not True
        query = Select(["Name", "Completed"], Not(Equal("Completed", True)))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 1)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "Alice")

    def test_select_city_not_chicago(self):
        # Test for selecting rows where City is not "Chicago"
        query = Select(["Name", "City"], NotEqual("City", "Chicago"))
        result = query.execute(self.table)
        # Assert the result based on the condition
        self.assertEqual(len(result.get_rows()), 2)
        self.assertEqual(result.get_column_by_name(
            "Name").elements[0].value, "John")
        self.assertEqual(result.get_column_by_name(
            "Name").elements[1].value, "Alice")


if __name__ == '__main__':
    unittest.main()
