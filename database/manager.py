
import os
from database import database as db

#############################################################
#                                                           #
#############################################################

# workdir = os.getenv('APPDATA/sql-engine')
# dbdir = f"{workdir}/databases"

#############################################################


class DatabaseManager:
    def __init__(self):
        self.databases = {}

    def create_database(self, name):
        # Create a new database with the given name
        if self.database_exists(name):
            raise ValueError("Database with the same name already exists.")
        new_database = db.Database(name)
        self.databases[name] = new_database
        return self.databases[name]

    def drop_database(self, name):
        # Drop (delete) a database by name
        if self.database_exists(name):
            del self.databases[name]
        else:
            raise ValueError("Database not found.")

    # temp
    # def backup_database(self, name, path):
    #     # Backup a database to a specified path
    #     if self.database_exists(name):
    #         database = self.databases[name]
    #         # Implement backup logic here
    #     else:
    #         raise ValueError("Database not found.")

    # temp
    # def connect(self, name):
    #     # Connect to a database by name
    #     if self.database_exists(name):
    #         return self.databases[name]
    #     else:
    #         raise ValueError("Database not found.")

    def get_database(self, name):
        # Get a database by name
        if self.database_exists(name):
            return self.databases[name]
        else:
            raise ValueError("Database not found.")

    def database_exists(self, name):
        # Check if a database with the given name exists
        return name in self.databases

#############################################################
#                                                           #
#############################################################


dbmanager = DatabaseManager()


def create_database(name):
    return dbmanager.create_database(name)


def drop_database(name):
    return dbmanager.drop_database(name)

# temp
# def backup_database(name, path):
#     Implement backup logic here

# temp
# def connect(name):
#     Implement backup logic here


def get_database(name):
    return dbmanager.get_database(name)


def database_exists(name):
    return dbmanager.database_exists(name)
