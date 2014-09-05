#include <algorithm>
#include <iostream>
#include <cstdlib>

using namespace std;

const int MaxN = 100010;

struct Node {
	int sz, v, sum, pri, rev;
	Node *l, *r;
	void rz() {
		sz = l->sz + 1 + r->sz;
		sum = l->sum + v + r->sum;
	}
	void push() {
		if(rev) {
			l->rev ^= 1;
			r->rev ^= 1;
			swap(l, r);
			rev = 0;
		}
	}
}nil[MaxN], *root;

Node *newNode() {
	static Node *tot = nil;
	++tot;
	tot->l = tot->r = nil;
	tot->sz = tot->v = tot->sum = 1;
	tot->pri = rand();
	tot->rev = 0;
	return tot;
}

Node *merge(Node *l, Node *r) {
	if(l == nil || r == nil) {
		return l - nil + r;
	}
	l->push();
	r->push();
	if(l->pri > r->pri){
		l->r = merge(l->r, r);
		return l->rz(), l;
	}else{
		r->l = merge(l, r->l);
		return r->rz(), r;
	}
}

Node *cut(Node *&cur, int k) {
	if(cur == nil) {
		return nil;
	}
	cur->push();
	Node *res = nil;
	if(k > cur->l->sz + 1) {
		res = cur;
		Node *tmp = cut(cur->r, k - cur->l->sz - 1);
		cur = cur->r;
		res->r = tmp;
		res->rz();
	} else {
		res = cut(cur->l, k);
		cur->rz();
	}
	return res;
}

Node *build(int l, int r) {
	int m = (l + r) / 2;
	return l == r ? newNode() : merge(build(l, m), build(m + 1, r));
}

int select(Node *cur, int k) {
	for(cur->push(); k != cur->l->sz + 1; cur->push()) {
		if(k > cur->l->sz + 1) {
			k -= cur->l->sz + 1;
			cur = cur->r;
		} else {
			cur = cur->l;
		}
	}
	return cur->v;
}

void add(Node *cur, int k, int delta) {
	cur->push();
	if(k == cur->l->sz + 1) {
		cur->v += delta;
	} else {
		if(k > cur->l->sz + 1) {
			add(cur->r, k - cur->l->sz - 1, delta);
		} else {
			add(cur->l, k, delta);
		}
	}
	cur->rz();
}

int N, Q;

int main() {
	cin >> N >> Q;
	root = build(1, N);
	while(Q--) {
		int op;
		cin >> op;
		if(op == 1) {
			int p;
			cin >> p;
			++p;
			Node *tmp = cut(root, p);
			tmp->rev ^= 1;
			if(tmp->sz > root->sz) {
				swap(tmp, root);
			}
			for(int i = 1; i <= tmp->sz; ++i) {
				add(root, i, select(tmp, i));
			}
		} else {
			int l, r;
			cin >> l >> r;
			Node *left = cut(root, l + 1);
			Node *mid = cut(root, r - l + 1);
			cout << mid->sum << endl;
			root = merge(left, merge(mid, root));
		}
	}
	return 0;
}

