fp = open("./rabbit", "r")
data = fp.readlines()
fp.close()
n = m = 0
for i in xrange(len(data)):
    print data[i]
    if 'element vertex' in data[i]:
        n = int(data[i].split()[2])
    if 'element face' in data[i]:
        m = int(data[i].split()[2])
    if 'end_header' in data[i]:
        data = data[i + 1:]
        break
points = []
for i in data[:n]:
    points.append(map(str, [j * 500 for j in map(float, i.split()[:3])]))
for i in data[n:]:
    cnt = 1
    print 'Triangle'
    for j in map(int, i.split()[1:]):
        print '\td%d' % cnt, ' '.join(points[j])
        cnt += 1
    print '\tmaterial 1'
