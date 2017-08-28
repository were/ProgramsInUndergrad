#include <algorithm>
#include <cstdio>
#include <iostream>
#define sum(l,r) (s[r]-s[l-1])
#define mid ((l+r)/2)
#define len(l,r) ((r)-(l)+1)
#define debug(x) std :: cout << #x << " = " << (x) << std :: endl
const int MaxN = 2222, INF = 1e9;
int N, P, a[MaxN], f[MaxN][MaxN], s[MaxN], pre[MaxN][MaxN];
int calc(int l, int r){
	return a[mid] * len(l, mid - 1) - sum(l, mid - 1) + sum(mid + 1, r) - a[mid] * len(mid + 1, r);
}
int main(){
	scanf("%d%d", &N, &P);
	for(int i = 1;i <= N;++ i){
		scanf("%d", a + i);
		s[i] = s[i - 1] + a[i];
		for(int j = 1;j <= P;++ j)
			f[i][j] = INF;
	}
	for(int i = 1;i <= N;++ i){
		f[i][1] = calc(1, i);
		for(int j = 2;j <= std :: min(P, i);++ j){
			for(int k = pre[i][j - 1] ? pre[i][j - 1] : 1;k < i;++ k){
				if(f[i][j] > f[k][j - 1] + calc(k + 1, i)){
					f[i][j] = f[k][j - 1] + calc(k + 1, i);
					pre[i][j] = k;
				}
			}
		}
	}
	printf("%d\n", f[N][P]);
	return 0;
}
