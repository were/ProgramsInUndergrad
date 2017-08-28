/*
PROG : ariprog
LANG : C++11
ID : weng_xo2
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

bool hsh[1 << 17];
vi num;
vector<pii> ans;
int N, M;

void check(int a, int b) {
	//printf("%d %d: ", a, b);
	for(int i = 0; i < N; ++i) {
		if(a + b * i > M * M * 2 || !hsh[a + b * i]) {
			//printf("failed @%d\n", a + b * i);
			return;
		}
	}
	//puts("ok!");
	ans.push_back(pii(b, a));
}

int main() {
	freopen("ariprog.in", "r", stdin);
	freopen("ariprog.out", "w", stdout);
	cin >> N >> M;
	rep(i, 0, M) {
		rep(j, i, M) {
			if(!hsh[i * i + j * j]) {
				num.push_back(i * i + j * j);
				hsh[i * i + j * j] = true;
				//printf("%d\n", num.back());
			}
		}
	}
	sort(num.begin(), num.end());
	for(unsigned i = 0; i < num.size(); ++i) {
		//printf("%d\n", num[i]);
		for(unsigned j = i + 1; j < num.size() && (N - 1) * (num[j] - num[i]) + num[i] <= M * M * 2; ++j) {
			check(num[i], num[j] - num[i]);
		}
	}
	if(ans.size()) {
		sort(ans.begin(), ans.end());
		for(auto &cur: ans) {
			cout << cur.second << " " << cur.first << endl;
		}
	} else {
		cout << "NONE" << endl;
	}
	return 0;
}

