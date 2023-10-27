

#############################################################


class ConstraintException(Exception):
    def __init(self, element_name, constraint_name):
        super().__init(
            f"{element_name} constraint '{constraint_name}' violation.")


#############################################################


class ConstraintNotNull:

    def copy(self):
        constraint = ConstraintNotNull()
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        if element_value is None:
            raise ConstraintException("NULL", "NOT NULL")
        return element_value

    def get_info(self):
        constraint_info = {
            "name": "not-null"
        }

#############################################################


class ConstraintUnique:
    def __init__(self):
        self.values = set()

    def copy(self):
        constraint = ConstraintUnique()
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        if element_value in self.values:
            raise ConstraintException(element_value, "UNIQUE")
        self.values.add(element_value)
        return (element_value)

    def get_info(self):
        constraint_info = {
            "name": "unique"
        }

#############################################################


class ConstraintPrimaryKey(ConstraintUnique):

    def copy(self):
        constraint = ConstraintPrimaryKey()
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        super().check(column, element_value, element_type)
        if element_value is None:
            raise ConstraintException(element_value, "PRIMARY KEY")
        return (element_value)

    def get_info(self):
        constraint_info = {
            "name": "primary-key"
        }


#############################################################


class ConstraintForeignKey:
    def __init__(self, reference_table, referenced_element):
        self.reference_table = reference_table
        self.referenced_element = referenced_element

    def copy(self):
        constraint = ConstraintForeignKey(
            self.reference_table, self.referenced_element)
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        # Implement logic to check if the reference exists in the reference_table
        # Return the element_value if the reference exists, otherwise raise an exception
        if not reference_exists(element_value, self.reference_table, self.referenced_element):
            raise ConstraintException(element_value, "Foreign KEY")
        return element_value

    def get_info(self):
        constraint_info = {
            "name": "foreign-key"
        }


def reference_exists(element_value, reference_table, referenced_element):
    # Implement logic to check if the reference exists in the reference_table
    # Return True if the reference exists, otherwise return False
    # Need to define this logic based on your database or data structure
    raise NotImplementedError(
        "ConstraintForeignKey::reference_exists(), function not yet implemented")
    # temp


#############################################################


class ConstraintCheck:
    def __init__(self, check_func):
        self.check_func = check_func

    def copy(self):
        constraint = ConstraintCheck(self.check_func)
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        if not self.check_func(column, element_value, element_type):
            raise ConstraintException(element_value, "CHECK")
        return element_value

    def get_info(self):
        raise NotImplementedError(
            "ConstraintCheck::get_info(), function not yet implemented")


#############################################################


class ConstraintDefault:
    def __init__(self, default_value):
        self.default_value = default_value

    def copy(self):
        constraint = ConstraintDefault(self.default_value)
        return constraint

    #########################################################

    def check(self, column, element_value, element_type):
        if element_value is None:
            return self.default_value
        return element_value

    def get_info(self):
        constraint_info = {
            "name": "default",
            "value": self.default_value
        }

#############################################################


class ConstraintCreateIndex:
    def __init__(self, index_name):
        self.index_name = index_name

    def copy(self):
        constraint = ConstraintCreateIndex(self.index_name)
        return constraint

    #########################################################

    def check(self, element_value, column, element_type):
        # Implement logic to create an index in the specified database and column
        raise NotImplementedError(
            "ConstraintCreateIndex::check(), method not yet implemented")
        # temp

    def get_info(self):
        raise NotImplementedError(
            "ConstraintCreateIndex::get_info(), method not yet implemented")

#############################################################
