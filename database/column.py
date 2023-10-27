
class ColumnElement:
    def __init__(self, value):
        self.value = None
        self.set_value(value)

    def get_value(self):
        return self.value

    def set_value(self, value):
        self.value = value

    def copy(self):
        newclm = ColumnElement(self.get_value())
        return newclm


class Column:
    def __init__(self, name, type, constraints=None):
        self.name = None
        self.type = type
        self.elements = []
        self.constraints = constraints or []

        self.set_name(name)

    def copy(self):
        constraints = []
        for constraint in self.constraints:
            constraints.append(constraint.copy())
        newclm = Column(self.get_name(), self.type, constraints)
        for element in self.elements:
            newclm.add_element(element.get_value())
        return newclm

    #########################################################

    def get_name(self):
        return self.name

    def set_name(self, name):
        if name is None or ' ' in name:
            raise ValueError("Name cannot be None or contain white spaces")
        self.name = name

    #########################################################

    def get_type(self):
        return self.type

    def set_type(self, type):
        if type is None or ' ' in type:
            raise ValueError("Type cannot be None or contain white spaces")
        self.type = type

    #########################################################

    def apply_constraints(self, element_value):
        for constraint in self.constraints:
            element_value = constraint.check(self, element_value, self.type)
        return element_value

    def add_element(self, value):
        if isinstance(value, ColumnElement):
            value = value.get_value()
        value = self.apply_constraints(value)
        # Initialize with None, allowing data to be set later
        element = ColumnElement(value)
        self.elements.append(element)

    def remove_elements_by_value(self, value):
        elements_to_remove = [
            element for element in self.elements if element.get_value() == value]
        for element in elements_to_remove:
            self.elements.remove(element)

    def remove_elements_except_value(self, value):
        elements_to_remove = [
            element for element in self.elements if element.get_value() != value]
        for element in elements_to_remove:
            self.elements.remove(element)

    def remove_element_by_index(self, index):
        if index < 0 or index >= len(self.elements):
            raise ValueError("Index is out of range")
        removed_element = self.elements.pop(index)
        return removed_element

    def remove_element_by_index_list(self, index_list):
        index_list.sort(reverse=True)
        for index in index_list:
            self.remove_element_by_index(index)

    def update_element(self, old_value, new_value):
        element_to_update = next(
            (element for element in self.elements if element.get_value() == old_value), None
        )
        if element_to_update:
            element_to_update.set_value(self.apply_constraints(new_value))
        else:
            raise ValueError(
                f"ColumnElement with value '{old_value}' not found in the column.")

    def get_element(self, index):
        if 0 <= index < len(self.elements):
            return self.elements[index]
        else:
            raise IndexError("Index is out of range.")

    def get_elements(self):
        return self.elements

    #########################################################

    def __len__(self):
        return len(self.elements)
