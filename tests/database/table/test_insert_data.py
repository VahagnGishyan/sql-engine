import unittest
from database import table as db
from database import constraints as dbcstrs

class TestTableInsert(unittest.TestCase):
    def test_insert(self):
        # Create a table
        my_table = db.Table("MyTable")

        # Create a column with a ConstraintDefault
        default_value = 42
        constraint_default = dbcstrs.ConstraintDefault(default_value)

        # Add columns
        my_table.add_column("ID", "int")
        my_table.add_column("Name", "text")
        my_table.add_column("Age", "int", [constraint_default])

        # Insert data into the table
        data = [("ID", 1), ("Name", "John")]
        my_table.insert_data(data)

        # Verify the data in the table
        elements = []
        for column in my_table.columns:
            elements.extend(column.elements)

        self.assertEqual(len(elements), 3)
        self.assertEqual(elements[0].value, 1)
        self.assertEqual(elements[1].value, "John")
        self.assertEqual(elements[2].value, default_value)

if __name__ == '__main__':
    unittest.main()
