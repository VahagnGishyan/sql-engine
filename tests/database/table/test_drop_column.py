import unittest
from database import table as db

class TestTableDropColumn(unittest.TestCase):
    def test_drop_column(self):
        # Create a table
        my_table = db.Table("MyTable")

        # Add columns
        my_table.add_column("ID", "int")
        my_table.add_column("Name", "text")
        my_table.add_column("Age", "int")

        # Get the initial number of columns
        initial_column_count = len(my_table.columns)

        # Drop a column
        my_table.drop_column("Name")
        self.assertEqual(len(my_table.columns), initial_column_count - 1)

        # Verify that the "Name" column is removed
        column_names = [col.name for col in my_table.columns]

        self.assertNotIn("Name", column_names)
        
        # Check the updated length of columns
        updated_column_count = len(my_table.columns)
        self.assertEqual(updated_column_count, initial_column_count - 1)

if __name__ == '__main__':
    unittest.main()
