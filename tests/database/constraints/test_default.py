import unittest
from database import constraints as dbcstrs
from database import column as db


def create_column_with_constraints(name, type, constraints=None):
    return db.Column(name, type, constraints)


class TestColumnConstraintsDefault(unittest.TestCase):
    def test_constraint_default(self):
        # Create a column with a ConstraintDefault
        default_value = 42
        constraint_default = dbcstrs.ConstraintDefault(default_value)
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_default])

        # Add an element without specifying a value
        my_column.add_element(None)

        # Check the element count
        self.assertEqual(len(my_column.elements), 1)

        # Check the default value
        self.assertEqual(my_column.elements[0].value, default_value)

    def test_add_elements_with_defaults(self):
        # Create a column with a ConstraintDefault
        default_value = 42
        constraint_default = dbcstrs.ConstraintDefault(default_value)
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_default])

        # Add multiple elements without specifying values
        my_column.add_element(None)
        my_column.add_element(None)
        my_column.add_element(None)

        # Check the element count
        self.assertEqual(len(my_column.elements), 3)

        # Check that all elements have the default value
        for element in my_column.elements:
            self.assertEqual(element.value, default_value)


if __name__ == '__main__':
    unittest.main()
