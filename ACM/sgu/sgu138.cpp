#include <algorithm>
#include <cstdio>
#include <functional>
#include <utility>
#include <vector>
const int MaxN = 100;
int N, sum;
std :: pair<int, int> a[MaxN];
std :: vector<int> win, lose;
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i){
		scanf("%d", &a[i].first);
		sum += a[i].first;
		a[i].second = i + 1;
	}
	sum /= 2;
	std :: sort(a, a + N, std :: greater< std :: pair<int, int> >());
	for(int i = 0, j = 0;i < sum;++ i){
		win.push_back(0);
		lose.push_back(0);
		if(a[j].first == 1){
			lose[i] = a[j].second;
			-- a[j ++].first;
		}
		win[i] = a[j].second;
		-- a[j].first;
	}
	for(int i = 0, j = 0;i < sum;++ i) if(lose[i] == 0){
		while(a[j].first == 0 && j < N)
			++ j;
		lose[i] = a[j].second;
		-- a[j].first;
	}
	printf("%d\n", sum);
	for(int i = 0;i < sum;++ i)
		printf("%d %d\n", win[i], lose[i]);
	return 0;
}
