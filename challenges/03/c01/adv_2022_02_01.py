# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
import string
letters = string.ascii_letters

def get_letter_point(s):
    mid_point = int(len(s)/2)
    halves = (set(s[:mid_point]), set(s[mid_point:]))
    return letters.index(list(halves[0].intersection(halves[1]))[0]) + 1

print(sum(map(get_letter_point, [line for line in input_file])))