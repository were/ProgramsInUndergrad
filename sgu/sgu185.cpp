#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

using std::min;
using std::vector;

const int MaxN = 402, Inf = ~0u >> 1;

int N, M, dis[MaxN], g[MaxN][MaxN], cap[MaxN][MaxN], q[MaxN], f, t, flow, route[MaxN];
vector<int> ans;
bool hsh[MaxN];

int dfs(int x, int flow) {
	hsh[x] = true;
	if(x == N) {
		return flow;
	}
	else {
		int ret;
		for(int i = 1; i <= N; ++i) {
			if(cap[x][i] && !hsh[i]) {
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

bool dfs(int x) {
	ans.push_back(x);
	if(x == N) {
		return true;
	}
	for(int i = 1; i <= N; ++i) {
		if(dis[x] + g[x][i] == dis[i] && cap[x][i] == 0) {
			if(dfs(i)) {
				cap[x][i] = -1;
				return true;
			}
		}
	}
	ans.pop_back();
	return false;
}

int main() {
	// freopen("input", "r", stdin);
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		dis[i] = ~0u >> 1;
		for(int j = 1; j <= N; ++j) {
			g[i][j] = Inf;
		}
	}
	for(int i = 1; i <= M; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u][v] = min(g[u][v], w);
		g[v][u] = min(g[v][u], w);
	}
	dis[1] = 0;
	for(q[t++] = 1, hsh[1] = true; f != t; (++f) %= (N + 1)) {
		for(int i = 1; i <= N; ++i) {
			if(g[q[f]][i] != Inf) {
				if(dis[q[f]] + g[q[f]][i] < dis[i]) {
					dis[i] = dis[q[f]] + g[q[f]][i];
					if(!hsh[i]) {
						q[t++] = i;
						t %= (N + 1);
						hsh[i] = true;
					}
				}
			}
		}
		hsh[q[f]] = false;
	}
	//puts("shortest path done...");
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= N; ++j) {
			if(g[i][j] != Inf && dis[i] + g[i][j] == dis[j]) {
				cap[i][j] = 1;
			}
		}
	}
	//puts("build done...");
	flow += dfs(1, ~0u >> 1);
	memset(hsh, 0, sizeof hsh);
	flow += dfs(1, ~0u >> 1);
	if(flow == 2) {
		dfs(1);
		for(unsigned i = 0; i < ans.size(); ++i) {
			printf("%d ", ans[i]);
		}
		puts("");
		ans.clear();
		dfs(1);
		for(unsigned i = 0; i < ans.size(); ++i) {
			printf("%d ", ans[i]);
		}
		puts("");
	}
	else {
		puts("No solution");
	}
	return 0;
}
