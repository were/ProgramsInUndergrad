#include <algorithm>
#include <cstdio>
#define rep(i,f,t) for(int i(f);i<=(t);++i)

using std::min;

const int MaxN = 222, MaxM = 44444;

int N, M, w[MaxN][MaxN], in[MaxN], out[MaxN];
int q[MaxN], h[MaxN], hsh[MaxN], flag;
int u[MaxM], v[MaxM], l[MaxM], c[MaxM];

struct Edge {
	int v;
	Edge *nxt;
	Edge(int v, Edge *nxt) : v(v), nxt(nxt) {}
}*g[MaxN];

void addEdge(int a, int b, int c) {
	g[a] = new Edge(b, g[a]);
	w[a][b] = c;
	g[b] = new Edge(a, g[b]);
	w[b][a] = 0;
}

bool bfs() {
	static int f, t;
	f = t = 0;
	for(q[t++] = 0, hsh[0] = flag; f < t; ++f) {
		for(Edge *cur = g[q[f]]; cur; cur = cur->nxt) {
			if(w[q[f]][cur->v] && hsh[cur->v] != flag) {
				q[t++] = cur->v;
				h[cur->v] = h[q[f]] + 1;
				hsh[cur->v] = flag;
			}
		}
	}
	return hsh[N + 1] == flag;
}

int dfs(int x, int flow) {
	if(x == N + 1) {
		return flow;
	}
	else {
		int ret = 0, delta;
		for(Edge *cur = g[x]; cur && flow; cur = cur->nxt) {
			if(w[x][cur->v] && h[cur->v] == h[x] + 1) {
				delta = dfs(cur->v, min(flow, w[x][cur->v]));
				ret += delta;
				flow -= delta;
				w[x][cur->v] -= delta;
				w[cur->v][x] += delta;
			}
		}
		return ret;
	}
}

int main(){
	scanf("%d%d", &N, &M);
	rep(i, 1, M) {
		scanf("%d%d%d%d", u + i, v + i, l + i, c + i);
		addEdge(u[i], v[i], c[i] - l[i]);
		out[u[i]] += l[i];
		in[v[i]] += l[i];
	}
	rep(i, 1, N) {
		if(in[i] > out[i]) {
			addEdge(0, i, in[i] - out[i]);
		}
		if(in[i] < out[i]) {
			addEdge(i, N + 1, out[i] - in[i]);
		}
	}
	while(++flag, bfs()) {
		dfs(0, ~0u >> 1);
	}
	rep(i, 1, N) {
		if(in[i] > out[i]) {
			if(w[0][i]) {
				puts("NO");
				return 0;
			}
		}
		if(in[i] < out[i]) {
			if(w[i][N + 1]) {
				puts("NO");
				return 0;
			}
		}
	}
	puts("YES");
	rep(i, 1, M) {
		printf("%d\n", w[v[i]][u[i]] + l[i]);
	}
	return 0;
}

