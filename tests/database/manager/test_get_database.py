import unittest
from database import manager as dbm


class TestDatabaseManagerGetDatabase(unittest.TestCase):
    def test_get_database_success(self):
        # Create multiple databases
        dbm.create_database("Database1")
        dbm.create_database("Database2")
        dbm.create_database("Database3")

        # Test getting an existing database
        retrieved_database = dbm.get_database("Database2")
        self.assertIsNotNone(retrieved_database)

    def test_get_database_failure(self):
        # Create a DatabaseManager
        manager = dbm.DatabaseManager()

        # Create multiple databases
        manager.create_database("DatabaseA")
        manager.create_database("DatabaseB")
        manager.create_database("DatabaseC")

        # Test getting a non-existent database (should raise an exception)
        with self.assertRaises(ValueError):
            manager.get_database("NonExistentDatabase")


if __name__ == '__main__':
    unittest.main()
