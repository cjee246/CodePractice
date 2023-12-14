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
Order = destination start, source start, length

- get first seed ranges

- get new section
    - search for numbers, 
    - if no numbers new section
- for each set, 
    - start with lower limit
    - track the upper limit as it gets truncated by ranges
- restart seed range but starting at the upper limit of the previous run

'''
seeds = list(map(int, (re.findall(r'\b\d+\b', lines[0]))))
locations = []
for seed in seeds[::2]:
    start = seed
    length = seeds[seeds.index(seed) + 1] 
    limit = seed + length - 1
    while start < limit:
        number = start
        changed = False
        for i in range(1, len(lines)):
            if re.findall(r'\b\d+\b', lines[i]):
                code = list(map(int, (re.findall(r'\b\d+\b', lines[i]))))
                
                if not changed and number in range(code[1], code[1] + code[2]):
                    if (number + length) > (code[1] + code[2]):
                        length -= ((number + length) - (code[1] + code[2]))
                    number += code[0] - code[1]
                    changed = True
            else:
                changed = False
        locations.append(number)
        start += length
        length = limit - start
print(min(locations))


