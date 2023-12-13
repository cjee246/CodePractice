__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-13"

# imports
import re

# define file
inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day3\\example.txt'
# inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day3\\input.txt'

# Program to read entire file
file = open(inputFile)
lines = file.readlines()
for line in lines:
    lines[lines.index(line)] = line.strip()

'''
Plan

- find all gear locations
- for each gear, are exactly two touching?
    - check lines +/- 1 from gear
        - make sure index+len < size
    - for each line, check all numbers
        - if idx or idx + len is within gear range, add number
    - count all numbers in gear
        - if exactly 2, mult and add to gear ratio list
'''

gearList = []
for line in lines:
    for i, ltr in enumerate(line):
        if ltr == '*':
            gearList.append([lines.index(line), i])

ratioList = []
for gear in gearList:
    numList = []
    y1 = max(gear[0] - 1, 0)
    y2 = min(gear[0] + 1, len(lines) - 1)
    x1 = max(gear[1]- 1, 0)
    x2 = min(gear[1] + 1, len(line) - 1)
    for i in range(y1, y2 + 1):
        numbers = re.findall(r'\b\d+\b', lines[i])
        last = 0
        for number in numbers:
            start = lines[i].index(number, last)
            last = start + len(number) - 1
            if range(max(x1, start), min(x2, last + 1)):
                numList.append(int(number))
    if len(numList) == 2:
        ratioList.append(numList[0] * numList[1])

print(sum(ratioList))



# ratioList = []
# for line in lines:
#     numbers = re.findall(r'\b\d+\b', line)
#     last = 0
#     for number in numbers:
#         y1 = max(lines.index(line) - 1, 0)
#         y2 = min(lines.index(line) + 1, len(lines) - 1)
#         x1 = max(line.index(number, last) - 1, 0)
#         x2 = min(line.index(number, last) + len(number), len(line) - 1)
#         last = line.index(number) + len(number)
#         for i in range(y1, y2 + 1):
#             for j in range(x1, x2 + 1): 
#                 if not lines[i][j].isdigit() and lines[i][j] != '.':
#                     numList.append(int(number))
#                     break
# print(sum(numList))