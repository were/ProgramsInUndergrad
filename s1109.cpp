#include <algorithm>
#include <cstdio>
#include <utility>
const int MaxN = 100000;
int N;
std :: pair<int, std :: pair<int, int> > a[MaxN];
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i){
		scanf("%d%d", &a[i].first, &a[i].second.first);
		a[i].second.second = i;
		int j = i;
		while(j > 0 && a[j] > a[j - 1] && a[j].second.first){
			std :: swap(a[j], a[j - 1]);
			-- j;
			-- a[j].second.first;
		}
	}
	for(int i = 0;i < N;++ i)
		printf(i == N - 1 ? "%d\n" : "%d ", a[i].second.second + 1);
	return 0;
}
