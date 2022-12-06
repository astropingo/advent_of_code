import timeit
starttime = timeit.default_timer()

# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
number_of_chars = 14
signal = input_file[0]
for i, c in enumerate(signal):
    if len(set(signal[i:i+number_of_chars])) == number_of_chars:
        print(i+number_of_chars)
        break

print("The time difference is :", timeit.default_timer() - starttime)