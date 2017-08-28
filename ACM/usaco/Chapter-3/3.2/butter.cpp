/*
PROG : butter
ID : weng_xo2
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

const int MaxN = 888, inf = ~0u >> 1;
int N, P, C, a[MaxN], hsh[MaxN], dis[MaxN][MaxN], ans = inf;
std :: vector<pii> g[MaxN];

void spfa(int s){
	std :: queue<int> q;
	q.push(s);
	hsh[s] = s;
	dis[s][s] = 0;
	while(!q.empty()){
		int x = q.front();
		for_vec(i, g[x]){
			if(dis[s][x] + g[x][i].Y <= dis[s][g[x][i].X]){
				dis[s][g[x][i].X] = dis[s][x] + g[x][i].Y;
				if(hsh[g[x][i].X] != s){
					q.push(g[x][i].X);
					hsh[g[x][i].X] = s;
				}
			}
		}
		q.pop();
		hsh[x] = -1;
	}
}

int main(){
	freopen("butter.in", "r", stdin);
	freopen("butter.out", "w", stdout);
	scanf("%d%d%d", &N, &P, &C);
	rep(i, 1, N) scanf("%d", a + i);
	rep(i, 1, C){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u].push_back(pii(v, w));
		g[v].push_back(pii(u, w));
	}
	rep(i, 1, P) rep(j, 1, P) dis[i][j] = inf;
	rep(i, 1, N) spfa(a[i]);
	rep(i, 1, P){
		int tmp = 0;
		rep(j, 1, N) tmp += dis[a[j]][i];
		ans = std :: min(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
}
