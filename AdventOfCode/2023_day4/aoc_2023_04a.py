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

- for each ticket, make winning numbers and your numbers
    - check each winning numbers against your numbers
    - if match, double point value
        - start at 0.5, and use math.floor 
    - add to total points   
'''

point_list = []
for line in lines:
    points = 0.5
    sets = re.split(': |\| ', line) 
    winning = re.findall(r'\b\d+\b', sets[1])
    yours = re.findall(r'\b\d+\b', sets[2])
    for number in winning:
        if number in yours:
            points *= 2
    point_list.append(math.floor(points))
print(sum(point_list))


    