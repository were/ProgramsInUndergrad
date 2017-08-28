/*
Programmed by wereFluke
*/
#include <algorithm>
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

using std :: max;
using std :: min;
using std :: swap;
using std :: lower_bound;
using std :: upper_bound;
using std :: vector;
using std :: map;
using std :: set;
using std :: priority_queue;
using std :: string;
using std :: pair;
using std :: make_pair;
using std :: less;
using std :: greater;
using std :: cin;
using std :: cout;
using std :: endl;
using std :: cerr;
using std :: clog;
using std :: ifstream;
using std :: ofstream;
using std :: queue;
using std :: stack;
using std :: deque;
using std :: list;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

const int MaxN = 10001;

int N, opt1[MaxN], opt2[MaxN], ans[MaxN], nxt1[MaxN], nxt2[MaxN];
bool hsh[MaxN];
vector<pii> g[MaxN];
set<pii> T_T;

void dfs1(int x){
	hsh[x] = true;
	priority_queue<int> heap;
	opt1[x] = opt2[x] = 0;
	for(vector<pii> :: iterator cur = g[x].begin();cur != g[x].end();++cur){
		if(!hsh[cur->X]){
			dfs1(cur->X);
			if(opt1[cur->X] + cur->Y > opt1[x]){
				opt2[x] = opt1[x];
				nxt2[x] = nxt1[x];
				opt1[x] = opt1[cur->X] + cur->Y;
				nxt1[x] = cur->X;
			}else{
				if(opt1[cur->X] + cur->Y > opt2[x]){
					opt2[x] = opt1[cur->X] + cur->Y;
					nxt2[x] = cur->X;
				}
			}
		}
	}
	hsh[x] = false;
}

void dfs2(int x, int d){
	ans[x] = opt1[x];
	hsh[x] = true;
	if(!T_T.empty()){
		ans[x] = max(ans[x], T_T.rbegin()->X + d);
	}
	for(vector<pii> :: iterator cur = g[x].begin();cur != g[x].end();++cur)
		if(!hsh[cur->X]){
			if(cur->X != nxt1[x]){
				T_T.insert(pii(opt1[x] - d, x));
			}
			if(cur->X != nxt2[x]){
				T_T.insert(pii(opt2[x] - d, x));
			}
			dfs2(cur->X, d + cur->Y);
			if(cur->X != nxt1[x])
				T_T.erase(pii(opt1[x] - d, x));
			if(cur->X != nxt2[x])
				T_T.erase(pii(opt2[x] - d, x));
		}
	hsh[x] = false;
}

int main(){
	scanf("%d", &N);
	rep(i, 2, N){
		int v, w;
		scanf("%d%d", &v, &w);
		g[i].push_back(pii(v, w));
		g[v].push_back(pii(i, w));
	}
	dfs1(1);
	dfs2(1, 0);
	rep(i, 1, N)
		printf("%d\n", ans[i]);
	return 0;
}

