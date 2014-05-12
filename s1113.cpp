#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>

typedef long long ll;

const int MaxN = 200010, inf = ~0u >> 1;

struct Node {
	int ky;
	Node *s[2];
}*root, nil[MaxN], *tot;

std::pair<int, int> a[MaxN];
int N, C, F, ans = -1;
ll l[MaxN], r[MaxN];

Node *merge(Node *a, Node *b) {
	if (!a || !b) {
		return a ? a : b;
	}
	if (a->ky < b->ky) {
		return merge(b, a);
	}
	int p = rand() & 1;
	return a->s[p] = merge(a->s[p], b), a;
}

int getMax(Node *root) {
	if (root) {
		return root->ky;
	}
	return 0;
}

int extract(Node *&root) {
	if (root) {
		int ret = root->ky;
		root = merge(root->s[0], root->s[1]);
		return ret;
	}
	return 0;
}

int main() {
	scanf("%d%d%d", &C, &N, &F);
	for(int i = 1; i <= N; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		l[i] = r[i] = inf;
	}
	std::sort(a + 1, a + 1 + N);
	//puts("init done");
	root = 0;
	tot = nil;
	for(int i = 1; i <= N; ++i) {
		static ll s = 0;
		static int cnt = 0;
		if(cnt == C / 2) {
			if(a[i].second < getMax(root)) {
				s += a[i].second - extract(root);
				tot->ky = a[i].second;
				root = merge(root, tot++);
			}
		}
		else {
			s += a[i].second;
			tot->ky = a[i].second;
			root = merge(root, tot++);
			++cnt;
		}
		if(cnt == C / 2) { 
			l[i] = s;
			//printf("%d: %lld\n", i, l[i]);
		}
	}
	//puts("l done");
	root = NULL;
	tot = nil;
	memset(nil, 0, sizeof nil);
	for(int i = N; i >= 1; --i) {
		static ll s = 0;
		static int cnt = 0;
		if(cnt == C / 2) {
			if(a[i].second < getMax(root)) {
				s -= extract(root);
				s += a[i].second;
				tot->ky = a[i].second;
				root = merge(root, tot++);
			}
		}
		else {
			s += a[i].second;
			tot->ky = a[i].second;
			root = merge(root, tot++);
			++cnt;
		}
		if(cnt == C / 2) {
			r[i] = s;
			//printf("%d: %lld\n", i, r[i]);
		}
	}
	//puts("r done");
	for(int i = N - 1; i > 1; --i) {
		//printf("%d: %lld %lld %d\n", i, l[i - 1], r[i + 1], a[i].second);
		if(l[i - 1] + r[i + 1] + a[i].second <= F) {
			printf("%d\n", a[i].first);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
