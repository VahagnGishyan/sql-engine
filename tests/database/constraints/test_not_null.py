import unittest
from database import constraints as dbcstrs
from database import column as db


def create_column_with_constraints(name, type, constraints=None):
    return db.Column(name, type, constraints)


class TestColumnConstraintsNotNull(unittest.TestCase):
    def test_constraint_not_null_pass(self):
        # Create a column with a ConstraintNotNull
        constraint_not_null = dbcstrs.ConstraintNotNull()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_not_null])

        try:
            # Add an element with a non-null value
            my_column.add_element(10, "int")
        except dbcstrs.ConstraintException:
            self.fail(
                "ConstraintException should not be raised for a non-null value.")

    def test_constraint_not_null_fail(self):
        # Create a column with a ConstraintNotNull
        constraint_not_null = dbcstrs.ConstraintNotNull()
        my_column = create_column_with_constraints(
            "my_column", "int", [constraint_not_null])

        try:
            # Add an element with a null value
            my_column.add_element(None, "int")
        except dbcstrs.ConstraintException as e:
            pass
        else:
            self.fail("ConstraintException should be raised for a null value.")


if __name__ == '__main__':
    unittest.main()
