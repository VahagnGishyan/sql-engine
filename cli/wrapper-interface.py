
#############################################################
#                                                           #
#############################################################


class DBWrapper:
    def create(self, name):
        pass

    def drop(self, name):
        pass

    #########################################################

    def connect(self, name):
        pass

    def disconnect(self, name):
        pass

    #########################################################

    def create_table(self, name, columns: list[{str, str}]):
        pass

    def drop_table(self, name):
        pass

    def alter_table_add(self, column_name, datatype):
        pass

    def alter_table_drop(self, column_name):
        pass

    def alter_table_rename(self, column_name):
        pass

    #########################################################

    def execute(self, query):
        pass

#############################################################
#                                                           #
#############################################################
