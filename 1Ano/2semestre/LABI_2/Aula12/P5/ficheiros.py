def readFile(nome):
    f = open(nome, 'r')
    l = []
    for linha in f:
        l.append(linha.rstrip())
    
    return l

def wordsCount(frases):
    d = {}
    for l in frases:
        pal = l.split(' ')
        for p in pal:
            if p in d:
                d[p] += 1
            else:
                d[p] = 1
                
    return d
    

def f(a, b):
    x = a + b
    y = a - b
    return (x, y) # devolução de um tuplo


l = readFile('f.txt')
print(l)
d = wordsCount(l)
print(d)

print(f(10, 5), f(50, 25), end=';', sep='->')
print(f(b = 10, a = 5)) # argumentos por keyword