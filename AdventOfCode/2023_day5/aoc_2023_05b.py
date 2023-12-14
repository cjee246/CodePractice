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
lines = aoc.file_lines(aoc.data_filepath('example.txt'))
# lines = aoc.file_lines(aoc.data_filepath('input.txt'))

'''
Plan
Order = destination start, source start, length

- get seed number - for each seed number...

- get new section
    - search for numbers, 
    - if no numbers new section
- for each set, check if range
    - if not in overlap range, number is the same
    - if in range, do mapping and break

'''
seeds = []
seed_range = list(map(int, (re.findall(r'\b\d+\b', lines[0]))))
for i in range(0, len(seed_range), 2):
    seeds.extend(seed_range[i] + j for j in range(0, seed_range[i+1]))

locations = []
for seed in seeds:
    number = seed
    changed = False
    for i in range(1, len(lines)):
        if re.findall(r'\b\d+\b', lines[i]):
            code = list(map(int, (re.findall(r'\b\d+\b', lines[i]))))
            if not changed and number in range(code[1], code[1] + code[2]):
                number += code[0] - code[1]
                changed = True
        else:
            changed = False
    locations.append(number)
print(min(locations))


