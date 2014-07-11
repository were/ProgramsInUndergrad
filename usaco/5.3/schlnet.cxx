/*
ID : weng_xo2
LANG : C++11
PROG : schlnet
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

const int MaxN = 111;

bool g[MaxN][MaxN], gPrime[MaxN][MaxN];
int N, degIn[MaxN], degOut[MaxN], sccCnt, scc[MaxN];

int main() {
	freopen("schlnet.in", "r", stdin);
	freopen("schlnet.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		int x;
		for(scanf("%d", &x); x; scanf("%d", &x)) {
			g[i][x] = true;
		}
	}
	rep(k, 1, N) rep(i, 1, N) rep(j, 1, N) {
		if(g[i][k] && g[k][j]) {
			g[i][j] = true;
		}
	}
	rep(i, 1, N) if(!scc[i]) {
		scc[i] = i;
		++sccCnt;
		rep(j, 1, N) if(g[j][i] && g[i][j]) {
			scc[j] = i;
		}
	}
	//rep(i, 1, N) printf("%d: %d\n", i, scc[i]);
	if(sccCnt == 1) {
		puts("1");
		puts("0");
		return 0;
	}
	rep(i, 1, N) rep(j, 1, N) {
		if(g[i][j] && scc[i] != scc[j] && !gPrime[scc[i]][scc[j]]) {
			gPrime[scc[i]][scc[j]] = true;
			++degIn[scc[j]];
			++degOut[scc[i]];
		}
	}
	int cnt1 = 0, cnt2 = 0;
	rep(i, 1, N) {
		if(scc[i] == i) {
			if(degIn[i] == 0) {
				++cnt1;
			}
			if(degOut[i] == 0) {
				++cnt2;
			}
		}
	}
	printf("%d\n", cnt1);
	printf("%d\n", max(cnt1, cnt2));
	return 0;
}

