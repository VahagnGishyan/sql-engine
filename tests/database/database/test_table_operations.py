import unittest
# Import the Database class and the 'table' alias from the 'database' module
from database import database as db
from database import file_manager as fm
from database import constraints as cstr

db_path = fm.FileManager.get_work_dir() + '/' + "test-dbase-dir"
db_name = "MyDatabase"


class TestDatabaseTableOperations(unittest.TestCase):
    def test_create_and_drop_tables(self):
        # Create a database
        my_database = db.Database.create(db_name, db_path, connect=True)

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

    def test_list_tables(self):
        # Create a database
        my_database = db.Database.create(db_name, db_path, connect=True)

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

    def test_get_table(self):
        # Create a database
        my_database = db.Database.create(db_name, db_path, connect=True)

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
