#include <algorithm>
#include <cstdio>

const int MaxN = 100010;

int N, K, n, a[MaxN], b[MaxN], bit[MaxN];

int main() {
	while(~scanf("%d%d", &N, &K)) {
		for(int i = 1; i <= N; ++i) {
			scanf("%d", a + i);
			b[i] = a[i];
			bit[i] = 0;
		}
		std::sort(b + 1, b + 1 + N);
		n = std::unique(b + 1, b + 1 + N) - b - 1;
		for(int i = 1; i <= N; ++i) {
			a[i] = std::lower_bound(b + 1, b + 1 + n, a[i]) - b;
		}
		long long ans = 0ll;
		for(int i = 1; i <= N; ++i) {
			ans += i - 1;
			for(int j = a[i]; j; j -= j & -j) {
				ans -= bit[j];
			}
			for(int j = a[i]; j <= n; j += j & -j) {
				++bit[j];
			}
		}
		printf("%lld\n", std::max(ans - K, 0ll));
	}
}
