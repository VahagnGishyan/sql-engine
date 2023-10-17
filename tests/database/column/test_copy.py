import unittest

# Import the class you want to test
# Replace 'your_module' with your actual module name
from database import column as dbc
from database import constraints as dbcstrs


class TestColumnCopyMethod(unittest.TestCase):
    def setUp(self):
        # Create an instance of the Column class for testing
        constraint_not_null = dbcstrs.ConstraintNotNull()
        self.column = dbc.Column(
            "Name", "text", [constraint_not_null])

        # Add elements to the column
        self.column.add_element("Element1")
        self.column.add_element("Element2")

    def test_copy_method(self):
        # Call the copy method to create a new column instance
        copied_column = self.column.copy()

        # Check if the copied column is a different instance
        self.assertIsNot(copied_column, self.column)

        # Check if the attributes match
        self.assertEqual(copied_column.get_name(), self.column.get_name())
        self.assertEqual(copied_column.get_type(), self.column.get_type())

        # Check if elements were copied properly
        self.assertEqual(len(copied_column.get_elements()),
                         len(self.column.get_elements()))


if __name__ == '__main__':
    unittest.main()
