#include <cstdio>
#include <cstdlib>
#define rep(i,f,t) for(int i(f);i <= (t);++ i)
#define mid (l + r >> 1)
const int MaxN = 111, MaxK = 555, inf = int(1e7);
int N, M, K, S, T, g[MaxN][MaxN], f[MaxN][MaxN], l = 1, r = 0, cnt;
int path[MaxN];
bool hsh[MaxN];
bool dfs(int x, int d){
	if(d + f[x][T] > mid)
		return false;
	if(x == T){
		++ cnt;
	}else{
		hsh[x] = true;
		rep(i, 1, N) if(!hsh[i] && d + g[x][i] <= mid){
			dfs(i, d + g[x][i]);
			hsh[i] = false;
			if(cnt >= K)
				return true;
		}
	}
	return false;
}
void printIt(int x, int d){
	if(d + f[x][T] > mid)
		return;
	if(x == T){
		++ cnt;
		if(d == l){
			printf("%d %d\n", d, path[0] + 1);
			rep(i, 1, path[0])
				printf("%d ", path[i]);
			printf("%d\n", T);
			exit(0);
		}
	}else{
		hsh[x] = true;
		rep(i, 1, N){
			if(!hsh[i] && d + g[x][i] <= l){
				path[++ path[0]] = x;
				printIt(i, d + g[x][i]);
				-- path[0];
				hsh[i] = false;
				if(cnt >= K)
					return;
			}
		}
	}
	return;
}
int main(){
	scanf("%d%d%d", &N, &M, &K);
	rep(i, 1, N){
		rep(j, 1, N) g[i][j] = f[i][j] = inf;
		f[i][i] = g[i][i] = 0;
	}
	rep(i, 1, M){
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		f[u][v] = f[v][u] = g[u][v] = g[v][u] = w;
		r += w;
	}
	scanf("%d%d", &S, &T);
	rep(k, 1, N) rep(i, 1, N) rep(j, 1, N)
		if(f[i][k] + f[k][j] < f[i][j])
			f[i][j] = f[i][k] + f[k][j];
	while(l < r){
		cnt = 0;
		dfs(S, 0) ? r = mid : l = mid + 1;
	}
	cnt = 0;
	printIt(S, 0);
	return 0;
}
