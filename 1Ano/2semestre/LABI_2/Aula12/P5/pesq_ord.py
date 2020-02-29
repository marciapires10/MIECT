l = [3, 1, 2, 4, 6]
l2 = sorted(l)
print(l2)

d = {1:'aaa', 3:'ccc', 2:'bbb'}
keys = sorted(d, reverse=True)
print('lista chaves ordenadas', keys)
for k in keys:
    print(k, ':', d[k])
    
if 2 in d:
    print('existe em d')
else:
    print('nao existe em d')

if 10 in l:
    print('existe em l')
else:
    print('nao existe em l')