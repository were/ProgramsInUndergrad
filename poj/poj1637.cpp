#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;

const int MaxN = 222, Inf = 1000000000;

int T, N, M, g[MaxN][MaxN], deg[MaxN], h[MaxN], gap[MaxN];

void init() {
	memset(g, 0, sizeof g);
	memset(deg, 0, sizeof deg);
	scanf("%d%d", &N, &M);
	for(int i = 0; i < M; ++i) {
		int u, v, d;
		scanf("%d%d%d", &u, &v, &d);
		g[u][v] += d ^ 1;
//if(!d) printf("%d, %d\n", u, v);
		++deg[u];
		--deg[v];
	}
}

int dfs(int x, int flow) {
	if(x == N + 1) {
//printf("flow: %d\n", flow);
		return flow;
	}
	int delta, ret = 0, minH = N + 2;
	for(int i = 0; i <= N + 1; ++i) {
		if(g[x][i]) {
			if(h[i] + 1 == h[x]) {
				delta = dfs(i, min(flow, g[x][i]));
				flow -= delta;
				g[x][i] -= delta;
				g[i][x] += delta;
				ret += delta;
				if(!flow || h[0] >= N + 2) {
					return ret;
				}
			}
			minH = min(minH, h[i]);
		}
	}
	if(ret) {
		return ret;
	}
	if(--gap[h[x]] == 0) {
		h[0] = N + 1;
	}
	h[x] = minH + 1;
	++gap[h[x]];
	return 0;
}

int sap() {
	memset(h, 0, sizeof h);
	memset(gap, 0, sizeof gap);
	gap[0] = N + 2;
	int ret = 0;
	while(h[0] < N + 2) {
		ret += dfs(0, Inf);
	}
//printf("%d\n", ret);
	return ret;
}

void work() {
	int full = 0;
	for(int i = 1; i <= N; ++i) {
		if(deg[i] % 2) {
			puts("impossible");
			return;
		}
		if(deg[i] > 0) {
			g[0][i] = deg[i] / 2;
			full += deg[i] / 2;
		}
		if(deg[i] < 0) {
			g[i][N + 1] = -deg[i] / 2;
		}
//printf("%d: %d\n", i, deg[i]);
	}
//for(int i = 0; i <= N + 1; ++i) for(int j = 0; j <= N + 1; ++j) if(g[i][j]) printf("<%d, %d>: %d\n", i, j, g[i][j]);
//printf("%d ", full);
	if(sap() != full) {
		puts("impossible");
	} else {
		puts("possible");
	}
}

int main() {
	scanf("%d", &T);
	while(T--) {
		init();
		work();
	}
}
