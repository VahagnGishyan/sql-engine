
import argparse
from utility import console
from cli.input_parser import InputParser
from cli.executor import Executor
from cli.state import State

#############################################################
#                                                           #
#############################################################


class CLILoop:
    def __init__(self, state=State()):
        self.state = state
        self.input_parser = InputParser(state)
        self.executor = Executor(state)

    #########################################################

    def print_application_description(self):
        console.PrintSignal("sql-engine")
        console.PrintInfo("version: 0.4.1")
        pass

    def start_app(self):
        self.print_application_description()

    #########################################################

    def close_app(self):
        pass

    #########################################################

    def read_user_input(self) -> str:
        user_input = input("Enter a command: ")
        return user_input

    #########################################################

    def parse_input(self, cmd_list: str) -> map:
        return self.input_parser.parse(cmd_list)

    #########################################################

    def execute(self, task: dict):
        self.executor.execute(task)

    #########################################################

    def loop(self):
        self.start_app()

        while self.state.get_state("condition") == True:
            try:
                user_input = self.read_user_input()
                task = self.parse_input(user_input)
                self.execute(task)
            except Exception as e:
                console.PrintError(f"{__name__}, loop(), error-message: {e}")

        self.close_app()


#############################################################
#                                                           #
#############################################################
