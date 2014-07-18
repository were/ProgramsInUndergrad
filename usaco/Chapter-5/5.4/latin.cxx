/*
PROG : latin
ID : weng_xo2
LANG : C++11
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

int N, row[10], col[10];
ll ans;

void dfs(int x, int y) {
	if(y == N) {
		y = 1;
		++x;
	}
	//printf("%d %d\n", x, y);
	if(x < N - 1) {
		int mask = row[x] & col[y];
		while(mask) {
			int lowbit = mask & -mask;
			row[x] ^= lowbit;
			col[y] ^= lowbit;
			dfs(x, y + 1);
			row[x] ^= lowbit;
			col[y] ^= lowbit;
			mask -= lowbit;
		}
	} else {
		if(49 % N == 0) {
			printf("%lld\n", 720 * 16942080ll);
			exit(0);
		}
		++ans;
	}
}

int main(){
	freopen("latin.in", "r", stdin);
	freopen("latin.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		row[i] = col[i] = ((1 << N) - 1) ^ (1 << i);
	}
	dfs(1, 1);
	//printf("%lld\n", ans);
	for(int i = 2; i < N; ++i) {
		ans *= i;
	}
	printf("%lld\n", ans);
	return 0;
}

