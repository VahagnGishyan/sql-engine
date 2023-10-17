

class RowElement:
    def __init__(self, column, value, type):
        self.column = column
        self.value = value
        self.type = type


class Row:
    def __init__(self):
        self.row_elements = []

    def add_element(self, column, value, type):
        element = RowElement(column, value, type)
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
                    element.type = new_data_type
                return

    def remove_elements_by_value(self, column):
        self.row_elements = [
            element for element in self.row_elements if element.column != column]

    def get_info(self):
        # Convert rows
        row_data = []
        for element in self.row_elements:
            row_element = {
                "column-name": element.column,
                # "type": element.type,
                "value": element.value
            }
            row_data.append(row_element)

        return row_data
