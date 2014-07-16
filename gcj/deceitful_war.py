T = input()
for test in range(1, T + 1):
    N = input()
    A = sorted(map(float, raw_input().split()))
    B = sorted(map(float, raw_input().split()))
    a = A[:]
    b = B[:]
    ans1 = ans2 = 0
    for i in b[::-1]:
        if a[-1] > i:
            a = a[:-1]
            ans1 += 1
        else:
            a = a[1:]
    a = A[:]
    b = B[:]
    for i in a:
        if b[-1] < i:
            b = b[1:]
            ans2 += 1
        else:
            for j in range(len(b)):
                if b[j] > i:
                    b = b[:j] + b[j + 1:]
                    break
    print 'Case #' + str(test) + ': ' + str(ans1) + ' ' + str(ans2)
