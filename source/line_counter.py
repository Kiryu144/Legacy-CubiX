import os

lines = 0
matches = []
for root, dirnames, filenames in os.walk('.'):
    for filename in filenames:
        line = len(open(os.path.join(root, filename), 'r').read().split("\n"))
        print("{}: {}".format(filename, line))
        lines = lines + line

print("In total {} lines".format(lines))
