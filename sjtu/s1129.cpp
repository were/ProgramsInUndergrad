#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

using std::vector;
using std::sort;

typedef long long ll;

int N, W, ans = ~0u >> 1, deg[66], tsk[66];
ll a[66], stat;
bool hsh[66];

int min(int a, int b) {
	return a < b ? a : b;
}

int cnt(ll x) {
	int ret = 0;
	for(; x; x -= x & -x) {
		if((x & -x & stat) == 0)
			++ret;
	}
	return ret;
}

bool cmp(int x, int y) {
	return cnt(a[x]) > cnt(a[y]);
}

void dfs(int x, ll y, int cnt) {
	if(cnt == ans && y != (1ll << N) - 1) {
		return;
	}
	if(x < N) {
		if(y >> tsk[x] & 1) {
			dfs(x + 1, y, cnt);
		}
		else {
			int b[66];
			int tot = 0;
			for(int i = 0; i < W; ++i) {
				if(!hsh[i] && (a[i] >> tsk[x] & 1)) { 
					b[tot++] = i;
				}
			}
			stat = y;
			sort(b, b + tot, cmp);
			for(int i = 0; i < tot; ++i) {
				hsh[b[i]] = true;
				dfs(x + 1, y | a[b[i]], cnt + 1);
				hsh[b[i]] = false;
			}
		}
	}
	else {
		ans = min(ans, cnt);
	}
}

bool cmpTsk(int x, int y) {
	return deg[x] < deg[y];
}

int main() {
	scanf("%d%d", &N, &W);
	for(int i = 0; i < N; ++i) {
		tsk[i] = i;
	}
	for(int i = 0; i < W; ++i) {
		int l;
		ll x;
		scanf("%d", &l);
		for(int j = 0; j < l; ++j) {
			scanf("%lld", &x);
			a[i] |= 1ll << (x - 1);
			++deg[x - 1];
		}
	}
	sort(tsk, tsk + N, cmpTsk);
	dfs(0, 0, 0);
	printf("%d\n", ans);
	return 0;
}
