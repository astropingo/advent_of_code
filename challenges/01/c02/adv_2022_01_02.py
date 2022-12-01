# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
calories_list = []
temp_pack = 0
for line in input_file:
    if line.strip() != "":
        temp_pack += int(line.strip())
    else:
        calories_list.append(temp_pack)
        temp_pack = 0
print(sum(sorted(calories_list, reverse=True)[:3]))