
from utility import console
from database.database import Database
from database.table import Table
from database.db_manager import DatabaseManager

#############################################################
#                                                           #
#############################################################


class DBWrapper:

    def database_exists(self, name):
        pass

    #########################################################

    def create(self, name):
        pass

    def drop(self, name):
        pass

    def list_db(self):
        pass

    def list_connected_db(self):
        pass

    #########################################################

    def connect(self, dbname):
        pass

    def disconnect(self, dbparam):
        pass

    #########################################################

    def create_table(self, dbname, tbname, columns: list[{str, str}]):
        pass

    def drop_table(self, dbname, tbname):
        pass

    def list_tables(self, dbname):
        pass

    def alter_table_add(self, dbname, tbname, column_name, datatype):
        pass

    def alter_table_drop(self, dbname, tbname, column_name):
        pass

    def alter_table_rename(self, column_name):
        pass

    #########################################################

    def execute(self, query):
        pass

    #########################################################

    def close(self):
        pass

#############################################################
#                                                           #
#############################################################


class DBWrapperPythonLib:
    def __init__(self):
        self.db_manager = DatabaseManager()

    #########################################################

    def work_dir(self):
        return self.db_manager.get_work_dir()

    #########################################################

    def database_exists(self, name):
        return self.db_manager.database_exists(name)

    #########################################################

    def create(self, name: str) -> Database:
        self.db_manager.create_database(name)

    def drop(self, name):
        self.db_manager.drop_database(name)

    def list_db(self):
        return self.db_manager.list_database()

    def list_connected_db(self):
        return self.db_manager.list_connected_database()

    #########################################################

    def connect(self, dbname):
        return self.db_manager.connect(dbname)

    def disconnect(self, dbparam):
        name = None
        if isinstance(dbparam, Database):
            name = dbparam
        elif isinstance(dbparam, str):
            name = dbparam
        return self.db_manager.disconnect(name)

    #########################################################

    def create_table(self, dbname, tbname, columns: list[{str, str}]):
        database: Database = self.db_manager.get_database(dbname)
        table = database.create_table(tbname)
        for column_name, datatype in columns:
            table.add_column(column_name, datatype)
        return table

    def drop_table(self, dbname, tbname):
        database: Database = self.db_manager.get_database(dbname)
        database.drop_table(tbname)

    def list_tables(self, dbname):
        database: Database = self.db_manager.get_database(dbname)
        return database.list_tables()

    def alter_table_add(self, dbname, tbname, column_name, datatype):
        database: Database = self.db_manager.get_database(dbname)
        table: Table = database.get_table(tbname)
        table.add_column(column_name, datatype)

    def alter_table_drop(self, dbname, tbname, column_name):
        database: Database = self.db_manager.get_database(dbname)
        table: Table = database.get_table(tbname)
        table.drop_column(column_name)

    def alter_table_rename(self, dbname, tbname, old_name, new_name):
        database: Database = self.db_manager.get_database(dbname)
        table: Table = database.get_table(tbname)
        table.rename_column(old_name, new_name)

    #########################################################

    def execute(self, dbname, query):
        database: Database = self.db_manager.get_database(dbname)
        return database.execute(query)

    #########################################################

    def close(self):
        self.db_manager.close()

#############################################################
#                                                           #
#############################################################
