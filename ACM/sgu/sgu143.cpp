#include <algorithm>
#include <cstdio>
const int MaxN = 16001, inf = ~0u >> 1;
int N, f[MaxN], w[MaxN], ans = -inf;
bool hsh[MaxN];
struct Node{
	int v;
	Node*nxt;
	Node(int v, Node*nxt) : v(v), nxt(nxt) {}
}*g[MaxN];
void dfs(int x){
	hsh[x] = true;
	f[x] = w[x];
	for(Node*cur = g[x];cur;cur = cur->nxt)
		if(!hsh[cur->v]){
			dfs(cur->v);
			if(f[cur->v] > 0){
				f[x] += f[cur->v];
//				printf("%d %d\n", x, cur->v);
			}
		}
	ans = std :: max(ans, f[x]);
//	printf("%d, %d\n", x, f[x]);
}
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++ i)
		scanf("%d", w + i);
	for(int i = 1, u, v;i < N;++ i){
		scanf("%d%d", &u, &v);
		g[u] = new Node(v, g[u]);
		g[v] = new Node(u, g[v]);
	}
	dfs(1);
	printf("%d\n", ans);
	return 0;
}
