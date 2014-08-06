#include <algorithm>
#include <cstdio>
#include <utility>

using namespace std;

const int MaxN = 2222;

int N, n, st[MaxN];
bool hsh[MaxN];
pair<int, int> a[MaxN];

pair<int, int> operator- (pair<int, int> a, pair<int, int> b) {
	return make_pair(a.first - b.first, a.second - b.second);
}

long long det(pair<int, int> a, pair<int, int> b) {
	return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

void makeHull() {
	st[0] = 0;
	for(int i = 1; i <= N; ++i) if(!hsh[i]) {
		while(st[0] >= 2 && det(a[st[st[0]]] - a[st[st[0] - 1]], a[i] - a[st[st[0] - 1]]) < 0) {
			--st[0];
		}
		st[++st[0]] = i;
	}
	int bottom = st[0];
	for(int i = N; i >= 1; --i) if(!hsh[i]) {
		while(st[0] > bottom && det(a[st[st[0]]] - a[st[st[0] - 1]], a[i] - a[st[st[0] - 1]]) < 0) {
			--st[0];
		}
		st[++st[0]] = i;
	}
	for(int i = 1; i <= st[0]; ++i) {
		if(!hsh[st[i]]) {
			hsh[st[i]] = true;
			--n;
		}
	}
}

int main() {
	while(~scanf("%d", &N)) {
		for(int i = 1; i <= N; ++i) {
			scanf("%d%d", &a[i].first, &a[i].second);
			hsh[i] = false;
		}
		n = N;
		int ans = 0;
		sort(a + 1, a + 1 + N);
		while(n >= 3) {
			makeHull();
			++ans;
		}
		printf("%d\n", ans);
	}
}
