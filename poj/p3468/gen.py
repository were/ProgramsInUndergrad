N, Q, R = map(int, raw_input().split())
print N, Q
from random import randint
from math import sqrt
r = int(sqrt(R))
print' '.join(map(str, [randint(-R, R)for i in range(N)]))
for i in range(Q):
	l = randint(1, N)
	r = randint(l, N)
	if randint(0, 1):
		print 'Q', l, r
	else:
		print 'C', l, r, randint(-r, r)
