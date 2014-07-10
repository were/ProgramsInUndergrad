/*
ID : weng_xo2
LANG : C++11
PROG : frameup
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

int N, M, u[26], d[26], l[26], r[26];
char a[33][33];
vector<string> ans;

void dfs(string s) {
	char tmp[33][33];
	bool done = true;
//	cout << s << endl;
	rep(i, 1, N) {
		rep(j, 1, M) {
			tmp[i][j] = a[i][j];
			if(a[i][j] != '.') {
				done = false;
			}
		}
//		puts(a[i] + 1);
	}
//	cout << done << endl;
	if(done) {
		ans.push_back(s);
		return;
	}
	for(int i = 0; i < 26; ++i) {
		if(l[i] <= r[i] && u[i] <= d[i]) {
			bool flag = true;
			int cnt = 0;
			rep(y, l[i], r[i]) {
				if(a[u[i]][y] != '.' && a[u[i]][y] != 'A' + i) {
					flag = false;
					break;
				}
				if(a[d[i]][y] != '.' && a[d[i]][y] != 'A' + i) {
					flag = false;
					break;
				}
				cnt += a[u[i]][y] == 'A' + i;
				cnt += a[d[i]][y] == 'A' + i;
			}
			rep(x, u[i], d[i]) {
				if(a[x][l[i]] != '.' && a[x][l[i]] != 'A' + i) {
					flag = false;
					break;
				}
				if(a[x][r[i]] != '.' && a[x][r[i]] != 'A' + i) {
					flag = false;
					break;
				}
				cnt += a[x][l[i]] == 'A' + i;
				cnt += a[x][r[i]] == 'A' + i;
			}
			if(flag && cnt) {
				rep(y, l[i], r[i]) a[u[i]][y] = a[d[i]][y] = '.';
				rep(x, u[i], d[i]) a[x][l[i]] = a[x][r[i]] = '.';
				dfs((char)(i + 'A') + s);
				rep(x, 1, N) rep(y, 1, M) a[x][y] = tmp[x][y];
			}
		}
	}
}

int main(){
	freopen("frameup.in", "r", stdin);
	freopen("frameup.out", "w", stdout);
	scanf("%d%d", &N, &M);
	rep(i, 1, N) scanf("%s", a[i] + 1);
	for(int i = 0; i < 26; ++i) {
		u[i] = N;
		d[i] = 1;
		l[i] = M;
		r[i] = 1;
		rep(x, 1, N) rep(y, 1, M) if(a[x][y] - 'A' == i) {
			u[i] = min(u[i], x);
			d[i] = max(d[i], x);
			l[i] = min(l[i], y);
			r[i] = max(r[i], y);
		}
//		printf("%d %d %d %d\n", u[i], d[i], l[i], r[i]);
	}
	dfs("");
	sort(ans.begin(), ans.end());
	for(unsigned i = 0; i < ans.size(); ++i) {
		cout << ans[i] << endl;
	}
	return 0;
}

