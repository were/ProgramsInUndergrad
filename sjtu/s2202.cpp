#include <cstdio>
#include <queue>
const int
	MaxN = 1000, inf = ~0u >> 1,
	dx[] = {0, 0, 1, -1},
	dy[] = {1, -1, 0, 0};
int T, N, M, a[MaxN][MaxN], dis[2][MaxN][MaxN];
bool hsh[2][MaxN][MaxN];
struct Data{
	int x, y;
	bool d;
	Data(int x, int y, bool d) : x(x), y(y), d(d) {}
};
bool inRange(int x, int y){
	return x >= 0 && x < N && y >= 0 && y < M;
}
int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d%d", &N, &M);
		for(int i = 0;i < N;++ i)
			for(int j = 0;j < M;++ j){
				scanf("%d", a[i] + j);
				dis[0][i][j] = dis[1][i][j] = inf;
				hsh[0][i][j] = hsh[0][i][j] = false;
			}
		std :: queue<Data> q;
		hsh[0][0][0] = true;
		dis[0][0][0] = 0;
		q.push(Data(0, 0, false));
		while(!q.empty()){
			int x = q.front().x,
				y = q.front().y;
			bool d = q.front().d;
//			printf("%d,%d %d\n", x, y, d);
			q.pop();
			hsh[d][x][y] = false;
			for(int i = 0;i < 4;++ i){
				int _x = x + dx[i], _y = y + dy[i];
				if(inRange(_x, _y)){
//					printf("%d %d\n", _x, _y);
					if(a[_x][_y] == 0){
						if(dis[d][_x][_y] > dis[d][x][y] + 1){
							dis[d][_x][_y] = dis[d][x][y] + 1;
							if(!hsh[d][_x][_y]){
//								puts("push it @0");
								q.push(Data(_x, _y, d));
								hsh[d][_x][_y] = true;
							}
						}
					}
					if(a[_x][_y] == 1 && !d){
						if(dis[1][_x][_y] > dis[d][x][y] + 1){
							dis[1][_x][_y] = dis[d][x][y] + 1;
							if(!hsh[1][_x][_y]){
//								puts("push it @1");
								q.push(Data(_x, _y, 1));
								hsh[1][_x][_y] = true;
							}
						}
					}
				}
			}
		}
		puts(dis[0][N - 1][M - 1] == inf && dis[1][N - 1][M -1] == inf ? "0" : "1");
	}
	return 0;
}

