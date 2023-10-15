
# from database import table as db
from database import file_manager as fm
from utlity import file as utfile
# from utlity import core as utcore

import os

#############################################################
#                                                           #
#############################################################


class Database:
    def __init__(self, name, path, datasever=fm.DataSaver()):
        self.path = None
        self.name = None
        self.datasever = None
        self.connected = None
        self.tables = []

        self.set_name(name)
        self.set_path(path)
        self.set_datasaver(datasever)
        self.set_connected(False)

    #########################################################

    def is_connected(self):
        return self.connected

    def set_connected(self, is_connected):
        if not isinstance(is_connected, bool):
            raise ValueError("is_connected must be a boolean value")
        self.connected = is_connected

    def get_path(self):
        return self.path

    def set_path(self, path):
        utfile.assert_dir_exists(path)
        self.path = path + '/' + self.name  # Update path with the new directory

    def get_name(self):
        return self.name

    def set_name(self, name):
        if name is None or ' ' in name:
            raise ValueError("Name cannot be None or contain white spaces")
        if self.path is not None:
            # Extract the parent directory from the current path
            parent_dir = os.path.dirname(self.path)
            # Create the new path with the updated name
            new_path = os.path.join(parent_dir, name)
            # Check if the new path already exists
            if os.path.exists(new_path):
                raise ValueError(
                    "A database with the same name already exists in the parent directory.")
            # Update the name and path
            self.path = new_path
        self.name = name

    def set_datasaver(self, datasaver):
        if not isinstance(datasaver, fm.DataSaver):
            raise ValueError("datasaver must be a DataSaver obj")
        self.datasaver = datasaver

    #########################################################

    def get_tables_dir_name(self):
        return "tables"

    def get_tables_dir_path(self):
        return os.path.join(self.get_path(), self.get_tables_dir_name())

    def get_info_file_name(self):
        return "db-info"

    def get_info_file_path(self):
        return os.path.join(self.get_path(), self.get_info_file_name())

    def list_tables(self):
        # Return a list of table names in the database
        return [table.name for table in self.tables]

    def table_exists(self, table_name):
        # Check if a table with the given name exists in the database
        return table_name in self.list_tables()

    #########################################################

    def assert_connected(self):
        if not self.connected:
            raise ValueError("Database is not connected")

    def assert_not_connected(self):
        if self.connected:
            raise ValueError("Database is already connected")

    #########################################################

    @staticmethod
    def create(dbname, path=None, connect=False):
        if path is None:
            path = fm.DataSaver.get_db_default_dir()
        # make files and dris
        db = Database(dbname, path)
        if connect:
            db.connect()
        return db

    @staticmethod
    def destroy(db):
        if not isinstance(db, Database):
            raise ValueError("Database.destroy: arg db must be a Database obj")
        if db.is_connected():
            db.disconnect(save=False)
        # remove files and dris

    #########################################################

    def connect(self):
        self.assert_not_connected()
        self.set_connected(True)
        pass

    def disconnect(self, save=True):
        self.assert_connected()
        self.set_connected(False)
        pass

    #########################################################

    def create_table(self, table_name):
        # # Create a new table and add it to the database
        # new_table = db.Table(table_name)  # Assuming you have a Table class
        # self.tables.append(new_table)
        # return (new_table)
        pass

    def drop_table(self, table_name):
        # Get the table by name
        # table = self.get_table(table_name)
        # self.tables.remove(table)
        pass

    def execute(self, query):
        pass


#############################################################
#                                                           #
#############################################################
