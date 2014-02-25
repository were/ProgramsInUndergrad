#include <cstdio>
const int MaxN = 333, Inf = int(1e9);
int N, M, S, T, u, v, w, f, t, dis[MaxN], q[MaxN], r[MaxN], tB[MaxN], tP[MaxN], pre[MaxN];
char c[MaxN];
bool hsh[MaxN];
struct Edge{
	int v, w;
	Edge* nxt;
	Edge(int v, int w, Edge* nxt) : v(v), w(w), nxt(nxt) {}
}*g[MaxN];
char calcColor(int v, int cur){
	if(cur < r[v])
		return c[v];
	cur = (cur - r[v]) % (tB[v] + tP[v]);
	return c[v] == 'B' ? "BP"[cur < tP[v]] : "PB"[cur < tB[v]];
}
int calcAlter(int v, int cur){
	if(cur < r[v])
		return r[v];
	int tmp = (cur - r[v]) % (tB[v] + tP[v]), half = c[v] == 'B' ? tP[v] : tB[v];
	return tmp < half ? cur + half - tmp : cur + tB[v] + tP[v] - tmp;
}
int calcPass(int u, int v, int cur){
	if(calcColor(u, cur) == calcColor(v, cur))
		return cur;
	int a = cur, b = cur;
	for(int i = 0;i < 3; ++i){
		a = calcAlter(u, a);
		b = calcAlter(v, b);
		if(a != b)
			return a < b ? a : b;
	}
	return Inf;
}
void findPath(int v){
	if(v != S)
		findPath(pre[v]);
	printf(v == T ? "%d\n" : "%d ", v);
}
int main(){
	scanf("%d%d%d%d", &S, &T, &N, &M);
	for(int i = 1;i <= N; ++i){
		scanf(" %c%d%d%d", c + i, r + i, tB + i, tP + i);
		dis[i] = Inf;
	}
	for(int i = 0;i < M; ++i){
		scanf("%d%d%d", &u, &v, &w);
		g[u] = new Edge(v, w, g[u]);
		g[v] = new Edge(u, w, g[v]);
	}
	for(dis[S] = 0, hsh[S] = true, q[t++] = S;f != t;hsh[q[f]] = false, f = (f + 1) % (N + 1)){
		for(Edge* cur = g[q[f]];cur;cur = cur->nxt){
			int pass = calcPass(q[f], cur->v, dis[q[f]]);
			if(pass + cur->w < dis[cur->v]){
				dis[cur->v] = pass + cur->w;
				pre[cur->v] = q[f];
				if(!hsh[cur->v]){
					hsh[q[t] = cur->v] = true;
					t = (t + 1) % (N + 1);
				}
			}
		}
	}
	if(dis[T] != Inf){
		printf("%d\n", dis[T]);
		findPath(T);
	}else
		puts("0");
	return 0;
}

