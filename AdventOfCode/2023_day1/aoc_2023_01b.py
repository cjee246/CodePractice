#!/usr/bin/env python

__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-12"

# imports
import os

# define file
inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day1\\input.txt'

# define lists
words = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
digits = ['1', '2', '3', '4', '5', '6', '7', '8', '9']

# Program to read entire file
file = open(inputFile)
Lines = file.readlines()

# round 2
numList = []
for line in Lines:
    subList = []
    idxList = []
    for item in words:  
        if line.find(item) >= 0:
            idxList.append(line.find(item))
            subList.append(str(words.index(item) + 1))
            idxList.append(line.rfind(item))
            subList.append(str(words.index(item) + 1))
    for item in digits:
        if line.find(item) >= 0:
            idxList.append(line.find(item))
            subList.append(str(digits.index(item) + 1))
            idxList.append(line.rfind(item))
            subList.append(str(digits.index(item) + 1))
    numList.append(int(subList[idxList.index(min(idxList))] + 
                       subList[idxList.index(max(idxList))]))
print (sum(numList))
file.close()