/*
ID : weng_xo2
PROG : stall4
LANG : C++11
*/
#include <cstdio>
#include <cstring>

int N, M, pre[222], ans;
bool g[222][222], hsh[222];

bool dfs(int x) {
	for(int i = 1; i <= M; ++i) {
		if(g[x][i] && !hsh[i]) {
			hsh[i] = true;
			if(pre[i] == 0 || dfs(pre[i])) {
				pre[i] = x;
				return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("stall4.in", "r", stdin);
	freopen("stall4.out", "w", stdout);
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		int x, y;
		scanf("%d", &x);
		for(int j = 0; j < x; ++j) {
			scanf("%d", &y);
			g[i][y] = true;
		}
	}
	for(int i = 1; i <= N; ++i) {
		memset(hsh, 0, sizeof hsh);
		ans += dfs(i);
	}
	printf("%d\n", ans);
	return 0;
}
