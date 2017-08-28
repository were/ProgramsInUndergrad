/*
ID : weng_xo2
LANG : C++11
PROG : packrec
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

const int Inf = ~0u >> 1;

int a[4], b[4], ans;
set<pii> res;

void update(int a, int b, int idx) {
	if(a > b) {
		swap(a, b);
	}
	//printf("%d %d\n", a, b);
	if(a * b < ans) {
		//printf("%d %d %d\n", a, b, idx);
		ans = a * b;
		res.clear();
	}
	if(a * b == ans) {
		res.insert(pii(a, b));
	}
}

void dfsAB(int x) {
	if(x < 4) {
		swap(a[x], b[x]);
		dfsAB(x + 1);
		swap(a[x], b[x]);
		dfsAB(x + 1);
	} else {
		int A, B;
		//1
		A = a[0] + a[1] + a[2] + a[3];
		B = max(b[0], max(b[1], max(b[2], b[3])));
		update(A, B, 1);
		//2
		A = max(a[0] + a[1] + a[2], a[3]);
		B = max(b[0], max(b[1], b[2])) + b[3];
		update(A, B, 2);
		//3
		A = max(a[0] + a[1], a[2]) + a[3];
		B = max(max(b[0], b[1]) + b[2], b[3]);
		update(A, B, 3);
		//4, 5
		A = max(a[0], a[1]) + a[2] + a[3];
		B = max(b[0] + b[1], max(b[2], b[3]));
		update(A, B, 4);
		//6
		A = a[0] + a[1];
		B = max(b[0] + b[2], b[1] + b[3]);
		if(b[0] < b[1]) {
			A = max(A, a[2] + a[1]);
		}
		if(b[0] + b[2] > b[1]) {
			A = max(A, a[2] + a[3]);
		}
		if(b[1] < b[0]) {
			A = max(A, a[0] + a[3]);
		}
		A = max(A, max(a[2], a[3]));
		update(A, B, 6);
		//T_T
		A = max(max(a[0], a[1]) + a[2], a[3]);
		B = max(b[0] + b[1], b[2]) + b[3];
		update(A, B, 7);
	}
}

void dfsPerm(int x) {
	if(x < 4) {
		for(int i = x; i < 4; ++i) {
			swap(a[i], a[x]);
			swap(b[i], b[x]);
			dfsPerm(x + 1);
			swap(a[i], a[x]);
			swap(b[i], b[x]);
		}
	} else {
		dfsAB(0);
	}
}

int main(){
	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);
	ans = Inf;
	for(int i = 0; i < 4; ++i) {
		scanf("%d%d", a + i, b + i);
	}
	dfsPerm(0);
	printf("%d\n", ans);
	for(auto &cur: res) {
		printf("%d %d\n", cur.X, cur.Y);
	}
	return 0;
}

