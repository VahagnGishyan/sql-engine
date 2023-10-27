
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

    def print_str(self, result: str):
        console.PrintInfo(result)

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

    #########################################################

    def try_to_print(self, result):
        console.PrintInfo(f"result: {result}")

    #########################################################

    def print(self, result):
        if result is None:
            return

        if isinstance(result, str):
            self.print_str(result)
            return

        if isinstance(result, Table):
            self.print_table(result)
            return

        self.try_to_print(result)

    #########################################################

#############################################################
#                                                           #
#############################################################
