
import argparse


def ParseArguments():
    parser = argparse.ArgumentParser(
        description="Script to process project parameters.")
    parser.add_argument("--project", type=str, required=True,
                        help="Name of the project.")
    parser.add_argument("--path", type=str, required=True,
                        help="Path to the project.")

    user_input = input("Please input your command: ")
    args = user_input.split()

    args = parser.parse_args(args)

    return args


if __name__ == "__main__":
    parsed_args = ParseArguments()
    print(f"parsed-arges: {parsed_args}")
