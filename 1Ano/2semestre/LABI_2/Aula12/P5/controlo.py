x = 10 #int(input('valor?'))
if x > 0:
    print('pos')
    print('if')
elif x == 0:
    print('zero')
    print('elif')
else:
    print('neg')
    print('else')
    
n = 0
while n < 10:
    print('while', n)
    n += 1
    
for i in range(0, 10, 2):
    print('range', i)
    
l = [10, 20, 30, 40]
for i in l:
    print('l', i)
    
for idx in range(len(l)):
    print('idx', l[idx])
    
d = {10:['ana', 123], 20:['antonio', 2345]}
for k in d:
    print('d', d[k])