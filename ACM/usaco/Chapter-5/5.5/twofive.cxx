/*
LANG : C++11
ID : weng_xo2
PROG : twofive
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

long long rank;
char maxRow[6], maxCol[6];
bool hsh[256];
int f[6][6][6][6][6], a[5];

char op[2];

void init(int a, char b) {
	maxRow[a / 5] = b;
	maxCol[a % 5] = b;
	hsh[(int) b] = true;
	memset(f, 0, sizeof f);
	f[5][5][5][5][5] = 1;
}

int dp(int a, int b, int c, int d, int e, char ch) {
	//printf("%d %d %d %d %d %c\n", a, b, c, d, e, ch);
	int &ret = f[a][b][c][d][e];
	if(ret) {
		return ret;
	}
	if(hsh[(int) ch]) {
		return ret = dp(a, b, c, d, e, ch + 1);
	}
	ret = 0;
	if(a < 5 && ch > maxCol[0] && ch > maxRow[a]) {
		ret += dp(a + 1, b, c, d, e, ch + 1);
	}
	if(b < a && ch > maxCol[1] && ch > maxRow[b]) {
		ret += dp(a, b + 1, c, d, e, ch + 1);
	}
	if(c < b && ch > maxCol[2] && ch > maxRow[c]) {
		ret += dp(a, b, c + 1, d, e, ch + 1);
	}
	if(d < c && ch > maxCol[3] && ch > maxRow[d]) {
		ret += dp(a, b, c, d + 1, e, ch + 1);
	}
	if(e < d && ch > maxCol[4] && ch > maxRow[e]) {
		ret += dp(a, b, c, d, e + 1, ch + 1);
	}
	//printf("%d, %d, %d, %d, %d: %d\n", a, b, c, d, e, ret);
	return ret;
}

int main(){
	freopen("twofive.in", "r", stdin);
	freopen("twofive.out", "w", stdout);
	scanf("%s", op);
	if(*op == 'N') {
		int N;
		scanf("%d", &N);
		memset(maxRow, '@', sizeof maxRow);
		memset(maxCol, '@', sizeof maxCol);
		for(int i = 0; i < 25; ++i) {
			++a[i % 5];
			for(char j = 'A'; j < 'Z'; ++j) {
				if(!hsh[(int) j] && j > maxRow[i / 5] && j > maxCol[i % 5]) {
					init(i, j);
					int delta = dp(a[0], a[1], a[2], a[3], a[4], 'A');
					//printf("%d\n\n", delta);
					if(N > delta) {
						N -= delta;
						hsh[(int) j] = false;
					} else {
						putchar(j);
						break;
					}
				}
			}
		}
		puts("");
	} else {
		char s[30];
		int ans = 1;
		scanf("%s", s);
		for(int i = 0; i < 25; ++i) {
			++a[i % 5];
			for(int j = 'A'; j < s[i]; ++j) {
				if(!hsh[(int) j] && j > maxRow[i / 5] && j > maxCol[i % 5]) {
					//printf("%c\n", j);
					init(i, j);
					int delta = dp(a[0], a[1], a[2], a[3], a[4], 'A');
					ans += delta;
					hsh[(int) j] = false;
				}
			}
			hsh[(int) s[i]] = true;
			maxRow[i / 5] = s[i];
			maxCol[i % 5] = s[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}

