#include <cstdio>
 
int M, N, a, b, c, d;
int x1, y1, x2, y2, ansSum;
int g[1001][1001], s[1001][1001];
 
int calc(int a, int b, int c, int d){
	//printf("%d %d %d %d\n", a, b, c, d);
	//printf("%d\n", s[c][d] - s[a - 1][d] - s[c][b - 1] + s[a - 1][b - 1]);
	return s[c][d] - s[a - 1][d] - s[c][b - 1] + s[a - 1][b - 1];
}
 
int main(){
	scanf("%d%d%d%d%d%d", &M, &N, &b, &a, &d, &c);
	for(int i = 1;i <= N;++i){
		for(int j = 1;j <= M;++j){
			scanf("%d", g[i] + j);
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + g[i][j];
			//printf("%d, %d: %d\n", i, j, s[i][j]);
		}
	}
	for(int i = 1;i + a - 1 <= N;++i){
		for(int j = 1;j + b - 1 <= M;++j){
			int sum = calc(i, j, i + a - 1, j + b - 1);
			int mn = ~0u >> 1, xx, yy;
			for(int x = i + 1;x + c - 1 < i + a - 1;++x){
				for(int y = j + 1;y + d - 1 < j + b - 1;++y){
					if(calc(x, y, x + c - 1, y + d - 1) < mn){
						mn = calc(x, y, x + c - 1, y + d - 1);
						xx = x;
						yy = y;
					}
				}
			}
			if(sum - mn > ansSum){
				x1 = i;
				y1 = j;
				x2 = xx;
				y2 = yy;
				ansSum = sum - mn;
			}
		}
	}
	printf("%d %d\n%d %d\n", y1, x1, y2, x2);
	return 0;
}

