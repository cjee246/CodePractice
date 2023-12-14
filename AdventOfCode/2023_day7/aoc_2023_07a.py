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
Plan:

- make a list to order the card number
- make a dictionary for hands and bids
- make a list for each hand type
    - high_card
    - one_pair
    - two_pair
    - three_kind
    - full_house
    - four_kind
    - five_kind
- sort each list from lowest to highest
- alphabetically encode hand for intra-type sorting
- perform sorting on master dictionary
- make a list for winnings
    - map to bid, multiply by index + 1
'''

# strength = [ '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A']

# definitions
dict_alpha = {
    '2':'A',
    '3':'B',
    '4':'C',
    '5':'D',
    '6':'E',
    '7':'F',
    '8':'G',
    '9':'H',
    'T':'I',
    'J':'J',
    'Q':'K',
    'K':'L',
    'A':'M'
}

def get_type(hand_string):
    count_list = []
    for i in range(len(dict_alpha)):
        count = 0
        for char in hand_string:
            if char == list(dict_alpha.keys())[i]:
                count += 1
        count_list.append(count)
    if count_list.count(5) == 1:
        return 6
    elif count_list.count(4) == 1:
        return 5
    elif count_list.count(3) == 1 and count_list.count(2) == 1:
        return 4
    elif count_list.count(3) == 1:
        return 3
    elif count_list.count(2) == 2:
        return 2
    elif count_list.count(2) == 1:
        return 1
    else:
        return 0

# set up lists
for line in lines:
    lines[lines.index(line)] = re.split(' ', line)
hands, bets = map(list, zip(*lines))
alphas = []
types = []
master = []
for hand in hands:
    types.append(get_type(hand))
    alphas.append(str(hand).translate(str.maketrans(dict_alpha)))
for i in range(len(hands)):
    master.append(
        {
            'hand': hands[i],
            'bet': bets[i],
            'type': types[i],
            'alpha': alphas[i],
        }
    )

# sort and calc
winnings = []
master = sorted(master, key=lambda k: (k['type'], k['alpha']))
for i in range(len(master)):
    winnings.append(int(master[i]['bet']) * (i + 1))
print(sum(winnings))