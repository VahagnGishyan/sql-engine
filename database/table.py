
from database import column as db;

class Table:
    def __init__(self, name):
        self.name = name
        self.columns = []

    def add_column(self, name, data_type, constraints=None):
        column = db.Column(name, data_type, constraints)
        self.columns.append(column)

    def get_column_by_name(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                return column
        return None  # Return None if the column is not found

    def insert_data(self, data):
        if len(data) > len(self.columns):
            raise ValueError("Too many values provided in the data list.")

        new_row = [{"column-name": column.name, "value": None, "type": column.type} for column in self.columns]
        for column_name, value in data:
            for entry in new_row:
                if entry["column-name"] == column_name:
                    entry["value"] = value
                    break

        for entry in new_row:
            column = self.get_column_by_name(entry["column-name"])
            column.add_element(entry["value"], entry["type"])

    def drop_column(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                self.columns.remove(column)
                return
        raise ValueError(f"Column '{column_name}' not found in the table.")

    def __len__(self):
        return len(self.columns)
