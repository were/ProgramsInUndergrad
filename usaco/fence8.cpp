/*
PROG : fence8
ID : weng_xo2
LANG : C++11
*/

#include <algorithm>
#include <cstdio>

using std::sort;

int N, M, a[1 << 6], b[1 << 10], v[1 << 6], l, r, mid, maxWaste, waste;

bool dfs(int x, int l) {
	if(x < 0) {
		// puts("done!");
		return true;
	}
	if(waste > maxWaste) {
		return false;
	}
	for(int i = N - 1; i >= l; --i) {
		// printf("%d, %d %d\n", x, b[x], v[i]);
		if(b[x] <= v[i]) {
			v[i] -= b[x];
			if(v[i] < b[0]) {
				waste += v[i];
			}
			if((x + 1 <= mid) && b[x] == b[x + 1]) {
				if(dfs(x - 1, i)) {
					return true;
				}
			}
			else {
				if(dfs(x - 1, 0)) {
					return true;
				}
			}
			if(v[i] < b[0]) {
				waste -= v[i];
			}
			v[i] += b[x];
		}
	}
	return false;
}

int main() {
	freopen("fence8.in", "r", stdin);
	freopen("fence8.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", a + i);
	}
	scanf("%d", &M);
	for(int i = 0; i < M; ++i) {
		scanf("%d", b + i);
	}
	sort(a, a + N);
	sort(b, b + M);
	l = 0;
	r = M;
	while(l < r) {
		mid = (l + r) / 2;
		// printf("%d %d: %d\n", l, r, mid);
		maxWaste = waste = 0;
		for(int i = 0; i < N; ++i) {
			v[i] = a[i];
			maxWaste += v[i];
		}
		for(int i = 0; i <= mid; ++i) {
			maxWaste -= b[i];
		}
		if(dfs(mid, 0)) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
	printf("%d\n", l);
	return 0;
}
