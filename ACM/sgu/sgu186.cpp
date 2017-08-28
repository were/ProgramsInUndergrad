#include <algorithm>
#include <cstdio>

const int MaxN = 111;

int N, a[MaxN], ans;

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		scanf("%d", a + i);
	}
	std::sort(a + 1, a + 1 + N);
	for(int l = 1, r = N; l < r; ++l) {
		while(l < r && a[l]) {
			--a[l];
			--r;
			++ans;
		}
	}
	printf("%d\n", ans);
	return 0;
}
