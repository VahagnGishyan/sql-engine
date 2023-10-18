

# Import the necessary modules
from database import database as db
from database import file_manager as fm
from database import table as tbl
from database import column as col
from database import constraints as cstr

#############################################################
#                                                           #
#############################################################

# Step 0: Set data names
db_path = fm.FileManager.get_work_dir() + '/' + "test-dbase-dir"
db_name = "MyDatabase"
table_name = "ToDoList"

#############################################################
#                                                           #
#############################################################

# Step 1: Create a database
todo_db = db.Database.create(db_name, db_path, connect=True)


# Step 2: Create a table for the to-do list tasks
todo_table = todo_db.create_table(table_name)

# Step 3: Define columns for the to-do list tasks
todo_table.add_column("Name", "text", [cstr.ConstraintNotNull()])
todo_table.add_column("Description", "text", [cstr.ConstraintNotNull()])
todo_table.add_column("DueDate", "date", [cstr.ConstraintNotNull()])
todo_table.add_column("Completed", "boolean", [
    cstr.ConstraintDefault(False)])

# Step 4: Add data to columns
taskList = [
    {"column-name": "Name", "value": "Task 1"},
    {"column-name": "Description", "value": "Description 1"},
    {"column-name": "DueDate", "value": "2023-10-15"},
    {"column-name": "Completed", "value": False},
    {"column-name": "Name", "value": "Task 2"},
    {"column-name": "Description", "value": "Description 2"},
    {"column-name": "DueDate", "value": "2023-10-16"},
    {"column-name": "Completed", "value": True},
    {"column-name": "Name", "value": "Task 3"},
    {"column-name": "Description", "value": "Description 3"},
    {"column-name": "DueDate", "value": "2023-10-17"},
    {"column-name": "Completed", "value": False},
    {"column-name": "Name", "value": "Task 4"},
    {"column-name": "Description", "value": "Description 4"},
    {"column-name": "DueDate", "value": "2023-10-18"},
    {"column-name": "Completed", "value": True}
]

for task in taskList:
    todo_table.insert_data(task)

print(f"Table: {todo_table.name}")

# Print column headers
column_headers = [column.name for column in todo_table.columns]
for header in column_headers:
    print(f"{header} ",  end="")
print()

# Print rows
for row in todo_table.get_rows():
    row_values = [str(element.get_value()) for element in row]
    print(f"{row_values}")
