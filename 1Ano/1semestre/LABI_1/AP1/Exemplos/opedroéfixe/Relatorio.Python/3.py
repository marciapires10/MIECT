
a = input("Input: ")

i = 2
prime = True
for i in range(2, a/2):
	if a%i == 0:
		prime = False

if prime == False:
	print "The number %d is not prime." %(a)

elif prime == True:
	print "The number %d is prime." %(a)

	
	
