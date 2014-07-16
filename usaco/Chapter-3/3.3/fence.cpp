/*
ID : weng_xo2
PROG : fence
LANG : C++
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
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

typedef long long ll;
typedef std :: vector<int> vi;
typedef std :: map<int, int> mii;
typedef std :: pair<int, int> pii;
typedef std :: vector<pii> :: iterator edge;
const int inf = ~0u >> 1;

int N, root = inf, ans[1026];
std :: vector<pii> g[501];
bool hsh[1025];

edge getNxt(std :: vector<pii>&a){
	edge ret = a.end();
	for(edge cur = a.begin();cur != a.end();++ cur)
		if(!hsh[cur->Y]){
			if(ret == a.end())
				ret = cur;
			else if(cur->X < ret->X)
				ret = cur;
		}
	return ret;
}

void dfs(int x){
	edge nxt;
	while((nxt = getNxt(g[x])) != g[x].end()){
		hsh[nxt->Y] = true;
		dfs(nxt->X);
	}
	ans[++ ans[0]] = x;
}

int main(){
	freopen("fence.in", "r", stdin);
	freopen("fence.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(pii(v, i));
		g[v].push_back(pii(u, i));
		root = std :: min(root, u);
		root = std :: min(root, v);
	}
	rep(i, 1, N)
		if(g[i].size() % 2 == 1){
			root = i;
			break;
		}
	dfs(root);
	per(i, ans[0], 1)
		printf("%d\n", ans[i]);
	return 0;
}

