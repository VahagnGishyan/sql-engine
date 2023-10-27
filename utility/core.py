
import os
import platform

#############################################################
#                                                           #
#############################################################

def getenv(var):
    return os.getenv(var)


def check_os():
    system = platform.system()
    if system == "Linux":
        return "Linux"
    elif system == "Windows":
        return "Windows"
    elif system == "Darwin":
        return "macOS"
    else:
        raise ValueError("Unsupported OS: " + system)
    

def get_default_appdata_path():
    system = platform.system()
    if system == "Windows":
        return os.environ.get('APPDATA')
    elif system == "Linux":
        # return "/usr/share"
        return os.path.expanduser("~")
    elif system == "Darwin":  # macOS
        return os.path.expanduser("~/Library/Application Support")
    else:
        raise ValueError("Unsupported OS: " + system)
    
#############################################################
#                                                           #
#############################################################
