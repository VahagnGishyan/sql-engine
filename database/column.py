
import element as db

class Column:
    def __init__(self, name, data_type, constraints=None):
        self.name = name
        self.data_type = data_type
        self.elements = []
        self.constraints = constraints or []

    def apply_constraints(self, element_value):
        for constraint in self.constraints:
            element_value = constraint.check(element_value)
        return element_value
    
    def add_element(self, value, type):
        value = self.apply_constraints(value)
        element = db.Element(value, type)  # Initialize with None, allowing data to be set later
        self.elements.append(element)

    def remove_element_by_value(self, value):
        elements_to_remove = [element for element in self.elements if element.value == value]
        for element in elements_to_remove:
            self.elements.remove(element)
