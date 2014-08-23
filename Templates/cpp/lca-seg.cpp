/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)

typedef long long ll;
typedef std::vector<int> vi;
typedef std::map<int, int> mii;

/*lca-seg-template*/
const int MaxN = 100010;
vi g[MaxN];
bool hsh[MaxN];
int dep[MaxN], pre[MaxN], hd[MaxN], nxt[MaxN], sz[MaxN], N;
int q[MaxN], f, t;
void dfs(int x){
	hsh[x] = true;
	sz[x] = 1;
	for_vec(i, g[x]){
		if(!hsh[g[x][i]]){
			pre[g[x][i]] = x;
			dep[g[x][i]] = dep[x] + 1;
			dfs(g[x][i]);
			sz[x] += sz[g[x][i]];
		}
	}
}
void lcaInit(){
	pre[1] = 0;
	dep[1] = 1;
//bfs
	q[t++] = 1;
	hsh[1] = true;
	while(f < t){
		for_vec(i, g[q[f]])
			if(!hsh[g[q[f]][i]]){
				hsh[g[q[f]][i]] = true;
				q[t ++] = g[q[f]][i];
				pre[g[q[f]][i]] = q[f];
				dep[g[q[f]][i]] = dep[q[f]] + 1;
			}
		++f;
	}
	for(int i = N - 1;i >= 0; --i){
		sz[pre[q[i]]] +=  ++sz[q[i]];
		if(sz[nxt[pre[q[i]]]] < sz[q[i]])
			nxt[pre[q[i]]] = q[i];
	}
//bfs-end
	for(int i = 0;i < N; ++i)
		if(!hd[q[i]]){
			for(int j = q[i];j;j = nxt[j])
				hd[j] = q[i];
		}
}
int query(int a, int b){
	while(hd[a] != hd[b]){
		if(dep[a] < dep[b])
			std::swap(a, b);
		a = pre[hd[a]];
	}
	return dep[a] < dep[b] ? a : b;
}
/*lca-seg-template-end*/
int main(){
	lcaInit();
}
