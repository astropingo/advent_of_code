# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
highest_calories_pack = 0
temp_pack = 0
for line in input_file:
    if line.strip() != "":
        temp_pack += int(line.strip())
    else:
        highest_calories_pack = max(temp_pack, highest_calories_pack)
        temp_pack = 0
print(highest_calories_pack)