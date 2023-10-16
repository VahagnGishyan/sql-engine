

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
    [("Name", "Task 1"), ("Description", "Description 1"),
     ("DueDate", "2023-10-15"), ("Completed", False)],
    [("Name", "Task 2"), ("Description", "Description 2"),
     ("DueDate", "2023-10-16"), ("Completed", True)],
    [("Name", "Task 3"), ("Description", "Description 3"),
     ("DueDate", "2023-10-17"), ("Completed", False)],
    [("Name", "Task 4"), ("Description", "Description 4"),
     ("DueDate", "2023-10-18"), ("Completed", True)],
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
    row_values = [str(element.value) for element in row]
    print(f"{row_values}")
