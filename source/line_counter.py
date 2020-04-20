import os
import functools

lines = 0
matches = []
for root, dirnames, filenames in os.walk('.'):
    for filename in filenames:
        line = len(open(os.path.join(root, filename), 'r').read().split("\n"))
        matches += ["{}: {}".format(filename, line)]
        lines = lines + line

def custom_compare(item1, item2):
    def strip(s):
        return int(s.split(": ")[1])
    return strip(item2) - strip(item1)

#matches.sort()
matches = sorted(matches, key=functools.cmp_to_key(custom_compare))

for match in matches:
    print(match)


print("In total {} lines".format(lines))
