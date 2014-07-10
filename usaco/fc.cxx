/*
ID : weng_xo2
LANG : C++11
PROG : fc
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

const double EPS = 1e-8;

int N, n, bottom;
double ans;

struct Cor {
	double x, y;
	Cor(double x, double y) : x(x), y(y) {}
	Cor() {}
}a[10001], hull[10001];

bool cmp(Cor a, Cor b) {
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}

double sqr(double x) {
	return x * x;
}

double dis(Cor a, Cor b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double det(Cor a, Cor b) {
	return a.x * b.y - a.y * b.x;
}

Cor operator- (Cor a, Cor b) {
	return Cor(a.x - b.x, a.y - b.y);
}

int main() {
	freopen("fc.in", "r", stdin);
	freopen("fc.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) scanf("%lf%lf", &a[i].x, &a[i].y);
	sort(a + 1, a + 1 + N, cmp);
	rep(i, 1, N) {
		while(n >= 2 && det(hull[n] - hull[n - 1], a[i] - hull[n - 1]) < EPS) {
			--n;
		}
		hull[++n] = a[i];
	}
	bottom = n;
	per(i, N - 1, 1) {
		while(n > bottom && det(hull[n] - hull[n - 1], a[i] - hull[n - 1]) < EPS) {
			--n;
		}
		hull[++n] = a[i];
	}
	rep(i, 2, n) {
		ans += dis(hull[i - 1], hull[i]);
	}
	printf("%.2f\n", ans);
	return 0;
}

