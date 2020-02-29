frase = str(input("Frase? "))

nova = str.replace(frase,"L", "U")
nova1 = str.replace(nova, "l", "u")
nova2 = str.replace(nova1, "R", "")
nova3 = str.replace(nova2, "r", "")

print(nova3)