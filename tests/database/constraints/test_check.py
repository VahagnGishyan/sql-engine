import unittest
from database import constraints as dbcstrs
from database import column as db


def create_column_with_constraints(name, type, constraints=None):
    return db.Column(name, type, constraints)


def check_func(column, element_value, element_type):
    return element_value > 0


class TestColumnConstraintsCheck(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestColumnConstraintsCheck, self).__init__(*args, **kwargs)
        constraint_check = dbcstrs.ConstraintCheck(check_func)
        self.my_column = create_column_with_constraints(
            "my_column", "int", [constraint_check])

    def test_constraint_check(self):
        # Add some elements
        self.my_column.add_element(10, "int")
        self.assertEqual(len(self.my_column.elements), 1)
        self.my_column.add_element(20, "int")
        self.assertEqual(len(self.my_column.elements), 2)
        self.my_column.add_element(30, "int")
        self.assertEqual(len(self.my_column.elements), 3)

    def test_constraint_check_pass(self):
        # Create a column with a ConstraintCheck that should pass
        constraint_check = dbcstrs.ConstraintCheck(check_func)
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_check])

        # Add an element with a value that should pass the check
        my_column.add_element(15, "int")

        # The element should be added successfully
        self.assertEqual(len(my_column.elements), 1)

    def test_constraint_check_fail(self):
        # Create a column with a ConstraintCheck that should fail
        constraint_check = dbcstrs.ConstraintCheck(check_func)
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_check])

        try:
            # Add an element with a value that should fail the check
            my_column.add_element(0, "int")
        except dbcstrs.ConstraintException as e:
            # The element should raise a ConstraintException due to the check
            self.assertEqual(len(my_column.elements), 0)
        else:
            # If no exception was raised, fail the test
            self.fail("ConstraintException was not raised.")


if __name__ == '__main__':
    unittest.main()
