/*
PROG : humble
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
#include <climits>
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

set<pii> heap;
int N, K, a[100];

void push(ll res, int idx) {
	if(res < INT_MAX) {
		if((int) heap.size() > K && (int) res > heap.rbegin()->first) {
			return;
		}
		heap.insert(pii((int) res, idx));
	}
}

int main(){
	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);
	scanf("%d%d", &N, &K);
	for(int i = 0; i < N; ++i) {
		scanf("%d", a + i);
		heap.insert(pii(a[i], i));
	}
	--K;
	while(K--) {
		pii top = *heap.begin();
		heap.erase(heap.begin());
		for(int j = top.Y; j < N; ++j) {
			push(ll(top.X) * a[j], j);
		}
	}
	printf("%d\n", heap.begin()->first);
	return 0;
}

