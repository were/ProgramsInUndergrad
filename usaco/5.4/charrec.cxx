/*
ID : weng_xo2
LANG : C++11
PROG : charrec
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
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

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

FILE *input = fopen("font.in", "r");

const char s[] = " abcdefghijklmnopqrstuvwxyz";

const int Inf = (int) 1e8;

int N, font[30][30], a[1300], dif[1300][3], opt[1300];
char ch[1300][3], buffer[30];
pii pre[1300];

int cntBit(int x) {
	int ret = 0;
	while(x) {
		x -= x & -x;
		++ret;
	}
	return ret;
}

void printIt(int x) {
	for(int i = 19; i >= 0; --i) {
		printf("%d", x >> i & 1);
	}
}

int diff(vi &a, vi &b) {
	int ret = 0;
	for(size_t i = 0; i < a.size(); ++i) {
		ret += cntBit(a[i] ^ b[i]);
		//printIt(a[i]); putchar(' '); printIt(b[i]); puts("");
	}
	return ret;
}

void printAns(int x) {
	if(x) {
		printAns(pre[x].X);
		putchar(ch[pre[x].X][pre[x].Y]);
	}
}

int main() {
	fscanf(input, "%d", &N);
	for(int i = 0; i < N; ++i) {
		fscanf(input, "%s", buffer);
		font[i / 20][i % 20] = (int) bitset<20>(buffer).to_ulong();
	}
	freopen("charrec.in", "r", stdin);
	freopen("charrec.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		scanf("%s", buffer);
		a[i] = (int) bitset<20>(buffer).to_ulong();
	}
	for(int i = 0; i < N; ++i) {
		//printf("%d\n", i);
		opt[i] = dif[i][0] = dif[i][1] = dif[i][2] = Inf;
		if(i + 19 <= N) {
			vi a1(a + i, a + 19 + i);
			for(int j = 0; j < 27; ++j) {
				for(int skip = 0; skip < 20; ++skip) {
					vi a2(font[j], font[j] + 20);
					a2.erase(a2.begin() + skip);
					int tmp = diff(a1, a2);// - cntBit(a1[skip] ^ a2[skip]);
					if(dif[i][0] > tmp) {
						dif[i][0] = tmp;
						ch[i][0] = s[j];
					}
					//printf("19 %d %c %d\n", i, s[j], diff(a1, a2));
				}
			}
		}
		if(i + 20 <= N) {
			vi a1(a + i, a + 20 + i);
			for(int j = 0; j < 27; ++j) {
				vi a2(font[j], font[j] + 20);
				//printf("20 %d %c %d\n", i, s[j], diff(a1, a2));
				int tmp = diff(a1, a2);
				if(dif[i][1] > tmp) {
					dif[i][1] = tmp;
					ch[i][1] = s[j];
				}
			}
		}
		if(i + 21 <= N) {
			for(int j = 0; j < 27; ++j) {
				vi a2(font[j], font[j] + 20);
				for(int skip = 0; skip < 21; ++skip) {
					vi a1(a + i, a + 21 + i);
					a1.erase(a1.begin() + skip);
					int tmp = diff(a1, a2);
					if(dif[i][2] > tmp) {
						dif[i][2] = tmp;
						ch[i][2] = s[j];
					}
				}
				//printf("21 %d %c %d\n", i, s[j], diff(a1, a2));
			}
		}
	}
	opt[N] = Inf;
	opt[0] = 0;
/*
	for(int k = 0; k < 3; ++k) {
		for(int i = 0; i < N; ++i) {
			if(dif[i][k] != Inf) {
				putchar(ch[i][k]);
			}
		}
		puts("");
	}
*/
	for(int i = 0; i < N; ++i) {
		if(dif[i][0] != Inf && opt[i + 19] > opt[i] + dif[i][0]) {
			pre[i + 19] = pii(i, 0);
			opt[i + 19] = opt[i] + dif[i][0];
		}
		if(dif[i][1] != Inf && opt[i + 20] > opt[i] + dif[i][1]) {
			pre[i + 20] = pii(i, 1);
			opt[i + 20] = opt[i] + dif[i][1];
		}
		if(dif[i][2] != Inf && opt[i + 21] > opt[i] + dif[i][2]) {
			pre[i + 21] = pii(i, 2);
			opt[i + 21] = opt[i] + dif[i][2];
		}
		//printf("%d: %d\n", i, opt[i]);
	}
	printAns(N);
	puts("");
	return 0;
}

