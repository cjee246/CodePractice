__author__ = "Calvin Jee"
__email__ = "cjee246@gmail.com"
__date__ = "2023-12-13"

'''
Description:

Module written for general functions used on 2023 Advent of Code

'''
# imports
import os

# Read entire file into list of lines, newline stripped
def file_lines(filepath):
    file = open(filepath)
    lines = file.readlines()
    for line in lines:
        lines[lines.index(line)] = line.strip()
    return lines

# Construct filepath of data file within same directory
def data_filepath(filename):
    return os.getcwd() + '\\' + filename