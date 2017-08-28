/*
LANG : C++11
PROG : hamming
ID : weng_xo2
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

int N, B, D;
vi ans;

int cnt(int x) {
	int ret = 0;
	while(x) {
		x -= x & -x;
		++ret;
	}
	return ret;
}

bool check(int x) {
	for(size_t i = 0; i < ans.size(); ++i) {
		if(cnt(ans[i] ^ x) < D) {
			return false;
		}
	}
	return true;
}

void dfs(int x) {
	if((int) ans.size() < N) {
		for(int i = x; i < (1 << B); ++i) {
			if(check(i)) {
				ans.push_back(i);
				dfs(i + 1);
				ans.pop_back();
			}
		}
	} else {
		for(int i = 0, j = 0; i < N; ++i) {
			printf(++j == 10 || i + 1 == N ? "%d\n" : "%d ", ans[i]);
			j %= 10;
		}
		exit(0);
	}
}

int main(){
	freopen("hamming.in", "r", stdin);
	freopen("hamming.out", "w", stdout);
	cin >> N >> B >> D;
	dfs(0);
}

