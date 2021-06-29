f1 = open("slurm-3101.out", 'r')
lines = f1.readlines()
count = 0
d = {}

for line in lines:
    s = line.split(' + ')
    s.remove('\n')
    print(s)
    count += 1
    for x in s:
        s1 = x.split('A^')
        if (float(s1[0]) != 0 or int(s1[1]) != 0):
            print(s1)
            res = d.get(int(s1[1]))
            if (res == None):
                d[int(s1[1])] = float(s1[0])
            else:
                d[int(s1[1])] = d[int(s1[1])] + float(s1[0])
        else:
            count -= 1

print(d)
final = {}
for key in sorted(d):
    final[key] = d[key] / count
    print(str(final[key]) + "A^" + str(key) + " + ",end=""),
print()
print(count)
