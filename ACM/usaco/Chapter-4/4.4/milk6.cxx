/*
ID : weng_xo2
LANG : C++11
PROG : milk6
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

int N, M, u[1111], v[1111], w[1111], flag, hsh[33];
bool ban[1111];
ll g[33][33], res;
vi ans;

void build() {
	rep(i, 1, N) rep(j, 1, N) g[i][j] = 0ll;
	rep(i, 1, M) if(!ban[i]) g[u[i]][v[i]] += (ll) w[i] * (M + 1) + 1ll;
}

ll dfs(int x, ll flow) {
	hsh[x] = flag;
	if(x == N) {
		return flow;
	} else {
		ll ret = 0ll;
		rep(i, 1, N) if(g[x][i] && hsh[i] != flag) {
			if((ret = dfs(i, min(g[x][i], flow))) != 0ll) {
				g[x][i] -= ret;
				g[i][x] += ret;
				return ret;
			}
		}
		return 0ll;
	}
}

ll ek() {
	ll delta, ret = 0;
	++flag;
	while((delta = dfs(1, ~0ull >> 1ll)) != 0ll) {
		ret += delta;
		++flag;
	}
	return ret;
}

int main(){
	freopen("milk6.in", "r", stdin);
	freopen("milk6.out", "w", stdout);
	scanf("%d%d", &N, &M);
	rep(i, 1, M) scanf("%d%d%d", u + i, v + i, w + i);
	build();
	res = ek();
	printf("%lld ", res / (M + 1));
	rep(i, 1, M) {
		ban[i] = true;
		build();
		if(ek() == res - (ll) w[i] * (M + 1) - 1ll) {
			res -= (ll) w[i] * (M + 1) + 1ll;
			ans.push_back(i);
		} else {
			ban[i] = false;
		}
	}
	printf("%d\n", (int) ans.size());
	for(size_t i = 0; i < ans.size(); ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}

