/*
PROG : ttwo
LANG : C++11
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

const pii dir[4]{pii(-1, 0), pii(0, 1), pii(1, 0), pii(0, -1)};

pii operator+ (pii a, pii b) {
	return pii(a.X + b.X, a.Y + b.Y);
}

char s[20][20];
int df = 0, dc = 0;
pii F, C;

bool inRange(pii a) {
	return a.X >= 0 && a.X < 10 && a.Y >= 0 && a.Y < 10 && s[a.X][a.Y] != '*';
}

int main(){
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	for(int i = 0; i < 10; ++i) {
		scanf("%s", s[i]);
		for(int j = 0; j < 10; ++j) {
			if(s[i][j] == 'C') {
				C = pii(i, j);
			}
			if(s[i][j] == 'F') {
				F = pii(i, j);
			}
		}
	}
	for(int i = 0; i < 1000000; ++i) {
		if(inRange(F + dir[df])) {
			F = F + dir[df];
		} else {
			(++df) %= 4;
		}
		if(inRange(C + dir[dc])) {
			C = C + dir[dc];
		} else {
			(++dc) %= 4;
		}
		/*
		printf("%d\n", i);
		rep(i, 0, 9) {
			rep(j, 0, 9) {
				if(s[i][j] == '*') {
					putchar('*');
				} else {
					if(pii(i, j) == F) {
						putchar('F');
					} else if(pii(i, j) == C) {
						putchar('C');
					} else {
						putchar('.');
					}
				}
			}
			puts("");
		}
		*/
		if(F == C) {
			printf("%d\n", i + 1);
			return 0;
		}
	}
	puts("0");
	return 0;
}

