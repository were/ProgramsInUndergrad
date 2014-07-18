/*
ID : weng_xo2
LANG : C++11
PROG : picture
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

const int PROTECT = 15000;

int N, ans;

struct Data {
	int h, l, r;
	int side;
};

vector<Data> ver, hor;

bool cmp(Data a, Data b) {
	return a.h != b.h ? a.h < b.h : a.side < b.side;
}

void work(vector<Data> &a) {
	static int lv[30000];
	memset(lv, 0, sizeof lv);
	for(size_t i = 0; i < a.size(); ++i) {
		if(!a[i].side) {
			for(int j = a[i].l; j < a[i].r; ++j) {
				if(++lv[j + PROTECT] == 1) {
					++ans;
				}
			}
		} else {
			for(int j = a[i].l; j < a[i].r; ++j) {
				if(--lv[j + PROTECT] == 0) {
					++ans;
				}
			}
		}
	}
}

int main(){
	freopen("picture.in", "r", stdin);
	freopen("picture.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 0; i < N; ++i) {
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		hor.push_back(Data{b, a, c, 0});
		hor.push_back(Data{d, a, c, 1});
		ver.push_back(Data{a, b, d, 0});
		ver.push_back(Data{c, b, d, 1});
	}
	sort(ver.begin(), ver.end(), cmp);
	work(ver);
	sort(hor.begin(), hor.end(), cmp);
	work(hor);
	printf("%d\n", ans);
	return 0;
}

