#include <algorithm>
#include <cstdio>
const int inf = int(1e9);
int N, M, candle[71], f[1 << 7][1 << 7], g[1 << 7][1 << 7], ans = inf;
bool full[1 << 7];
char s[8];
bool fff = false;
void show(int x){
	for(int i = 0;i < M;++ i)
		printf("%d", x >> i & 1);
	puts("");
}
void dfs(int dep, int a, int b, int c, int d, int delta){
	if(dep == (1 << M)){
		f[c][d] = std :: min(g[a][b] + delta, f[c][d]);
	}else{
		if(c & dep)
			dfs(dep << 1, a, b, c, d, delta);
		if((c & dep) == 0 && (dep == 1 || ((dep >> 1) & c) != 0) && (dep & a) != 0)
			dfs(dep << 1, a, b, c, d, delta);
		if((dep << 1) < (1 << M) && (c & dep) == 0 && (c & (dep << 1)) == 0)
			dfs(dep << 2, a, b, c ^ dep ^ (dep << 1), d, delta + 1);
		if((c & dep) == 0 && (d & dep) == 0)
			dfs(dep << 1, a, b, c ^ dep, d ^ dep, delta + 1);
	}
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0;i < N;++ i){
		scanf("%s", s);
		for(int j = 0;j < M;++ j)
			if(s[j] == '*')
				candle[i] |= 1 << j;
	}
	for(int i = 0;i < 1 << M;++ i){
		full[i] = true;
		for(int j = 1;j < M && full[i];++ j)
			if((i >> j & 1) == 0 && (i >> (j - 1) & 1) == 0)
				full[i] = false;
	}
	for(int i = 0;i < 1 << M;++ i)
		for(int j = 0;j < 1 << M;++ j)
			g[i][j] = inf;
	g[(1 << M) - 1][candle[0]] = 0;
	for(int i = 1;i <= N;++ i){
		for(int j = 0;j < 1 << M;++ j)
			for(int k = 0;k < 1 << M;++ k)
				f[j][k] = inf;
		for(int j = 0;j < 1 << M;++ j) if(full[j])
			for(int k = 0;k < 1 << M;++ k) if(g[j][k] != inf && (k & candle[i - 1]) == candle[i - 1])
				dfs(1, j, k, k, candle[i], 0);
		for(int j = 0;j < 1 << M;++ j)
			for(int k = 0;k < 1 << M;++ k)
				g[j][k] = f[j][k];
	}
	for(int i = 0;i < 1 << M;++ i) if(full[i])
		ans = std :: min(g[i][0], ans);
	printf("%d\n", ans);
	return 0;
}
