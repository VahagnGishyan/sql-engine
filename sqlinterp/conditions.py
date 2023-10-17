
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

#############################################################


class ConditionExecutor:
    def __init__(self, column_name, cond: Condition):
        self.column_name = column_name
        self.cond = cond

    def execute(self, table):
        column = table.get_column_by_name(self.column_name)
        index_list = []
        index = 0
        for element in column.elements:  # Iterate through elements in the column
            index += 1
            # Evaluate the condition against the element's value
            if self.cond.check(element.value):
                index_list.append(index)

        return index_list


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


#############################################################


class Or(Logical):
    def __init__(self, leftCond: Condition, rightCond: Condition):
        self.leftCond = leftCond
        self.rightCond = rightCond

    def check(self, value):
        return self.leftCond.check(value) or self.rightCond.check(value)

#############################################################


class Not(Logical):
    def __init__(self, cond: Condition):
        self.cond = cond

    def check(self, value):
        return not self.cond.check(value)


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

#############################################################


class NotEqual(Comparison):
    def __init__(self, value):
        self.cond = Not(Equal(value))

    def check(self, value):
        return self.cond.check(value)


#############################################################


class GreaterThan(Comparison):
    def __init__(self, value):
        self.value = value

    def check(self, value):
        return value > self.value


#############################################################


class GreaterThanOrEqualTo(Comparison):
    def __init__(self, value):
        self.cond = Or(GreaterThan(value), Equal(value))

    def check(self, value):
        return self.cond.check(value)


#############################################################


class LessThan(Comparison):
    def __init__(self, value):
        self.cond = Not(GreaterThanOrEqualTo(value))

    def check(self, value):
        return self.cond.check(value)


#############################################################


class LessThanOrEqualTo(Comparison):
    def __init__(self, value):
        self.cond = Not(GreaterThan(value))

    def check(self, value):
        return self.cond.check(value)


#############################################################
#                                                           #
#############################################################
