#include <iostream>
#include <cstdio>
const int MaxN = 444;
typedef long long ll;
int N, M, a[MaxN][MaxN];
ll s[MaxN][MaxN], ans[2];
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++ i)
		for(int j = 1;j <= N;++ j){
			scanf("%d", a[i] + j);
			s[i][j] = s[i - 1][j] + s[i][j - 1] + a[i][j] - s[i - 1][j - 1];
		}
	for(int i = 1;i <= N;++ i)
		for(int j = i;j <= N;++ j){
			ll cnt[2] = {1ll, 0ll};
			for(int k = 1;k <= N;++ k){
				ll sgm = s[j][k] - s[i - 1][k];
				ans[0] += cnt[sgm & 1];
				ans[1] += cnt[~sgm & 1];
				++ cnt[sgm & 1];
			}
		}
	std :: cout << ans[1] << " " << ans[0] << "\n";
	return 0;
}
