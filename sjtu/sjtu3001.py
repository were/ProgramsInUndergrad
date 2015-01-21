def f(x):
    if not ''.join(sorted(set(i for i in str(x)))) in ['4', '7', '47']:
        return 1
    for i in range(2, x):
        if x % i == 0:
            return 1
        if i * i > x:
            break
    return 0
print "YNEOS"[f(input())::2]
