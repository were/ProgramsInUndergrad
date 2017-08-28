#include <algorithm>
#include <cstdio>
int K, N, a[8000], ans = 2, cnt = 1;
int main(){
	scanf("%d%d", &K, &N);
	for(int i = 0;i < N;++i)
		scanf("%d", a + i);
	std :: sort(a, a + N);
	for(int i = 1;i < N;++i)
		if(a[i] / 1000 != a[i - 1] / 1000){
			ans += (cnt - 1) / K + 1;
			cnt = 1;
		}else
			++cnt;
	printf("%d\n", ans + (cnt - 1) / K + 1);
	return 0;
}
