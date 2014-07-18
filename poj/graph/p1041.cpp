/*
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

int N, M, flag, hsh[2000], s;
vector<pii> g[50];
vi res;

void dfs(int x) {
	for(size_t i = 0; i < g[x].size(); ++i) {
		if(hsh[g[x][i].X] != flag) {
			hsh[g[x][i].X] = flag;
			dfs(g[x][i].Y);
			res.push_back(g[x][i].X);
		}
	}
}

int main(){
	for(;;) {
		++flag;
		s = 100;
		M = 0;
		res.clear();
		for(int i = 0; i < 45; ++i) g[i].clear();
		for(;;) {
			int x, y, z;
			scanf("%d%d", &x, &y);
			if(x + y) {
				scanf("%d", &z);
				g[x].push_back(pii(z, y));
				g[y].push_back(pii(z, x));
				++M;
				s = min(s, min(x, y));
			} else {
				break;
			}
		}
		if(!M) {
			break;
		}
		bool exist = true;
		for(int i = 0; i < 50; ++i) {
			if(g[i].size() % 2) {
				exist = false;
				break;
			} else {
				sort(g[i].begin(), g[i].end());
			}
		}
		if(exist) {
			dfs(s);
			for(size_t i = 0; i < res.size(); ++i) {
				printf(i + 1 == res.size() ? "%d\n" : "%d ", res[res.size() - 1 - i]);
			}
		} else {
			puts("Round trip does not exist.");
		}
	}
}

