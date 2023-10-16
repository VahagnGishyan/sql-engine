
from database import column as db
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

    def table_to_table_info_columns(self):
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

    def table_to_table_info_rows(self):
        # Convert rows
        rows = []
        for row in self.get_rows():
            row_json = []
            for element in row.row_elements:
                row_element_json = {
                    "column": element.column,
                    # "type": element.type,
                    "value": element.value
                }
                row_json.append(row_element_json)

            rows.append(row_json)
        return rows

    def table_to_table_info(self):
        table_json = {
            "table": self.get_name(),
            "columns": [],
            "rows": []
        }
        table_json["columns"] = self.table_to_table_info_columns()
        table_json["rows"] = self.table_to_table_info_rows()
        return table_json

    def save(self, path, filem=fm.FileManager()):
        utfile.assert_dir_exists(path)
        data = self.table_to_table_info()
        tableFile = path + '/' + self.get_name()
        tableFile = filem.fix_file_extension(tableFile)
        filem.save(data, tableFile)

    def load(self, path, filem=fm.FileManager()):
        utfile.assert_file_exists(path)
        data = filem.load(path)
        self.set_name(data["table"])
        for column in data["columns"]:
            self.add_column(column["name"], column["type"])
        for row in data["rows"]:
            self.insert_data(row)

    #########################################################

    def __len__(self):
        return len(self.columns)


#############################################################
#                                                           #
#############################################################
