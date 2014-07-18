/*
ID : weng_xo2
LANG : C++11
PROG : tour
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

int N, M, f[111][111], ans;
bool g[111][111];
map<string, int> idx;

int main(){
	freopen("tour.in", "r", stdin);
	freopen("tour.out", "w", stdout);
	scanf("%d%d", &N, &M);
	rep(i, 1, N) {
		string tmp;
		cin >> tmp;
		idx[tmp] = i;
	}
	rep(i, 1, M) {
		string s1, s2;
		cin >> s1 >> s2;
		g[idx[s1]][idx[s2]] = true;
		g[idx[s2]][idx[s1]] = true;
		//printf("%d %d\n", idx[s1], idx[s2]);
	}
	f[1][1] = 1;
	rep(i, 1, N) {
		rep(j, i + 1, N) {
			rep(k, 1, j - 1) {
				if(g[k][j] && f[i][k]) {
					f[i][j] = max(f[i][k] + 1, f[i][j]);
				}
			}
			f[j][i] = f[i][j];
		}
	}
	int ans = 1;
	rep(i, 1, N) if(g[i][N]) {
		ans = max(ans, f[i][N]);
	}
	printf("%d\n", ans);
	return 0;
}

