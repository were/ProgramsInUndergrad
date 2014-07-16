#include <algorithm>
#include <cstdio>
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

int N, M, a[1001][1001], ans[1001][1001];

int getAns(int x, int y){
	if(x < 1 || x > N || y < 1 || y > M)
		return ~0u >> 1;
	return ans[x][y];
}

int calc(int x, int y){
	return std::min(getAns(x, y + 1), std::min(getAns(x + 1, y), getAns(x - 1, y + 1)));
}

int main(){
	scanf("%d%d", &N, &M);
	rep(i, 1, N) rep(j, 1, M) scanf("%d", a[i] + j);
	per(j, M, 1) per(i, N, 1) ans[i][j] = std::min(calc(i, j), a[i][j]);
	rep(i, 1, N) rep(j, 1, M) printf(j == M ? "%d\n" : "%d ", ans[i][j]);
	return 0;
}
