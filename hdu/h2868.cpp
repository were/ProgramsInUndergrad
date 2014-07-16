/*
Programmed by wereFluke
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

int N, M, ans;
bool g[201][201], hsh[201][201];

void solve(){
	rep(i, 1, N) rep(j, 1, N) g[i][j] = hsh[i][j] = false;
	ans = 0;
	rep(i, 1, M){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v] = true;
	}
	rep(k, 1, N)
		rep(i, 1, N)
			rep(j, 1, N)
				g[i][j] |= g[i][k] && g[k][j];
	rep(i, 1, N)
		rep(j, 1, N) if(i != j && !g[j][i]){
			bool flag = true;
			rep(k, 1, N){
				if(g[i][k] && g[k][j]){
					flag = false;
					break;
				}
			}
			if(flag && !hsh[i][j]){
				++ ans;
				hsh[i][j] = hsh[j][i] = true;
//				printf("    %d %d\n", i, j);
			}
		}
	printf("%d\n", ans);
}

int main(){
	while(~scanf("%d%d", &N, &M)){
		solve();
	}
	return 0;
}

