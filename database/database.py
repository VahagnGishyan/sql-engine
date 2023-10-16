
from database import table as tb
from database import file_manager as fm
from utility import file as utfile
from database import row as rw
# from utility import core as utcore

import os

#############################################################
#                                                           #
#############################################################


class Database:
    def __init__(self, name, path, filem=fm.DataSaver()):
        self.path = None
        self.name = None
        self.filem = None
        self.connected = None
        self.tables = []

        self.set_name(name)
        self.set_path(path)
        self.set_datasaver(filem)
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

    def set_datasaver(self, file_manager):
        if not isinstance(file_manager, fm.DataSaver):
            raise ValueError("file-manager must be a DataSaver obj")
        self.filem = file_manager

    #########################################################

    def get_tables_dir_name(self):
        return "tables"

    def get_tables_dir_path(self):
        return os.path.join(self.get_path(), self.get_tables_dir_name())

    def get_info_file_name_without_extension(self):
        return "db-info"

    def get_info_file_name(self):
        return self.filem.fix_file_extension(
            self.get_info_file_name_without_extension())

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

    def get_info(self):
        info = {
            "name": self.get_name(),
            "access": "public"
        }
        return info

    def save_tables(self, path):
        utfile.assert_dir_exists(path)
        path = path + '/' + self.get_tables_dir_name()
        for table in self.tables:
            if not isinstance(table, tb.Table):
                raise ValueError("element in list tables is not obj of Table")
            data = table.get_rows()
            tableFile = path + '/' + table.get_name()
            tableFile = self.filem.fix_file_extension(tableFile)
            self.filem.save_row_list(data, tableFile)

    def save_info(self, path):
        utfile.assert_dir_exists(path)
        info = self.get_info()
        self.filem.save(info, path + '/' + self.get_info_file_name())

    def save(self, path=None):
        if path is None:
            path = self.get_path()
        self.save_info(path)
        self.save_tables(path)

    def load_tables(self):
        tables_dir = self.get_tables_dir_path()
        extension = self.filem.get_data_file_extension()
        tables = utfile.list_files_in_dir_with_extension(
            tables_dir, extension)
        if len(tables):
            print(f"table-list: {tables}")

        for table_name in tables:
            table_path = f"{tables_dir}/{table_name}"
            table_data = self.filem.load(table_path)

            rows = []
            for row_data in table_data:
                row = rw.Row()
                for element_data in row_data:
                    element = rw.RowElement(
                        element_data["column"], element_data["value"], element_data["type"])
                    row.row_elements.append(element)
                rows.append(row)

            table = self.create_table(table_name)
            for element in rows[0].row_elements:
                table.add_column(element.column, element.type)
                # temp, also add constraints

            table.insert_rows(rows)

    def load_info(self):
        info = self.filem.load(self.get_info_file_path())
        # do-something

    def load(self):
        # self.load_info()
        # self.load_tables()
        pass

    #########################################################

    @staticmethod
    def create(dbname, path=None, connect=False):
        if path is None:
            path = fm.DataSaver.get_db_default_dir()
        if utfile.is_path_exists(path) is False:
            utfile.mkdir(path)

        # make files and dris
        db = Database(dbname, path)
        tblDir = db.get_tables_dir_path()
        dbDataFile = db.get_info_file_path()

        if not utfile.is_path_exists(dbDataFile) or utfile.is_file_empty_or_spaces(dbDataFile):
            utfile.mkdir(tblDir)
            utfile.create_empty_file(dbDataFile)
            db.save()

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
        self.load()
        self.set_connected(True)

    def disconnect(self, save=True):
        self.assert_connected()
        if save is True:
            self.save()
        self.set_connected(False)

    #########################################################

    def create_table(self, table_name):
        # Create a new table and add it to the database
        new_table = tb.Table(table_name)  # Assuming you have a Table class
        self.tables.append(new_table)
        return (new_table)

    def drop_table(self, table_name):
        # Get the table by name
        table = self.get_table(table_name)
        self.tables.remove(table)

    def get_table(self, table_name):
        # Retrieve a table from the database by its name using a for loop
        for table in self.tables:
            if table.name == table_name:
                return table
        raise ValueError(f"Table '{table_name}' not found in the database.")

    def execute(self, query):
        pass


#############################################################
#                                                           #
#############################################################
