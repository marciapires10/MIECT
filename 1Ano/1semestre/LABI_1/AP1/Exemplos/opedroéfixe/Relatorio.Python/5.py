sum = 0
cont = 0
while True:
	n = input("Input(0 to stop): ")
	if n == 0:
		break
	sum = sum + n
	cont += 1
if cont==0:
	print "The sum is 0 and is not possible to determine the average."
else:
	av = sum/cont
	print "The sum of the values is %.1f and the average is %.1f" % (sum, av)
