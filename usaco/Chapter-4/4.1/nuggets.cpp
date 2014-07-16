/*
PROB : nuggets
ID : weng_xo2
LANG : C++
*/
#include <cstdio>
int N, a[10], ans;
bool f[1 << 17];
int main() {
	freopen("nuggets.in", "r", stdin);
	freopen("nuggets.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d", a + i);
	}
	f[0] = true;
	for(int i = 0; i < (1 << 17); ++i) {
		if(f[i]) {
			for(int j = 0; j < N; ++j) {
				if(i + a[j] < (1 << 17)) {
					f[i + a[j]] = true;
				}
			}
		}
		else {
			ans = i;
		}
	}
	printf("%d\n", ans <= (1 << 16) ? ans : 0);
	return 0;
}
