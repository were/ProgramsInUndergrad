#include <cstdio>
#include <vector>
const int MaxN = 111;
int N, x, color[MaxN][MaxN];
unsigned cnt[MaxN];
std :: vector<int> g[MaxN];
void dfs(int x, int c){
	for(std :: vector<int> :: iterator cur = g[x].begin();cur != g[x].end();++cur)
		if(!color[x][*cur]){
			color[x][*cur] = color[*cur][x] = c;
			dfs(*cur, 3 - c);
			c = 3 - c;
		}
}
bool empty(int x){
	for(std :: vector<int> :: iterator cur = g[x].begin();cur != g[x].end();++cur)
		if(!color[x][*cur])
			return false;
	return true;
}
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++i)
		while(scanf("%d", &x), x)
			g[i].push_back(x);
	for(int i = 1;i <= N;++i)
		if(!empty(i) && g[i].size() % 2u == 1u)
			dfs(i, 1);
	for(int i = 1;i <= N;++i)
		if(!empty(i))
			dfs(i, 1);
	for(int i = 1;i <= N;++i){
		for(std :: vector<int> :: iterator cur = g[i].begin();cur != g[i].end();++cur)
			if(color[i][*cur] == 1)
				++ cnt[i];
		if((cnt[i] == g[i].size() || cnt[i] == 0) && g[i].size() > 1u){
			puts("No solution");
			return 0;
		}
	}
	for(int i = 1;i <= N;++i){
		for(std :: vector<int> :: iterator cur = g[i].begin();cur != g[i].end();++cur)
			printf("%d ", color[i][*cur]);
		puts("0");
	}
	return 0;
}
