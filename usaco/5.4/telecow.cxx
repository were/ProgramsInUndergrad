/*
LANG : C++11
ID : weng_xo2
PROG : telecow
Programmed by wereFluke
C++0x stardard head file
*/
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#define X first
#define Y second
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

using std::fill;
using std::sort;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::tuple;
using std::make_tuple;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::pair;
using std::make_pair;
using std::less;
using std::greater;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::clog;
using std::ifstream;
using std::ofstream;
using std::queue;
using std::stack;
using std::deque;
using std::list;
using std::bitset;

using ll = long long;
using vi = vector<int>;
using mii = map<int, int>;
using pii = pair<int, int>;

const int MaxN = 10000, Inf = (int) 1e8;

struct Edge {
	int v, w, nxt;
}e[MaxN];

vi res;

int N, M, S, T, tot, u[MaxN], v[MaxN], h[MaxN], g[MaxN];

bool ban[MaxN];

int inVex(int x) {
	return x * 2 - 1;
}

int outVex(int x) {
	return x * 2;
}

void addEdge(int u, int v, int w) {
	//cerr << u << ", " << v << ": " << w << endl;
	e[tot] = Edge{v, w, g[u]}; g[u] = tot++;
	e[tot] = Edge{u, 0, g[v]}; g[v] = tot++;
}

void build() {
	tot = 0;
	fill(g + 1, g + 1 + N * 2, -1);
	rep(i, 1, N) if(!ban[i]) {
		addEdge(inVex(i), outVex(i), i == S || i == T ? Inf : 1);
		//addEdge(outVex(i), inVex(i), i == S || i == T ? Inf : 1);
	}
	rep(i, 1, M) {
		addEdge(outVex(u[i]), inVex(v[i]), Inf);
		addEdge(outVex(v[i]), inVex(u[i]), Inf);
	}
}

int dfs(int x, int flow) {
	//cerr << "!" << x << ", " << flow << endl;
	if(x == inVex(T)) {
		//cerr << flow << endl;
		return flow;
	} else {
		int ret = 0;
		for(int cur = g[x]; ~cur; cur = e[cur].nxt) {
			//printf("%d: %d %d: %d\n", e[cur].v, h[e[cur].v], x, h[x]);
			if(h[e[cur].v] == h[x] + 1) {
				int delta = dfs(e[cur].v, min(flow, e[cur].w));
				ret += delta;
				flow -= delta;
				e[cur].w -= delta;
				e[cur ^ 1].w += delta;
			}
		}
		return ret;
	}
}

bool bfs() {
	static int q[MaxN];
	int f, t;
	rep(i, 1, N * 2) {
		h[i] = -1;
	}
	f = t = 0;
	for(h[inVex(S)] = 1, q[t++] = inVex(S); f < t; ++f) {
		for(int cur = g[q[f]]; ~cur; cur = e[cur].nxt) {
			if(e[cur].w && h[e[cur].v] == -1) {
				q[t++] = e[cur].v;
				h[e[cur].v] = h[q[f]] + 1;
			}
		}
	}
	//rep(i, 1, N * 2) printf("%d ", h[i]); puts("");
	return ~h[inVex(T)];
}

int maxFlow() {
	int ret = 0;
	build();
	while(bfs()) {
		ret += dfs(inVex(S), Inf);
	}
	return ret;
}

int main(){
	freopen("telecow.in", "r", stdin);
	freopen("telecow.out", "w", stdout);
	scanf("%d%d%d%d", &N, &M, &S, &T);
	rep(i, 1, M) {
		scanf("%d%d", u + i, v + i);
	}
	//puts("read done");
	int ans = maxFlow();
	printf("%d\n", ans);
	rep(i, 1, N) {
		if(i == S || i == T) {
			continue;
		}
		//printf("%d\n", i);
		ban[i] = true;
		//printf("ban %d\n", i);
		//printf("%d\n", maxFlow());
		if(maxFlow() == ans - 1) {
			--ans;
			res.push_back(i);
		} else {
			ban[i] = false;
		}
	}
	for(size_t i = 0; i < res.size(); ++i) {
		printf(i == res.size() - 1u ? "%d\n" : "%d ", res[i]);
	}
	return 0;
}

