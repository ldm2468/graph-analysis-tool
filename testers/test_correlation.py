#!/usr/bin/env python3

import math
import sys

# file[0]: file name, file[1]: column
def get_data(file):
    fname, column = file[0], int(file[1])
    res = {}
    with open(fname, mode = 'r') as f:
        for line in f:
            cols = line.split()
            if not cols[0].isnumeric():
                continue # numeric id only
            res[int(cols[0])] = float(cols[column])
    return res

# data[0], data[1]: dictionary with same keys
# returns tuple (a, b, r^2)
def calc_correlation(data):
    sumx, sumx2, sumy, sumy2, sumxy, n = 0, 0, 0, 0, 0, 0
    for key in data[0]:
        assert key in data[1], f'Error: key {key} does not exist in file 2'
        x, y = data[0][key], data[1][key]
        sumx += x
        sumy += y
        sumx2 += x * x
        sumy2 += y * y
        sumxy += x * y
        n += 1

    b = (n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx)
    a = (sumy - b * sumx) / n
    r2 = b * (n * sumxy - sumx * sumy) / (n * sumy2 - sumy * sumy)
    return a, b, r2

if len(sys.argv) != 5:
    print('usage: test_correlation.py <file 1> <column> <file 2> <column>')
    exit(1)

files = [sys.argv[1:3], sys.argv[3:5]]

data = [get_data(f) for f in files]

a, b, r2 = calc_correlation(data)

print('y = a + b x')
print(f'a = {a}')
print(f'b = {b}')
print(f'r^2 = {r2}')
