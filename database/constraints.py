

#############################################################


class CheckConstraintException(Exception):
    def __init__(self, element_name, constraint_name):
        super().__init(f"{element_name} constraint '{constraint_name}' violation.")


#############################################################


class CheckNotNull:
    def check(self, table, element_value, element_type):
        if element_value is None:
            raise CheckConstraintException(self.element_value, "NOT NULL")
        return element_value


#############################################################
    

class CheckUnique:
    def __init__(self):
        self.values = set()

    def check(self, table, element_value, element_type):
        if element_value in self.values:
            raise CheckConstraintException(element_value, "UNIQUE")
        self.values.add(element_value)
        return (element_value)


#############################################################


class CheckPrimaryKey(CheckUnique):
    def check(self, table, element_value, element_type):
        super().check(element_value)
        if element_value is None:
            raise CheckConstraintException(element_value, "PRIMARY KEY")
        return (element_value)


#############################################################


class ConstraintForeignKey:
    def __init__(self, reference_table, referenced_element):
        self.reference_table = reference_table
        self.referenced_element = referenced_element

    def check(self, element_value, table, element_type):
        # Implement logic to check if the reference exists in the reference_table
        # Return the element_value if the reference exists, otherwise raise an exception
        if not reference_exists(element_value, self.reference_table, self.referenced_element):
            raise CheckConstraintException(element_value, "Foreign KEY")
        return element_value


def reference_exists(element_value, reference_table, referenced_element):
    # Implement logic to check if the reference exists in the reference_table
    # Return True if the reference exists, otherwise return False
    # Need to define this logic based on your database or data structure
    raise NotImplementedError("ConstraintForeignKey::reference_exists(), function not yet implemented")
    #temp


#############################################################


class ConstraintCheck:
    def __init__(self, check_func):
        self.check_func = check_func

    def check(self, element_value, table, element_type):
        if not self.check_func(element_value):
            raise CheckConstraintException(element_value, "CHECK")
        return element_value


#############################################################


class ConstraintDefault:
    def __init__(self, default_value):
        self.default_value = default_value

    def check(self, element_value, table, element_type):
        if element_value is None:
            return self.default_value
        return element_value
    

#############################################################


class ConstraintCreateIndex:
    def __init__(self, index_name):
        self.index_name = index_name

    def check(self, element_value, table, element_type):
        # Implement logic to create an index in the specified database and table
        raise NotImplementedError("ConstraintCreateIndex::check(), method not yet implemented")
        #temp

#############################################################


# Example usage
def apply_constraint(constraint, element_value):
    constraint.check(element_value)


#############################################################

