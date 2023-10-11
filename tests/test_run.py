import unittest
from database import constraints as dbcstrs
from database import column as db

def create_column_with_constraints(name, data_type, constraints=None):
    return db.Column(name, data_type, constraints)

def check_func(column, element_value, element_type):
    return element_value > 0

class TestColumnConstraintsCheck(unittest.TestCase):
    def __init__(self, *args, **kwargs):
        super(TestColumnConstraints, self).__init__(*args, **kwargs)
        constraint_check = dbcstrs.ConstraintCheck(check_func)
        self.my_column = create_column_with_constraints("my_column", "int", [constraint_check])

    def test_constraint_check(self):
        # Add some elements
        self.my_column.add_element(10, "int")
        self.assertEqual(len(self.my_column.elements), 1)
        self.my_column.add_element(20, "int")
        self.assertEqual(len(self.my_column.elements), 2)
        self.my_column.add_element(30, "int")
        self.assertEqual(len(self.my_column.elements), 3)

if __name__ == '__main__':
    unittest.main()
