
# import unittest
# from database.database import Database
# from database.table import Table
# from database.column import Column, ColumnElement
# from sqlinterp.operations import Delete
# from sqlinterp.conditions import Equal
# from sqlinterp.conditions import GreaterThan


# class TestDelete(unittest.TestCase):
#     def setUp(self):
#         # Create a table and insert data
#         self.table = Table("MyTable")
#         self.table.add_column("Name", "text")
#         self.table.add_column("Age", "integer")
#         self.table.add_column("City", "date")
#         self.table.add_column("Completed", "boolean")
#         data_to_insert = [
#             [
#                 {"column-name": "Name", "value": "John"},
#                 {"column-name": "Age", "value": 25},
#                 {"column-name": "City", "value": "New York"},
#                 {"column-name": "Completed", "value": True}
#             ],
#             [
#                 {"column-name": "Name", "value": "Alice"},
#                 {"column-name": "Age", "value": 30},
#                 {"column-name": "City", "value": "Los Angeles"},
#                 {"column-name": "Completed", "value": False}
#             ],
#             [
#                 {"column-name": "Name", "value": "Bob"},
#                 {"column-name": "Age", "value": 35},
#                 {"column-name": "City", "value": "Chicago"},
#                 {"column-name": "Completed", "value": True}
#             ]
#         ]
#         for row in data_to_insert:
#             self.table.insert_data(row)

#     def test_delete_john_by_name(self):
#         # Test for deleting rows with Name "John"
#         query = Delete(Equal("Name", "John"))
#         query.execute(self.table)
#         result = self.table.get_rows()
#         # Assert the result based on the deletion
#         self.assertEqual(len(result), 2)  # Only Alice and Bob should remain

#     def test_delete_completed_tasks(self):
#         # Test for deleting rows where Completed is True
#         query = Delete(Equal("Completed", True))
#         query.execute(self.table)
#         result = self.table.get_rows()
#         # Assert the result based on the deletion
#         self.assertEqual(len(result), 1)  # Only Alice should remain

#     def test_delete_age_above_30(self):
#         # Test for deleting rows with Age greater than 30
#         query = Delete(GreaterThan("Age", 30))
#         query.execute(self.table)
#         result = self.table.get_rows()
#         # Assert the result based on the deletion
#         self.assertEqual(len(result), 2)  # Only John should remain


# if __name__ == '__main__':
#     unittest.main()
