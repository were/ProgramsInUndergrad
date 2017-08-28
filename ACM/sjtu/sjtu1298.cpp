#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MaxN = 500010;

int N, M, a[MaxN], l[MaxN], r[MaxN], idx, dep[MaxN], delta[MaxN * 2][2];
vector<int> g[MaxN];

void dfs(int x) {
	l[x] = ++idx;
	for(size_t i = 0; i < g[x].size(); ++i) {
		if(!l[g[x][i]]) {
			dep[g[x][i]] = dep[x] + 1;
			dfs(g[x][i]);
		}
	}
	r[x] = idx;
//printf("%d: %d, %d\n", x, l[x], r[x]);
}

int getId(int l, int r) {
	return (l + r) | (l != r);
}

void modify(int l, int r, int a, int b, int dep, int v) {
	if(b < l || a > r) {
		return;
	}
	int x = getId(l, r);
	if(a <= l && r <= b) {
//printf("%d, %d: %d, %d\n", l, r, dep, v);
		delta[x][dep] += v;
	} else {
		int m = (l + r) / 2;
		modify(l, m, a, b, dep, v);
		modify(m + 1, r, a, b, dep, v);
	}
}

int query(int l, int r, int pos, int dep) {
	if(pos < l || pos > r) {
		return 0;
	}
	int x = getId(l, r), m = (l + r) / 2;
	if(l == r) {
//printf("delta %d %d\n", delta[x][dep], delta[x][1 - dep]);
		return delta[x][dep] - delta[x][1 - dep];
	} else {
//printf("delta %d %d\n", delta[x][dep], delta[x][1 - dep]);
		return query(l, m, pos, dep) + query(m + 1, r, pos, dep) + delta[x][dep] - delta[x][1 - dep];
	}
}

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		scanf("%d", a + i);
	}
	for(int i = 1, u, v; i < N; ++i) {
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dep[1] = 1;
	dfs(1);
//for(int i = 1; i <= N; ++i) printf("%d: %d\n", i, dep[i]);
	while(M--) {
		int op, x;
		scanf("%d%d", &op, &x);
		if(op == 1) {
			int v;
			scanf("%d", &v);
//printf("dep %d: %d\n", x, dep[x] & 1);
			modify(1, N, l[x], r[x], dep[x] & 1, v);
		} else {
//printf("dep %d: %d\n", x, dep[x] & 1);
			printf("%d\n", query(1, N, l[x], dep[x] & 1) + a[x]);
		}
	}
	return 0;
}
