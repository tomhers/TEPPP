import math
import os

indir = '../main/slurmoutput/other/M04'
outdir = '../percentages/M04'
for filename in os.listdir(indir):

    print("Reading "+filename)
    f1 = open(indir+'/'+filename, 'r')
    f2 = open(outdir+'/globalpercentages'+filename, 'w')
    lines = f1.readlines()
    numlines = 0
    percentages = [0, 0, 0, 0, 0, 0, 0]
    halves = [0, 0, 0]
    numover50 = 0
    for line in lines:
        s = line.split()
        print(s)
        if len(s) == 2 and s[0].isdigit() == True:
            numlines+=1
            chunk = int(s[0])
            atom = int(s[1])
            if (chunk > 50):
                percentages[6] += 1
            else:
                percentages[int(math.floor(chunk/10))] += 1
            
            if (chunk > 50):
                numover50 += 1
            elif (atom < 50 and atom + chunk <= 50):
                halves[1] += 1
            elif (atom > 50 and atom + chunk > 50):
                halves[2] += 1
            else:
                halves[0] += 1
        else:
            print("bad line")

    f2.write("Number of lines: "+str(numlines)+'\n')
    f2.write("Percentage of chunk length 0: "+str((percentages[0] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 10: "+str((percentages[1] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 20: "+str((percentages[2] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 30: "+str((percentages[3] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 40: "+str((percentages[4] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 50: "+str((percentages[5] / numlines) * 100)+'\n')
    f2.write("Percentage of chunk length 51+: "+str((percentages[6] / numlines) * 100)+'\n')
    f2.write("Number over 50: "+str(numover50)+'\n')
    f2.write("Percentage in first half: "+str((halves[1] / (numlines-numover50)) * 100)+'\n')
    f2.write("Percentage in second half: "+str((halves[2] / (numlines-numover50)) * 100)+'\n')
    f2.write("Percentage in both halves: "+str((halves[0] / (numlines-numover50)) * 100)+'\n')
    f1.close()
    f2.close()
