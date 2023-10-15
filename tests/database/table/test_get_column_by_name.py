import unittest
from database import table as db

class TestTableGetColumnByName(unittest.TestCase):
    def test_get_column_by_name(self):
        # Create a table
        my_table = db.Table("MyTable")

        # Add columns
        my_table.add_column("ID", "int")
        my_table.add_column("Name", "text")
        my_table.add_column("Age", "int")

        # Retrieve columns by name
        id_column = my_table.get_column_by_name("ID")
        name_column = my_table.get_column_by_name("Name")
        age_column = my_table.get_column_by_name("Age")

        # Verify the retrieved columns
        self.assertIsNotNone(id_column)
        self.assertIsNotNone(name_column)
        self.assertIsNotNone(age_column)

        # Check the column properties
        self.assertEqual(id_column.name, "ID")
        self.assertEqual(name_column.name, "Name")
        self.assertEqual(age_column.name, "Age")

        self.assertEqual(id_column.type, "int")
        self.assertEqual(name_column.type, "text")
        self.assertEqual(age_column.type, "int")

if __name__ == '__main__':
    unittest.main()
