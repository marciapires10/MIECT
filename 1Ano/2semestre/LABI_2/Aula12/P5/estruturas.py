#listas
s = 'ola'
s2 = "ola"

l = [10, 20, 30]

print(s[0])
print(l[0])

print(len(s), len(l))

print(l + l)
print(s * 3)

l.append(40)
print(l)

print(s.upper())

s = 'ola+labi+python'
print(s.split('+'))

l = [0, 5.5, 'texto', True, [1, 2, 3]]
print(l)

# dicionarios

d = {10:['ana', 123], 20:['antonio', 2345]}
print(d)
d[30] = ['maria', 23345]
print(d)
print(len(d))

# tuplos

t = (1, 2, 3)
print(t)
print(len(t))
print(t[0])