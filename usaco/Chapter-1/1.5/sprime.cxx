/*
PROG : sprime
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

bool isPrime(int x) {
	if(x < 2) {
		return false;
	}
	if(x < 4) {
		return true;
	}
	for(int i = 2; i * i <= x; ++i) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}

int N;

void dfs(int x, int cur) {
	if(x < N) {
		for(int i = 1; i < 10; ++i) {
			if(isPrime(cur * 10 + i)) {
				dfs(x + 1, cur * 10 + i);
			}
		}
	} else {
		printf("%d\n", cur);
	}
}

int main(){
	freopen("sprime.in", "r", stdin);
	freopen("sprime.out", "w", stdout);
	scanf("%d", &N);
	dfs(0, 0);
	return 0;
}

