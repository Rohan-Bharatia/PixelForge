import platform from sys
import uname from platform

MAJOR = 1
MINOR = 0
PATCH = 0

PLATFORM = sys.platform
for x in platform.uname():
    if "microsoft" in x.lower():
        PLATFORM = "windows"
        break

    if "darwin" in x.lower():
        PLATFORM = "macOS"
        break

def is_windows():
    return PLATFORM == "windows"

def is_linux():
    return PLATFORM == "linux"

def is_macOS():
    return PLATFORM == "macOS"