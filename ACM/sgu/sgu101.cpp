#include <cstdio>
struct __node{
	int v, idx;
	__node*nxt;
	__node(int v, int idx, __node*nxt) : v(v), idx(idx), nxt(nxt) {}
}*g[11];
int N, a[111], b[111], d[11], cnt[2], hsh[111], ans[111], top, tot;
int abs(int x){
	return x < 0 ? -x : x;
}
void dfs(int x){
	for(__node*cur = g[x];cur;cur = cur->nxt) if(!hsh[abs(cur->idx)]){
		hsh[abs(cur->idx)] = 1;
		dfs(cur->v);
	}
	ans[tot ++] = x;
}
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++ i){
		scanf("%d%d", a + i, b + i);
		g[a[i]] = new __node(b[i], i, g[a[i]]);
		g[b[i]] = new __node(a[i],-i, g[b[i]]);
		++ d[a[i]];
		++ d[b[i]];
	}
	for(int i = 0;i < 7;++ i)
		++ cnt[d[i] & 1];
	if(cnt[1] == 2 || cnt[1] == 0){
		if(cnt[1] == 2){
			for(int i = 0;i < 7;++ i) if(d[i] & 1){
				dfs(i);
				break;
			}
		}else
			for(int i = 0;i < 7;++ i) if(d[i]){
				dfs(i);
				break;
			}
		for(int i = 1;i <= N;++ i)
			hsh[i] = 0;
		if(tot - 1 == N){
			for(int i = 1;i < tot;++ i)
				for(int j = 1;j <= N;++ j) if(!hsh[j]){
					if(a[j] == ans[i-1] && b[j] == ans[i]){
						printf("%d +\n", j);
						hsh[j] = 1;
						break;
					}
					if(b[j] == ans[i-1] && a[j] == ans[i]){
						printf("%d -\n", j);
						hsh[j] = 1;
						break;
					}
				}
		}else
			puts("No solution");
	}else
		puts("No solution");
	return 0;
}
