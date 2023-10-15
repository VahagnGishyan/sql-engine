

class RowElement:
    def __init__(self, column, value, data_type):
        self.column = column
        self.value = value
        self.data_type = data_type


class Row:
    def __init__(self):
        self.row_elements = []

    def add_element(self, column, value, data_type):
        element = RowElement(column, value, data_type)
        self.row_elements.append(element)

    def get_element(self, column):
        for element in self.row_elements:
            if element.column == column:
                return element
        return None

    def update_element(self, column, new_value, new_data_type=None):
        for element in self.row_elements:
            if element.column == column:
                element.value = new_value
                if new_data_type:
                    element.data_type = new_data_type
                return

    def remove_element(self, column):
        self.row_elements = [
            element for element in self.row_elements if element.column != column]
