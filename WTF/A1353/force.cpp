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

const int MaxN = 100010;

int N, M, root, flag, v[MaxN], ans, x, hsh[MaxN];
vi g[MaxN];

void dfs(int cur, bool in){
	hsh[cur] = flag;
	if(x == cur)
		in = true;
	if(in){
		ans = min(ans, v[cur]);
//printf("%d: %d\n", cur, v[cur]);
	}
	for_vec(i, g[cur])
		if(hsh[g[cur][i]] != flag)
			dfs(g[cur][i], in);
	if(x == cur)
		in = false;
}

int main(){
	freopen("input", "r", stdin);
	freopen("answer", "w", stdout);
	scanf("%d%d", &N, &M);
	root = 1;
	rep(i, 1, N){
		int f;
		scanf("%d%d", &f, v + i);
		if(f){
			g[f].push_back(i);
			g[i].push_back(f);
		}
	}
	while(M--){
		char s[10];
		scanf("%s%d", s, &x);
		if(*s == 'V')
			scanf("%d", v + x);
		if(*s == 'E')
			root = x;
		if(*s == 'Q'){
			ans = ~0u >> 1;
			++flag;
			dfs(root, false);
			printf("%d\n", ans);
		}
	}
	return 0;
}

