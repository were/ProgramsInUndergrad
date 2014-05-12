#include <algorithm>
#include <cstdio>
#include <cstdlib>

const int MaxN = 100010;
typedef long long ll;

struct Node {
	Node *s[2];
	ll ky;
}nil[MaxN * 5], *root, *tot = nil;

Node *merge(Node *l, Node *r) {
	if(!l || !r) {
		return l ? l : r;
	}
	if(l->ky > r->ky) {
		std::swap(l, r);
	}
	int p = rand() & 1;
	return l->s[p] = merge(l->s[p], r), l;
}

ll extract(Node *&root) {
	ll ret = root->ky;
	root = merge(root->s[0], root->s[1]);
	return ret;
}

int N, M, sz;
ll ans;

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		int x;
		scanf("%d", &x);
		tot->ky = x;
		root = merge(root, tot++);
	}
	while((N - 1) % (M - 1)) {
		++N;
		root = merge(root, tot++);
	}
	sz = N;
	while(sz != 1) {
		ll s = 0;
		for(int j = 1; j <= M; ++j) {
			s += extract(root);
			--sz;
		}
		ans += s;
		++sz;
		tot->ky = s;
		root = merge(root, tot++);
	}
	printf("%lld\n", ans);
	return 0;
}
