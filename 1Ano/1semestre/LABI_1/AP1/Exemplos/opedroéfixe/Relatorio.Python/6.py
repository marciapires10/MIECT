from random import randint

num = randint(1,100)
cont = 0
print "Guess the number!"
print "The computer is choosing a number between 0-100..."
print "Done!"
while True:
	tmp = input("Guess: ")
	cont += 1
	if tmp == num:
		break
	if tmp > num:
		print "The correct number is lower!"
	if tmp < num:
		print "The correct number is higher!"	
print "Congratulations! You got %d points (lower is better)." % (cont)
