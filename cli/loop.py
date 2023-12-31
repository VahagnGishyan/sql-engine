
import argparse
from utility import console
from cli.input_parser import InputParser
from cli.executor import Executor
from cli.state import State
from cli.visitor import Visitor, DefaultVisitor
from cli.io_manager import IOManager, ConsoleIOManager

#############################################################
#                                                           #
#############################################################


class CLILoop:
    def __init__(self, state=State()):
        self.state = state
        self.input_parser = InputParser(state)
        self.executor = Executor(state)
        self.io: IOManager = ConsoleIOManager(state)
        self.visitor: Visitor = DefaultVisitor(self)

    #########################################################

    def read_user_input(self) -> str:
        return self.io.read()

    #########################################################

    def parse_input(self, cmd_list: str) -> map:
        return self.input_parser.parse(cmd_list)

    #########################################################

    def execute(self, task: dict):
        result = self.executor.execute(task)
        return result

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

                result = self.execute(task)
                self.visitor.execution_result(result)
                self.io.print(result)

                self.visitor.close_iter()

            except Exception as e:
                console.PrintError(f"loop(), error-message: {e}")

        self.visitor.close_loop()


#############################################################
#                                                           #
#############################################################
