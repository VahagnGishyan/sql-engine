
from database import column as db
from database import row as rw
from database import file_manager as fm
from utility import console

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

    def add_column(self, name, type, constraints=None):
        column = db.Column(name, type, constraints)
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

        # Determine the number of rows (use the first column as a reference)
        num_rows = len(self.columns[0].elements) if self.columns else 0

        for i in range(num_rows):
            row_instance = rw.Row()
            for column in self.columns:
                element = column.elements[i]
                row_instance.add_element(
                    column.get_name(), element.value, element.type)
            rows.append(row_instance)

        return rows

    #########################################################

    def insert_data(self, data):
        if len(data) == 0:
            return
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

    def insert_rows(self, rows):
        dataList = rw.rows_to_tuple_list(rows)
        for data in dataList:
            self.insert_data(data)

    #########################################################

    def __len__(self):
        return len(self.columns)


#############################################################
#                                                           #
#############################################################
