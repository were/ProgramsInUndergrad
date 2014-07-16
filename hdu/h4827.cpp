#include <algorithm>
#include <bitset>
#include <cstdio>

using std::bitset;
using std::swap;

int T, N, M, ans[1000], cs;
bitset<1001> g[1000];

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &N, &M);
		printf("Case #%d:\n", ++cs);
		for(int i = 0; i < N; ++i) {
			g[i].reset();
			ans[i] = 0;
		}
		for(int i = 0; i < M; ++i) {
			int x, y;
			scanf("%d%d", &x, &y);
			--x;
			--y;
			g[x][x] = g[x][x] ^ 1;
			g[x][y] = g[x][y] ^ 1;
			g[x][N] = g[x][N] ^ 1;
			g[y][x] = g[y][x] ^ 1;
			g[y][y] = g[y][y] ^ 1;
			g[y][N] = g[y][N] ^ 1;
		}
		for(int i = 0, x = 0; i < N; ++i) {
			for(int j = x; j < N; ++j) {
				if(g[j][i]) {
					swap(g[x], g[j]);
					break;
				}
			}
			if(g[x][i]) {
				for(int j = x + 1; j < N; ++j) {
					if(g[j][i]) {
						g[j] ^= g[x];
					}
				}
				++x;
			}
		}
		for(int i = N - 1; i >= 0; --i) {
			int x = 0;
			while(x < N && !g[i][x]) {
				++x;
			}
			if(x != N) {
				ans[x] = g[i][N];
				for(int j = 0; j < i; ++j) {
					if(g[j][x]) {
						g[j][N] = g[j][N] ^ ans[x];
					}
				}
			}
		}
		for(int i = 0; i < N; ++i) {
			printf("%d", ans[i]);
		}
		puts("");
	}
}
