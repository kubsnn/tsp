import sys
import random

#if len(sys.argv) < 4 get that data by input
if len(sys.argv) < 4:
    filename = input("Enter filename: ")
    n = int(input("Enter the number of cities: "))
    m = int(input("Enter the max coord: "))
else:
    filename = sys.argv[1]
    n = int(sys.argv[2])
    m = int(sys.argv[3])

result = set();
while len(result) < n:
    result.add((random.randint(0, m), random.randint(0, m)))

with open(filename, 'w') as f:
    f.write(str(n) + "\n")
    for x, y in result:
        f.write(str(x) + " " + str(y) + "\n")
