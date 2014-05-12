#include <algorithm>
#include <cstdio>
#define rep(i,f,t) for(int i(f);i<=(t);++i)

const int MaxN = 500010;

struct Node {
	int ky, sz;
	Node *s[2];
	void rz() {
		sz = s[0]->sz + 1 + s[1]->sz;
	}
}nil[MaxN * 2], *root;

int N, M, fa[MaxN], sz[MaxN];

int getfa(int x) {
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

Node *newNode(int ky) {
	static Node *tot = nil;
	++tot;
	tot->ky = ky;
	tot->sz = 1;
	tot->s[0] = tot->s[1] = nil;
	return tot;
}

void rotate(Node *&cur, int d) {
	Node *tmp = cur->s[d];
	cur->s[d] = tmp->s[!d];
	tmp->s[!d] = cur;
	cur->rz();
	tmp->rz();
	cur = tmp;
}

void maintain(Node *&cur, int d) {
	if(cur->s[d]->s[d]->sz > cur->s[!d]->sz) {
		rotate(cur, d);
	}
	else {
		if(cur->s[d]->s[!d]->sz > cur->s[!d]->sz) {
			rotate(cur->s[d], !d);
			rotate(cur, d);
		}
	}
}

void insert(Node *&cur, int ky) {
	if(cur == nil) {
		cur = newNode(ky);
	}
	else {
		int d = ky > cur->ky;
		insert(cur->s[d], ky);
		cur->rz();
		maintain(cur, d);
	}
}

void erase(Node *&cur, int ky) {
	int d = ky > cur->ky;
	if(ky == cur->ky) {
		if(cur->s[0] == nil || cur->s[1] == nil) {
			cur = cur->s[0] - nil + cur->s[1];
			return;
		}
		Node *tmp = cur->s[1];
		while(tmp->s[0] != nil) {
			tmp = tmp->s[0];
		}
		cur->ky = tmp->ky;
		erase(cur->s[1], tmp->ky);
		d = 1;
	}
	else {
		erase(cur->s[d], ky);
	}
	cur->rz();
	maintain(cur, !d);
}

int rank(int k) {
	if(k > root->sz) {
		return 0;
	}
	k = root->sz - k + 1;
	Node *cur = root;
	while(cur->s[0]->sz + 1 != k) {
		if(k > cur->s[0]->sz + 1) {
			k -= cur->s[0]->sz + 1;
			cur = cur->s[1];
		}
		else {
			cur = cur->s[0];
		}
	}
	return cur->ky;
}

int main() {
	root = nil->s[0] = nil->s[1] = nil;
	scanf("%d%d", &N, &M);
	rep(i, 1, N) {
		fa[i] = i;
		sz[i] = 1;
		insert(root, 1);
	}
	while(M--) {
		char op[5];
		int x, y;
		scanf("%s", op);
		if(*op == 'C') {
			scanf("%d%d", &x, &y);
			x = getfa(x);
			y = getfa(y);
			if(x != y && sz[x] && sz[y]) {
				erase(root, sz[x]);
				erase(root, sz[y]);
				sz[y] += sz[x];
				sz[x] = 0;
				insert(root, sz[y]);
				fa[x] = y;
			}
		}
		if(*op == 'D') {
			scanf("%d", &x);
			x = getfa(x);
			if(sz[x]) {
				erase(root, sz[x]);
				sz[x] = 0;
			}
		}
		if(*op == 'Q') {
			scanf("%d", &x);
			printf("%d\n", rank(x));
		}
	}
	return 0;
}
