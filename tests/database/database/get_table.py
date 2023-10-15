import unittest
from database import database as db  # Import the Database class and the 'table' alias from the 'database' module

class TestDatabaseGetTable(unittest.TestCase):
    def test_get_table(self):
        # Create a database
        my_database = db.Database("MyDatabase")

        # Create tables and add them to the database
        my_database.create_table("Customers")
        my_database.create_table("Orders")

        # Get tables using the get_table method
        customers_table = my_database.get_table("Customers")
        orders_table = my_database.get_table("Orders")

        # Verify that the tables are retrieved correctly
        self.assertIsNotNone(customers_table)
        self.assertIsNotNone(orders_table)

        # Check the name of the retrieved tables
        self.assertEqual(customers_table.name, "Customers")
        self.assertEqual(orders_table.name, "Orders")

        # Check the name of an invalid table (not found)
        with self.assertRaises(ValueError):
            my_database.get_table("Products")

if __name__ == '__main__':
    unittest.main()
