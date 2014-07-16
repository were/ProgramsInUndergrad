/*
ID : weng_xo2
LANG : C++11
PROG : agrinet
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

int N, g[MaxN][MaxN], dis[MaxN], ans;

int main(){
	freopen("agrinet.in", "r", stdin);
	freopen("agrinet.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		rep(j, 1, N) {
			scanf("%d", g[i] + j);
		}
		dis[i] = ~0u >> 1;
	}
	dis[1] = 0;
	rep(i, 1, N) {
		int idx = -1;
		rep(j, 1, N) {
			if(dis[j] != -1 && (idx == -1 || dis[idx] > dis[j])) {
				idx = j;
			}
		}
		ans += dis[idx];
		dis[idx] = -1;
		rep(j, 1, N) {
			if(dis[j] != -1) {
				dis[j] = min(dis[j], g[idx][j]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}

