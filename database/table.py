
from database import column as db;

class Table:
    def __init__(self, name):
        self.name = name
        self.columns = []

    def add_column(self, name, data_type, constraints=None):
        column = db.Column(name, data_type, constraints)
        self.columns.append(column)

    def insert_data(self, data):
        if len(data) > len(self.columns):
            raise ValueError("Too many values provided in the data list.")

        row = [column.get_default_value() for column in self.columns]

        for column_name, value in data:
            for i, col in enumerate(self.columns):
                if col.name == column_name:
                    row[i] = value

        for i, column in enumerate(self.columns):
            column.add_element(row[i])

    def drop_column(self, column_name):
        column_to_remove = next(
            (column for column in self.columns if column.name == column_name), None
        )
        if column_to_remove:
            self.columns.remove(column_to_remove)

    def rename_column(self, column_name, new_name):
        column_to_rename = next(
            (column for column in self.columns if column.name == column_name), None
        )
        if column_to_rename:
            column_to_rename.name = new_name

    def __len__(self):
        return len(self.columns)
