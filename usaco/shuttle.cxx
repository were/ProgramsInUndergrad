/*
ID : weng_xo2
LANG : C++11
PROG : shuttle
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

int N;
string s, des;
map<string, vector<int> > dis;
queue<pair<string, int> > q;

void push(string s, int x, vi &d) {
	if(dis[s].size() == 0) {
		vi v = d;
		v.push_back(x);
		dis[s] = v;
		q.push(make_pair(s, x));
		if(s == des) {
			for(unsigned i = 1; i < dis[s].size(); ++i) {
				printf("%d", dis[s][i] + 1);
				if(i % 20 == 0 || i + 1 == dis[s].size()) {
					puts("");
				} else {
					putchar(' ');
				}
			}
			//if((dis[s].size() - 1) % 20) {
			//	puts("");
			//}
			exit(0);
		}
	}
}

int main(){
	freopen("shuttle.in", "r", stdin);
	freopen("shuttle.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		s += 'W';
		des += 'B';
	}
	s += ' ';
	des += ' ';
	for(int i = 0; i < N; ++i) {
		s += 'B';
		des += 'W';
	}
	q.push(make_pair(s, N));
	dis[s].push_back(0);
	while(!q.empty()) {
		s = q.front().X;
		int x = q.front().Y;
		vi &d = dis[s];
		q.pop();
		//cout << s << endl;
		bool flag = false;
		for(int p = x - 1; p >= 0; --p) {
			if(p - 2 >= 0 && s[p] == 'B' && s[p - 1] == 'B' && s[p - 2] == 'W') {
				flag = true;
			}
		}
		for(int p = x + 1; p < (int)s.size(); ++p) {
			if(p + 2 < (int)s.size() && s[p] == 'W' && s[p + 1] == 'W' && s[p + 2] == 'B') {
				flag = true;
			}
		}
		if(flag) {
			continue;
		}
		for(int i = -2; i <= 2; ++i) {
			if(x + i >= 0 && x + i < (int)s.size()) {
				if(i > 0 && s[x + i] == 'W') continue;
				if(i < 0 && s[x + i] == 'B') continue;
				swap(s[x], s[x + i]);
				push(s, x + i, d);
				swap(s[x], s[x + i]);
			}
		}
	}
	return 0;
}

