/*
PROG : rockers
ID : weng_xo2
LANG : C++11
*/
#include <algorithm>
#include <cstdio>
#include <map>
using std :: max;
using std :: map;
map<int, int> h;
int N, T, M, a[20], ans;
int check(int x){
	int ret = 0;
	for(int m = M, t = T;x && m;){
		if(a[h[x & -x]] > t){
			t = T;
			--m;
		}else{
			t -= a[h[x & -x]];
			x -= x & -x;
			++ret;
		}
	}
	return ret;
}
int main(){
	freopen("rockers.in", "r", stdin);
	freopen("rockers.out", "w", stdout);
	scanf("%d%d%d", &N, &T, &M);
	for(int i = 0;i < N; ++i){
		scanf("%d", a + i);
		h[1 << i] = i;
	}
	for(int i = 0, n = 1 << N;i < n; ++i)
		ans = max(ans, check(i));
	printf("%d\n", ans);
	return 0;
}
