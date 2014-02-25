/*
PROG : camelot
ID : weng_xo2
LANG : C++11
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define X first
#define Y second

using std :: vector;
using std :: map;
using std :: pair;
using std :: cin;
using std :: cout;
using std :: cerr;
using std :: clog;
using std :: endl;
using std :: queue;
using std :: string;
using std :: ifstream;
using std :: ofstream;
using std :: max;
using std :: min;
using std :: lower_bound;
using std :: upper_bound;

using ll = long long;
using vi =  vector<int>;
using mii = map<int, int>;
using pii = pair<int, int>;

const vector<pii> dk{pii(-1, -2), pii(-2, -1), pii(-2, 1), pii(-1, 2), pii(1, -2), pii(2, -1), pii(1, 2), pii(2, 1)};

pii operator+ (const pii&a, const pii&b){
	return pii(a.X + b.X, a.Y + b.Y);
}

int R, C, dis[27][31][27][31], x, y, total[27][31], ans = ~0u >> 1;
char buffer[10];
pii konig;
vector<pii> kn;

bool inGrid(int x, int y){
	return x >= 0 && x < R && y >= 0 && y < C;
}

void bfs(const pii&x){
	queue<pii> q;
	q.push(x);
	dis[x.X][x.Y][x.X][x.Y] = 0;
	while(!q.empty()){
		for(auto &i: dk){
			auto tmp = i + q.front();
			if(!~dis[x.X][x.Y][tmp.X][tmp.Y] && inGrid(tmp.X, tmp.Y)){
				q.push(tmp);
				dis[x.X][x.Y][tmp.X][tmp.Y] = dis[x.X][x.Y][q.front().X][q.front().Y] + 1;
			}
		}
		q.pop();
	}
}

int main(){
	freopen("camelot.in", "r", stdin);
	freopen("camelot.out", "w", stdout);
	scanf("%d%d", &C, &R);
	memset(dis, -1, sizeof dis);
	for(int i = 0;i < R; ++i)
		for(int j = 0;j < C; ++j)
			bfs(pii(i, j));
	scanf("%s%d", buffer, &y);
	konig.X = *buffer - 'A';
	konig.Y = y - 1;
	while(~scanf("%s%d", buffer, &y)){
		x = *buffer - 'A';
		kn.push_back(pii(x, --y));
		for(int i = 0;i < R; ++i)
			for(int j = 0;j < C; ++j)
				total[i][j] += dis[i][j][x][y];
	}
	for(int i = 0;i < R; ++i)
		for(int j = 0;j < C; ++j){
			for(auto &k: kn){
				int tmp = total[i][j] - dis[i][j][k.X][k.Y];
				for(int dx = -2;dx <= 2; ++dx)
					for(int dy = -2;dy <= 2; ++dy)
						if(inGrid(x = konig.X + dx, y = konig.Y + dy) && ~dis[i][j][x][y] && ~dis[x][y][k.X][k.Y])
							ans = min(ans, tmp + dis[i][j][x][y] + dis[x][y][k.X][k.Y] + max(abs(dx), abs(dy)));
			}
		}
	printf("%d\n", kn.size() ? ans : 0);
	return 0;
}

