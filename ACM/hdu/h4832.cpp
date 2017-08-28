#include <cstdio>
#include <cstring>

const int MaxN = 1001, Mod = 9999991;

int T, N, M, K, x0, y0, c[MaxN][MaxN], f[MaxN][MaxN], g[MaxN][MaxN], ans, cs;

int main() {
	scanf("%d", &T);
	c[0][0] = 1;
	for(int i = 1; i < MaxN; ++i) {
		c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; ++j) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % Mod;
		}
	}
	while(T--) {
		scanf("%d%d%d%d%d", &N, &M, &K, &x0, &y0);
		ans = 0;
		for(int i = 0; i <= K; ++i) {
			for(int j = 0; j <= N; ++j) {
				f[i][j] = 0;
			}
			for(int j = 0; j <= M; ++j) {
				g[i][j] = 0;
			}
		}
		f[0][x0] = 1;
		for(int i = 1; i <= K; ++i) {
			for(int j = 1; j <= N; ++j) {
				for(int k = -2; k <= 2; ++k) {
					if(k && j + k >= 1 && j + k <= N) {
						f[i][j] = (f[i][j] + f[i - 1][j + k]) % Mod;
					}
				}
			}
		}
		g[0][y0] = 1;
		for(int i = 1; i <= K; ++i) {
			for(int j = 1; j <= M; ++j) {
				for(int k = -2; k <= 2; ++k) {
					if(k && j + k >= 1 && j + k <= M) {
						g[i][j] = (g[i][j] + g[i - 1][j + k]) % Mod;
					}
				}
			}
		}
		for(int i = 0; i <= K; ++i) {
			int a = 0, b = 0;
			for(int j = 1; j <= N; ++j) {
				a = (a + f[i][j]) % Mod;
			}
			for(int j = 1; j <= M; ++j) {
				b = (b + g[K - i][j]) % Mod;
			}
			// printf("%d %d\n", a, b);
			// printf("%d %d %d\n", K, i, c[K][i]);
			ans = (1ll * a * b % Mod * c[K][i] % Mod + ans) % Mod;
		}
		printf("Case #%d:\n%d\n", ++cs, ans);
	}
}
