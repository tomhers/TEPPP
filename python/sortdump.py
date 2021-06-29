import os
import sys

dirs = ['T0.70', 'T0.72', 'T0.74', 'T0.76', 'T0.78', 'T0.80', 'T0.90', 'T1.00', 'T1.10', 'T1.20', 'T1.30', 'T1.40', 'T1.50']
for d in dirs:
    indir = '../oakridgedata/other/' + sys.argv[1] + '/' + d
    outdir = '../oakridgedata/other_sorted/' + sys.argv[1] + '/' + d
    for filename in os.listdir(indir):
        f1 = open(indir+'/'+filename, 'r')
        new = []
        for i, line in enumerate(f1):
            if i < 9:
                continue
            else:
                s = line.split()
                s[0] = int(s[0])
                new.append(s)
        new.sort()
        tmp = filename.split('.txt')
        newfname = tmp[0]
        f2 = open(outdir+"/"+newfname+"sorted.txt", 'w')
        for x in new:
            for y in x:
                f2.write(str(y) + " ")
            f2.write('\n')
        f1.close()
        f2.close()
