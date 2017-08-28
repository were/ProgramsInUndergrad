/*
PROG : checker
ID : weng_xo
LANG : C++11
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

int N, a[20], ans;
vector<vi> res;
vi cur;

void dfs(int dep, int x, int y, int col) {
	if(dep < N) {
		int mask = x & y & col & ((1 << N) - 1);
		//printf("%d, %d, %d, %d, %d\n", dep, x, y, col, mask);
		while(mask) {
			int lowbit = mask & -mask;
			if(res.size() < 3) {
				cur.push_back(lowbit);
			}
			dfs(dep + 1, (x ^ lowbit) << 1 | 1, (y ^ lowbit) >> 1 | (1 << (N - 1)), col ^ lowbit);
			if(res.size() < 3) {
				cur.pop_back();
			}
			mask -= lowbit;
		}
	} else {
		if(res.size() < 3) {
			vi tmp;
			for(size_t i = 0; i < cur.size(); ++i) {
				for(int j = 0; j < N; ++j) {
					if(cur[i] & (1 << j)) {
						tmp.push_back(j + 1);
						break;
					}
				}
			}
			res.push_back(tmp);
		}
		++ans;
	}
}

int main() {
	freopen("checker.in", "r", stdin);
	freopen("checker.out", "w", stdout);
	scanf("%d", &N);
	dfs(0, (1 << N) - 1, (1 << N) - 1, (1 << N) - 1);
	for(size_t i = 0; i < res.size(); ++i) {
		for(size_t j = 0; j < res[i].size(); ++j) {
			printf(j == res[i].size() - 1 ? "%d\n" : "%d ", res[i][j]);
		}
	}
	printf("%d\n", ans);
	return 0;
}

