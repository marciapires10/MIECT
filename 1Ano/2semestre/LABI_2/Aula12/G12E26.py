a = []
x=1
n=0
soma=0
media=0
while x!=0:
    x = int(input("Valor? "))
    a.append(x)
    n=n+1

for a in a:
    soma = soma + a
    media = soma/(n-1)

print("Soma: ", soma)
print("Média: ", media)

