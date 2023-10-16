import json
from utility import core as utcore
from utility import file as utfile
import os

#############################################################
#                                                           #
#############################################################


class FileManager:

    @staticmethod
    def get_work_dir():
        return utcore.get_default_appdata_path() + "/sql-engine"

    @staticmethod
    def get_db_default_dir():
        return FileManager.get_work_dir() + "/main"

    #########################################################

    def get_data_file_extension(self):
        return "json"

    def fix_file_extension(self, path):
        extension = self.get_data_file_extension()
        if extension is not None:
            # Check if the provided path already has the correct extension
            base, ext = os.path.splitext(path)
            if ext == '.' + extension:
                return path  # The extension is correct; no changes needed
            else:
                # If not, append the correct extension
                return path + '.' + extension
        return path  # Return the original path if extension retrieval failed

    #########################################################

    def get_data_file_name(self, path):
        return (self.fix_file_extension(path))

    #########################################################

    def save(self, data, path):
        try:
            with open(path, 'w') as file:
                json.dump(data, file, indent=4)
        except Exception as e:
            raise ValueError(f"Error saving JSON data to {path}: {e}")

    def save_row_list(self, rows, path):
        list_of_lists = []

        for row in rows:
            row_list = []
            for element in row.row_elements:
                row_dict = {
                    "column": element.column,
                    "value": element.value,
                    "type": element.type
                }
                row_list.append(row_dict)
            list_of_lists.append(row_list)

        self.save(list_of_lists, path)

    def load(self, path):
        utfile.assert_is_file(path)
        try:
            with open(path, 'r') as file:
                data = json.load(file)
                return data
        except Exception as e:
            raise ValueError(f"Error loading JSON data from {path}: {e}")
