# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
import string
letters = string.ascii_letters

# Creates groups of 3 lines from the input.
groups = [list(map(str.strip, input_file[i*3:(i+1)*3])) for i in range(int(len(input_file) / 3))]

# Calculates the intersection of the sets for each line. Each set contains just the unique characters found on each line.
intersections = [set(groups[k][0]).intersection(set(groups[k][1]), set(groups[k][2])) for k in range(len(groups))]

def get_points(s):
    return letters.index(s.pop()) + 1

print(sum(map(get_points, [line for line in intersections])))