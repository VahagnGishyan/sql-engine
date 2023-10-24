
import argparse
from utility import console
from cli.input_parser import InputParser
from cli.executor import Executor
from cli.state import State
from cli.visitor import Visitor, DefaultVisitor
from cli.input_reader import InputReader, ConsoleInputReader

#############################################################
#                                                           #
#############################################################


class CLILoop:
    def __init__(self, state=State()):
        self.state = state
        self.input_parser = InputParser(state)
        self.executor = Executor(state)
        self.visitor: Visitor = DefaultVisitor(state)
        self.ireader: InputReader = ConsoleInputReader(state)

    #########################################################

    def read_user_input(self) -> str:
        return self.ireader.read()

    #########################################################

    def parse_input(self, cmd_list: str) -> map:
        return self.input_parser.parse(cmd_list)

    #########################################################

    def execute(self, task: dict):
        self.executor.execute(task)

    #########################################################

    def loop(self):
        self.visitor.start_loop()

        while self.state.get_state("condition") == True:
            try:
                self.visitor.start_iter()

                user_input = self.read_user_input()
                self.visitor.user_input(user_input)

                task = self.parse_input(user_input)
                self.visitor.parsed_input(task)

                self.execute(task)

                self.visitor.close_iter()
            except Exception as e:
                console.PrintError(f"{__name__}, loop(), error-message: {e}")

        self.visitor.close_loop()


#############################################################
#                                                           #
#############################################################


