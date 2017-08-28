#include <cstdio>
int N, M, a[111][111], f[111][111], pre[111][111], ans = 1;
void printIt(int x, int i){
	if(i != 1)
		printIt(pre[i][x], i - 1);
	printf(i == N ? "%d\n" : "%d ", x);
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 1;i <= N;++i)
		for(int j = 1;j <= M;++j)
			scanf("%d", a[i] + j);
	for(int i = 1;i <= N;++i)
		for(int j = i;j <= M;++j){
			f[i][j] = -int(1e9);
			if(i == 1)
				f[i][j] = a[i][j];
			else
				for(int k = i - 1;k < j;++ k)
					if(f[i - 1][k] + a[i][j] > f[i][j]){
						f[i][j] = f[i - 1][k] + a[i][j];
						pre[i][j] = k;
					}
		}
	for(int i = 1;i <= M;++i)
		if(f[N][ans] < f[N][i])
			ans = i;
	printf("%d\n", f[N][ans]);
	printIt(ans, N);
	return 0;
}
