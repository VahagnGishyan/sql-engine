
from database.db_manager import DatabaseManager

dbmanager = DatabaseManager()
print(f"databases: {dbmanager.databases}")

db_name = "my-new-database"

if not dbmanager.database_exists(db_name):
    dbmanager.create_database(db_name)

db = dbmanager.connect(db_name)
assert (db is not None)

print(f"tables: {db.list_tables()}")

table0 = db.create_table("my-table-0")
table1 = db.create_table("my-table-1")
table2 = db.create_table("my-table-2")

print(f"tables: {db.list_tables()}")

dbmanager.disconnect_all_dbs()
