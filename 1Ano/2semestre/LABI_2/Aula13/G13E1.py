import hashlib
import sys

ficheiro = open(sys.argv[1], "r")
h = hashlib.sha1()

for l in ficheiro:
    h.update(l.encode('utf-8'))


print(h.hexdigest())

ficheiro.close()

