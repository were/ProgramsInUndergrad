//
//  main.cpp
//  sgu172
//
//  Created by were on 2014/03/30.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstdlib>

const int MaxN = 201;

int N, M, dep[MaxN], ans;

struct Node{
	int v;
	Node *nxt;
	Node(int v, Node *nxt) : v(v), nxt(nxt) {}
}*g[MaxN];

void dfs(int x, int d){
	dep[x] = d;
	if(d % 2 == 0)
		++ans;
	for(Node *cur = g[x];cur;cur = cur->nxt){
		if(!dep[cur->v]){
			dfs(cur->v, d + 1);
		}else{
			if(dep[cur->v] % 2 == d % 2){
				puts("no");
				exit(0);
			}
		}
	}
}

int main(int argc, const char * argv[])
{
	scanf("%d%d", &N, &M);
	for(int i = 0;i < M;++i){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u] = new Node(v, g[u]);
		g[v] = new Node(u, g[v]);
	}
	for(int i = 1;i <= N;++i){
		if(!dep[i])
			dfs(i, 1);
	}
	puts("yes");
	printf("%d\n", ans);
	for(int i = 1;i <= N;++i)
		if(dep[i] % 2 == 0)
			printf("%d ", i);
    return 0;
}

