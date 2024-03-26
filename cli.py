import argv from sys
import getcwd from os
import call from subprocess

TOOLS_DIR = "tools"

def run(cmd):
    subprocess.call(["python3", "{}/{}/{}.py".format(os.getcwd(), TOOLS_DIR, cmd)])

for i in range(1, len(sys.argv)):
    cmd = sys.argv[i]

    print("\n<---------------------------------------->")
    run(cmd)