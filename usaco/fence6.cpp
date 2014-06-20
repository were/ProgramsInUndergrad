/*
ID : weng_xo2
PROG : fence6
LANG : C++11
*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

const int MaxN = 222, Inf = ~0u >> 1;

using std::vector;
using std::priority_queue;
using std::min;

struct Edge {
	int v, w;
	Edge(int v, int w) : v(v), w(w) {}
};

bool operator< (const Edge &a, const Edge &b) {
	return a.w > b.w;
}

int N, root, ans = Inf, dis[MaxN * 2];
//int cnt;
bool linked[2][MaxN][MaxN], hsh[MaxN * 2], onRoute[MaxN * 2];
vector<Edge> g[MaxN * 2];

void addEdge(int u, int v, int w) {
	g[u].push_back(Edge(v, w));
	g[v].push_back(Edge(u, w));
}

int calc(int s, int t, int len) {
	priority_queue<Edge> q;
	for(int i = 1; i <= 2 * N; ++i) {
		dis[i] = Inf;
	}
	dis[s] = 0;
	q.push(Edge(s, 0));
	while(!q.empty()) {
		Edge top = q.top();
		q.pop();
		for(auto &cur: g[top.v]) {
			if(top.w + cur.w < dis[cur.v]) {
				if(top.v == s && cur.v == t) {
					continue;
				}
				dis[cur.v] = top.w + cur.w;
				q.push(Edge(cur.v, dis[cur.v]));
			}
		}
	}
	return dis[t] != Inf ? len + dis[t] : Inf;
}

int main() {
	freopen("fence6.in", "r", stdin);
	freopen("fence6.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		int s, l, n[2], x;
		scanf("%d%d%d%d", &s, &l, n, n + 1);
		addEdge(s * 2 - 1, s * 2, l);
		for(int j = 0; j < 2; ++j) {
			for(int k = 0; k < n[j]; ++k) {
				scanf("%d", &x);
				linked[j][s][x] = true;
			}
		}
	}
	for(int a = 0; a < 2; ++a) {
		for(int b = 0; b < 2; ++b) {
			for(int u = 1; u <= N; ++u) {
				for(int v = 1; v <= N; ++v) {
					if(linked[a][u][v] && linked[b][v][u]) {
						addEdge(u * 2 - a, v * 2 - b, 0);
					}
				}
			}
		}
	}
	for(int i = 1; i <= 2 * N; i += 2) {
		for(auto &j: g[i]) {
			if(j.w != 0 && j.v > i) {
				ans = min(ans, calc(i, j.v, j.w));
			}
		}
	}
	printf("%d\n", ans);
//	printf("%d\n", cnt);
	return 0;
}
