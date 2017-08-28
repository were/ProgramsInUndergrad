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

int T, N, hsh[1111], flag, in[26];
vi g[26], res;
char s[1111][30];

bool cmp(int a, int b) {
	return strcmp(s[a], s[b]) < 0;
}

void dfs(int x) {
	for(size_t i = 0; i < g[x].size(); ++i) {
		if(hsh[g[x][i]] != flag) {
			hsh[g[x][i]] = flag;
			dfs(s[g[x][i]][strlen(s[g[x][i]]) - 1] - 'a');
			res.push_back(g[x][i]);
		}
	}
}

int main(){
	scanf("%d", &T);
	while(T--) {
		++flag;
		rep(i, 0, 25) {
			g[i].clear();
			in[i] = 0;
		}
		res.clear();
		scanf("%d", &N);
		rep(i, 1, N) {
			scanf("%s", s[i]);
			g[s[i][0] - 'a'].push_back(i);
			++in[s[i][strlen(s[i]) - 1] - 'a'];
		}
		rep(i, 0, 25) {
			sort(g[i].begin(), g[i].end(), cmp);
		}
		bool ok = true;
		int cnt1 = 0, cnt2 = 0;
		rep(i, 0, 25) {
			if(in[i] == (int) g[i].size()) {
				continue;
			} else {
				if(in[i] - 1 == (int) g[i].size()) {
					++cnt1;
				} else {
					if((int) g[i].size() - 1 == in[i]) {
						++cnt2;
					} else {
						ok = false;
						break;
					}
				}
			}
		}
		if(ok && (cnt1 == cnt2 && (cnt1 == 1 || cnt1 == 0))) {
			if(cnt1 == 0) {
				rep(i, 0, 25) {
					if(g[i].size()) {
						dfs(i);
						break;
					}
				}
			} else {
				rep(i, 0, 25) {
					if(g[i].size() - in[i] == 1) {
						dfs(i);
						break;
					}
				}
			}
			if((int) res.size() != N) {
				puts("***");
			} else {
				for(size_t i = 0; i < res.size(); ++i) {
					printf(i ? ".%s" : "%s", s[res[N - 1 - i]]);
				}
				puts("");
			}
		} else {
			puts("***");
		}
	}
}

