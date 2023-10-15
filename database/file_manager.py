import json
from utility import core as utcore
from utility import file as utfile
import os

#############################################################
#                                                           #
#############################################################


class DataSaver:

    @staticmethod
    def get_work_dir():
        return utcore.get_default_appdata_path() + "/sql-engine"

    @staticmethod
    def get_db_default_dir():
        return DataSaver.get_work_dir() + "/main"

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

    def load(self, path):
        try:
            with open(path, 'r') as file:
                data = json.load(file)
                return data
        except Exception as e:
            raise ValueError(f"Error loading JSON data from {path}: {e}")
