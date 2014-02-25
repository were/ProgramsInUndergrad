#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
int N, ans, a[1000], b[1000];
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i)
		scanf("%d", a + i);
	for(int i = 0;i < N;++ i)
		scanf("%d", b + i);
	std :: sort(a, a + N);
	std :: sort(b, b + N);
	for(int i = 0;i < N;++ i)
		ans += abs(a[i] - b[i]);
	printf("%d\n", ans);
	return 0;
}
