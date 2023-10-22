
from utility import console
from cli.state import State

#############################################################
#                                                           #
#############################################################


class Executor:
    def __init__(self, state: State):
        self.state = state

    #########################################################

    def cmd_exit(self):
        self.state.set_state("condition", False)

    #########################################################

    def execute(self, task: dict):
        command = task["command"]
        if command == "exit":
            self.cmd_exit()
            return
        console.PrintWarning(f"command: {command} is not supported yet.")

    #########################################################


#############################################################
#                                                           #
#############################################################
