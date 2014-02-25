#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
const int MaxN = 16001, inf = int(1e9);
int N, sz[MaxN], q[MaxN], f, t, pre[MaxN], ansVal = inf;
std :: vector<int> g[MaxN], ans;
int calc(int x){
	int ret = 0;
	for(std :: vector<int> :: iterator cur = g[x].begin();cur != g[x].end();++ cur)
		if(sz[*cur] < sz[x])
			ret = std :: max(ret, sz[*cur]);
	return std :: max(N - sz[x], ret);
}
int main(){
	scanf("%d", &N);
	for(int i = 1, u, v;i < N;++ i){
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	pre[1] = -1;
	sz[1] = 1;
	for(q[t ++] = 1;f < t;++ f)
		for(std :: vector<int> :: iterator cur = g[q[f]].begin();cur != g[q[f]].end();++ cur) if(!pre[*cur]){
			pre[*cur] = q[f];
			q[t ++] = *cur;
		}
	for(int i = N - 1;i > 0;-- i)
		sz[pre[q[i]]] += ++ sz[q[i]];
	for(int i = 1;i <= N;++ i)
		ansVal = std :: min(ansVal, calc(i));
	for(int i = 1;i <= N;++ i)
		if(calc(i) == ansVal)
			ans.push_back(i);
	printf("%d %u\n", ansVal, ans.size());
	for(unsigned i = 0;i < ans.size();++ i)
		printf(i == ans.size() - 1 ? "%d\n" : "%d ", ans[i]);
	return 0;
}
