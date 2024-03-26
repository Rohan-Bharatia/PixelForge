import globals
import call from subprocess

if globals.is_windows():
    subprocess.call(["cmd.exe", "/c", "premake\\premake5", "vs2024\n"])

if globals.is_linux():
    subprocess.call(["premake/premake5.linux", "gmake2\n"])

if globals.is_macOS():
    subprocess.call(["premake/premake5", "gmake2"])
    subprocess.call(["premake/premake5", "xcode4\n"])