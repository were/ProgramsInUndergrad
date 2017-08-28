/*
LANG : C++11
ID : weng_xo2
PROG : race3
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

int N, hsh[55], flag;
int dfn[55], low[55], idx, cnt[55];
vi g[55], ans, res;

bool dfs(int x) {
	hsh[x] = flag;
	if(x == N) {
		return true;
	}
	for(auto &v: g[x]) {
		if(hsh[v] != flag) {
			if(dfs(v)) {
				return true;
			}
		}
	}
	return false;
}

void dfs(int x, int ban) {
	hsh[x] = flag;
	++cnt[x];
	for(auto &v: g[x]) {
		if(hsh[v] != flag && v != ban) {
			dfs(v, ban);
		}
	}
}

int main(){
	freopen("race3.in", "r", stdin);
	freopen("race3.out", "w", stdout);
	for(N = 0; ; ++N) {
		int x;
		for(scanf("%d", &x); x >= 0; g[N].push_back(x), scanf("%d", &x));
			if(x == -1) {
				break;
			}
		}
		--N;
		for(int i = 1; i < N; ++i) {
			hsh[i] = ++flag;
			if(!dfs(0)) {
				ans.push_back(i);
			}
		}
		if(ans.size()) {
			printf("%d ", (int)ans.size());
			for(unsigned i = 0; i < ans.size(); ++i) {
				printf(i + 1 < ans.size() ? "%d " : "%d\n", ans[i]);
//		printf("%d\n", ans[i]);
				memset(cnt, 0, sizeof cnt);
				++flag;
				dfs(0, ans[i]);
				++flag;
				dfs(ans[i], ans[i]);
				bool flag = true;
				for(int j = 0; j <= N; ++j) {
					if(cnt[j] != 1) {
//				printf("failed @%d\n", j);
						flag = false;
					}
				}
				if(flag) {
					res.push_back(ans[i]);
				}
			}
		} else {
			puts("0");
		}
		if(res.size()) {
			printf("%d ", (int)res.size());
			for(unsigned i = 0; i < res.size(); ++i) {
				printf(i + 1 < res.size() ? "%d " : "%d\n", res[i]);
			}
		} else {
			puts("0");
		}
		return 0;
	}

