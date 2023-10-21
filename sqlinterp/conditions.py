
from database.table import Table
from database.column import Column, ColumnElement
from database import column as cl
from utility import console

#############################################################
#                                                           #
#############################################################


# possible conditions
#   Comparison          =, !=, >, <. >=, <=
#   Logical             And, Or, Not
#   Pattern Matching:   Like, NOT LIKE
#   Null:               IS NULL/IS NOT NULL
#   IN:
#   BETWEEN:            From, To
#   EXISTS
#   Functions:          UPPER(), LOWER(), LENGTH(), DATE()

# supported conditions [temp, in pp]
# Comparison and Logical


#############################################################
#                                                           #
#############################################################


class Condition:
    def check(self, value) -> bool:
        pass

    def execute(self, table: Table) -> list[int]:
        pass

    # for debug
    def print(self):
        pass


#############################################################


class Comparison(Condition):
    def check(value) -> bool:
        pass


#############################################################
#                                                           #
#############################################################


class Logical(Condition):
    pass


#############################################################


class And(Logical):
    def __init__(self, leftCond: Condition, rightCond: Condition):
        self.leftCond = leftCond
        self.rightCond = rightCond

    def check(self, value) -> bool:
        return self.leftCond.check(value) and self.rightCond.check(value)

    def execute(self, table: Table) -> list[int]:
        left_result = self.leftCond.execute(table)
        if len(left_result) == 0:
            return []
        right_result = self.rightCond.execute(table)
        if len(left_result) == 0:
            return []
        inner_join_result = [
            index for index in left_result if index in right_result]
        return inner_join_result

    # for debug
    def print(self):
        print(f"And, left: ", end="")
        self.leftCond.print()
        print(f"And, right: ", end="")
        self.rightCond.print()


#############################################################


class Or(Logical):
    def __init__(self, leftCond: Condition, rightCond: Condition):
        self.leftCond = leftCond
        self.rightCond = rightCond

    def check(self, value) -> bool:
        return self.leftCond.check(value) or self.rightCond.check(value)

    def execute(self, table: Table) -> list[int]:
        left_result = self.leftCond.check(table)
        right_result = self.rightCond.check(table)
        # Find the union of both lists
        union = set(left_result).union(right_result)
        # Find indexes that exist in both lists
        common_indexes = [
            index for index in union if index in left_result and index in right_result]
        return common_indexes

    # for debug
    def print(self):
        print(f"Or, left: ", end="")
        self.leftCond.print()
        print(f"Or, right: ", end="")
        self.rightCond.print()

#############################################################


class Not(Logical):
    def __init__(self, cond: Condition):
        self.cond = cond

    def check(self, value) -> bool:
        return not self.cond.check(value)

    def execute(self, table: Table) -> list[int]:
        if not table.columns or table.columns[0].elements:
            return []
        n = len(table.columns[0])
        indexes = list(range(n + 1))

        cond_result = self.leftCond.check(table)
        result = [x for x in cond_result if x not in indexes]
        return result

    # for debug
    def print(self):
        print(f"Not, ", end="")
        self.cond.print()


#############################################################
#                                                           #
#############################################################


class ComparisonImpl(Condition):
    def __init__(self, column_name, value):
        self.column_name = column_name
        self.value = value

    def execute(self, table: Table) -> list[int]:
        indexes: list[int] = []
        column: Column = table.get_column_by_name(self.column_name)
        elements: list[ColumnElement] = column.elements
        index = -1
        for element in elements:
            index += 1
            if self.check(element.get_value()):
                indexes.append(index)
        return indexes


#############################################################


class Equal(ComparisonImpl):
    def __init__(self, column_name, value):
        super().__init__(column_name, value)

    def check(self, value) -> bool:
        return self.value == value

    # for debug
    def print(self):
        print(f"Equal, value: {self.value}", end="")


#############################################################


class GreaterThan(ComparisonImpl):
    def __init__(self, column_name, value):
        super().__init__(column_name, value)

    def check(self, value) -> bool:
        return value > self.value

    # for debug
    def print(self):
        print(f"GreaterThan, value: {self.value}", end="")


#############################################################
#                                                           #
#############################################################


class ComparisonReuse(Condition):
    def __init__(self, cond):
        self.cond = cond

    def check(self, table: Table) -> list[int]:
        return self.cond.check(table)

#############################################################


class NotEqual(ComparisonReuse):
    def __init__(self, column_name, value):
        self.cond = Not(Equal(column_name, value))

    # for debug
    def print(self):
        print(f"NotEqual: ", end="")
        self.cond.print()


#############################################################


class GreaterThanOrEqualTo(ComparisonReuse):
    def __init__(self, column_name, value):
        self.cond = Or(GreaterThan(column_name, value),
                       Equal(column_name, value))

    # for debug
    def print(self):
        print(f"GreaterThanOrEqualTo: ", end="")
        self.cond.print()


#############################################################


class LessThan(ComparisonReuse):
    def __init__(self, column_name, value):
        self.cond = Not(GreaterThanOrEqualTo(column_name, value))

    # for debug

    def print(self):
        print(f"LessThan: ", end="")
        self.cond.print()


#############################################################


class LessThanOrEqualTo(ComparisonReuse):
    def __init__(self, column_name, value):
        self.cond = Not(GreaterThan(column_name, value))

    # for debug
    def print(self):
        print(f"LessThanOrEqualTo: ", end="")
        self.cond.print()


#############################################################
#                                                           #
#############################################################
