/*
ID : weng_xo2
PROG : rectbarn
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

const int MaxN = 3333;

int N, M, P, col[MaxN], q[MaxN], l[MaxN], r[MaxN], ans;
bool a[MaxN][MaxN];

int main() {
	freopen("rectbarn.in", "r", stdin);
	freopen("rectbarn.out", "w", stdout);
	scanf("%d%d%d", &N, &M, &P);
	while(P--) {
		int x, y;
		scanf("%d%d", &x, &y);
		a[x][y] = true;
	}
	rep(i, 1, N) {
		rep(j, 1, M) {
			if(!a[i][j]){
				++col[j];
			} else {
				col[j] = 0;
			}
		}
		int f = 1, t = 0;
		rep(j, 1, M) {
			while(f <= t && col[q[t]] >= col[j]) {
				--t;
			}
			if(f <= t) {
				l[j] = q[t] + 1;
			} else {
				l[j] = 1;
			}
			q[++t] = j;
		}
		f = 1, t = 0;
		per(j, M, 1) {
			while(f <= t && col[q[t]] >= col[j]) {
				--t;
			}
			if(f <= t) {
				r[j] = q[t] - 1;
			} else {
				r[j] = M;
			}
			q[++t] = j;
		}
		rep(j, 1, M) {
			ans = max(ans, col[j] * (r[j] - l[j] + 1));
		}
	}
	printf("%d\n", ans);
	return 0;
}

