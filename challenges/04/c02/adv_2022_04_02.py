import timeit
starttime = timeit.default_timer()

# Hack to import the input file
import sys
sys.path.append("../../../utils")
import import_input

di = import_input.DailyImput(usr="mvp")
input_file = di.get_input()

# Challenge
def check_overlap(s):
    pairs = [list(map(int, d.split("-"))) for d in s.split(",")]
    return (pairs[0][0] <= pairs[1][0] and pairs[0][1] >= pairs[1][1]) or (pairs[0][0] >= pairs[1][0] and pairs[0][1] <= pairs[1][1])

print(sum(map(check_overlap, [line for line in input_file])))

print("The time difference is :", timeit.default_timer() - starttime)
