#include <algorithm>
#include <cstdio>
#include <queue>
const int
	MaxN = 1111,
	dx[] = {0, 0, 1, -1},
	dy[] = {1, -1, 0, 0};
int N, M, K, hsh[MaxN][MaxN], ans;
struct Data{
	int x, y;
	Data(int x, int y) : x(x), y(y) {}
};
int sqr(int x){
	return x * x;
}
int dis(int x, int y, int _x, int _y){
	return sqr(x - _x) + sqr(y - _y);
}
bool inRange(int x, int y){
	return x > 0 && x <= N && y > 0 && y <= M;
}
int main(){
	scanf("%d%d%d", &N, &M, &K);
	for(int i = 1;i <= K;++ i){
		int x, y, r;
		scanf("%d%d%d", &x, &y, &r);
		std :: queue<Data> q;
		q.push(Data(x, y));
		hsh[x][y] = i;
		while(!q.empty()){
			int X = q.front().x, Y = q.front().y;
//			printf("%d %d\n", X, Y);
			q.pop();
			for(int j = 0;j < 4;++ j){
				int _x = X + dx[j], _y = Y + dy[j];
				if(inRange(_x, _y) && dis(x, y, _x, _y) <= sqr(r) && hsh[_x][_y] != i){
					q.push(Data(_x, _y));
					hsh[_x][_y] = i;
				}
			}
		}
	}
	for(int i = 0;i <= N;++ i)
		for(int j = 0;j <= M;++ j)
			if(hsh[i][j] != 0)
				++ ans;
	printf("%d\n", ans);
	return 0;
}
