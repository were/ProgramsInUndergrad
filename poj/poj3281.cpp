#include <algorithm>
#include <cstdio>

const int MaxN = 444, Inf = 1000000000;

int N, F, D, g[MaxN][MaxN], n, hsh[MaxN], ans, flag, delta;

int dfs(int x, int flow) {
	hsh[x] = flag;
	if(x == n - 1) {
		return flow;
	} else {
		int delta;
		for(int i = 0; i < n; ++i) {
			if(g[x][i] && hsh[i] != flag) {
				delta = dfs(i, std::min(g[x][i], flow));
				if(delta) {
					g[x][i] -= delta;
					g[i][x] += delta;
					return delta;
				}
			}
		}
	}
	return 0;
}

int main() {
	scanf("%d%d%d", &N, &F, &D);
	n = N + N + F + D + 2;
	for(int i = 1; i <= F; ++i) {
		g[0][i] = 1;
	}
	for(int i = 1; i <= N; ++i) {
		g[i + F][i + F + N] = 1;
	}
	for(int i = 1; i <= D; ++i) {
		g[N + N + F + i][n - 1] = 1;
	}
	for(int i = 1; i <= N; ++i) {
		int f, d, x;
		scanf("%d%d", &f, &d);
		for(int j = 0; j < f; ++j) {
			scanf("%d", &x);
			g[x][F + i] = 1;
		}
		for(int j = 0; j < d; ++j) {
			scanf("%d", &x);
			g[N + F + i][N + N + F + x] = 1;
		}
	}
	for(++flag; delta = dfs(0, Inf); ++flag) {
		ans += delta;
	}
	printf("%d\n", ans);
	return 0;
}
