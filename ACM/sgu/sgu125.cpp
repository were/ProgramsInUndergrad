#include <cstdio>
const int
	dx[] = {-1, 0, 1, 0},
	dy[] = {0, -1, 0, 1};
int N, a[3][3], b[3][3], B[3][3], cnt[3][3];
int calc(int x, int y){
	return 5 - (!x) - (x == N - 1) - (!y) - (y == N - 1);
}
bool inRange(int x, int y){
	return x >= 0 && x < N && y >= 0 && y < N;
}
bool check(int x, int y){
	bool ret = true;
	for(int i = 0;i < 4;++i){
		int _x = x + dx[i], _y = y + dy[i];
		if(inRange(_x, _y)){
			if(i < 2){
				if(a[x][y] > a[_x][_y])
					++B[_x][_y];
				if(a[x][y] < a[_x][_y])
					++B[x][y];
			}
			if(++cnt[_x][_y] == calc(_x, _y) && b[_x][_y] != B[_x][_y]){
				ret = false;
			}
		}
	}
	if(++cnt[x][y] == calc(x, y) && b[x][y] != B[x][y]){
		ret = false;
	}
	return ret;
}
void erase(int x, int y){
	for(int i = 0;i < 4;++i){
		int _x = x + dx[i], _y = y + dy[i];
		if(inRange(_x, _y)){
			if(i < 2){
				if(a[x][y] > a[_x][_y])
					--B[_x][_y];
				if(a[x][y] < a[_x][_y])
					--B[x][y];
			}
			--cnt[_x][_y];
		}
	}
	--cnt[x][y];
}
bool dfs(int dep){
	if(dep == N * N)
		return true;
	int x = dep / N, y = dep % N;
	for(a[x][y] = 0;a[x][y] <= 9;++a[x][y]){
		if(check(x, y) && dfs(dep + 1))
			return true;
		erase(x, y);
	}
	return false;
}
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++i)
		for(int j = 0;j < N;++j){
			scanf("%d", b[i] + j);
			a[i][j] = -1;
		}
	if(dfs(0)){
		for(int i = 0;i < N;++i)
			for(int j = 0;j < N;++j)
				printf(j == N - 1 ? "%d\n" : "%d ", a[i][j]);
	}else
		puts("NO SOLUTION");
	return 0;
}

