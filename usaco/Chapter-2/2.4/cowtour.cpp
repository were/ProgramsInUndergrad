/*
ID : weng_xo2
LANG : C++11
PROG : cowtour
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
	Cor sub(Cor b) {
		return Cor(x - b.x, y - b.y);
	}
	double abs() {
		return sqrt(x * x + y * y);
	}
}cor[155];

double dis[155][155], ans = 1e9, d[155], far[155];
char s[155][155];
int belong[155];
int N;

int main(){
	freopen("cowtour.in", "r", stdin);
	freopen("cowtour.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N) {
		scanf("%lf%lf", &cor[i].x, &cor[i].y);
	}
	rep(i, 1, N) {
		scanf("%s", s[i] + 1);
		rep(j, 1, N) {
			if(s[i][j] == '0') {
				dis[i][j] = 1e9;
			} else {
				dis[i][j] = cor[i].sub(cor[j]).abs();
				//printf("%d, %d: %f\n", i, j, dis[i][j]);
			}
		}
		dis[i][i] = 0.;
	}
	rep(k, 1, N) rep(i, 1, N) rep(j, 1, N) {
		dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
	}
	rep(i, 1, N) {
		if(!belong[i]) {
			belong[i] = i;
			rep(j, i + 1, N) {
				if(fabs(dis[i][j] - 1e9) > EPS) {
					belong[j] = i;
				}
			}
			rep(j, i, N) {
				rep(k, j + 1, N) {
					if(belong[j] == i && belong[k] == i) {
						d[i] = max(d[i], dis[j][k]);
					}
				}
			}
		}
		rep(j, 1, N) {
			//printf("%f ", dis[i][j] - 1e9);
			if(fabs(dis[i][j] - 1e9) > EPS) {
				//printf("%f ", dis[i][j]);
				far[i] = max(far[i], dis[i][j]);
			}
		}
		//puts("");
	}
	rep(i, 1, N) {
		rep(j, 1, N) {
			if(belong[i] != belong[j]) {
				//printf("%f %f %f\n", far[i], far[j], cor[i].sub(cor[j]).abs());
				ans = min(ans, max(max(d[belong[i]], d[belong[j]]), far[i] + far[j] + cor[i].sub(cor[j]).abs()));
			}
		}
	}
	printf("%.6f\n", ans);
	return 0;
}

