
from utility import console
from cli.state import State
from cli.wrapper import DBWrapperPythonLib

#############################################################
#                                                           #
#############################################################


class Executor:
    def __init__(self, state: State):
        self.state = state
        self.executor = DBWrapperPythonLib()

    #########################################################
    #                                                       #
    #########################################################

    def cmd_create_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.create(dbname)

    def cmd_drop_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.drop(dbname)

    #########################################################

    def cmd_connect_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.connect(dbname)

    def cmd_disconnect_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.disconnect(dbname)

    #########################################################

    def cmd_list_db(self, task: dict):
        command = task["command"]
        list_db = self.executor.list_db()
        console.PrintInfo(f"list-db: {list_db}")

    def cmd_list_connected_db(self, task: dict):
        command = task["command"]
        list_db = self.executor.list_connected_db()
        console.PrintInfo(f"list-connected-db: {list_db}")

    def cmd_list_table(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        list_tb = self.executor.list_tables(dbname)
        console.PrintInfo(f"db: {dbname}, list-table: {list_tb}")

    #########################################################
    #                                                       #
    #########################################################

    def cmd_create_tb(self, task: dict):
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        command = task["command"]
        columns = task["columns"]
        console.PrintInfo(
            f"db: {db_name}, tb: {tb_name}, command: {command}, columns: {columns}")
        self.executor.create_table(db_name, tb_name, columns)

    def cmd_drop_tb(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        self.executor.drop_table(db_name, tb_name)

    #########################################################
    #                                                       #
    #########################################################

    def cmd_work_dir(self, task: dict):
        command = task["command"]
        work_dir = self.executor.work_dir()
        console.PrintInfo(f"current-work-dir: {work_dir}") 

    #########################################################

    def cmd_exit(self, task: dict):
        self.state.set_state("condition", False)

    #########################################################
    #                                                       #
    #########################################################

    def execute(self, task: dict):
        command = task["command"]
        cmd_executor_runner_list = {
            "create-db": self.cmd_create_db,
            "drop-db": self.cmd_drop_db,

            "connect-db": self.cmd_connect_db,
            "disconnect-db": self.cmd_disconnect_db,

            "list-db": self.cmd_list_db,
            "list-connected-db": self.cmd_list_connected_db,
            "list-table": self.cmd_list_table,

            "create-tb": self.cmd_create_tb,
            "drop-tb": self.cmd_drop_tb,

            "work-dir": self.cmd_work_dir,
            "exit": self.cmd_exit,
        }
        if command not in cmd_executor_runner_list:
            console.PrintWarning(f"command: {command} is not supported yet.")
            return

        cmd_executor_runner_list[command](task)

    #########################################################


#############################################################
#                                                           #
#############################################################
