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

const int MaxN = 11111;

vi g[MaxN];
int N, M, dfn[MaxN], low[MaxN], pre[MaxN], cnt[MaxN], cur, connectCnt, root, ans;

void dfs(int x) {
	dfn[x] = low[x] = ++cur;
	int deg = 0;
	for(size_t i = 0; i < g[x].size(); ++i) {
		if(g[x][i] == pre[x]) {
			continue;
		}
		if(!dfn[g[x][i]]) {
			pre[g[x][i]] = x;
			dfs(g[x][i]);
			++deg;
			low[x] = min(low[x], low[g[x][i]]);
			if((x == root && deg > 1) || (x != root && dfn[x] <= low[g[x][i]])) {
				++cnt[x];
			}
		} else {
			low[x] = min(low[x], dfn[g[x][i]]);
		}
	}
}

int main(){
	while(scanf("%d%d", &N, &M), N) {
		if(M == 0) {
			printf("%d\n", N - 1);
			continue;
		}
		rep(i, 0, N - 1) {
			g[i].clear();
			cnt[i] = dfn[i] = low[i] = 0;
			pre[i] = -1;
		}
		connectCnt = cur = 0;
		ans = 0;
		rep(i, 1, M) {
			int u, v;
			scanf("%d%d", &u, &v);
			g[u].push_back(v);
			g[v].push_back(u);
		}
		rep(i, 0, N - 1) {
			if(!dfn[i]) {
				++connectCnt;
				root = i;
				dfs(i);
			}
			ans = max(ans, cnt[i]);
		}
		printf("%d\n", connectCnt + ans);
	}
}

