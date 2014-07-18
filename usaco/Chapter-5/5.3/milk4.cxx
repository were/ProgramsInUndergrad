/*
 ID : weng_xo2
 PROG : milk4
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

int Q, N, a[101], choice, flag;
bool hsh[101][20001];
vi ans;

void dfs(int dep, int done) {
	if(done + (N - dep + 1) < choice) {
		return;
	}
	/*
	 printf("%d %d\n", dep, done);
	 printf("%d", (int)ans.size());
	 for(unsigned i = 0; i < ans.size(); ++i) {
		printf(" %d", ans[i]);
	 }puts("");
	 */
	
	if(hsh[dep - 1][Q]) {
		printf("%d", (int)ans.size());
		for(unsigned i = 0; i < ans.size(); ++i) {
			printf(" %d", ans[i]);
		}
		puts("");
		exit(0);
	}
	if(done < choice && dep <= N) {
		ans.push_back(a[dep]);
		rep(i, 0, Q) hsh[dep][i] = hsh[dep - 1][i];
		rep(i, a[dep], Q) hsh[dep][i] |= hsh[dep][i - a[dep]];
		//rep(i, 1, Q) if(hsh[dep][i]) printf("%d\n", i);
		dfs(dep + 1, done + 1);
		rep(i, 0, Q) hsh[dep][i] = hsh[dep - 1][i];
		ans.pop_back();
		dfs(dep + 1, done);
	}
}

int main(){
	freopen("milk4.in", "r", stdin);
	freopen("milk4.out", "w", stdout);
	scanf("%d%d", &Q, &N);
	rep(i, 1, N) {
		scanf("%d", a + i);
	}
	sort(a + 1, a + N + 1);
	hsh[0][0] = true;
	rep(i, 1, N) {
		choice = i;
		dfs(1, 0);
	}
	return 0;
}
