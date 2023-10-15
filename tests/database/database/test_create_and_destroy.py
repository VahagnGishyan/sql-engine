import unittest
from database import database as db
from database import file_manager as fm

db_path = fm.DataSaver.get_work_dir() + '/' + "test-dbase-dir"
db_name = "TestDB"


class TestDatabaseCreationAndDestruction(unittest.TestCase):

    def test_create_and_destroy(self):
        # Test creating and destroying a database
        dbase = db.Database.create(db_name, db_path, connect=True)
        self.assertTrue(dbase.is_connected())
        db.Database.destroy(dbase)
        self.assertFalse(dbase.is_connected())

    def test_create_invalid_db(self):
        # Test creating an invalid database
        with self.assertRaises(ValueError):
            db.Database.create(None, connect=True)

    def test_destroy_invalid_db(self):
        # Test destroying an invalid database
        with self.assertRaises(ValueError):
            db.Database.destroy(None)


if __name__ == '__main__':
    unittest.main()
