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

int T, N, M, fa[111];

struct Edge {
	int u, v, w;
	bool used;
}e[20000];

bool cmp(Edge a, Edge b) {
	return a.w < b.w;
}

int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

int main(){
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		rep(i, 1, M) {
			scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
			e[i].used = false;
		}
		sort(e + 1, e + 1 + M, cmp);
		int ans1 = 0, n = N;
		rep(i, 1, N) fa[i] = i;
		rep(i, 1, M) {
			if(getfa(e[i].u) != getfa(e[i].v)) {
				fa[getfa(e[i].u)] = getfa(e[i].v);
				ans1 += e[i].w;
				--n;
				e[i].used = true;
			}
			if(n == 1) {
				break;
			}
		}
		if(n == 1) {
			bool isUnique = true;
			rep(ban, 1, M) if(e[ban].used) {
				n = N; int ans2 = 0;
				rep(i, 1, N) fa[i] = i;
				rep(i, 1, M) if(i != ban) {
					if(getfa(e[i].u) != getfa(e[i].v)) {
						fa[getfa(e[i].u)] = getfa(e[i].v);
						//printf("%d %d %d\n", e[i].u, e[i].v, e[i].w);
						ans2 += e[i].w;
						--n;
					}
					if(n == 1) {
						break;
					}
				}
				//printf("%d: %d %d\n", ban, ans1, ans2);
				if(n == 1 && ans1 == ans2) {
					isUnique = false;
					break;
				}
			}
			if(isUnique) {
				printf("%d\n", ans1);
			} else {
				puts("Not Unique!");
			}
		} else {
			puts("Not Unique!");
		}
	}
}

