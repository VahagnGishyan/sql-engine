
#############################################################
#                                                           #
#############################################################

RED = '\033[91m'
GREEN = '\033[92m'
YELLOW = '\033[93m'
BLUE = '\033[94m'
MAGENTA = '\033[95m'
CYAN = '\033[96m'
RESET = '\033[0m'  # Reset to the default text color

#############################################################


def Print(message):
    print(RESET + message)


def PrintInfo(message):
    print(GREEN + message + RESET)


def PrintWarning(message):
    print(YELLOW + message + RESET)


def PrintDebug(message):
    print(BLUE + message + RESET)


def PrintError(message):
    print(RED + message + RESET)


def PrintSignal(message):
    print(MAGENTA + message + RESET)

#############################################################
#                                                           #
#############################################################
