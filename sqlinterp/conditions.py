
from database import table as tb
from database import column as cl

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
    def check(self, value):
        pass

    # for debug
    def print(self):
        pass

#############################################################


class ConditionExecutor:
    def __init__(self, column_name, cond: Condition):
        self.column_name = column_name
        self.cond = cond

    def execute(self, table):
        column = table.get_column_by_name(self.column_name)
        index_list = []
        index = -1
        for element in column.elements:  # Iterate through elements in the column
            index += 1
            # Evaluate the condition against the element's value
            if self.cond.check(element.value):
                index_list.append(index)

        return index_list

    # for debug
    def print(self):
        print(f"[ConditionExecutor] column-name: {self.column_name}, ", end="")
        self.cond.print()
        print()

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

    def check(self, value):
        return self.leftCond.check(value) and self.rightCond.check(value)

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

    def check(self, value):
        return self.leftCond.check(value) or self.rightCond.check(value)

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

    def check(self, value):
        return not self.cond.check(value)

    # for debug
    def print(self):
        print(f"Not, ", end="")
        self.cond.print()


#############################################################
#                                                           #
#############################################################


class Comparison(Condition):
    def check(self, value):
        pass


#############################################################


class Equal(Comparison):
    def __init__(self, value):
        self.value = value

    def check(self, value):
        return self.value == value

    # for debug
    def print(self):
        print(f"Equal, value: {self.value}", end="")

#############################################################


class NotEqual(Comparison):
    def __init__(self, value):
        self.cond = Not(Equal(value))

    def check(self, value):
        return self.cond.check(value)

    # for debug
    def print(self):
        print(f"NotEqual: ", end="")
        self.cond.print()


#############################################################


class GreaterThan(Comparison):
    def __init__(self, value):
        self.value = value

    def check(self, value):
        return value > self.value

    # for debug
    def print(self):
        print(f"GreaterThan, value: {self.value}", end="")


#############################################################


class GreaterThanOrEqualTo(Comparison):
    def __init__(self, value):
        self.cond = Or(GreaterThan(value), Equal(value))

    def check(self, value):
        return self.cond.check(value)

    # for debug
    def print(self):
        print(f"GreaterThanOrEqualTo: ", end="")
        self.cond.print()


#############################################################


class LessThan(Comparison):
    def __init__(self, value):
        self.cond = Not(GreaterThanOrEqualTo(value))

    def check(self, value):
        return self.cond.check(value)

    # for debug
    def print(self):
        print(f"LessThan: ", end="")
        self.cond.print()


#############################################################


class LessThanOrEqualTo(Comparison):
    def __init__(self, value):
        self.cond = Not(GreaterThan(value))

    def check(self, value):
        return self.cond.check(value)

    # for debug
    def print(self):
        print(f"LessThanOrEqualTo: ", end="")
        self.cond.print()


#############################################################
#                                                           #
#############################################################
