#include <cstdio>
#include <queue>
const int
	inf = ~0u >> 1,
	dx[] = {0, 0, 1, -1},
	dy[] = {1, -1, 0, 0};
int N, M, a[100][100], x, y, tre[100][100], cur = 1, dis[1 << 5][100][100], ans = inf;
bool hsh[1 << 5][100][100];
struct Data{
	int x, y, sat;
	Data(int x, int y, int sat) : x(x), y(y), sat(sat) {}
};
std :: queue<Data> q;
bool inRange(int x, int y){
	return x >= 0 && x < N && y >= 0 && y < M && a[x][y] != -1;
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0;i < N;++ i)
		for(int j = 0;j < M;++ j){
			scanf("%d", a[i] + j);
			if(a[i][j] == 2){
				x = i;
				y = j;
			}
			if(a[i][j] == 1){
				tre[i][j] = cur;
				cur <<= 1;
			}
		}
	for(int i = 0;i < cur;++ i)
		for(int j = 0;j < N;++ j)
			for(int k = 0;k < M;++ k)
				dis[i][j][k] = inf;
	dis[0][x][y] = 0;
	hsh[0][x][y] = true;
	q.push(Data(x, y, 0));
	while(!q.empty()){
		int x = q.front().x, y = q.front().y, sat = q.front().sat;
		q.pop();
		hsh[sat][x][y] = false;
//		printf("%d %d %d\n", x, y, sat);
		for(int i = 0;i < 4;++ i){
			int _x = x + dx[i], _y = y + dy[i], _sat;
			if(inRange(_x, _y)){
//				printf("%d %d\n", _x, _y);
				_sat = sat | tre[_x][_y];
				if(dis[sat][x][y] + 1 < dis[_sat][_x][_y]){
					dis[_sat][_x][_y] = dis[sat][x][y] + 1;
					if(!hsh[_sat][_x][_y]){
						hsh[_sat][_x][_y] = true;
						q.push(Data(_x, _y, _sat));
					}
				}
			}
		}
	}
	for(int i = 0;i < N;++ i)
		for(int j = 0;j < M;++ j)
			if(ans > dis[cur - 1][i][j]){
				ans = dis[cur - 1][i][j];
//				printf("%d %d %d\n", i, j, dis[cur - 1][i][j]);
			}
	printf("%d\n", ans == inf ? -1 : ans);
	return 0;
}
