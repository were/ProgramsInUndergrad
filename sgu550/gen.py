from random import shuffle, choice, randint
N,R = map(int, raw_input().split())
print N
a = range(1, N + 1)
shuffle(a)
for i in range(1, N):
	print a[i], a[randint(0, i - 1)], randint(0, R)
a = range(1, N)
shuffle(a)
print ' '.join(map(str, a))
