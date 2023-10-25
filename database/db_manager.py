
import os
from database.database import Database
from utility import file as utfile
from database.file_manager import FileManager

#############################################################
#                                                           #
#############################################################


class DatabaseManager:
    def __init__(self, path=None, file_manager=FileManager()):
        self.file_manager = file_manager

        if path is None:
            path = self.file_manager.get_db_default_dir()
        if not utfile.is_path_exists(path):
            utfile.mkdir(path)
        utfile.assert_dir_exists(path)
        self.path = path

        self.databases: list[str] = utfile.list_dirs_in_dir(self.path)
        self.connected_dbs: map = {}

    #########################################################

    def get_work_dir(self):
        return self.path

    def database_exists(self, name):
        return name in self.databases

    def database_connected(self, name):
        return name in self.connected_dbs

    #########################################################

    def list_database(self):
        return list(self.databases)

    def list_connected_database(self):
        connected_dbs_names = list(self.connected_dbs.keys())
        return connected_dbs_names

    #########################################################

    def assert_db_exists(self, name):
        if not self.database_exists(name):
            raise ValueError(
                f"Database with the name: {name} does not exists.")

    def assert_db_not_exists(self, name):
        if self.database_exists(name):
            raise ValueError(
                f"Dtabase with the same name: {name} exists.")

    def assert_db_connected(self, name):
        self.assert_db_exists(name)
        if not self.database_connected(name):
            raise ValueError(
                f"Database with the name: {name} is not connected.")

    def assert_db_not_connected(self, name):
        self.assert_db_exists(name)
        if self.database_connected(name):
            raise ValueError(
                f"Database with the name: {name} is connected.")

    #########################################################

    def create_database(self, name):
        # Create a new database with the given name
        self.assert_db_not_exists(name)
        new_database = Database.create(name, self.get_work_dir())
        self.databases.append(name)

    def drop_database(self, name):
        self.assert_db_exists(name)
        self.assert_db_not_connected(name)
        database = Database.create(name, self.get_work_dir())
        Database.destroy(database)
        self.databases.remove(name)

    #########################################################

    def connect(self, name):
        self.assert_db_not_connected(name)
        database = Database.create(name, self.get_work_dir(), connect=True)
        self.connected_dbs[name] = database
        return database

    def get_database(self, name):
        self.assert_db_connected(name)
        return self.connected_dbs[name]

    def disconnect(self, dbparam):
        database = None
        name = None
        if isinstance(dbparam, str):
            name = dbparam
            self.assert_db_connected(name)
            database = self.connected_dbs[name]
        elif isinstance(dbparam, Database):
            database = dbparam
            name = database.get_name()
            self.assert_db_connected(name)

        database.disconnect()
        del self.connected_dbs[name]

    def disconnect_all_dbs(self):
        connected_dbs_names = self.list_connected_database()
        for dbname in connected_dbs_names:
            self.disconnect(dbname)

    #########################################################

    def close(self):
        self.disconnect_all_dbs()

#############################################################
#                                                           #
#############################################################
