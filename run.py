
from database import constraints as dbcstrs
from database import column as db

def create_column_with_constraints(name, data_type, constraints=None):
    return db.Column(name, data_type, constraints)

def check_func(column, element_value, element_type):
    return (element_value > 0)

constraint_check = dbcstrs.ConstraintCheck(check_func)
my_column = create_column_with_constraints("my_column", "int", [constraint_check])

# Add some elements
my_column.add_element(10, "int")
my_column.add_element(20, "int")
my_column.add_element(30, "int")

# Remove elements by value
my_column.remove_element_by_value(20)

# Add another element
my_column.add_element(40, "int")

# Print the remaining elements
for element in my_column.elements:
    print(f"Value: {element.value}, Type: {element.type}")