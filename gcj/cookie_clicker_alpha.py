T = input()
for test in range(1, T + 1):
    c, f, x = map(float, raw_input().split())
    ans = 0.
    g = 2.
    while (c / g) + (x / (g + f)) < x / g:
        ans += c / g
        g += f
    print 'Case #' + str(test) + ': ' + str(ans + x / g)
