import sys

def default():
	sys.exit("Invalid input!")

line = raw_input("Input: ")
parts = line.split(" ")
part1 = float(parts[0])
op = parts[1];
part3 = float(parts[2])

d = {
    '+': lambda x,y: x+y,
    '-': lambda x,y: x-y,
    '*': lambda x,y: x*y,
    '/': lambda x,y: x/y
    }

try:
	result = d[op] (part1, part3)
except KeyError:
	default()
	
print "%s = %.2f" % (line, result)