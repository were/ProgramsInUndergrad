from math import exp
x = [8.660254037844386e-01, 0, -8.660254037844386e-01]
y = map(exp, x)
n = len(x)
for i in range(n):
    for j in range(n):
        if i != j:
            print '(y - (', x[j], '))',
    print '(',
    for j in range(n):
        if i != j:
            print '(%f - (' % x[i], x[j], '))',
    print ')+',
