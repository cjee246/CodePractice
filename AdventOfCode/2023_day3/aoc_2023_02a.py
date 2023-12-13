#!/usr/bin/env python

__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-12"

# imports
import re

# define file
# inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day2\\example.txt'
inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day2\\input.txt'

# Program to read entire file
file = open(inputFile)
lines = file.readlines()

# define key
bag = {
    "red": 12,
    "green": 13,
    "blue": 14
}

""" 
Plan: 

- go through each line
- separate by colon, comma, semi-colon
- check each semi-colon set
    - separate by comma
    - get substring
    - find integer
    - compare with bag key
    - if not exceeds max, record game ID
- count all in game ID list
"""

idList = []
for line in lines:
    possible = True
    line = line.strip()
    line = line.replace('Game ', '')
    sets = re.split(': |; ', line)
    for i in range(1, len(sets)):
        draw = sets[i].split(', ')
        for color in draw:
            cubes = color.split(' ')
            if int(cubes[0]) > bag[cubes[1]]:
                possible = False
    if possible:
        idList.append(int(sets[0]))        
print(sum(idList))


