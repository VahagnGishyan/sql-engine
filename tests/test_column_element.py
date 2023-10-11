import unittest
from database import column as db

def create_column(name, data_type):
    return db.Column(name, data_type)

class TestColumnElement(unittest.TestCase):
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
    
    def test_remove_elements(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements
        my_column.add_element(10, "int")
        my_column.add_element(20, "int")
        my_column.add_element(30, "int")

        # Check the initial element count
        self.assertEqual(len(my_column.elements), 3)

        # Remove an element
        my_column.remove_element(20)

        # Check the updated element count
        self.assertEqual(len(my_column.elements), 2)

        # Check the values of the remaining elements
        self.assertEqual(my_column.elements[0].value, 10)
        self.assertEqual(my_column.elements[1].value, 30)

    def test_update_element_existing(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements
        my_column.add_element(10, "int")
        my_column.add_element(20, "int")
        my_column.add_element(30, "int")

        # Update an existing element
        my_column.update_element(20, 25, "int")

        # Check the updated element value and type
        self.assertEqual(my_column.elements[1].value, 25)
        self.assertEqual(my_column.elements[1].type, "int")

    def test_update_element_not_found(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Attempt to update a non-existent element
        with self.assertRaises(ValueError):
            my_column.update_element(50, 60, "int")
            
if __name__ == '__main__':
    unittest.main()
