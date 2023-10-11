
import console

import os
import shutil

#############################################################
#                                                           #
#############################################################

def ReadFileToList(file_path):
    try:
        with open(file_path, 'r') as file:
            lines = file.readlines()
        # Remove leading and trailing whitespace from each line
        cleaned_lines = [line.strip() for line in lines]
        return cleaned_lines
    except FileNotFoundError:
        console.PrintWarning(f"File '{file_path}' not found.")
        return []


def CopyingFiles(srcdir, destdir):
    if not os.path.exists(srcdir):
        console.PrintWarning(
            f"directory: {srcdir} does not exists")
        return
    shutil.copytree(srcdir, destdir, dirs_exist_ok=True)


def CopyFileToFile(fromfile, tofile):
    sfile = open(fromfile, "r")
    dfile = open(tofile, "w")
    for line in sfile:
        dfile.write(line)


#############################################################
#                                                           #
#############################################################
