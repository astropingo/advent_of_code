# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
from collections import deque

hand_code = "ABC"
out_code = "XYZ"

plays = [f"{e}{y}" for e in hand_code for y in hand_code]
points = deque([3, 6, 0])
pairs_value = {}
for i in range(len(points)):
    pairs_value.update({pair:point for pair, point in zip(plays[i*len(points):len(points)*(i+1)], points)})
    points.rotate()

def score(play):
    elf, outcome = play.strip().split(" ")
    
    outcome = out_code.index(outcome)
    outcome_points = 3 * outcome

    possible_pairs = [pair for pair, value in pairs_value.items() if value == outcome_points]
    pair = [s for s in possible_pairs if elf in s[0]][0]

    return 1 + hand_code.index((pair[1])) + outcome_points

print(sum(map(score, [line for line in input_file])))