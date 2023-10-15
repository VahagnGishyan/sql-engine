
from utility import console

import os
import shutil

#############################################################
#                                                           #
#############################################################


def read_file_to_list(file_path):
    # Read and return cleaned lines from a file.
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
        cleaned_lines = [line.strip() for line in lines]
        return cleaned_lines
    except FileNotFoundError:
        console.print_warning(f"File '{file_path}' not found.")
        return []


def copy_files(src_dir, dest_dir):
    # Copy files and directories from source to destination.
    if not os.path.exists(src_dir):
        console.print_warning(f"Directory: {src_dir} does not exist.")
        return
    shutil.copytree(src_dir, dest_dir, dirs_exist_ok=True)


def copy_file_to_file(from_file, to_file):
    # Copy the contents of one file to another.
    s_file = open(from_file, "r")
    d_file = open(to_file, "w")
    for line in s_file:
        d_file.write(line)


#############################################################
#                                                           #
#############################################################

def is_path_exists(path):
    # Check if a path exists.
    return path is not None and os.path.exists(path)


def assert_path_exists(path):
    # Assert that a path exists or raise a ValueError.
    if not is_path_exists(path):
        raise ValueError(f"'{path}' does not exist.")


def is_file(path):
    # Check if a path is a file.
    return os.path.isfile(path)


def is_dir(path):
    # Check if a path is a directory.
    return os.path.isdir(path)


def assert_is_file(path):
    # Assert that a path is a file or raise a ValueError.
    if not is_file(path):
        raise ValueError(f"'{path}' is not a file.")


def assert_is_dir(path):
    # Assert that a path is a directory or raise a ValueError.
    if not is_dir(path):
        raise ValueError(f"'{path}' is not a directory.")


def assert_dir_exists(path):
    assert_path_exists(path)
    assert_is_dir(path)


def list_dirs_in_dir(path):
    # List directories in a given directory.
    return [d for d in os.listdir(path) if is_dir(os.path.join(path, d))]


def list_files_in_dir(path):
    # List files in a given directory.
    return [f for f in os.listdir(path) if is_file(os.path.join(path, f))]


def list_dir(path):
    # List names of all files and directories in a given directory.
    return os.listdir(path)


def is_dir_empty(path):
    # Check if a directory is empty.
    return not list_dir(path)


def assert_dir_empty(path):
    # Assert that a directory is empty or raise a ValueError.
    if not is_dir_empty(path):
        raise ValueError(f"'{path}' is not an empty directory.")


#############################################################
#                                                           #
#############################################################

def mkdir(path):
    os.makedirs(path, exist_ok=True)


def rmdir(path):
    os.remove(path, exist_ok=True)


def create_empty_file(path):
    with open(path, 'w') as file:
        pass


def remove(path):
    if os.path.exists(path):
        os.remove(path)

#############################################################
#                                                           #
#############################################################
