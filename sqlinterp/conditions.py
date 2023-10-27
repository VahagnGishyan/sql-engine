
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
        raise NotImplementedError(
            "This is an interface method and should not be used directly")

    def execute(self, table: Table) -> list[int]:
        raise NotImplementedError(
            "This is an interface method and should not be used directly")

    # for debug
    def print(self):
        raise NotImplementedError(
            "This is an interface method and should not be used directly")


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
        # console.PrintInfo("And(Logical)")
        # self.print()

        left_result = self.leftCond.execute(table)

        # left_result_str = [str(x) for x in left_result]
        # console.PrintInfo(f"left-result: {left_result_str}")

        if len(left_result) == 0:
            return []
        right_result = self.rightCond.execute(table)

        # right_result_str = [str(x) for x in right_result]
        # console.PrintInfo(f"right-result: {right_result_str}")

        if len(left_result) == 0:
            return []
        inner_join_result = [
            index for index in left_result if index in right_result]
        return inner_join_result

    # for debug
    def print(self):
        print(f"And, left: ")
        self.leftCond.print()
        print(f"And, right: ")
        self.rightCond.print()


#############################################################


class Or(Logical):
    def __init__(self, leftCond: Condition, rightCond: Condition):
        self.leftCond = leftCond
        self.rightCond = rightCond

    def check(self, value) -> bool:
        return self.leftCond.check(value) or self.rightCond.check(value)

    def execute(self, table: Table) -> list[int]:
        # console.PrintInfo("Or(Logical)")
        # self.print()
        left_result = self.leftCond.execute(table)
        # left_result_str = [str(x) for x in left_result]
        # console.PrintInfo(f"left-result: {left_result_str}")

        right_result = self.rightCond.execute(table)
        # right_result_str = [str(x) for x in right_result]
        # console.PrintInfo(f"right-result: {right_result_str}")

        # Find the union of both lists
        union = set(left_result).union(right_result)
        # union_str = [str(x) for x in union]
        # console.PrintInfo(f"union: {union_str}")
        return union

    # for debug
    def print(self):
        print(f"Or, left: ")
        self.leftCond.print()
        print(f"Or, right: ")
        self.rightCond.print()

#############################################################


class Not(Logical):
    def __init__(self, cond: Condition):
        self.cond = cond

    def check(self, value) -> bool:
        return not self.cond.check(value)

    def execute(self, table: Table) -> list[int]:
        # console.PrintInfo("Not(Logical)")
        # self.print()
        if not table.columns or not table.columns[0].elements:
            return []
        n = len(table.columns[0].elements)
        indexes = list(range(n))

        cond_result = self.cond.execute(table)
        # cond_result_str = [str(x) for x in cond_result]
        # console.PrintInfo(f"cond-result: {cond_result_str}")
        result = [x for x in indexes if x not in cond_result]
        # result_str = [str(x) for x in result]
        # console.PrintInfo(f"result: {result_str}")
        return result

    # for debug
    def print(self):
        print(f"Not, ")
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
        print(f"Equal, column-name: {self.column_name} value: {self.value}")


#############################################################


class GreaterThan(ComparisonImpl):
    def __init__(self, column_name, value):
        super().__init__(column_name, value)

    def check(self, value) -> bool:
        return value > self.value

    # for debug
    def print(self):
        print(f"GreaterThan, column-name: {self.column_name}, value: {self.value}")


#############################################################
#                                                           #
#############################################################


class ComparisonReuse(Condition):
    def __init__(self, cond: Condition):
        self.cond: Condition = cond

    def check(self, value) -> bool:
        return self.cond.check(value)

    def execute(self, table: Table) -> list[int]:
        return self.cond.execute(table)


#############################################################


class NotEqual(ComparisonReuse):
    def __init__(self, column_name, value):
        super().__init__(Not(Equal(column_name, value)))

    # for debug
    def print(self):
        print(f"NotEqual: ")
        self.cond.print()


#############################################################


class GreaterThanOrEqualTo(ComparisonReuse):
    def __init__(self, column_name, value):
        super().__init__(Or(GreaterThan(column_name, value),
                            Equal(column_name, value)))

    # for debug
    def print(self):
        print(f"GreaterThanOrEqualTo: ")
        self.cond.print()


#############################################################


class LessThan(ComparisonReuse):
    def __init__(self, column_name, value):
        super().__init__(Not(GreaterThanOrEqualTo(column_name, value)))

    # for debug
    def print(self):
        print(f"LessThan: ")
        self.cond.print()


#############################################################


class LessThanOrEqualTo(ComparisonReuse):
    def __init__(self, column_name, value):
        super().__init__(Not(GreaterThan(column_name, value)))

    # for debug
    def print(self):
        print(f"LessThanOrEqualTo: ")
        self.cond.print()


#############################################################
#                                                           #
#############################################################
