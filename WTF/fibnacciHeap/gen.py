N = input()
print N
from random import randint
print ' '.join([str(randint(-1000000000, 1000000000)) for i in range(N)])
