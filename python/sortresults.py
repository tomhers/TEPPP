import os
import sys

indir = '../data/100/results/'
total = {}
count = 0
for filename in os.listdir(indir):
    f1 = open(indir + filename, 'r')
    lines = f1.readlines()
    for line in lines:
        s1 = line.split(' + ')
        if len(s1) <= 1:
            continue
        else:
            count += 1
            for el in s1:
                if el != '\n':
                    s2 = el.split('A^')
                    if int(s2[1]) in total:
                        total[int(s2[1])] += float(s2[0])
                    else:
                        total[int(s2[1])] = float(s2[0])

print(count)
print(total)