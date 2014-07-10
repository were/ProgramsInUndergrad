/*
ID : weng_xo2
LANG : C++11
PROG : starry
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
#define rep(i,f,t) for(int i(f);i<=(int)(t);++i)
#define per(i,t,f) for(int i(t);i>=(int)(f);--i)

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

int N, M;
char s[111][111];
bool hsh[111][111];
vector< pair<double, double> > stars;

struct Data {
	int x, y;
	Data(int x = 0, int y = 0) : x(x), y(y) {}
};

bool inRange(int x, int y) {
	return x >= 1 && x <= N && y >= 1 && y <= M;
}

double sqr(double x) {
	return x * x;
}

double dis(Data a, Data b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

void bfs(int x, int y) {
	static int f, t;
	static Data q[11111];
	for(f = t = 0, q[t++] = Data(x, y), hsh[x][y] = true; f < t; ++f) {
		rep(dx, -1, 1) rep(dy, -1, 1) {
			x = q[f].x + dx;
			y = q[f].y + dy;
			//printf("%d %d %c\n", x, y, s[x][y]);
			if(inRange(x, y) && !hsh[x][y] && s[x][y] == '1') {
				hsh[x][y] = true;
				q[t++] = Data(x, y);
			}
		}
	}
	//puts("");
	double mean = 0., var = 0.;
	rep(i, 0, t - 1) rep(j, i + 1, t - 1) {	
		mean += dis(q[i], q[j]);
	}
	if(t > 1) {
		mean /= t * (t - 1) / 2;
	}
	rep(i, 0, t - 1) rep(j, i + 1, t - 1) {
		var += sqr(mean - dis(q[i], q[j]));
	}
	//printf("%f\n", var);
	rep(i, 0, stars.size() - 1) {
		if(fabs(stars[i].first - var) < EPS && fabs(stars[i].second - mean) < EPS) {
			rep(j, 0, t - 1) {
				//printf("%d %d\n", q[j].x, q[j].y);
				s[q[j].x][q[j].y] = 'a' + i;
			}
			//puts("");
			return;
		}
	}
	rep(j, 0, t - 1) {
		//printf("%d %d\n", q[j].x, q[j].y);
		s[q[j].x][q[j].y] = 'a' + stars.size();
	}
	//puts("");
	stars.push_back(make_pair(var, mean));
}

int main(){
	freopen("starry.in", "r", stdin);
	freopen("starry.out", "w", stdout);
	scanf("%d%d", &M, &N);
	rep(i, 1, N) {
		scanf("%s", s[i] + 1);
	}
	rep(i, 1, N) rep(j, 1, M) if(!hsh[i][j] && s[i][j] == '1') {
		bfs(i, j);
	}
	rep(i, 1, N) {
		puts(s[i] + 1);
	}
	return 0;
}
