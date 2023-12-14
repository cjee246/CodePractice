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
Plan:

- make a list to order the card number
- make a dictionary for hands and bids
- make a list for each hand type
    - five_kind
    - four_kind
    - full_house
    - three_kind
    - two_pair
    - one_pair
    - high_card
- sort each list from lowest to highest
- combine all lists
- make a list for winnings
    - map to bid, multiply by index + 1
'''

strength = [ '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']

for line in lines:
    lines[lines.index(line)] = re.split(' ', line)
hands, bets = map(list, zip(*lines))
plays = dict(map(lambda i,j : (i,j) , hands,list(map(int, bets))))