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

const int MaxN = 200010, Mod = 99990001;

int N, u[MaxN], v[MaxN], hsh[MaxN], e[MaxN], flag, p;
vi g[MaxN];
ll w[MaxN];

void dfs(int x, int &sz, int &m){
	hsh[x] = flag;
	++sz;
	m = min(m, x);
	for_vec(i, g[x]) if(!e[g[x][i]]){
		int V = u[g[x][i]] != x ? u[g[x][i]] : v[g[x][i]];
		if(hsh[V] != flag)
			dfs(V, sz, m);
	}
}

void mul(int x){
	hsh[x] = flag;
	for_vec(i, g[x]) if(!e[g[x][i]]){
		int V = u[g[x][i]] != x ? u[g[x][i]] : v[g[x][i]];
		if(hsh[V] != flag){
			(w[g[x][i]] *= w[p]) %= Mod;
			mul(V);
		}
	}
}

void add(int x){
	hsh[x] = flag;
	for_vec(i, g[x]) if(!e[g[x][i]]){
		int V = u[g[x][i]] != x ? u[g[x][i]] : v[g[x][i]];
		if(hsh[V] != flag){
			(w[g[x][i]] += w[p]) %= Mod;
			add(V);
		}
	}
}

int main(){
	freopen("input", "r", stdin);
	freopen("answer", "w", stdout);
	scanf("%d", &N);
	for(int i = 1;i < N;++i){
		scanf("%d%d%lld", u + i, v + i, w + i);
		g[u[i]].push_back(i);
		g[v[i]].push_back(i);
	}
	for(int i = 1;i < N;++i){
		scanf("%d", &p);
		int sz1 = 0, m1 = N + 1, sz2 = 0, m2 = N + 1;
		e[p] = i;
		++flag; dfs(u[p], sz1, m1);
		++flag; dfs(v[p], sz2, m2);
		if(pii(sz1, m1) < pii(sz2, m2)){
			++flag; mul(u[p]);
			++flag; add(v[p]);
		}else{
			++flag; mul(v[p]);
			++flag; add(u[p]);
		}
		printf("%lld\n", w[p]);
	}
	return 0;
}

