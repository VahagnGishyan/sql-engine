import unittest
# Replace 'your_module_name' with the actual module name
from database.table import Table


class TestTableCopy(unittest.TestCase):
    def setUp(self):
        # Create a sample table with columns and rows for testing
        self.sample_table = Table("SampleTable")
        self.sample_table.add_column("Name", "text")
        self.sample_table.add_column("Description", "text")
        self.sample_table.add_column("DueDate", "date")
        self.sample_table.add_column("Completed", "boolean")

        self.taskList = [
            [
                {"column-name": "Name", "value": "Task 1"},
                {"column-name": "Description", "value": "Description 1"},
                {"column-name": "DueDate", "value": "2023-10-15"},
                {"column-name": "Completed", "value": False},
            ],
            [
                {"column-name": "Name", "value": "Task 2"},
                {"column-name": "Description", "value": "Description 2"},
                {"column-name": "DueDate", "value": "2023-10-16"},
                {"column-name": "Completed", "value": True},
            ],
            [
                {"column-name": "Name", "value": "Task 3"},
                {"column-name": "Description", "value": "Description 3"},
                {"column-name": "DueDate", "value": "2023-10-17"},
                {"column-name": "Completed", "value": False},
            ],
            [
                {"column-name": "Name", "value": "Task 4"},
                {"column-name": "Description", "value": "Description 4"},
                {"column-name": "DueDate", "value": "2023-10-18"},
                {"column-name": "Completed", "value": True}
            ]
        ]

        for task in self.taskList:
            self.sample_table.insert_data(task)

    def test_copy(self):
        # Copy the sample table
        copied_table = self.sample_table.copy()

        # Check if the copied table has the same name
        self.assertEqual(copied_table.get_name(), "SampleTable")

        # Check if the copied table has the same columns
        self.assertEqual(len(self.sample_table.columns), len(self.taskList[0]))
        self.assertEqual(len(copied_table.columns), len(self.taskList[0]))
        for i, row_data in enumerate(self.taskList[0]):
            column_name = row_data["column-name"]
            self.assertEqual(copied_table.columns[i].get_name(), column_name)

        # Check if the copied table has the same data in rows
        original_rows = self.sample_table.get_rows()
        copied_rows = copied_table.get_rows()
        self.assertEqual(len(original_rows), len(copied_rows))
        # self.assertEqual(original_rows, copied_rows)

        original = self.sample_table.get_info_rows()
        copied = copied_table.get_info_rows()
        self.assertEqual(original, copied)


if __name__ == '__main__':
    unittest.main()
