//
//  main.cpp
//  s1050
//
//  Created by were on 2014/04/22.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstdlib>

const int MaxN = 300010;

int N, M;

struct Node {
	int ky;
	Node *s[2];
}*root[MaxN], a[MaxN * 2], *tot = a;

Node *merge(Node *l, Node *r) {
	if (!l || !r) {
		return l ? l : r;
	}
	if (l->ky > r->ky) {
		return merge(r, l);
	}
	int p = rand() & 1;
	return l->s[p] = merge(l->s[p], r), l;
}

int extract(Node *&t) {
	if (t) {
		int ret = t->ky;
		t = merge(t->s[0], t->s[1]);
		return ret;
	}
	return -1;
}

int main(int argc, const char * argv[]) {
	scanf("%d%d", &N, &M);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &a[i].ky);
		root[i] = tot++;
	}
	while (M--) {
		int p;
		scanf("%d", &p);
		if (p == 0) {
			int a, b;
			scanf("%d%d", &a, &b);
			root[a] = merge(root[a], root[b]);
		}
		if (p == 1) {
			int a;
			scanf("%d", &a);
			printf("%d\n", extract(root[a]));
		}
		if (p == 2) {
			int a, b;
			scanf("%d%d", &a, &b);
			tot->ky = b;
			root[a] = merge(root[a], tot);
			++tot;
		}
	}
	return 0;
}

