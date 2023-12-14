__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-13"

# imports
import re
import os
import sys
import math

# get module
module_path = os.path.dirname(os.getcwd()) + '\\2023 Libraries'
sys.path.insert(0, module_path)
import aoc2023 as aoc

# read file
lines: list[str]
# lines = aoc.file_lines(aoc.data_filepath('example.txt'))
lines = aoc.file_lines(aoc.data_filepath('input.txt'))

'''
Plan

- for each race
    - loop from 0 to time
    - calculate distance
        - if > than record, start = true - save start index
        - keep going until < record, end = true - save end index
    - subtract end and start, append to list
- multiply list (math.prod(list))

'''

def calc(hold, total):
    return hold * (total - hold)

times = re.findall(r'\b\d+\b', lines[0])
dists = re.findall(r'\b\d+\b', lines[1])
time = int(''.join(times))
dist = int(''.join(dists))
ways = []

first = last = 0
for i in range(0, time):
    if calc(i, time) > dist:
        first = i
        break
for i in range(first, time):
    if calc(i, time) <= dist:
        last = i
        break
ways.append(last - first)
print(math.prod(ways))


