import unittest
from database import column as db


def create_column(name, type):
    return db.Column(name, type)


class TestColumnElement(unittest.TestCase):
    def test_add_elements(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements with values
        my_column.add_element(10)
        my_column.add_element(20)
        my_column.add_element(30)

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
        my_column.add_element(10)
        my_column.add_element(20)
        my_column.add_element(30)

        # Check the initial element count
        self.assertEqual(len(my_column.elements), 3)

        # Remove an element
        my_column.remove_elements_by_value(20)

        # Check the updated element count
        self.assertEqual(len(my_column.elements), 2)

        # Check the values of the remaining elements
        self.assertEqual(my_column.elements[0].value, 10)
        self.assertEqual(my_column.elements[1].value, 30)

    def test_update_element_existing(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements
        my_column.add_element(10)
        my_column.add_element(20)
        my_column.add_element(30)

        # Update an existing element
        my_column.update_element(20, 25)

        # Check the updated element value and type
        self.assertEqual(my_column.elements[1].value, 25)

    def test_update_element_not_found(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Attempt to update a non-existent element
        with self.assertRaises(ValueError):
            my_column.update_element(50, 60)

    def test_get_element_by_index(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Add elements
        my_column.add_element(10)
        my_column.add_element(20)
        my_column.add_element(30)

        # Get elements by index
        element_1 = my_column.get_element(0)
        element_2 = my_column.get_element(1)
        element_3 = my_column.get_element(2)

        # Check the values and types of the retrieved elements
        self.assertEqual(element_1.value, 10)
        self.assertEqual(element_2.value, 20)
        self.assertEqual(element_3.value, 30)

    def test_get_element_by_index_out_of_range(self):
        # Create a column
        my_column = create_column("my_column", "int")

        # Attempt to get an element with an out-of-range index
        with self.assertRaises(IndexError):
            my_column.get_element(3)


if __name__ == '__main__':
    unittest.main()
