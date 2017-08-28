#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>

using std::min;

const int MaxN = 44;

int N, M, a[MaxN * MaxN], pre[MaxN * MaxN], ans, flag, hsh[MaxN * MaxN];
std::vector<int> ver, hor;

int v(int x, int y) {
	return x * N + y;
}

int dfs(int vex) {
	int x = vex / N;
	int y = vex % N;
	for(int dx = -1; dx <= 1; ++dx) {
		for(int dy = -1;dy <= 1; ++dy) if(abs(dx) + abs(dy) == 1){
			int _x = x + dx, _y = y + dy;
			if(_x >= 0 && _x < N && _y >= 0 && _y < N && !a[v(_x, _y)] && hsh[v(_x, _y)] != flag) {
				hsh[v(_x, _y)] = flag;
				if(!pre[v(_x, _y)] || dfs(pre[v(_x, _y)])) {
					pre[v(_x, _y)] = v(x, y);
					return 1;
				}
			}
		}
	}
	return 0;
}

void show(int x) {
	printf("%d %d\n", x / N + 1, x % N + 1);
}

int main() {
	scanf("%d%d", &N, &M);
	if((N * N - M) % 2) {
		puts("No");
		return 0;
	}
	for(int i = 0; i < M; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		--x; --y;
		a[v(x, y)] = true;
	}
/*
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			printf("%d ", a[v(i, j)]);
		}
		puts("");
	}
*/
	for(int i = 0; i < N; ++i) {
		for(int j = 0; j < N; ++j) {
			if((i + j) % 2 && !a[v(i, j)]) {
//printf("working... %d %d\n", i, j);
				++flag;
				ans += dfs(v(i, j));
//				printf("%d\n", ans);
			}
		}
	}
	if(ans == (N * N - M) / 2) {
		puts("Yes");
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if((i + j) % 2 == 0 && !a[v(i,  j)]) {
					if(abs(v(i, j) - pre[v(i, j)]) == 1) {
						hor.push_back(min(v(i, j), pre[v(i, j)]));
					}
					else {
						ver.push_back(min(v(i, j), pre[v(i, j)]));
					}
				}
			}
		}
		std::cout << ver.size() << std::endl;
		for(unsigned i = 0; i < ver.size(); ++i) {
			show(ver[i]);
		}
		std::cout << hor.size() << std::endl;
		for(unsigned i = 0; i < hor.size(); ++i) {
			show(hor[i]);
		}
	}
	else {
		puts("No");
	}
	return 0;
}
