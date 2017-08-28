#include <algorithm>
#include <cstdio>
const int MaxN = 1000;
int N, M, k, ans[MaxN];
int main(){
	scanf("%d%d", &N, &M);
	std :: fill(ans, ans + N, M / N);
	M %= N;
	for(k = 1;(k * M + 1) % N;++ k);
	for(int i = k;M --;i = (i + k) % N)
		++ ans[i];
	for(int i = 0;i < N;++ i)
		printf(i == N - 1 ? "%d\n" : "%d ", ans[i]);
	return 0;
}
