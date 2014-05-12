#include <algorithm>
#include <cstdio>
#include <utility>

const int MaxN = 100010;

int N, f[MaxN], ans;
std::pair<int, int> a[MaxN];

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
	}
	std::sort(a + 1, a + 1 + N);
	for(int i = 1; i <= N; ++i) {
		f[i] = 1;
		for(int j = 1; j < i; ++j) {
			if(a[j].first < a[i].first && a[j].second < a[i].second) {
				f[i] = std::max(f[i], f[j] + 1);
			}
		}
//printf("%d %d\n", i, f[i]);
		ans = std::max(f[i], ans);
	}
	printf("%d\n", ans);
	return 0;
}
