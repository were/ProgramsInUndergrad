#include <algorithm>
#include <cstdio>
#include <utility>
const int MaxN = 16001, inf = 2000000000;
int N, R, ans;
std :: pair<int, int> a[MaxN];
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i)
		scanf("%d%d", &a[i].first, &a[i].second);
	a[N] = std :: make_pair(inf + 1, inf + 2);
	std :: sort(a, a + N);
	for(int r = 1, l = 0;r <= N;++ r)
		if(a[r].first != a[r - 1].first){
			for(int i = l;i < r;++ i)
				if(R > a[i].second)
					++ ans;
			for(int i = l;i < r;++ i)
				R = std :: max(R, a[i].second);
			l = r;
		}
	printf("%d\n", ans);
	return 0;
}
