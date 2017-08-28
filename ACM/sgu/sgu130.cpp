#include <cstdio>
int k;
long long f[100];
int main(){
	scanf("%d", &k);
	f[0] = 1;
	for(int i = 1;i <= k;++ i)
		for(int a = 0, b = i - 1;b != -1;++ a, -- b)
			f[i] += f[a] * f[b];
	printf("%lld %d\n", f[k], k + 1);
	return 0;
}
