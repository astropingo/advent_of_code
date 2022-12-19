import timeit
starttime = timeit.default_timer()

# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

asd = ["$ cd /",
"$ ls",
"dir a",
"14848514 b.txt",
"8504156 c.dat",
"dir d",
"$ cd a",
"$ ls",
"dir e",
"29116 f",
"2557 g",
"62596 h.lst",
"$ cd e",
"$ ls",
"584 i",
"$ cd ..",
"$ cd ..",
"$ cd d",
"$ ls",
"4060174 j",
"8033020 d.log",
"5626152 d.ext",
"7214296 k"]

# Challenge
import re
file_pattern = re.compile(r"(\d*) (.*)") # 14848514 b.txt
import sys
sys.setrecursionlimit(2000)

folder  = {
    "parent":None,
    "size":0,
    "subfolders":{},
    "files":{},
    "name":"root",
}

def run_command(commands, current_folder):
    try:
        command = next(commands)
    except StopIteration:
        return 0
    if command == "$ cd /": #it just shows once
        run_command(commands, current_folder)
    elif command == "$ ls": #doesn't change anything, is just a header for the command list
        run_command(commands, current_folder) # ***
    elif command.startswith("dir"): #creates a subfolder if it doesn't exist
        folder_name = command[4:]
        create_folder(folder_name, current_folder) # current_folder is a dict, representing the current folder
        run_command(commands, current_folder)
    elif command.startswith("$ cd .."): # goes up one folder
        run_command(commands, current_folder["parent"])
    elif command.startswith("$ cd"): # goes down one folder
        subfolder_name = command[5:]
        current_folder["size"] += run_command(commands, current_folder["subfolders"][subfolder_name]) # run the next command on the subfolder
    elif file_pattern.match(command):
        file_size, file_name = file_pattern.match(command).groups()
        file_size = int(file_size)
        current_folder["files"][file_name] = {
            "size":file_size,
            "name":file_name,
        }
        current_folder["size"] += file_size + run_command(commands, current_folder)
    return current_folder["size"]

def create_folder(subfolder_name, current_folder_dict):
    current_folder_dict["subfolders"][subfolder_name] = {
        "parent":current_folder_dict,
        "size":0,
        "subfolders":{},
        "files":{},
        "name":subfolder_name,
    }
    # current_folder_dict["subfolders"][subfolder_name]["this"] = current_folder_dict["subfolders"][subfolder_name]

input69 = [
"$ cd /",
"$ ls",
"dir a",
"$ cd a",
"$ ls",
"dir b",
"$ cd b",
"$ ls",
"dir c",
"dir d",
"10 a.txt",
"20 ba.txt",
"30 ca.txt",
"$ cd c",
"$ ls",
"30 asd.txt",
"$ cd ..",
"$ cd d",
"$ ls",
"10 absd.md",
"90 pjq.m"]

'''
root (190)
    a (190)
        b (60 + 130 = 190)
            a.txt   10
            ba.txt  20
            ca.txt  30
            c (30)
                asd.txt   30
            d (100)
                absd.md   10
                pjq.m     90
'''

def get_commands(command_list):
    for command in command_list:
        yield command.strip()

run_command(get_commands(input69), folder)

def count_sizes_recursively(folder):
    #calculate recursively the sum of the folder size with the sum of all subfolders, but only if the folder or subfolder size is less or equan than 100000
    if folder["size"] <= 100000:
        return folder["size"] + sum(count_sizes_recursively(subfolder) for subfolder in folder["subfolders"].values())
    else:
        return sum(count_sizes_recursively(subfolder) for subfolder in folder["subfolders"].values())

print(count_sizes_recursively(folder))
print(f"Root size = {folder['size']}")
print("The time difference is :", timeit.default_timer() - starttime)