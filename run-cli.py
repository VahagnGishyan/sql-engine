
from cli.wrapper import DBWrapper
from cli.wrapper import DBWrapperPythonLib
from utility import console

dbwrapper: DBWrapper = DBWrapperPythonLib()

#####################################################

db_name = "my-test-db-for-cli"

#####################################################

if not dbwrapper.database_exists(db_name):
    dbwrapper.create(db_name)

dbwrapper.connect(db_name)

#####################################################

table0 = "table-0"
table1 = "table-1"

# dbwrapper.create_table(db_name, table0, [
#     ('column-00', 'value-00'),
#     ('column-01', 'value-01')])
# dbwrapper.create_table(db_name, table1, [
#     ('column-10', 'value-10'),
#     ('column-11', 'value-11')])

#####################################################

console.PrintInfo(f"table-list: {dbwrapper.list_tables(db_name)}")

#####################################################


#####################################################

dbwrapper.disconnect(db_name)
dbwrapper.close()
# dbwrapper.drop()
