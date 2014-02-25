/*
Programmed by wereFluke
*/
#include <cstdio>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

const int MaxN = 1000010;

int Q, N = 4, S, T, ans;
struct Node{
	int v;
	Node*nxt;
}buf[MaxN], *g[MaxN];

void add(int u, int v){
	static Node*tot = buf;
	++ tot;
	tot->v = v;
	tot->nxt = g[u];
	g[u] = tot;
}

/*lca-seg-template*/
bool hsh[MaxN];
int dep[MaxN], pre[MaxN], hd[MaxN], nxt[MaxN], sz[MaxN];
int q[MaxN], f, t;
void lcaInit(){
	pre[1] = 0;
	dep[1] = 1;
//bfs
	q[t ++] = 1;
	while(f < t){
		for(Node*cur = g[q[f]];cur;cur = cur->nxt){
			q[t ++] = cur->v;
			pre[cur->v] = q[f];
			dep[cur->v] = dep[q[f]] + 1;
		}
		++ f;
	}
	per(i, N - 1, 0){
		sz[pre[q[i]]] += ++ sz[q[i]];
		if(sz[nxt[pre[q[i]]]] < sz[q[i]])
			nxt[pre[q[i]]] = q[i];
	}
//bfs-end
	rep(i, 0, N - 1)
		if(!hd[q[i]]){
			for(int j = q[i];j;j = nxt[j])
				hd[j] = q[i];
		}
//rep(i, 1, N)
//	printf("%d %d\n", i, hd[i]);
}
int query(int a, int b){
//printf("[%d, %d]\n", a, b);
	while(hd[a] != hd[b]){
		int &x = (dep[hd[a]] < dep[hd[b]]) ? b : a;
//printf("%d %d %d\n", a, b, x);
		x = pre[hd[x]];
	}
	return dep[a] < dep[b] ? a : b;
}
/*lca-seg-template-end*/

int dis(int u, int v){
//printf("%d %d %d\n", u, v, query(u, v));
	return dep[u] + dep[v] - dep[query(u, v)] * 2;
}

int main(){
	add(1, 2);
	add(1, 3);
	add(1, 4);
	S = 2;
	T = 4;
	ans = 2;
	scanf("%d", &Q);
	while(Q --){
		int v;
		scanf("%d", &v);
		add(v, ++ N);
		add(v, ++ N);
	}
	lcaInit();
	for(int i = 5;i <= N;i += 2){
		int tmp = dis(S, i);
		if(tmp > ans){
			T = i;
			ans = tmp;
		}else{
			tmp = dis(T, i);
			if(tmp > ans){
				S = i;
				ans = tmp;
			}
		}
//printf("[%d\n", i);
		printf("%d\n", ans);
	}
	return 0;
}

