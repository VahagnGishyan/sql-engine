
from sqlinterp import conditions as sqlcnd
from database.table import Table
from database.column import Column
from database.row import Row
# from utility import console

#############################################################
#                                                           #
#############################################################


class Operation:
    def execute(self):
        pass


#############################################################


class InsertInto(Operation):
    def __init__(self, values: list, condExecList: list[sqlcnd.ConditionExecutor] = []):
        self.values = values

    def execute(self, table: Table):
        if not self.values:
            raise ValueError("No values provided for insert.")
        new_rows = []
        for value in self.valuesvalues:
            new_row = Row()
            for column_name, new_value in value.items():
                column: Column = table.get_column_by_name(column_name)
                if column:
                    new_row.add_element(column_name, new_value)

            new_rows.append(new_row)

        table.insert_rows(new_rows)
        return table


#############################################################


class ConditionalBasedOperation(Operation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor] = []):
        self.condExecList = condExecList

    def add_condition_executor(self, condExec: sqlcnd.ConditionExecutor):
        self.condExecList.append(condExec)

    #########################################################

    def get_filtered_indexes(self, table: Table):
        # If the condExecList is empty, return an empty list
        if not self.condExecList:
            n = len(table.columns[0])
            index_list = [i for i in range(n)]
            return index_list

        # Initialize the index_list with the indices from the first condition
        index_list = self.condExecList[0].execute(table)

        # Iterate over the rest of the ConditionExecutors and update the index_list
        for condExec in self.condExecList[1:]:
            new_index_list = condExec.execute(table)
            # Filter the indices that are common in both lists
            index_list = [
                index for index in index_list if index in new_index_list]

            # If at any point, the new_index_list becomes empty, return an empty list
            if not index_list:
                return []

        return index_list

    #########################################################

    def execute(self, table: Table):
        pass


#############################################################


class Select(ConditionalBasedOperation):
    def __init__(self, column_list: list[Column], condExecList: list[sqlcnd.ConditionExecutor] = []):
        super().__init__(condExecList)
        self.column_list = column_list

    def execute(self, table: Table):
        if not self.column_list:
            raise ValueError("No columns selected in the query.")

        if self.column_list[0] == "*":
            self.column_list = table.list_columns()
        print()

        index_list = self.get_filtered_indexes(table)

        result = Table("ResultTable")

        for column_name in self.column_list:
            column: Column = table.get_column_by_name(column_name).copy()
            column.elements = [column.elements[index] for index in index_list]
            result.insert_column(column)

        return result


#############################################################


class Delete(ConditionalBasedOperation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor] = []):
        super.__init__(condExecList)

    def execute(self, table: Table):
        # Get the indexes to delete based on the condition
        index_list = self.get_filtered_indexes(table)
        # Remove rows with the obtained indexes
        for index in reversed(index_list):
            table.remove_row(index)

#############################################################


class Update(ConditionalBasedOperation):
    def __init__(self, values: list, condExecList: list[sqlcnd.ConditionExecutor] = []):
        super.__init__(condExecList)
        self.values = values

    def execute(self, table: Table):
        if not self.values:
            raise ValueError("No values provided for update.")
        index_list = self.get_filtered_indexes(table)
        for index in index_list:
            for value in self.values:
                for column_name, new_value in value.items():
                    column = table.get_column_by_name(column_name)
                    if column:
                        element = column.get_element(index)
                        if element:
                            element.set_value(new_value)


#############################################################
#                                                           #
#############################################################
