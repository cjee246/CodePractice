#!/usr/bin/env python

__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-12"

# includes
import os

# define
inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day1\\input.txt'

# Program to read entire file
file = open(inputFile)
Lines = file.readlines()

# get the first and last of the first line
count = 0
numList = []
for line in Lines:
    numStr = list("00")
    idx = 0
    for char in line:
        if char.isnumeric():
            numStr[idx] = char
            idx = 1
            numStr[idx] = char
    numList.append(int(''.join(numStr)))
    count += 1
Sum = sum(numList)
print(Sum)

file.close()