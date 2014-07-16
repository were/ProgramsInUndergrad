/*
LANG : C++11
ID : weng_xo2
PROG : hidden
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

const int MaxN= 200010;

int N;
char s[MaxN];

int calc(char *s, int N) {
	int i = 0, j = 1, k = 0, t;
	while(i < N && j < N && k < N) {
		t = s[(i + k) % N] - s[(j + k) % N];
		if(t) {
			t > 0 ? i += k + 1 : j += k + 1;
			if(i == j) {
				++j;
			}
			k = 0;
		} else {
			++k;
		}
	}
	return min(i, j);
}

int main(){
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		while(!islower(s[i] = getchar()));
	}
	printf("%d\n", calc(s, N));
	return 0;
}
