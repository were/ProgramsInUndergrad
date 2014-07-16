/*
ID : weng_xo2
PROG : fracdec
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

int a, b, pos[100000], res[100000];
char s[1000000], *tl;



int main(){
	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);
	cin >> a >> b;
	sprintf(tl = s, "%d", a / b);
	while(*tl) {
		++tl;
	}
	if(a % b) {
		*tl++ = '.';
		a %= b;
		while(!pos[a]) {
			pos[a] = ++res[0];
			res[res[0]] = a * 10 / b;
			a = a * 10 % b; 
		}
		for(int i = 1; i < pos[a]; ++i) {
			*tl++ = '0' + res[i];
		}
		if(a) {
			*tl++ = '(';
			for(int i = pos[a]; i <= res[0]; ++i) {
				*tl++ = '0' + res[i];
			}
			*tl++ = ')';
		}
	} else {
		*tl++ = '.';
		*tl++ = '0';
	}
	//puts(s);
	for(int i = 0, j = 0; s[i]; ++i) {
		printf(++j == 76 || !s[i + 1] ? "%c\n" : "%c", s[i]);
		j %= 76;
	}
}

