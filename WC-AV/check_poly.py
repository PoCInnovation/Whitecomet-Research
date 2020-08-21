from qiling import *
import sys
import os
import shutil
import difflib

paths = ["./malware"] if len(sys.argv) == 1 else sys.argv[1:]
# not clean var inits my brother
OKGREEN = '\033[92m'
WARNING = '\033[93m'
OKBLUE = '\033[94m'
FAIL = '\033[91m'
BOLD = '\033[1m'
ENDC = '\033[0m'


def setup_sandbox(path):
    shutil.copytree("./base_root", "./malware_root")  # Unique root jail
    new_path = shutil.copy(path, "./malware_root/home/")
    os.chdir("./malware_root")
    return new_path.replace("./malware_root", ".", 1)
    # Copy to jail and return path


def sandbox(path):  # IDEA: Multiple execution and add contents to set
    ql = Qiling(filename=[path], rootfs="./",
                env={"HOME": "/home", "PATH": "/bin"},
                console=False)
    ql.run()
    os.chdir("..")


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


def content_check(new_f, old_f):
    if new_f != old_f:
        print("New bin content after execution. ", end='')
        print("The file is polymorphic. ❌")
    else:
        print("The program doesn't seem to be polymorphic. ✅")


def risk_check(path, old_path):
    if path_check(path) is False:
        return
    with open(path, mode='rb') as new_f, open(old_path, mode='rb') as old_f:
        new_f = new_f.read()
        old_f = old_f.read()
    size_check(new_f, old_f)
    content_check(new_f, old_f)


# TODO: Iterate over all paths and check if bin. exist
old_path = paths[0]
path = setup_sandbox(paths[0])
sandbox(path)
path = path.replace(".", "./malware_root", 1)
print_finish(path)
risk_check(path, old_path)
shutil.rmtree("./malware_root")  # Clean up
