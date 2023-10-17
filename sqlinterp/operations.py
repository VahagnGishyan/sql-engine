
from sqlinterp import conditions as sqlcnd
from database.table import Table
from database.column import Column

#############################################################
#                                                           #
#############################################################


class Operation:
    def execute(self):
        pass


#############################################################


class InsertInto:
    def execute(self):
        pass


#############################################################


class ConditionalBasedOperation(Operation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor]):
        self.condExecList = condExecList

    def add_condition_executor(self, condExec: sqlcnd.ConditionExecutor):
        self.condExecList.append(condExec)

    #########################################################

    def get_filtered_indexes(self, table: Table):
        # If the condExecList is empty, return an empty list
        if not self.condExecList:
            return []

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

    def execute(self, table):
        pass


#############################################################


class Select(ConditionalBasedOperation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor]):
        super.__init(condExecList)

    def execute(self, column_list: list[Column], table: Table):
        if not column_list:
            raise ValueError("No columns selected in the query.")

        index_list = self.get_filtered_indexes(table)

        result = Table("ResultTable")

        for column_name in column_list:
            column: Column = table.get_column_by_name(column_name).copy()
            column.elements = [column.elements[index] for index in index_list]
            result.insert_column(column)

        return result


#############################################################


class Delete(ConditionalBasedOperation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor]):
        super.__init(condExecList)

    def execute(self, column_list: list[Column], table: Table):
        # Get the indexes to delete based on the condition
        index_list = self.get_filtered_indexes(table)
        # Remove rows with the obtained indexes
        for index in reversed(index_list):
            table.remove_row(index)

#############################################################


class Update(ConditionalBasedOperation):
    def __init__(self, condExecList: list[sqlcnd.ConditionExecutor]):
        super.__init(condExecList)

    def execute(self, table, values: list):
        if not values:
            raise ValueError("No values provided for update.")
        index_list = self.get_filtered_indexes(table)
        for index in index_list:
            for value in values:
                for column_name, new_value in value.items():
                    column = table.get_column_by_name(column_name)
                    if column:
                        element = column.get_element(index)
                        if element:
                            element.set_value(new_value)


#############################################################
#                                                           #
#############################################################
