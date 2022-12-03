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
    # Segments the string into two equal length halves and generate their sets
    # Each set is a unique set of characters on each half. e.g.: set('abcacba') = {"a", "b", "c"}
    halves_set = (set(s[:mid_point]), set(s[mid_point:]))

    # Calculates the intersection between each set, an unique character
    # and returns the amount of points for that unique letter.
    # E.g: set('abcacba').intersection(set('pblkubp')) = {"b"}
    return letters.index(halves_set[0].intersection(halves_set[1]).pop()) + 1

print(sum(map(get_letter_point, [line for line in input_file])))