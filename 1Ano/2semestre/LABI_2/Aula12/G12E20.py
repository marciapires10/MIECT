ficheiro = open("texto1.txt", "r")
cont = 0
cont1 = 0
cont2 = 0
while True:
    linha = ficheiro.readline() #f.read(512) significa que queria ler 512 bytes
    cont += 1

    if linha == '': #significa que cheguei ao fim do ficheiro
        break

    palavras = linha.split(" ")
    for linha in palavras:
        cont1+=1
        cont2+= len(linha)

ficheiro.close()

print("Número de linhas: ", (cont-1))
print("Número de palavras: ", cont1)
print("Número de letras: ", cont2)