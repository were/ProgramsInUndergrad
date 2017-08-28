/*
ID : weng_xo2
LANG : C++11
PROG : sort3
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

const int MaxN = 1111;

int N, ans, a[MaxN], cnt[4];

int target(int x) {
	if(x >= 1 && x <= cnt[1]) {
		return 1;
	}
	if(x >= cnt[1] + 1 && x <= cnt[1] + cnt[2]) {
		return 2;
	}
	return 3;
}

bool inRange(int x) {
	return a[x] == target(x);
}

bool outOfRange(int tar, int x) {
	tar = target(tar);
	if(tar == 1) {
		return x < 1 || x > cnt[1];
	}
	if(tar == 2) {
		return x <= cnt[1] || x > cnt[1] + cnt[2];
	}
	return x <= cnt[1] + cnt[2] || x > N;
}

int getNxt(int x) {
	rep(i, 1, N) {
		if(outOfRange(x, i) && a[i] == target(x) && a[x] == target(i)) {
			return i;
		}
	}
	rep(i, x + 1, N) {
		if(outOfRange(x, i) && a[i] == target(x)) {
			return i;
		}
	}
	return -1;
}

void work(int x) {
	//printf("%d %d %d\n", x, target(x), a[x]);
	if(!inRange(x)) {
		int nxt = getNxt(x);
		++ans;
		swap(a[x], a[nxt]);
		work(nxt);
	}
}

int main(){
	freopen("sort3.in", "r", stdin);
	freopen("sort3.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		scanf("%d", a + i);
		++cnt[a[i]];
	}
	rep(i, 1, N) {
		work(i);
	}
	printf("%d\n", ans);
	return 0;
}

