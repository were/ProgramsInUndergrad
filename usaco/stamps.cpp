/*
ID : weng_xo 2
PROB : stamps
LANG : C++
*/
#include <algorithm>
#include <cstdio>
const int inf = ~0u >> 1;
int K, N, opt[2222222], a[55], n;
int main(){
	freopen("stamps.in", "r", stdin);
	freopen("stamps.out", "w", stdout);
	scanf("%d%d", &K, &N);
	for(int i = 0;i < N;++ i){
		scanf("%d", a + i);
		n = std :: max(n, a[i]);
	}
	n = n * K;
	*opt = 0;
	for(int i = 1;i <= n;++ i)
		opt[i] = inf;
	for(int i = 0;i <= n;++ i)
		if(opt[i] <= K){
			for(int j = 0;j < N;++ j)
				opt[i + a[j]] = std :: min(opt[i] + 1, opt[i + a[j]]);
		}else{
			printf("%d\n", i - 1);
			return 0;
		}
	printf("%d\n", n);
	return 0;
}
