# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput()
input_file = di.get_input()

# Challenge
values = [int(x.strip()) for x in input_file]
print(sum([(v - values[i] > 0) for i, v in enumerate(values[1:])]))