import unittest
from database import manager as dbm

class TestDatabaseManager(unittest.TestCase):
    def test_create_database(self):
        # Create a DatabaseManager
        manager = dbm.DatabaseManager()

        # Test creating a new database
        result = manager.create_database("NewDatabase")
        self.assertTrue(result)  # Creation should succeed

        # Test creating a database with the same name
        with self.assertRaises(ValueError):
            manager.create_database("NewDatabase")

    def test_drop_database(self):
        # Create a DatabaseManager
        manager = dbm.DatabaseManager()

        # Test dropping a non-existent database
        with self.assertRaises(ValueError):
            manager.drop_database("NonExistentDatabase")

        # Create a new database and test dropping it
        manager.create_database("ToBeDropped")
        manager.drop_database("ToBeDropped")
        self.assertFalse(manager.database_exists("ToBeDropped"))  # Drop should succeed

if __name__ == '__main__':
    unittest.main()
