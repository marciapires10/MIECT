import os
import Crypto.Cipher
from Crypto.Cipher import ARC4
import sys

ficheiro = open (sys.argv[1], "rb")


cipher = ARC4.new("chave") #new = inicializar a cifra

block = ficheiro.read(1024)

while len(block) > 0:
    cryptogram = cipher.encrypt(block) #encrypt funciona para todas as cifras, ARC4, SHA1, etc.
    os.write(1, cryptogram ) #impressão dos dados binários no stdout

decipher = ARC4.new("chave")
decrypted = decipher.decrypt( cryptogram )
print( decrypted.decode("utf-8") )