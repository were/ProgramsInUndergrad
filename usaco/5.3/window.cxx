/*
ID : weng_xo2
LANG : C++11
PROG : window
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

const double EPS = 1e-10;

char buffer[100];

struct Data {
	char ch;
	double x1, y1, x2, y2;
	Data(double x, double y, double X, double Y) {
		x1 = min(x, X);
		y1 = min(y, Y);
		x2 = max(x, X);
		y2 = max(y, Y);
	}
	Data() {}
	double area() {
		return (x2 - x1) * (y2 - y1);
	}
};

vector<Data> rect;

double cover(Data a, size_t x){
	if(a.area() > EPS && x < rect.size()){
		double ret = 0.;
		if(a.x1 < rect[x].x1)
			ret += cover(Data(a.x1, max(a.y1, rect[x].y1), min(a.x2, rect[x].x1), max(a.y2, rect[x].y1)), x + 1);
		if(a.y2 > rect[x].y2)
			ret += cover(Data(max(rect[x].x1, a.x1), max(a.y1, rect[x].y2), max(rect[x].x1, a.x2), a.y2), x + 1);
		if(a.x2 > rect[x].x2)
			ret += cover(Data(max(a.x1, rect[x].x2), min(rect[x].y2, a.y1), a.x2, min(rect[x].y2, a.y2)), x + 1);
		if(a.y1 < rect[x].y1)
			ret += cover(Data(min(rect[x].x2, a.x1), a.y1, min(rect[x].x2, a.x2), min(a.y2, rect[x].y1)), x + 1);
		//printf("%f\n", ret);
		return ret;
	} else {
		//printf("%f\n", a.area());
		return a.area();
	}
	return 0.;
}

int main(){
	freopen("window.in", "r", stdin);
	freopen("window.out", "w", stdout);
	while(gets(buffer)) {
		//puts(buffer);
		if(*buffer == 'w') {
			Data tmp;
			double x, y, X, Y;
			char ch;
			sscanf(buffer, "w(%c,%lf,%lf,%lf,%lf)", &ch, &x, &y, &X, &Y);
			tmp = Data(x, y, X, Y);
			tmp.ch = ch;
			rect.push_back(tmp);
		}
		if(*buffer == 't') {
			char ch;
			sscanf(buffer, "t(%c)", &ch);
			Data tmp;
			//for(size_t i = 0; i < rect.size(); ++i) fprintf(stderr, "%c", rect[i].ch); fputs("\n", stderr);
			for(size_t i = 0; i < rect.size(); ++i) {
				if(rect[i].ch == ch) {
					tmp = rect[i];
					rect.erase(rect.begin() + i);
					//puts("erased\n");
					break;
				}
			}
			//for(size_t i = 0; i < rect.size(); ++i) fprintf(stderr, "%c", rect[i].ch); fputs("\n", stderr);
			rect.push_back(tmp);
		}
		if(*buffer == 'b') {
			char ch;
			sscanf(buffer, "b(%c)", &ch);
			size_t pos;
			Data tmp;
			for(pos = 0; pos < rect.size(); ++pos) {
				if(rect[pos].ch == ch) {
					tmp = rect[pos];
					break;
				}
			}
			for(size_t i = pos; i >= 1; --i) {
				rect[i] = rect[i - 1];
			}
			rect[0] = tmp;
		}
		if(*buffer == 'd') {
			char ch;
			sscanf(buffer, "d(%c)", &ch);
			for(size_t i = 0; i < rect.size(); ++i) {
				if(rect[i].ch == ch) {
					rect.erase(rect.begin() + i);
					break;
				}
			}
		}
		if(*buffer == 's') {
			char ch;
			sscanf(buffer, "s(%c)", &ch);
			for(size_t i = 0; i < rect.size(); ++i) {
				if(rect[i].ch == ch) {
					printf("%.3f\n", cover(rect[i], i + 1) / rect[i].area() * 100.);
				}
			}
		}
		/*
		for(size_t i = 0; i < rect.size(); ++i) {
			fprintf(stderr, "%c\n", rect[i].ch);
		}
		fputs("\n", stderr);
		*/
	}
}

