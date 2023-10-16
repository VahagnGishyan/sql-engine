import unittest
from database import constraints as dbcstrs
from database import column as db


def create_column_with_constraints(name, type, constraints=None):
    return db.Column(name, type, constraints)


class TestColumnConstraintsUnique(unittest.TestCase):
    def test_constraint_unique_pass(self):
        # Create a column with a ConstraintUnique
        constraint_unique = dbcstrs.ConstraintUnique()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_unique])

        try:
            # Add elements with unique values
            my_column.add_element(10, "int")
            my_column.add_element(20, "int")
        except dbcstrs.ConstraintException:
            self.fail(
                "ConstraintException should not be raised for unique values.")

    def test_constraint_unique_fail(self):
        # Create a column with a ConstraintUnique
        constraint_unique = dbcstrs.ConstraintUnique()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_unique])

        try:
            # Add elements with non-unique values
            my_column.add_element(10, "int")
            my_column.add_element(10, "int")
        except dbcstrs.ConstraintException as e:
            pass
        else:
            self.fail(
                "ConstraintException should be raised for non-unique values.")


if __name__ == '__main__':
    unittest.main()
