/*
LANG : C++11
PROG : nocows
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

const int Mod = 9901;

int N, K, f[222][222], g[222][222];

int main(){
	freopen("nocows.in", "r", stdin);
	freopen("nocows.out", "w", stdout);
	scanf("%d%d", &N, &K);
	f[1][1] = 1;
	for(int i = 3;i <= N; i += 2) {
		for(int j = 1; j <= i - 2; j += 2) {
			for(int a = 1; a <= (j + 1) / 2; ++a) {
				for(int b = 1; b <= (i - j) / 2; ++b) {
					(f[i][max(a, b) + 1] += f[j][a] * f[i - j - 1][b]) %= Mod;
				}
			}
		}
	}
	printf("%d\n", f[N][K]);
	return 0;
}

