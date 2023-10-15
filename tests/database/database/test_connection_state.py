import unittest
from database import database as db
from database import data_saver as ds


class TestDatabaseConnectionState(unittest.TestCase):
    def setUp(self):
        db_name = "TestDB"
        db_path = ds.DataSaver.get_work_dir() + '/' + "test-dbase-dir"
        self.db = db.Database(db_name, db_path)

    def test_connect(self):
        # Ensure that the database starts as not connected
        self.assertFalse(self.db.is_connected())

        # Test connecting
        self.db.connect()

        # Check that the database is now connected
        self.assertTrue(self.db.is_connected())

    def test_disconnect(self):
        # Ensure that the database starts as not connected
        self.assertFalse(self.db.is_connected())

        # Test disconnecting
        with self.assertRaises(Exception):  # Replace with the actual exception class
            self.db.disconnect()

        # Check that the database is still not connected
        self.assertFalse(self.db.is_connected())

if __name__ == '__main__':
    unittest.main()
