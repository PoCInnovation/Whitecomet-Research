from qiling import *
import sys
import os
import time
import shutil
from contextlib import redirect_stdout
import argparse

# Colors
OKBLUE = '\033[94m'
FAIL = '\033[91m'
BOLD = '\033[1m'
ENDC = '\033[0m'


def arguments_parsing():
    parser = argparse.ArgumentParser(prog='Polymorphic checker')
    slow_type_int = lambda x: x if (x.isnumeric() and int(x) >= 3) else parser.error(
                                    "--slow/-s: N should be an int and >= 3)")

    parser.add_argument("--show-output", "-o", action='store_true',
                        help='show binary output.')
    parser.add_argument("--slow", "-s", type=slow_type_int, nargs=1, metavar='N',
                        help='multiple (slow) executions. must be >= 3.')
    parser.add_argument("programs", type=str, nargs="*", default=['./malware'],
                        help='program to test for polymorphism.')
    return parser.parse_args()


def setup_sandbox(path):
    shutil.copytree("./base_root", "./malware_root")  # Unique root jail
    new_path = shutil.copy(path, "./malware_root/home/")
    os.chdir("./malware_root")
    return new_path
    # Copy to jail and return path


def read(path):
    with open(path, mode='rb') as file:
        content = file.read()
    return content


def sandbox(path):  # IDEA: Multiple execution and add contents to set
    contents = set()
    output = sys.stdout if show_output is True else open(os.devnull, 'w')
    for exec in range(slow_exec if slow_exec else 1):
        if slow_exec:
            contents.add(read(path))
            time.sleep(3)
        with redirect_stdout(output):
            ql = Qiling(filename=[path], rootfs="./",
                        env={"HOME": "/home", "PATH": "/bin"},
                        console=False)
            ql.run()
    if show_output is False:
        output.close()  # Close /dev/null
    os.chdir("..")
    return contents


def print_finish(path):
    print(OKBLUE + "████████████████████████████████████████", end='\n\n')
    print(path + " has finished running." + ENDC)


def path_check(path) -> bool:
    exists = os.path.exists(path)
    if exists is False:
        print(FAIL + "Extremely suspicious behavior detected:")
        print("The file deleted/moved itself! ❌" + ENDC)
    else:
        print(BOLD + "The program did not move (" + path + ") ✅" + ENDC)
    return exists


def size_check(new_f, old_f):
    new_size = len(new_f)
    old_size = len(old_f)
    print(BOLD + "Before exec size : " + str(new_size), end=' bytes ')
    print("&& After exec size : " + str(old_size), end=' bytes ')
    print(("✅" if new_size == old_size else "❌") + ENDC)


def content_check(new_f, old_f, contents):
    polymorphic = False
    if slow_exec:
        print("For " + str(slow_exec) + " executions, the program had " +
              str(len(contents)) + " different version(s) of itself.")
        polymorphic = len(contents) != 1
    elif new_f != old_f:
        print("New bin content after execution. ", end='')
        polymorphic = True
    print("The file is polymorphic. ❌" if polymorphic else "The program doesn't seem to be polymorphic. ✅")


def risk_check(path, old_path, contents):
    new_f, old_f = None, None
    if path_check(path) is False:
        return
    if slow_exec is None:
        with open(path, mode='rb') as new_f, open(old_path, mode='rb') as old_f:
            new_f = new_f.read()
            old_f = old_f.read()
        size_check(new_f, old_f)
    else:
        print("No size check in slow mode.")
    content_check(new_f, old_f, contents)


if __name__ == "__main__":
    args = arguments_parsing()
    paths = args.programs
    show_output = args.show_output
    slow_exec = int(args.slow[0]) if args.slow else None

    for path in paths:
        try:
            old_path = path
            path = setup_sandbox(path)
            contents = sandbox(path.replace("./malware_root", ".", 1))
            print_finish(path)
            risk_check(path, old_path, contents)
            shutil.rmtree("./malware_root")  # Clean up
        except Exception as e:
            print(e)
            print(os.getcwd())
            if os.path.split((os.getcwd()))[1] == "malware_root":
                os.chdir("..")
            if os.path.exists("./malware_root"):
                shutil.rmtree("./malware_root")
                print("Deleted ./malware_root")
