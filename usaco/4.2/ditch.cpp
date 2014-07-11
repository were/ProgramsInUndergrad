/*
ID : weng_xo2
LANG : C++11
PROG : ditch
*/
#include <algorithm>
#include <cstdio>

using std::min;

const int Inf = ~0u >> 1;

int N, M, ans, h[222];

struct Edge {
	int v, w;
	Edge *nxt, *op;
}*g[222], buffer[888];

void addEdge(int u, int v, int w) {
	static Edge *tot = buffer;
	++tot; tot->w = w; tot->v = v; tot->nxt = g[u]; g[u] = tot;
	++tot; tot->w = 0; tot->v = u; tot->nxt = g[v]; g[v] = tot;
	g[u]->op = g[v];
	g[v]->op = g[u];
}

bool bfs() {
	for(int i = 1; i <= N; ++i) {
		h[i] = 0;
	}
	static int q[222], f = 0, t = 0;
	for(q[t++] = 1, h[1] = 1; f < t; ++f) {
		for(Edge *cur = g[q[f]]; cur; cur = cur->nxt) {
			if(cur->w && !h[cur->v]) {
				q[t++] = cur->v;
				h[cur->v] = h[q[f]] + 1;
			}
		}
	}
	return h[N] != 0;
}

int dfs(int x, int flow) {
	if(x == N) {
		return flow;
	}
	int ret = 0, delta;
	for(Edge *cur = g[x]; cur; cur = cur->nxt) {
		if(h[x] + 1 == h[cur->v]) {
			delta = dfs(cur->v, min(flow, cur->w));
			flow -= delta;
			cur->w -= delta;
			cur->op->w += delta;
			ret += delta;
		}
	}
	return ret;
}

int main() {
	freopen("ditch.in", "r", stdin);
	freopen("ditch.out", "w", stdout);
	scanf("%d%d", &M, &N);
	for(int i = 1; i <= M; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addEdge(u, v, w);
	}
	while(bfs()) {
		ans += dfs(1, Inf);
	}
	printf("%d\n", ans);
	return 0;
}
