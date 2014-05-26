#include <algorithm>
#include <cstdio>

using std::min;

const int MaxN = 402;

int N, M, dis[MaxN], g[MaxN][MaxN], cap[MaxN][MaxN], q[MaxN], f, t, flow;
bool hsh[MaxN];

int dfs(int x, int flow) {
	if(x == N) {
		return flow;
	}
	else {
		int ret;
		for(int i = 1; i <= N; ++i) {
			if(cap[x][i]) {
				ret = dfs(i, min(flow, cap[x][i]));
				if(ret) {
					cap[x][i] -= ret;
					cap[i][x] += ret;
					return ret;
				}
			}
		}
	}
	return 0;
}

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		dis[i] = ~0u >> 1;
	}
	for(int i = 1; i <= M; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u][v] = w;
		g[v][u] = w;
	}
	dis[1] = 0;
	for(q[t++] = 1, hsh[1] = true; f != t; (++f) %= (N + 1)) {
		for(int i = 1; i <= N; ++i) {
			if(g[q[f]][i]) {
				if(dis[q[f]] + g[q[f]][i] < dis[i]) {
					dis[i] = dis[q[f]] + g[q[f]][i];
					if(!hsh[i]) {
						q[t++] = i;
						t %= (N + 1);
					}
				}
			}
		}
		hsh[q[f]] = false;
	}
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(g[i][j] && dis[i] + g[i][j] == dis[j]) {
				cap[i][j] = 1;
			}
		}
	}
	flow += dfs(1, ~0u >> 1);
	flow += dfs(1, ~0u >> 1);
	if(flow == 2) {
		puts("yep");
	}
	else {
		puts("no solution");
	}
	return 0;
}
