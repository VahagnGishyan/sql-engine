
import argparse
from utility import console

#############################################################
#                                                           #
#############################################################


class InputParser:
    def __init__(self, state):
        self.state = state

    #########################################################

    def split(self, cmd: str):
        return cmd.split()

    #########################################################

    def get_parser(self):
        parser = argparse.ArgumentParser(
            description="Script to process project parameters.")
        subparsers = parser.add_subparsers(dest="command")

        #####################################################

        # Create subparser for the "create" command
        create_db_parser = subparsers.add_parser(
            "create-db", help="Create database by given name")
        create_db_parser.add_argument(
            "name", help="Name of the database to create")

        # Create subparser for the "drop" command
        drop_db_parser = subparsers.add_parser(
            "drop-db", help="Drop database by given name")
        drop_db_parser.add_argument(
            "name", help="Name of the database to drop")

        #####################################################

        connect_db_parser = subparsers.add_parser(
            "connect-db", help="Connect to database by given name")
        connect_db_parser.add_argument(
            "name", help="Name of the database to connect")

        disconnect_db_parser = subparsers.add_parser(
            "disconnect-db", help="Disconnect to database by given name")
        disconnect_db_parser.add_argument(
            "name", help="Name of the database to disconnect")

        #####################################################

        # Create subparser for the "list-database" command
        list_db_parser = subparsers.add_parser(
            "list-db", help="List existing databases")

        # Create subparser for the "list-database" command
        list_connected_db_parser = subparsers.add_parser(
            "list-connected-db", help="List existing databases")

        # Create subparser for the "list-database" command
        list_db_table_parser = subparsers.add_parser(
            "list-table", help="List existing databases")
        list_db_table_parser.add_argument(
            "name", help="Name of the database to list tales")

        #####################################################

        # Create subparser for the "exit" command
        exit_parser = subparsers.add_parser("exit", help="Exit the program")
        return parser

    #########################################################

    def parse(self, cmd: str) -> dict:
        cmd_list = cmd.split()
        parser = self.get_parser()
        result_ns = parser.parse_args(cmd_list)
        result = vars(result_ns)
        return result

    #########################################################


#############################################################
#                                                           #
#############################################################
