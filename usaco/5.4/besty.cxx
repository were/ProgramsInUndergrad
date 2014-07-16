/*
PROG : betsy
LANG : C++11
ID : weng_xo2
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

bool hsh[7][7];
int N, ans;

const int
	dx[] = {0, 0, 1, -1},
	dy[] = {-1, 1, 0, 0};

bool inRange(int x, int y) {
	return x >= 0 && x < N && y >= 0 && y < N && !hsh[x][y];
}

int cnt(int x, int y) {
	if(x == N - 1 && y == 0) {
		return -1;
	}
	int ret = 0;
	for(int i = 0; i < 4; ++i) {
		ret += inRange(x + dx[i], y + dy[i]);
	}
	return ret;
}

int must(int x, int y) {
	bool vergin = true;
	int ret = -1;
	for(int i = 0; i < 4; ++i) {
		if(inRange(x + dx[i], y + dy[i])) {
			if(cnt(x + dx[i], y + dy[i]) == 1) {
				if(vergin) {
					ret = i;
					vergin = false;
				} else {
					return 4;
				}
			}
		}
	}
	return ret;
}

void dfs(int x, int y, int cnt) {
	hsh[x][y] = true;
	if(x == N - 1 && y == 0) {
		ans += cnt == N * N;
	} else {
		int dir = must(x, y);
		if(dir == 4) {
			hsh[x][y] = false;
			return;
		}
		if(~dir) {
			dfs(x + dx[dir], y + dy[dir], cnt + 1);
			hsh[x][y] = false;
			return;
		}
		for(int i = 0; i < 4; ++i) {
			if(inRange(x + dx[i], y + dy[i])) {
				dfs(x + dx[i], y + dy[i], cnt + 1);
			}
		}
	}
	hsh[x][y] = false;
}

int main(){
	freopen("betsy.in", "r", stdin);
	freopen("betsy.out", "w", stdout);
	scanf("%d", &N);
	dfs(0, 0, 1);
	printf("%d\n", ans);
	return 0;
}

