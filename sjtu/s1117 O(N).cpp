//
//  main.cpp
//  s1117-N
//
//  Created by were on 2014/04/14.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#define max(a,b) ((a)>(b)?(a):(b))

const int MaxN = 100010;

struct Edge{
	int v;
	Edge *nxt;
	Edge(int v, Edge *nxt) : v(v), nxt(nxt) {}
	Edge() {}
}*g[MaxN], nil[MaxN * 2];

int N, deg[MaxN], st[MaxN], top, ans[MaxN];
char s[MaxN * 10];
bool hsh[MaxN];

void add(int u, int v){
	static Edge *tot = nil;
	++tot; tot->v = v; tot->nxt = g[u]; g[u] = tot;
	++tot; tot->v = u; tot->nxt = g[v]; g[v] = tot;
	++deg[u];
	++deg[v];
}

int getAns(int x) {
	for (Edge *cur = g[x]; cur; cur = cur->nxt) {
		if (!hsh[cur->v]) {
			return cur->v;
		}
	}
	return -1;
}

int main(int argc, const char * argv[]) {
	gets(s);
	for (int i = 0; s[i]; ++i) {
		if (s[i] >= '0' && s[i] <= '9') {
			int x = 0;
			while (s[i] >= '0' && s[i] <= '9') {
				x = x * 10 + s[i++] - '0';
			}
			--i;
			N = max(N, x);
			if (top) {
				add(st[top], x);
			}
			st[++top] = x;
		}
		else {
			if (s[i] == ')') {
				--top;
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		static int cnt = 0;
		int x = i;
		while (deg[x] == 1 && x <= i) {
			hsh[x] = true;
			printf(++cnt == N - 1 ? "%d\n" : "%d ", x = getAns(x));
			--deg[x];
		}
	}
    return 0;
}
