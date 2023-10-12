import unittest
from database import table as db

class TestAddColumn(unittest.TestCase):
    def test_add_column(self):
        # Create a table
        my_table = db.Table("MyTable")

        # Add columns
        my_table.add_column("ID", "int")
        my_table.add_column("Name", "text")
        my_table.add_column("Age", "int")

        # Check the number of columns in the table
        num_columns = len(my_table)

        # Verify the column names
        column_names = [col.name for col in my_table.columns]
        expected_names = ["ID", "Name", "Age"]
        self.assertEqual(column_names, expected_names)

if __name__ == '__main__':
    unittest.main()
