
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

    def execution_result(self, result):
        pass

    def close_iter(self):
        pass

    def close_loop(self):
        pass


#############################################################
#                                                           #
#############################################################

class DefaultVisitor:
    def __init__(self, loop):
        self.loop = loop

    #########################################################

    def print_application_description(self):
        console.PrintSignal("sql-engine")
        console.PrintInfo("version: 1.0.0")
        task = {"command": "list-db"}
        console.PrintInfo(self.loop.executor.execute(task))

    def start_loop(self):
        self.print_application_description()

    #########################################################

    def start_iter(self):
        pass

    def user_input(self, user_input):
        pass

    def parsed_input(self, task):
        pass

    def execution_result(self, result):
        pass

    def close_iter(self):
        pass

    def close_loop(self):
        self.loop.executor.close()


#############################################################
#                                                           #
#############################################################
