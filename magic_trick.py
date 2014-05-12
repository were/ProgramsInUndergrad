T = input()
for test in range(1, T + 1):
    a = []
    b = []
    x = input() - 1
    for i in range(4):
        a.append(map(int, raw_input().split()))
    y = input() - 1
    for i in range(4):
        b.append(map(int, raw_input().split()))
    ans = set(a[x]) & set(b[y])
    res = ''
    if len(ans) > 1:
        res = 'Bad magician!'
    elif len(ans) < 1:
        res = 'Volunteer cheated!'
    else:
        res = ''.join(map(str, ans))
    print 'Case #' + str(test) + ': ' + res
