import timeit
starttime = timeit.default_timer()

# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
from collections import deque

stack_read = False
stack = []
commands = []
for line in input_file:
    if line.rstrip() == "":
        stack_read = True
    if not stack_read:
        stack.append(line.replace("\n", ""))
    else:
        commands.append(line.strip())

commands.pop(0) # Necessary hack because it adds an empty string at index 0

deques = {(i+1):deque() for i in range(int((len(stack[0]) + 1) / 4))}
stacks = [[s[i*4:i*4+4] for i in range(int((len(s) + 1) / 4))] for s in stack[:-1]] 

def move_2(quantity, origin, destination):  
    deques[destination].extend(list(deques[origin])[-quantity:])
    for qt in range(quantity):
        deques[origin].pop()

for stack in stacks:
    for i, item in enumerate(stack, start=1):
        if item == "    ": # Ignores spaces on the stack that does not contain an item
            pass
        else:
            deques[i].appendleft(item)

for command in commands:
    move_2(*map(int,command.split(" ")[1::2]))

print("".join([d[-1][1] for d in deques.values()]))
print("The time difference is :", timeit.default_timer() - starttime)