#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

const int MaxN = 100010;

int N, n;
LL K, a[MaxN], s[MaxN], l = LL(-1e15), r = LL(1e15);

struct Node {
	LL ky;
	int sz;
	Node *s[2];
	void rz() {
		sz = s[0]->sz + 1 + s[1]->sz;
	}
}nil[MaxN], *root, *tot;

Node *newNode(LL ky) {
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
	tmp->sz = cur->sz;
	cur->rz();
	cur = tmp;
}

void maintain(Node *&cur, int d) {
	if(cur->s[d]->s[d]->sz > cur->s[!d]->sz) {
		rotate(cur, d);
	} else {
		if(cur->s[d]->s[!d]->sz > cur->s[!d]->sz) {
			rotate(cur->s[d], !d);
			rotate(cur, d);
		}
	}
}

void insert(LL ky, Node *&cur) {
	if(cur == nil) {
		cur = newNode(ky);
	} else {
		int d = ky > cur->ky;
		insert(ky, cur->s[d]);
		cur->rz();
		maintain(cur, d);
	}
}

LL calc(LL m) {
	tot = root = nil;
	insert(0LL, root);
	LL ret = 0ll;
	for(int i = 1; i <= N; ++i) {
		Node *cur = root;
		while(cur != nil) {
			if(s[i] - cur->ky >= m) {
				ret += cur->s[0]->sz + 1;
				cur = cur->s[1];
			} else {
				cur = cur->s[0];
			}
		}
		insert(s[i], root);
	}
	return ret;
}

int main() {
	cin >> N >> K;
	for(int i = 1; i <= N; ++i) {
		cin >> a[i];
		a[i] += a[i - 1];
		s[i] = a[i];
	}
	sort(a + 1, a + 1 + N);
	n = unique(a + 1, a + 1 + N) - a - 1;
	while(r - l > 1) {
		LL m = (l + r) / 2;
		if(calc(m) < K) {
			r = m;
		} else {
			l = m;
		}
	}
	cout << l << endl;
	return 0;
}
