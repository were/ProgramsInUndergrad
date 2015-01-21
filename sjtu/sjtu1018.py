import sys
for i in sys.stdin.read().split('\n'):
    if len(i.split()) == 2:
        print sum(map(int, i.split()))
