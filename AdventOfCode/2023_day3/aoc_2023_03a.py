__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-13"

# imports
import re

# define file
# inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day3\\example.txt'
inputFile = 'C:\\Users\\cjee2\\Documents\\Git\\CodePractice\\AdventOfCode\\2023_day3\\input.txt'

# Program to read entire file
file = open(inputFile)
lines = file.readlines()
for line in lines:
    lines[lines.index(line)] = line.strip()

'''
Plan

- find a number
- for each number, is a symbol touching?
    - check from index-1 to index+len
        - make sure index-1 > 0
        - make sure index+len < size
    - if symbol found, add to sumList
'''

numList = []
for line in lines:
    numbers = re.findall(r'\b\d+\b', line)
    last = 0
    for number in numbers:
        y1 = max(lines.index(line) - 1, 0)
        y2 = min(lines.index(line) + 1, len(lines) - 1)
        x1 = max(line.index(number, last) - 1, 0)
        x2 = min(line.index(number, last) + len(number), len(line) - 1)
        last = line.index(number) + len(number)
        for i in range(y1, y2 + 1):
            for j in range(x1, x2 + 1): 
                if not lines[i][j].isdigit() and lines[i][j] != '.':
                    numList.append(int(number))
                    break
print(sum(numList))