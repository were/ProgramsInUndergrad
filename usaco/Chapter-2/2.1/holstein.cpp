/*
ID : weng_xo2
LANG : C++11
PROG : holstein
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

int N, M, cur[1111], need[1111], a[20][1111], ans, ansMask;

bool check() {
	for(int i = 1; i <= N; ++i) {
		if(cur[i] < need[i]) {
			return false;
		}
	}
	return true;
}

void dfs(int x, int mask) {
	if(x <= M) {
		for(int i = 1; i <= N; ++i) {
			cur[i] += a[x][i];
		}
		dfs(x + 1, mask | (1 << x));
		for(int i = 1; i <= N; ++i) {
			cur[i] -= a[x][i];
		}
		dfs(x + 1, mask);
	} else {
		if(check()) {
			int cnt = 0;
			rep(i, 1, M) if(mask >> i & 1) ++cnt;
			if(cnt < ans) ans = cnt, ansMask = 1 << (M + 2);
			//printf("%d %d %d %d\n", cnt, ans, mask, ansMask);
			if(cnt == ans) ansMask = min(ansMask, mask);
		}
	}
}

int main(){
	freopen("holstein.in", "r", stdin);
	freopen("holstein.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		scanf("%d", need + i);
	}
	scanf("%d", &M);
	rep(i, 1, M) {
		rep(j, 1, N) {
			scanf("%d", a[i] + j);
		}
	}
	ans = M;
	ansMask = 1 << (M + 2);
	dfs(1, 0);
	int cnt = 0;
	rep(i, 1, M) if(ansMask >> i & 1) ++cnt;
	printf("%d", cnt);
	rep(i, 1, M) if(ansMask >> i & 1) {
		printf(" %d", i);
	}
	puts("");
	return 0;
}

