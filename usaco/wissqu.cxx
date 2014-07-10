/*
ID : weng_xo2
LANG : C++11
PROG : wissqu
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
#define rep(i,f,t) for(int i(f);i<=(int)(t);++i)
#define per(i,t,f) for(int i(t);i>=(int)(f);--i)

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

char s[5][5];
bool hsh[5][5];
int cnt[5], ans;
vector<pii> res;

bool inRange(int x, int y) {
	return x >= 0 && x <= 3 && y >= 0 && y <= 3;
}

bool notExist(int x, int y, int k) {
	rep(dx, -1, 1) rep(dy, -1, 1) if(inRange(x + dx, y + dy) && s[x + dx][y + dy] == k) {
		return false;
	}
	return true;
}

void dfs(int dep) {
	if(dep < 16) {
		rep(k, 0, 4) if(cnt[k]) rep(i, 0, 3) rep(j, 0, 3) if(!hsh[i][j]) {
			if(notExist(i, j, k)) {
				--cnt[k];
				char pre = s[i][j];
				hsh[i][j] = true;
				s[i][j] = k;
				if(!ans) {
					res.push_back(pii(i + 1, j + 1));
				}
				dfs(dep + 1);
				if(!ans) {
					res.pop_back();
				}
				hsh[i][j] = false;
				s[i][j] = pre;
				++cnt[k];
			}
		}
	} else {
/*
		rep(i, 0, 4) {
			printf("%c %d\n", 'A' + i, cnt[i]);
		}
*/		if(!ans) rep(i, 0, res.size() - 1) printf("%c %d %d\n", s[res[i].X - 1][res[i].Y - 1] + 'A', res[i].X, res[i].Y);
		++ans;
		//printf("%d\n", ans);
	}
}

int main(){
	freopen("wissqu.in", "r", stdin);
	freopen("wissqu.out", "w", stdout);
	rep(i, 0, 3) {
		scanf("%s", s[i]);
		rep(j, 0, 3) s[i][j] -= 'A';
	}
/*
	rep(i, 0, 3) {
		rep(j, 0, 3)
			printf("%d", (int)s[i][j]);
		puts("");
	}
*/
	cnt[0] = 3;
	cnt[1] = 3;
	cnt[2] = 3;
	cnt[3] = 4;
	cnt[4] = 3;
	dfs(0);
	printf("%d\n", ans);
	return 0;
}

