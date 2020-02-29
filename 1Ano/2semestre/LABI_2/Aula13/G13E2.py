import hashlib
import sys

ficheiro = open("texto1.txt", "rb")
h = hashlib.sha1()

buffer = ficheiro.read(512)

while len(buffer) > 0:
    buffer = ficheiro.read(512)

for l in ficheiro:
    h.update(l.encode('utf-8'))


print(h.hexdigest())

ficheiro.close()

