/*
LANG : C++11
PROG : prefix
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

char s[222][22], S[222222], *hd = S;
int n, len[222], N, ans = -1;
bool f[222222];

int main(){
	freopen("prefix.in", "r", stdin);
	freopen("prefix.out", "w", stdout);
	while(scanf("%s", s[++n]), strcmp(s[n], "."));
	--n;
	rep(i, 1, n) {
		len[i] = (int) strlen(s[i]);
	}
	while(~scanf("%s", hd)) {
		while(*hd)
			++hd;
	}
	N = strlen(S);
	//cerr << "done\n";
	for(int i = 0; i < N; ++i) {
		for(int j = 1; j <= n; ++j) {
			bool flag = true;
			for(int k = 0; k < len[j]; ++k) {
				if(i - len[j] + 1 + k < 0 || S[i - len[j] + 1 + k] != s[j][k]) {
					flag = false;
					break;
				}
			}
			if(flag) {
				//cerr << s[j] << endl;
				//cerr << i << " " << endl;
				if(i - len[j] >= 0) {
					f[i] |= f[i - len[j]];
				} else {
					f[i] = true;
				}
			}
			if(f[i]) {
				break;
			}
		}
		if(f[i]) {
			//printf("true %d\n", i);
			ans = i;
		}
	}
	printf("%d\n", ans + 1);
	return 0;
}

