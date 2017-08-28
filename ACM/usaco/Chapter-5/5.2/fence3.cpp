/*
PROG : fence3
ID : weng_xo2
LANG : C++
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

const double EPS = 1e-10;

struct Cor {
	double x, y;
	Cor(double x, double y) : x(x), y(y) {}
	Cor() {}

	Cor sub(Cor a) {
		return Cor(x - a.x, y - a.y);
	}
	
	Cor mul(double t) {
		return Cor(x * t, y * t);
	}

	Cor add(Cor a) {
		return Cor(x + a.x, y + a.y);
	}

	double dot(Cor a) {
		return x * a.x + y * a.y;
	}

	double det(Cor a) {
		return x * a.y - y * a.x;
	}

	double abs2() {
		return x * x + y * y;
	}

	double abs() {
		return sqrt(x * x + y * y);
	}
}a[155], b[155], c[155];

Cor proj(Cor p1, Cor p2, Cor q) {
	return p1.add(p2.sub(p1).mul(p2.sub(p1).dot(q.sub(p1)) / p2.sub(p1).abs2()));
}

bool onSeg(Cor p1, Cor p2, Cor q) {
	return fabs(q.sub(p1).abs() + q.sub(p2).abs() - p1.sub(p2).abs()) < EPS;
}

int N, idx;
double res[155];

double calc(Cor O) {
	double ret = 0.;
	rep(i, 1, N) {
		Cor p = proj(a[i], b[i], O);
		if(onSeg(a[i], b[i], p)) {
			ret += p.sub(O).abs();
		} else {
			ret += min(a[i].sub(O).abs(), b[i].sub(O).abs());
		}
	}
	return ret;
}

int main() {
	freopen("fence3.in", "r", stdin);
	freopen("fence3.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		scanf("%lf%lf%lf%lf", &a[i].x, &a[i].y, &b[i].x, &b[i].y);
	}
	rep(i, 1, 100) {
		c[i] = Cor(rand() % 100, rand() % 100);
		res[i] = calc(c[i]);
	}
	for(double T = 100.; T > 1e-3; T *= .8) {
		rep(i, 1, 100) {
			double theta = rand();
			double dx = T * cos(theta);
			double dy = T * sin(theta);
			double tmp = calc(c[i].add(Cor(dx, dy)));
			if(tmp < res[i]) {
				res[i] = tmp;
				c[i] = c[i].add(Cor(dx, dy));
			}
		}
	}
	idx = 1;
	rep(i, 2, 100) {
		if(res[i] < res[idx]) {
			idx = i;
		}
	}
	printf("%.1f %.1f %.1f\n", c[idx].x, c[idx].y, res[idx]);
	return 0;
}

