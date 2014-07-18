/*
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

const ll Mod = 1000000007ll;

int N, ans;
ll c[1111][1111], a[1111];

int main(){
	scanf("%d", &N);
	if(N == 0 || N == 1) {
		puts("1");
		return 0;
	}
	c[0][0] = 1;
	rep(i, 1, N) {
		c[i][0] = c[i][i] = 1;
		rep(j, 1, i - 1) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
			//printf("%d, %d: %lld\n", i, j, c[i][j]);
		}
	}
	a[0] = 1;
	rep(i, 1, N) {
		int h = (log(i + 1) / log(2.)) - 1;
		int b = (1 << h) - 1;
		int r = i - 1 - 2 * b;
		int r1 = r - (r / (1 << h)) * (r - (1 << h));
		int r2 = r - r1;
		a[i] = c[i - 1][b + r1] * a[b + r1] % Mod * a[b + r2] % Mod;
	}
	printf("%lld\n", (a[N] * 2ll) % Mod);
//	rep(i, 1, N) {
//		a[i] = i;
//	}
//	dfs(1);
}

