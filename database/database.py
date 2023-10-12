 
from database import table as db

class Database:
    def __init__(self, name):
        self.name = name
        self.tables = []

    def create_table(self, table_name):
        # Create a new table and add it to the database
        new_table = db.Table(table_name)  # Assuming you have a Table class
        self.tables.append(new_table)

    # def drop_table(self, table_name):
    #     table = self.get_table(table_name)
    #     self.tables.remove(table)

    def drop_table(self, table_name):
        # Get the table by name
        table = self.get_table(table_name)
        # Remove the table from the list
        self.tables.remove(table)

    def get_table(self, table_name):
        # Retrieve a table from the database by its name using a for loop
        for table in self.tables:
            if table.name == table_name:
                return table
        raise ValueError(f"Table '{table_name}' not found in the database.")

    def list_tables(self):
        # Return a list of table names in the database
        return [table.name for table in self.tables]

    def table_exists(self, table_name):
        # Check if a table with the given name exists in the database
        return table_name in self.list_tables()

    def describe_table(self, table_name):
        # Describe the structure of a table
        table = self.get_table(table_name)
        if table:
            print(f"Table: {table_name}")
            for column in table.columns:
                print(f"Column: {column.name}, Type: {column.type}")
        else:
            print(f"Table '{table_name}' not found in the database.")
