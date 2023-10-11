import unittest
from database import column as db

def create_column(name, data_type):
    return db.Column(name, data_type)

class TestColumnAddElements(unittest.TestCase):
    def test_add_elements(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements with values
        my_column.add_element(10, "int")
        my_column.add_element(20, "int")
        my_column.add_element(30, "int")

        # Check the element count
        self.assertEqual(len(my_column.elements), 3)

        # Check the values of the elements
        self.assertEqual(my_column.elements[0].value, 10)
        self.assertEqual(my_column.elements[1].value, 20)
        self.assertEqual(my_column.elements[2].value, 30)

if __name__ == '__main__':
    unittest.main()
