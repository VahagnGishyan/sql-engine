
import os
from utlity import file

#############################################################
#                                                           #
#############################################################

workdir = os.getenv('APPDATA/sql-engine')

#############################################################


class DatabaseManager:
    def __init__(self):
        dbdir = workdir + "/databases"
        self.dbdir = dbdir
        self.databases = {}

    def create_database(self, db_name):
        db_path = os.path.join(self.dbdir, f"{db_name}.db")
        if db_name not in self.databases and not os.path.exists(db_path):
            with open(db_path, 'w'):
                pass  # Create an empty database file
            self.databases[db_name] = db_path
            return True
        else:
            return False  # Database with the same name already exists

    def connect_to_database(self, db_name):
        db_path = self.databases.get(db_name)
        if db_path:
            # You can implement database connection logic here
            print(f"Connected to database: {db_name}")
        else:
            print(f"Database '{db_name}' does not exist.")

    def execute_query(self, query):
        # You can implement query execution logic here
        print(f"Executing query: {query}")

#############################################################
#                                                           #
#############################################################

