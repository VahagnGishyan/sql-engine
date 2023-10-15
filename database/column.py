
class ColumnElement:
    def __init__(self, value, type):
        self.value = value
        self.type = type


class Column:
    def __init__(self, name, type, constraints=None):
        self.name = None
        self.type = type
        self.elements = []
        self.constraints = constraints or []

        self.set_name(name)

    #########################################################

    def get_name(self):
        return self.name

    def set_name(self, name):
        if name is None or ' ' in name:
            raise ValueError("Name cannot be None or contain white spaces")
        self.name = name

    #########################################################

    def apply_constraints(self, element_value):
        for constraint in self.constraints:
            element_value = constraint.check(self, element_value, self.type)
        return element_value

    def add_element(self, value, type):
        value = self.apply_constraints(value)
        # Initialize with None, allowing data to be set later
        element = ColumnElement(value, type)
        self.elements.append(element)

    def remove_element(self, value):
        elements_to_remove = [
            element for element in self.elements if element.value == value]
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
            raise ValueError(
                f"ColumnElement with value '{old_value}' not found in the column.")

    def get_element(self, index):
        if 0 <= index < len(self.elements):
            return self.elements[index]
        else:
            raise IndexError("Index is out of range.")

    def __len__(self):
        return len(self.elements)
