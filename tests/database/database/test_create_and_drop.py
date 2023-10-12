import unittest
from database import database as db  # Import the Database class and the 'table' alias from the 'database' module

class TestDatabaseTableOperations(unittest.TestCase):
    def test_create_and_drop_tables(self):
        # Create a database
        my_database = db.Database("MyDatabase")

        # Create tables and add them to the database
        my_database.create_table("Customers")
        my_database.create_table("Orders")

        # Verify the tables are in the database
        self.assertTrue(my_database.table_exists("Customers"))
        self.assertTrue(my_database.table_exists("Orders"))

        # Check the number of tables
        self.assertEqual(len(my_database.tables), 2)

        # Drop the tables
        my_database.drop_table("Customers")
        my_database.drop_table("Orders")

        # Verify that the tables are no longer in the database
        self.assertFalse(my_database.table_exists("Customers"))
        self.assertFalse(my_database.table_exists("Orders"))

        # Check the number of tables
        self.assertEqual(len(my_database.tables), 0)

if __name__ == '__main__':
    unittest.main()
