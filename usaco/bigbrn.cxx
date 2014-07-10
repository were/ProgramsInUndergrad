/*
ID : weng_xo2
LANG : C++11
PROG : bigbrn
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

int N, M, s[1001][1001], a[1001][1001];

int main() {
	freopen("bigbrn.in", "r", stdin);
	freopen("bigbrn.out", "w", stdout);
	for(scanf("%d%d", &N, &M); M--; ) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = 1;
	}
	rep(i, 1, N) rep(j, 1, N) {
		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + a[i][j];
	}
	int ans = 0;
	rep(i, 1, N) rep(j, 1, N) {
		int l = 1, r = min(N - i + 1, N - j + 1) + 1;
		while(l != r) {
			int mid = (l + r) / 2;
			int x = i + mid - 1;
			int y = j + mid - 1;
			int sum = s[x][y] - s[x][j - 1] - s[i - 1][y] + s[i - 1][j - 1];
			if(sum == 0) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		if(l - 1 > ans) {
			ans = l - 1;
		}
	}
	printf("%d\n", ans);
	return 0;
}

