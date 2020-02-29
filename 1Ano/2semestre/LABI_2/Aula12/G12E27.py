#Adivinhe o número
import random
n=0
a = random.randint(0,100)
x=0
while x!=a:
    x=int(input("Valor? "))
    n=n+1
    if x>a:
        print("O valor introduzido é maior.")
    elif x<a:
        print("O valor introduzido é menor.")
    elif x==a:
        print("O valor está certo!")

print("Acertou em ", n, " tentativas.")