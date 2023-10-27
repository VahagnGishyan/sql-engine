

#############################################################
#                                                           #
#############################################################


class State:
    def __init__(self):
        self.state = {}

        self.set_default()

    #########################################################

    def __getitem__(self, key):
        return self.get_state(key)

    #########################################################

    def set_default(self):
        self.state["condition"] = True

    #########################################################

    def get_state(self, state_key: str):
        if state_key in self.state:
            return self.state[state_key]
        else:
            raise KeyError(f"'{state_key}' not found")

    def set_state(self, state_key: str, state_value):
        self.state[state_key] = state_value

    #########################################################


#############################################################
#                                                           #
#############################################################
