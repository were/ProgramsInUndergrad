/*
Programmed by wereFluke
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
#include <list>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)
#define bit_up(i,f,t) for(int i(f);i<=(t);i+=i&-i)
#define bit_down(i,f) for(int i(f);i;i-=i&-i)

#define X first
#define Y second

using std::sort;
using std::bitset;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
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

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

int T, N, M, dfn[1111], low[1111], scc[1111], st[1111], cur, in[1111];
bool hsh[1111], flag;
vi g[1111], G[1111];

void dfs(int x) {
	st[++st[0]] = x;
	low[x] = dfn[x] = ++cur;
	for(size_t i = 0; i < g[x].size(); ++i) {
		if(!scc[g[x][i]]) {
			if(!dfn[g[x][i]]) {
				dfs(g[x][i]);
			}
			low[x] = min(low[x], low[g[x][i]]);
		}
	}
//printf("%d %d\n", dfn[x], low[x]);
	if(low[x] == dfn[x]) {
		scc[x] = x;
		while(st[st[0]] != x) {
			scc[st[st[0]--]] = x;
		}
		--st[0];
	}
}

void topo(int x) {
	static int q[1111];
	int f = 0, t = 0;
	for(q[t++] = x, hsh[x] = true; f < t; ++f) {
//printf("%d ", q[f]);
		int cnt = 0;
		for(size_t i = 0; i < G[q[f]].size(); ++i) {
			if(--in[G[q[f]][i]] == 0) {
				q[t++] = G[q[f]][i];
				hsh[G[q[f]][i]] = true;
				++cnt;
			}
		}
		if(cnt > 1) {
//puts("T_T");
			flag = false;
			return;
		}
	}
//puts("");
}

int main(){
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		cur = st[0] = 0;
		rep(i, 1, N) {
			in[i] = scc[i] = dfn[i] = low[i] = 0;
			hsh[i] = false;
			g[i].clear();
			G[i].clear();
		}
		rep(i, 1, M) {
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
		}
		rep(i, 1, N) {
			if(!dfn[i]) {
				dfs(i);
			}
		}
		rep(i, 1, N) {
			for(size_t j = 0; j < g[i].size(); ++j) {
				if(scc[i] != scc[g[i][j]]) {
//printf("%d %d\n", scc[i], scc[g[i][j]]);
					G[scc[i]].push_back(scc[g[i][j]]);
					++in[scc[g[i][j]]];
				}
			}
		}
		flag = true;
//rep(i, 1, N) printf("%d %d\n", i, scc[i]);
		if(flag) {
			rep(i, 1, N) {
				if(i == scc[i] && in[i] == 0) {
//printf("%d\n", i);
					topo(i);
					break;
				}
			}
			rep(i, 1, N) {
				if(i == scc[i] && !hsh[i]) {
//printf("%d\n", i);
					flag = false;
					break;
				}
			}
		}
		puts(flag ? "Yes" : "No");
	}
}

