
from database import element as db

class Column:
    def __init__(self, name, type, constraints=None):
        self.name = name
        self.type = type
        self.elements = []
        self.constraints = constraints or []

    def __len__(self):
        return len(self.elements)

    def apply_constraints(self, element_value):
        for constraint in self.constraints:
            element_value = constraint.check(self, element_value, self.type)
        return element_value
    
    def add_element(self, value, type):
        value = self.apply_constraints(value)
        element = db.Element(value, type)  # Initialize with None, allowing data to be set later
        self.elements.append(element)

    def remove_element(self, value):
        elements_to_remove = [element for element in self.elements if element.value == value]
        for element in elements_to_remove:
            self.elements.remove(element)

    def update_element(self, old_value, new_value, new_type=None):
        element_to_update = next(
            (element for element in self.elements if element.value == old_value), None
        )
        if element_to_update:
            element_to_update.value = self.apply_constraints(new_value)
            if new_type:
                element_to_update.type = new_type
        else:
            raise ValueError(f"Element with value '{old_value}' not found in the column.")
