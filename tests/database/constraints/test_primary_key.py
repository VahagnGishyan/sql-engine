import unittest
from database import constraints as dbcstrs
from database import column as db


def create_column_with_constraints(name, type, constraints=None):
    return db.Column(name, type, constraints)


class TestColumnConstraintsPrimaryKey(unittest.TestCase):
    def test_constraint_primary_key_pass(self):
        # Create a column with a ConstraintPrimaryKey
        constraint_primary_key = dbcstrs.ConstraintPrimaryKey()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_primary_key])

        try:
            # Add elements with unique values
            my_column.add_element(10)
            my_column.add_element(20)
        except dbcstrs.ConstraintException:
            self.fail(
                "ConstraintException should not be raised for elements with unique values.")

    def test_constraint_primary_key_fail(self):
        # Create a column with a ConstraintPrimaryKey
        constraint_primary_key = dbcstrs.ConstraintPrimaryKey()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_primary_key])

        try:
            # Add elements with duplicate values
            my_column.add_element(10)
            my_column.add_element(10)
        except dbcstrs.ConstraintException as e:
            pass
        else:
            self.fail(
                "ConstraintException should be raised for elements with duplicate values.")


if __name__ == '__main__':
    unittest.main()
