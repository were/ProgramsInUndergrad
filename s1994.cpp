#include <cstdio>
const int
	MaxN = 500,
	dx[] = {0, 0, 1, -1},
	dy[] = {1, -1, 0, 0};
int N, M, a[MaxN][MaxN], ans;
bool hsh[MaxN][MaxN];
bool inRange(int x, int y){
	return x >= 0 && x < N && y >= 0 && y < M && !hsh[x][y] && a[x][y] == 0;
}
void dfs(int x, int y){
	hsh[x][y] = true;
	for(int i = 0;i < 4;++ i)
		if(inRange(x + dx[i], y + dy[i]))
			dfs(x + dx[i], y + dy[i]);
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0;i < N;++ i)
		for(int j = 0;j < M;++ j)
			scanf("%d", a[i] + j);
	for(int i = 0;i < N;++ i)
		for(int j = 0;j < M;++ j)
			if(a[i][j] == 0 && !hsh[i][j]){
				dfs(i, j);
				++ ans;
			}
	printf("%d\n", ans);
	return 0;
}
