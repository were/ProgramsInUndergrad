//
//  main.cpp
//  s1046
//
//  Created by were on 2014/04/14.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstdlib>

const int MaxN = 100010;

int N, P, Q, l[MaxN], r[MaxN], sz[MaxN], dfn[MaxN], root, tot;
int rnk[MaxN], sum[MaxN], curRnk, pos[MaxN];
bool hsh[MaxN];

void dfs(int x) {
	if (x) {
		dfn[x] = ++tot;
		sz[x] = 1;
		dfs(l[x]);
		rnk[x] = ++curRnk;
		pos[curRnk] = x;
		dfs(r[x]);
		sz[x] = sz[l[x]] + 1 + sz[r[x]];
	}
}

int main(int argc, const char * argv[])
{
	scanf("%d%d%d", &N, &P, &Q);
	for (int i = 1; i <= N; ++i) {
		int x;
		scanf("%d", &x);
		scanf("%d%d", l + x, r + x);
		hsh[l[x]] = hsh[r[x]] = true;
	}
	for (int i = 1; i <= N; ++i) {
		if (!hsh[i]) {
			root = i;
			break;
		}
	}
	dfs(root);
	while (P--) {
		int t, x;
		scanf("%d%d", &t, &x);
		sum[dfn[pos[(rnk[t] - sz[l[t]]) + (x % sz[t])]]] = 1;
//		printf("rank %d\n", rnk[t] - sz[l[t]] + (x % sz[t]));
//		printf("add %d\n", pos[(rnk[t] - sz[l[t]]) + (x % sz[t])]);
	}
	for (int i = 1; i <= N; ++i) {
		sum[i] += sum[i - 1];
	}
	while (Q--) {
		int x;
		scanf("%d", &x);
		printf("%d\n", sum[dfn[x] + sz[x] - 1] - sum[dfn[x] - 1]);
	}
    return 0;
}

/*
     2
    / \
   3   4
  / \
 1   5
 */
