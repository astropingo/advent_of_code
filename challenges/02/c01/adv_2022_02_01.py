# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
from collections import deque

elf_code = "ABC"
your_code = "XYZ"

plays = [f"{e}{y}" for e in elf_code for y in your_code]
points = deque([3, 6, 0])
pairs_value = {}
for i in range(len(points)):
    pairs_value.update({pair:point for pair, point in zip(plays[i*len(points):len(points)*(i+1)], points)})
    points.rotate()

def score(play):
    elf, you = play.strip().split(" ")
    round_points = pairs_value[f"{elf}{you}"]
    your_points = 1 + your_code.index(you)
    return round_points + your_points

# print(sum(map(score, [line for line in input_file])))
print(score("A Y"))