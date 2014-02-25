a,b = map(int, raw_input().split())
ans = 0
out = a * b
while out / b:
    ans += out / b
    out = out / b + out % b
print ans
