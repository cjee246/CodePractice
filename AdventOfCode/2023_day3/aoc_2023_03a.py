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
    numbers = re.findall(r'\b\d+\b')
    for number in numbers:
        y1 = max(lines.index(line) - 1, 0)
        y2 = min(lines.index(line) + 1, lines.__len__)
        x1 = max(numbers.index(number) - 1, 0)
        x2 = min(numbers.index(number) + len(number) + 1, len(line))
        for i in range(x1, x2):
            for j in range(y1, y2):
                if not lines[j][i].isdigit() & lines[j][i] != '.':
                    numList.append(int(number))
                    break
print(sum(numList))