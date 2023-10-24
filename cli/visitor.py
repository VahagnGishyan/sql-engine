
from cli.state import State
from utility import console

#############################################################
#                                                           #
#############################################################


class Visitor:
    def start_loop(self):
        pass

    def start_iter(self):
        pass

    def user_input(self, user_input):
        pass

    def parsed_input(self, task):
        pass

    def close_iter(self):
        pass

    def close_loop(self):
        pass


#############################################################
#                                                           #
#############################################################

class DefaultVisitor:
    def __init__(self, state: State):
        self.state = state

    #########################################################

    def print_application_description(self):
        console.PrintSignal("sql-engine")
        console.PrintInfo("version: 0.4.1")

    def start_loop(self):
        self.print_application_description()

    #########################################################

    def start_iter(self):
        pass

    def user_input(self, user_input):
        pass

    def parsed_input(self, task):
        pass

    def close_iter(self):
        pass

    def close_loop(self):
        pass


#############################################################
#                                                           #
#############################################################
