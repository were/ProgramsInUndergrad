from random import randint
N, M = map(int, raw_input().split())
print N, M
print 0, randint(1, 123456)
for i in range(1, N):
	print randint(1, i), randint(1, 123456)
for i in range(M):
	op = randint(0, 2)
	if op == 0:
		print 'V', randint(1, N), randint(1, 123456)
	if op == 1:
		print 'E', randint(1, N)
	if op == 2:
		print 'Q', randint(1, N)
