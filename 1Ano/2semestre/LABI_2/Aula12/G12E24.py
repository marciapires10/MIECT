x = int(input("Valor? "))
div = 0

for i in range(1, x):
    if x%i == 0:
       div += 1
       if div > 1:
           break
if (div > 1 or x==1):
    print("O número não é primo")
else:
    print("O número é primo")