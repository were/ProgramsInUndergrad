/*
PROG : snail
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

const int MaxN = 122;

int N, M, ans;
bool hsh[MaxN][MaxN], handi[MaxN][MaxN];
char s[10];


bool inRange(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= N && !hsh[x][y] && !handi[x][y];
}

void dfs(int x, int y, int step) {
	int xx, yy, delta;
	//printf("[%d %d]\n", x, y);
	rep(dx, -1, 1) rep(dy, -1, 1) if(abs(dx) + abs(dy) == 1) {
		for(xx = x, yy = y, delta = 0; inRange(xx + dx, yy + dy); xx += dx, yy += dy) {
			++delta;
			hsh[xx][yy] = true;
		}
		if(delta && !hsh[xx + dx][yy + dy]) {
			dfs(xx, yy, step + delta);
		} else {
			ans = max(ans, step + delta);
		}
		for(; xx != x || yy != y; xx -= dx, yy -= dy) {
			hsh[xx][yy] = false;
		}
	}
}

int main(){
	freopen("snail.in", "r", stdin);
	freopen("snail.out", "w", stdout);
	scanf("%d%d", &N, &M);
	rep(i, 1, M) {
		scanf("%s", s);
		int x = *s - 'A' + 1;
		int y;
		sscanf(s + 1, "%d", &y);
		//printf("%d %d\n", x, y);
		handi[x][y] = true;
	}
	dfs(1, 1, 1);
	printf("%d\n", ans);
	return 0;
}

