//
//  main.cpp
//  s1108
//
//  Created by were on 2014/04/14.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>

int g[111][111];

int main(int argc, const char * argv[]) {
	int N;
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			g[i][j] = int(1e8);
		}
	}
	for (int i = 1; i < N; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		g[u][v] = g[v][u] = w;
	}
	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (g[i][k] + g[k][j] < g[i][j]) {
					g[i][j] = g[i][k] + g[k][j];
				}
			}
		}
	}
	int M;
	scanf("%d", &M);
	while (M--) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%d\n", g[u][v]);
	}
    return 0;
}

