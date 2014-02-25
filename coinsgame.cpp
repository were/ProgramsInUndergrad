#include <algorithm>
#include <cstdio>
int calc(int N, int K, int C){
	int sum = K / N * N;
	if(sum >= C)
		return C;
	int ret = 0;
	C -= sum;
	ret += sum;
	K -= sum;
	ret += N - K;
	ret += C;
	return ret;
}
int main(){
	int T, caseCnt = 0;
	scanf("%d", &T);
	while(T --){
		int N, C, K;
		scanf("%d%d%d", &N, &K, &C);
		int ans = ~0u >> 1;
		for(int i = 0;i < N;++ i)
			ans = std :: min(ans, calc(N - i, K, C) + i);
		printf("Case #%d: %d\n", ++ caseCnt, ans);
	}
	return 0;
}
