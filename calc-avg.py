#!/usr/bin/env python3
# Calculate the average of the values in the second column.
# Each line in the file must contain two comma-separated columns.

import sys

filename = sys.argv[1]
count = 0; sum = 0

f = open(filename, 'r', encoding="utf-8")
for line in f:
    count += 1
    _, value = line.split(",")
    sum += int(value)
f.close()

avg = sum / count
print(f'{avg:.3f}')
