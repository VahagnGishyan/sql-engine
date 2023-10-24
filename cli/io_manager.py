
from cli.state import State
from utility import console
from database.table import Table

#############################################################
#                                                           #
#############################################################


class IOManager:
    def read(self):
        pass

    def print(self):
        pass


#############################################################
#                                                           #
#############################################################

class ConsoleIOManager:
    def __init__(self, state: State):
        self.state = state

    #########################################################

    def read(self) -> str:
        user_input = input("Enter a command: ")
        return user_input

    #########################################################

    def print_table(self, table: Table):
        console.PrintInfo(f"table: {table.get_name()}")
        console.PrintInfo(f"columns: {table.list_columns()}")

        console.PrintInfo(f"rows: ")
        rows = table.get_info_rows()
        index = -1
        for row in rows:
            index += 1
            console.PrintInfo(f"\t[{index}] row: {row}")

    def print(self, result):
        if result is not None and isinstance(result, Table):
            self.print_table(result)


#############################################################
#                                                           #
#############################################################
