while True:
	aitp1 = input("AITP1: ")
	if (aitp1 >= 0) and (aitp1 <= 20) :
		break
	print "Invalid!"
while True:
	aip = input("AIP: ")
	if (aip >= 0) and (aip <= 20) :
		break
	print "Invalid!"
while True:
	aitp2 = input("AITP2: ")
	if (aitp2 >= 0) and (aitp2 <= 20) :
		break
	print "Invalid!"
while True:	
	apf = input("APF: ")
	if (apf >= 0) and (apf <= 20) :
		break
	print "Invalid!"
final= aitp1*0.15 + aip*0.2 + aitp2*0.15 + apf*0.5
print "The final grade is %.2f" % (final)
if final >= 9.5 :
	print "Approved!"
else:
	print "Reproved!"