#include <cstdio>
#include <cstdlib>
#include <queue>
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define range(i,f,t) for(int i(f);i<(t);++i)

const int MaxN = 222;

int N, ans;
bool cube[MaxN][MaxN][MaxN], hsh[MaxN][MaxN][MaxN];

struct Cube {
	int x, y, z;
	Cube(int x, int y, int z) : x(x), y(y), z(z) {}
};

std::queue<Cube> q;


bool inRange(int x, int y, int z) {
	return x >= 0 && x <= 202 && y >= 0 && y <= 202 && z >= 0 && z <= 202;
}

int main() {
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		int x1, y1, z1, x2, y2, z2;
		scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
		++x1; ++y1; ++z1; ++x2; ++y2; ++z2;
		range(x, x1, x2) range(y, y1, y2) range(z, z1, z2) {
			cube[x][y][z] = true;
		}
	}
	for(q.push(Cube(202, 202, 202)); !q.empty(); q.pop()) {
		int x = q.front().x, y = q.front().y, z = q.front().z;
		rep(i, -1, 1) rep(j, -1, 1) rep(k, -1, 1) {
			if(abs(i) + abs(j) + abs(k) == 1 && inRange(x + i, y + j, z + k) && !hsh[x + i][y + j][z + k]) {
				if(cube[x + i][y + j][z + k]) {
					++ans;
				}
				else {
					q.push(Cube(x + i, y + j, z + k));
					hsh[x + i][y + j][z + k] = true;
				}
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
