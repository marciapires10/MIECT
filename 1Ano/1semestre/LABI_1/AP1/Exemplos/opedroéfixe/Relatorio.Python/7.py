import sys
import os.path

name_in = sys.argv[1]
name_out = sys.argv[2]


#Permissions(file in)
if not os.path.exists(name_in):
	sys.exit("ERROR: file '%s' does not exist!" % name_in)
if os.path.isdir(name_in):
	sys.exit("ERROR: file '%s' is a directory!" % name_in)
if not os.path.isfile(name_in):
	sys.exit("ERROR: '%s' is not a file!" % name_in)
name_in_dir = os.path.dirname(os.path.realpath(name_in))
if not os.access(name_in_dir, os.R_OK):
	sys.exit("ERROR: Cannot read file.")
	
#Permissions(file out)
if os.path.exists(name_out) and os.path.isfile(name_out):
	name_out_dir = os.path.dirname(os.path.realpath(name_out))
	while True:
		sub = raw_input("The file '%s' already exists. Overwrite it? (y/n):" % name_out)
		if sub == 'n' or sub == 'N':
			print "Bye!"
			sys.exit()
		if sub == 'y' or sub == 'Y':
			break
name_out_dir = os.path.dirname(os.path.realpath(name_out))
if not os.access(name_out_dir, os.W_OK):
	sys.exit("It is not possible to write in this directory.")

file_in = open(name_in, "r")
file_out = open(name_out, "w")

#Copy
while True:
	line = file_in.readline()
	if line == '':
		break
	file_out.write(line)

file_in.close()
file_out.close()

print "Copy completed!"
