__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-13"

# imports
import re
import os
import sys

# get module
modulePath = os.path.dirname(os.getcwd()) + '\\2023 Libraries'
sys.path.insert(0, modulePath)
import aoc2023 as aoc

# read file
lines = aoc.file_lines(aoc.data_filepath('example.txt'))
# lines = aoc.file_lines(aoc.data_filepath('input.txt'))

'''
Plan

- for each ticket, make winning numbers and your numbers
    - check each winning numbers against your numbers
    - if match, double point value
        - start at 0.5, and use math.floor 
    - add to total points   
'''