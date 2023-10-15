
from database import column as db

#############################################################
#                                                           #
#############################################################


class Table:
    def __init__(self, name):
        self.name = None
        self.columns = []

        self.set_name(name)

    #########################################################

    def get_name(self):
        return self.name

    def set_name(self, name):
        if name is None or ' ' in name:
            raise ValueError("Name cannot be None or contain white spaces")
        self.name = name

    #########################################################

    def add_column(self, name, data_type, constraints=None):
        column = db.Column(name, data_type, constraints)
        self.columns.append(column)

    def drop_column(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                self.columns.remove(column)
                return
        raise ValueError(f"Column '{column_name}' not found in the table.")

    #########################################################

    def get_column_by_name(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                return column
        # temp, throw and exception
        return None  # Return None if the column is not found

    def get_rows(self):
        # Get rows from columns
        rows = []
        if not self.columns:
            return rows  # Return an empty list if there are no columns
        num_rows = len(self.columns[0].elements)
        for i in range(num_rows):
            row = [column.elements[i] for column in self.columns]
            rows.append(row)
        return rows

    #########################################################

    def insert_data(self, data):
        if len(data) > len(self.columns):
            raise ValueError("Too many values provided in the data list.")

        new_row = [{"column-name": column.name, "value": None,
                    "type": column.type} for column in self.columns]
        for column_name, value in data:
            for entry in new_row:
                if entry["column-name"] == column_name:
                    entry["value"] = value
                    break

        for entry in new_row:
            column = self.get_column_by_name(entry["column-name"])
            column.add_element(entry["value"], entry["type"])

    #########################################################

    def __len__(self):
        return len(self.columns)


#############################################################
#                                                           #
#############################################################
