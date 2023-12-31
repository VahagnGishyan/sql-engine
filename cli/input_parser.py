
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
            "db-name", help="Name of the database to create")

        # Create subparser for the "drop" command
        drop_db_parser = subparsers.add_parser(
            "drop-db", help="Drop database by given name")
        drop_db_parser.add_argument(
            "db-name", help="Name of the database to drop")

        #####################################################

        connect_db_parser = subparsers.add_parser(
            "connect-db", help="Connect to database by given name")
        connect_db_parser.add_argument(
            "db-name", help="Name of the database to connect")

        disconnect_db_parser = subparsers.add_parser(
            "disconnect-db", help="Disconnect to database by given name")
        disconnect_db_parser.add_argument(
            "db-name", help="Name of the database to disconnect")

        #####################################################

        # Create subparser for the "list-database" command
        list_db_parser = subparsers.add_parser(
            "list-db", help="List existing databases")

        # Create subparser for the "list-database" command
        list_connected_db_parser = subparsers.add_parser(
            "list-connected-db", help="List existing connected databases")

        # Create subparser for the "list-database" command
        list_db_table_parser = subparsers.add_parser(
            "list-table", help="List existing tables in database")
        list_db_table_parser.add_argument(
            "db-name", help="Name of the database to list tales")

        #####################################################

        class CreateTableAction(argparse.Action):
            def __call__(self, parser, namespace, values, option_string=None):
                # print(f"values: {values}")

                db_name = values.pop(0)
                tb_name = values.pop(0)

                if len(values) % 2 != 0:
                    raise argparse.ArgumentError(
                        self, "Each column name must have a corresponding data type.")

                pairs = [(values[i], values[i + 1])
                         for i in range(0, len(values), 2)]

                # Set db_name, tb_name, and pairs in the namespace
                setattr(namespace, "db-name", db_name)
                setattr(namespace, "tb-name", tb_name)
                setattr(namespace, self.dest, pairs)

        create_tb_parser = subparsers.add_parser(
            "create-tb", help="Create table by given name")
        create_tb_parser.add_argument(
            "columns", nargs='*', action=CreateTableAction)

        drop_tb_parser = subparsers.add_parser(
            "drop-tb", help="Drop table by given name")
        drop_tb_parser.add_argument(
            "db-name", help="Name of the database")
        drop_tb_parser.add_argument(
            "tb-name", help="Name of the table")

        #####################################################

        add_column_parser = subparsers.add_parser(
            "add-column", help="Add column to table by given name and type")
        add_column_parser.add_argument(
            "db-name", help="Name of the database")
        add_column_parser.add_argument(
            "tb-name", help="Name of the table")
        add_column_parser.add_argument(
            "column-name", help="Name of the column")
        add_column_parser.add_argument(
            "column-type", help="Type of the column")

        remove_column_parser = subparsers.add_parser(
            "remove-column", help="Remove column in table")
        remove_column_parser.add_argument(
            "db-name", help="Name of the database")
        remove_column_parser.add_argument(
            "tb-name", help="Name of the table")
        remove_column_parser.add_argument(
            "column-name", help="Name of the column")

        rename_column_parser = subparsers.add_parser(
            "rename-column", help="Rename column in table")
        rename_column_parser.add_argument(
            "db-name", help="Name of the database")
        rename_column_parser.add_argument(
            "tb-name", help="Name of the table")
        rename_column_parser.add_argument(
            "column-name-old", help="Old name of the column")
        rename_column_parser.add_argument(
            "column-name-new", help="New name of the column")

        #####################################################

        class ExecuteAction(argparse.Action):
            def __call__(self, parser, namespace, values, option_string=None):

                db_name = values.pop(0)
                query = " ".join(values)

                setattr(namespace, "db-name", db_name)
                setattr(namespace, self.dest, query)

        create_tb_parser = subparsers.add_parser(
            "execute", help="Execute query for database")
        create_tb_parser.add_argument(
            "query", nargs='*', action=ExecuteAction)

        #####################################################

        # Create subparser for the "create" command
        work_dir_parser = subparsers.add_parser(
            "work-dir", help="Get current work-dir")

        # Create subparser for the "exit" command
        exit_parser = subparsers.add_parser("exit", help="Exit the program")
        return parser

    #########################################################

    def parse(self, cmd: str) -> dict:
        cmd_list = cmd.split()
        parser = self.get_parser()
        result_ns = parser.parse_args(cmd_list)
        result = vars(result_ns)
        # console.PrintSignal(f"task: {result}")
        return result

    #########################################################


#############################################################
#                                                           #
#############################################################
