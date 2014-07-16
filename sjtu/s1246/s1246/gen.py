from random import randint
N, M = map(int, raw_input().split())
a = randint(3, N)
b = randint(3, M)
c = randint(1, a - 2)
d = randint(1, b - 2)
print M, N, b, a, d, c
for i in range(N):
    print ' '.join(map(str, [randint(1, 100) for j in range(M)]))
