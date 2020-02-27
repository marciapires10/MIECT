name = raw_input("File name: ")
f = open(name, 'r+')
while True:
	line = f.readline()
	if line == "":
		break
	new_line = line.replace("r", "")
	new_line = new_line.replace("R", "")
	new_line = new_line.replace("l","u")
	new_line = new_line.replace("L","u")
	print new_line
f.close()