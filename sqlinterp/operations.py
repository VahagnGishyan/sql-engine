
from sqlinterp.conditions import Condition
from database.table import Table
from database.column import Column, ColumnElement
from database.row import Row
from utility import console

#############################################################
#                                                           #
#############################################################


class Operation:
    def execute(self, table: Table) -> Table:
        pass

    # for debug
    def print(self):
        pass


#############################################################


class InsertInto(Operation):
    def __init__(self, values: list):
        self.values = values

    def execute(self, table: Table) -> Table:
        if not self.values:
            raise ValueError("No values provided for insert.")
        table.insert_data(self.values)
        return table

    # for debug
    def print(self):
        console.PrintInfo("[InsertInto]")
        print(f"values: {self.values}")


#############################################################


class ConditionalBasedOperation(Operation):
    def __init__(self, condition: Condition = None):
        self.condition = condition

    def set_condition(self, condExec: Condition):
        self.condition.append(condExec)

    def get_filtered_indexes(self, table: Table):
        if not table.columns:
            return []
        if not self.condition:
            return list(range(len(table.columns[0])))
        index_list = self.condition.execute(table)
        return index_list

    #########################################################

    def execute(self, table: Table) -> Table:
        pass


#############################################################


class Select(ConditionalBasedOperation):
    def __init__(self, column_list: list[Column], condition: Condition = None):
        super().__init__(condition)
        self.column_list = column_list

    def execute(self, table: Table) -> Table:
        if not self.column_list:
            raise ValueError("No columns selected in the query.")

        if self.column_list[0] == "*":
            self.column_list = table.list_columns()

        index_list = self.get_filtered_indexes(table)

        result = Table("ResultTable")

        for column_name in self.column_list:
            column: Column = table.get_column_by_name(column_name).copy()
            column.elements = [column.elements[index] for index in index_list]
            result.insert_column(column)

        return result

    # for debug
    def print(self):
        console.PrintInfo("[Select]")
        print(f"column-list: {self.column_list}")
        if self.condition:
            condExec = self.condition[0]
            print(f"condition: ", end="")
            condExec.print()


#############################################################


class Delete(ConditionalBasedOperation):
    def __init__(self, condition: Condition = None):
        super().__init__(condition)

    def execute(self, table: Table):
        # Get the indexes to delete based on the condition
        index_list = self.get_filtered_indexes(table)

        # Remove rows with the obtained indexes
        for index in reversed(index_list):
            table.remove_row(index)

    # for debug
    def print(self):
        console.PrintInfo("[Delete]")
        if self.condition:
            condExec = self.condition[0]
            print(f"condition: ", end="")
            condExec.print()

#############################################################


class Update(ConditionalBasedOperation):
    def __init__(self, values: list, condition: Condition = None):
        super().__init__(condition)
        self.values = values

    def execute(self, table: Table):
        if not self.values:
            raise ValueError("No values provided for update.")
        index_list = self.get_filtered_indexes(table)
        for index in index_list:
            for value in self.values:
                column: Column = table.get_column_by_name(value["column-name"])
                element: ColumnElement = column.elements[index]
                element.set_value(value["value"])

    # for debug
    def print(self):
        console.PrintInfo("[Update]")
        print(f"values: {self.values}")
        if self.condition:
            condExec = self.condition[0]
            print(f"condition: ", end="")
            condExec.print()


#############################################################
#                                                           #
#############################################################
