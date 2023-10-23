import argparse
from utility import console

# Custom action to parse pairs


class CreateTableAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        if values[0] != "create-tb":
            raise argparse.ArgumentError(self, "The first argument must be 'create-tb'")
        values.pop(0)

        db_name = values.pop(0)
        tb_name = values.pop(0)

        if len(values) % 2 != 0:
            raise argparse.ArgumentError(self, "Each column name must have a corresponding data type.")
        
        pairs = [(values[i], values[i + 1]) for i in range(0, len(values), 2)]

        # Set db_name, tb_name, and pairs in the namespace
        setattr(namespace, "db-name", db_name)
        setattr(namespace, "tb-name", tb_name)
        setattr(namespace, self.dest, pairs)


parser = argparse.ArgumentParser(
    description="Script to process project parameters")

# Define the create-tb command with a list of pairs
parser.add_argument("create-tb", nargs='*',
                    action=CreateTableAction, metavar="column-pairs")

args = parser.parse_args()
result = vars(args)

console.PrintSignal(f"result: {result}")
