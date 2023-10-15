import unittest
from database import database as db  # Import the 'database' module as 'db'

class TestDatabaseListTables(unittest.TestCase):
    def test_list_tables(self):
        # Create a database
        my_database = db.Database("MyDatabase")

        # Create tables and add them to the database
        my_database.create_table("Customers")
        my_database.create_table("Orders")
        my_database.create_table("Products")

        # Get the list of table names
        table_names = my_database.list_tables()

        # Check if the expected table names are in the list
        self.assertIn("Customers", table_names)
        self.assertIn("Orders", table_names)
        self.assertIn("Products", table_names)

        # Check the number of table names
        self.assertEqual(len(table_names), 3)

if __name__ == '__main__':
    unittest.main()
