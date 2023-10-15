import unittest
# Import the Database class and the 'table' alias from the 'database' module
from database import database as db
from database import data_saver as ds
from utlity import file as utfile

db_path = ds.DataSaver.get_work_dir() + '/' + "test-dbase-dir"
db_new_path = ds.DataSaver.get_work_dir() + '/' + "test-dbase-dir-new"
db_name = "TestDB"


class TestDatabaseTableOperations(unittest.TestCase):
    def test_is_connected(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Check if it's not connected initially
        self.assertFalse(dbase.is_connected())

    def test_set_connected(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Set it as connected
        dbase.set_connected(True)

        # Check if it's connected
        self.assertTrue(dbase.is_connected())

    def test_get_path(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Check if the path is correct
        self.assertEqual(dbase.get_path(), db_path + '/' + db_name)

    def test_set_path(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Set a new path
        dbase.set_path(db_new_path)

        # Check if the path is updated
        self.assertEqual(dbase.get_path(), db_new_path + '/' + db_name)

    def test_get_name(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Check if the name is correct
        self.assertEqual(dbase.get_name(), db_name)

    def test_set_name(self):
        # Create a db.Database object
        dbase = db.Database(db_name, db_path)

        # Set a new name
        dbase.set_name("NewDB")

        # Check if the name is updated
        self.assertEqual(dbase.get_name(), "NewDB")


if __name__ == '__main__':
    unittest.main()
