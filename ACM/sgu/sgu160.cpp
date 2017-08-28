#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

const int MaxN = 10001;

int N, M, a[MaxN];
std::pair<int, int> f[MaxN];
std::vector<int> ans;

int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		scanf("%d", a + i);
		a[i] %= M;
		for(int j = 0; j < M; ++j) {
			if(f[j].first != 0 && f[j].first != i && !f[j * a[i] % M].first) {
				f[j * a[i] % M].first = i;
				f[j * a[i] % M].second = j;
			}
		}
		if(!f[a[i]].first) {
			f[a[i]].first = i;
			f[a[i]].second = -1;
		}
	}
	for(int i = M - 1; i >= 1; --i) {
		if(f[i].first) {
			printf("%d\n", i);
			int x = i;
			while(x != -1) {
				ans.push_back(f[x].first);
				x = f[x].second;
			}
			break;
		}
	}
	if(!ans.size()) {
		puts("1");
	}
	std::sort(ans.begin(), ans.end());
	for(unsigned i = 0; i < ans.size(); ++i) {
		printf(i == ans.size() - 1u ? "%d\n" : "%d ", ans[i]);
	}
	return 0;
}
