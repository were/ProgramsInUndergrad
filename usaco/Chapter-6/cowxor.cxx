/*
LANG : C++11
ID : weng_xo2
PROG : cowxor
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

const int MaxN = 100010;

int N, M, ans, l, r;

struct Node {
	int idx;
	Node *s[2];
}nil[MaxN * 10], *root = nil, *tot = nil;

void insert(int sum, int idx) {
	Node *cur = root;
	for(int j = 20; j >= 0; --j) {
		if(!cur->s[sum >> j & 1]) {
			cur->s[sum >> j & 1] = ++tot;
		}
		cur = cur->s[sum >> j & 1];
	}
	cur->idx = idx;
}

int main(){
	freopen("cowxor.in", "r", stdin);
	freopen("cowxor.out", "w", stdout);
	scanf("%d", &N);
	insert(0, 0);
	ans = 0;
	l = r = 1;
	for(int i = 1, sum = 0, x, res = 0; i <= N; ++i, res = 0) {
		scanf("%d", &x);
		sum ^= x;
		Node *cur = root;
		for(int j = 20; j >= 0; --j) {
			if(cur->s[~sum >> j & 1]) {
				cur = cur->s[~sum >> j & 1];
				res |= 1 << j;
			} else {
				cur = cur->s[sum >> j & 1];
			}
		}
		insert(sum, i);
		if(res > ans) {
			l = cur->idx + 1;
			r = i;
			ans = res;
		}
	}
	//printf("%d\n", (int) (tot - nil));
	printf("%d %d %d\n", ans, l, r);
	return 0;
}

