
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
        return self.cmd_list_db(task)

    def cmd_drop_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.drop(dbname)
        return self.cmd_list_db(task)

    #########################################################

    def cmd_connect_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.connect(dbname)
        return self.cmd_list_connected_db(task)

    def cmd_disconnect_db(self, task: dict):
        command = task["command"]
        dbname = task["name"]
        self.executor.disconnect(dbname)
        return self.cmd_list_connected_db(task)

    #########################################################

    def cmd_list_db(self, task):
        # command = task["command"]
        list_db = self.executor.list_db()
        return f"list-db: {list_db}"

    def cmd_list_connected_db(self, task):
        # command = task["command"]
        list_db = self.executor.list_connected_db()
        return f"list-connected-db: {list_db}"

    def cmd_list_table(self, task: dict):
        # command = task["command"]
        dbname = task["name"]
        list_tb = self.executor.list_tables(dbname)
        return f"db: {dbname}, list-table: {list_tb}"

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
        return self.cmd_list_table(task)

    def cmd_drop_tb(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        self.executor.drop_table(db_name, tb_name)
        return self.cmd_list_table(task)

    #########################################################
    #                                                       #
    #########################################################

    def cmd_add_column(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        clm_name = task["column-name"]
        clm_type = task["column-type"]
        return self.executor.alter_table_add(db_name, tb_name, clm_name, clm_type)
        # columns = ", ".join(clm_name)
        # return self.executor.execute(db_name, f"select {columns} from {tb_name}")

    def cmd_remove_column(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        clm_name = task["column-name"]
        return self.executor.alter_table_drop(db_name, tb_name, clm_name)
        # columns = ", ".join(clm_name)
        # return self.executor.execute(db_name, f"select {columns} from {tb_name}")

    def cmd_rename_column(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        tb_name = task["tb-name"]
        clmn_name_old = task["column-name-old"]
        clmn_name_new = task["column-name-new"]
        return self.executor.alter_table_rename(
            db_name, tb_name, clmn_name_old, clmn_name_new)

    #########################################################
    #                                                       #
    #########################################################

    def cmd_execute(self, task: dict):
        command = task["command"]
        db_name = task["db-name"]
        query = task["query"]
        return self.executor.execute(db_name, query)

    #########################################################
    #                                                       #
    #########################################################

    def cmd_work_dir(self, task: dict):
        command = task["command"]
        work_dir = self.executor.work_dir()
        return f"current-work-dir: {work_dir}"

    #########################################################

    def cmd_exit(self, task: dict):
        self.state.set_state("condition", False)
        # return "condition: false",

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

            "add-column": self.cmd_add_column,
            "remove-column": self.cmd_remove_column,
            "rename-column": self.cmd_rename_column,

            "execute": self.cmd_execute,

            "work-dir": self.cmd_work_dir,
            "exit": self.cmd_exit,
        }
        if command not in cmd_executor_runner_list:
            raise ValueError(f"command: {command} is not supported.")

        return cmd_executor_runner_list[command](task)

    #########################################################
    #                                                       #
    #########################################################

    def close(self):
        self.executor.close()

    #########################################################
    #                                                       #
    #########################################################


#############################################################
#                                                           #
#############################################################
