import json 
from utlity import core as utcore

def json_default(obj):
    if isinstance(obj, list):
        return ",".join(map(str, obj))
    else:
        raise TypeError(f"Object of type {type(obj)} is not JSON serializable")

class DataSaver:
    # def __init__(self, file_path):
    #     self.file_path = file_path

    @staticmethod
    def get_work_dir():
        return utcore.get_default_appdata_path() + '/' + "sql-engine"

    # def save_data(self, data):
    #     try:
    #         with open(self.file_path, 'w') as file:
    #             json.dump(data, file, indent=4, default=json_default)
    #         print("Data saved successfully to:", self.file_path)
    #     except Exception as e:
    #         print("Error saving data:", str(e)

    # def load_data(self):
    #     try:
    #         with open(self.file_path, 'r') as file:
    #             data = json.load(file)
    #         return data
    #     except Exception as e:
    #         print("Error loading data:", str(e))