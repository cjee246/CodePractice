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

""" 
Plan: 

- go through each line
- separate by colon, comma, semi-colon
- check each semi-colon set
    - separate by comma
    - get substring
    - find integer
    - compare with bag key
    - if larger than recorded max, update new max
- multiply all maxes and append to power list
"""

powerList = []
for line in lines:
    bag = {
        "red": 0,
        "green": 0,
        "blue": 0
    }
    power = 1
    line = line.strip()
    line = line.replace('Game ', '')
    sets = re.split(': |; ', line)
    for i in range(1, len(sets)):
        draw = sets[i].split(', ')
        for color in draw:
            cubes = color.split(' ')
            if int(cubes[0]) > bag[cubes[1]]:
                bag[cubes[1]] = int(cubes[0])
    for i in bag:
        power = power*bag[i]
    powerList.append(power)
print(sum(powerList))


