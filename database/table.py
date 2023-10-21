
from database import column as clm
from database import row as rw
from database import file_manager as fm
from utility import console
from utility import file as utfile

#############################################################
#                                                           #
#############################################################


class Table:
    def __init__(self, name):
        self.name = None
        self.columns: list[clm.Column] = []
        self.set_name(name)

    def copy(self):
        newtb = Table(self.get_name())
        for column in self.columns:
            newtb.add_column(column.get_name(), column.get_type())
        data = self.get_info_rows()
        for data in data:
            newtb.insert_data(data)
        return newtb

    #########################################################

    def get_name(self):
        return self.name

    def set_name(self, name):
        if name is None or ' ' in name:
            raise ValueError("Name cannot be None or contain white spaces")
        self.name = name

    #########################################################

    def add_column(self, name, type, constraints=None):
        column = clm.Column(name, type, constraints)
        self.insert_column(column)
        return column

    def drop_column(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                self.columns.remove(column)
                return
        raise ValueError(f"Column '{column_name}' not found in the table.")

    #########################################################

    def list_columns(self):
        return [column.name for column in self.columns]

    def get_column_by_name(self, column_name):
        for column in self.columns:
            if column.name == column_name:
                return column
        # If the column is not found, raise an exception
        raise ValueError(f"Column with name '{column_name}' not found.")

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
                    column.get_name(), element.get_value(), column.get_type())
            rows.append(row_instance)

        return rows

    #########################################################

    def insert_column(self, column):
        if not isinstance(column, clm.Column):
            raise ValueError("Input must be a Column object.")
        self.columns.append(column)

    def insert_data(self, data):
        if len(data) == 0:
            return
        if len(data) > len(self.columns):
            raise ValueError("Too many values provided in the data list.")

        new_row = [{"column-name": column.name, "value": None,
                    "type": column.type} for column in self.columns]

        for element in data:
            for entry in new_row:
                if entry["column-name"] == element["column-name"]:
                    entry["value"] = element["value"]
                    break

        for entry in new_row:
            column = self.get_column_by_name(entry["column-name"])
            column.add_element(entry["value"])

    def insert_rows(self, rows):
        dataList = self.get_info_rows()
        for data in dataList:
            self.insert_data(data)

    def remove_row(self, index):
        # Check if the table is empty or the index is out of range
        if not self.columns:
            raise ValueError("Table is empty.")
        if index < 0 or index >= len(self.columns[0].elements):
            raise ValueError("Invalid row index provided.")

        # Remove each element from all columns at the given index
        for column in self.columns:
            del column.elements[index]

    #########################################################

    def get_info_columns(self):
        # Convert columns
        columns = []
        for column in self.columns:
            column_json = {
                "name": column.name,
                "type": column.type,
                # "constraints": []
            }
            # for constraint in column.constraints:
            #     constraint_json = {
            #         "name": constraint.name
            #     }
            #     if constraint.value is not None:
            #         constraint_json["value"] = constraint.value
            #     column_json["constraints"].append(constraint_json)
            columns.append(column_json)
        return columns

    def get_info_rows(self):
        # Convert rows
        rows = []
        for row in self.get_rows():
            row_data = row.get_info()
            rows.append(row_data)
        return rows

    def get_info(self):
        table_json = {
            "table": self.get_name(),
            "columns": [],
            "rows": []
        }
        table_json["columns"] = self.get_info_columns()
        table_json["rows"] = self.get_info_rows()
        return table_json

    def reset_by_info(self, info):
        for column in info["columns"]:
            self.add_column(column["name"], column["type"])
        for row in info["rows"]:
            self.insert_data(row)

    def save(self, path, filem=fm.FileManager()):
        utfile.assert_dir_exists(path)

        data = self.get_info()
        tableFile = path + '/' + self.get_name()
        tableFile = filem.fix_file_extension(tableFile)
        filem.save(data, tableFile)

    def load(self, path, filem=fm.FileManager()):
        utfile.assert_file_exists(path)
        data = filem.load(path)
        self.reset_by_info(data)

    #########################################################

    def __len__(self):
        return len(self.columns)


#############################################################
#                                                           #
#############################################################
