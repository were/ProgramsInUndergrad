#include <algorithm>
#include <cstdio>
#define min(a,b) ((a)<(b)?(a):(b))
const int MaxN = 10001, Inf = int(1e9);
int N, a[MaxN], idx, pre[MaxN], ans[MaxN], opt[MaxN];
bool hsh[MaxN];
bool cmp(int a, int b){
	return a > b;
}
int main(){
	hsh[1] = true;
	for(int i = 2;i < MaxN;++i) if(!hsh[i]){
		if(!hsh[++idx])
			a[++a[0]] = i;
		for(int j = i + i;j < MaxN;j += i)
			hsh[j] = true;
	}
	scanf("%d", &N);
	for(int i = 1;i <= N;++i){
		opt[i] = Inf;
		pre[i] = -1;
	}
	for(int i = 1;i <= a[0];++i)
		for(int j = a[i];j <= N;++j)
			if(opt[j - a[i]] + 1 < opt[j]){
				pre[j] = j - a[i];
				opt[j] = opt[j - a[i]] + 1;
			}
	if(opt[N] != Inf){
		for(int n = N;n;n = pre[n])
			ans[++ans[0]] = n - pre[n];
		printf("%d\n", ans[0]);
		std :: sort(ans + 1, ans + 1 + ans[0], cmp);
		for(int i = 1;i <= ans[0];++i)
			printf(i==ans[0] ? "%d\n" : "%d ", ans[i]);
	}else
		puts("0");
	return 0;
}
