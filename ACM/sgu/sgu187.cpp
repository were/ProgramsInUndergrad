#include <algorithm>
#include <cstdio>

using std :: swap;

const int MaxN = 130010;

struct Node{
	Node *s[2], *p;
	int sz, rev;
	void sets(Node *, int);
	int d(){
		return this == p->s[1];
	}
	void rz(){
		sz = s[0]->sz + 1 + s[1]->sz;
	}
	void push(){
		if(rev){
			rev = 0;
			swap(s[0], s[1]);
			s[0]->rev ^= 1;
			s[1]->rev ^= 1;
		}
	}
	Node();
}nil[MaxN], *root;

Node :: Node(){
	s[0] = s[1] = p = nil;
	sz = this != nil;
	rev = false;
}

void Node :: sets(Node *t, int d){
	if((s[d] = t) != nil)
		s[d]->p = this;
	rz();
}

void rotate(Node *t){
	Node *p = t->p;
	int d = t->d();
	p->sets(t->s[!d], d);
	if(t->p == root)
		(root = t)->p = nil;
	else
		p->p->sets(t, p->d());
	t->sets(p, !d);
}

void splay(Node *t, Node *o){
	for(o = o->p;t->p != o;rotate(t)){
		if(t->p->p != o)
			rotate(t->d() == t->p->d() ? t->p : t);
	}
}

Node *findNode(int ky){
	Node *cur = root;
	while(ky != cur->s[0]->sz + 1)
		if(ky < cur->s[0]->sz + 1)
			(cur = cur->s[0])->push();
		else{
			ky -= cur->s[0]->sz + 1;
			(cur = cur->s[1])->push();
		}
	return cur;
}

Node *findRange(int l, int r){
	splay(findNode(l), root);
	splay(findNode(r + 2), root->s[1]);
	return root->s[1]->s[0];
}

Node *build(int l, int r){
	if(l == r)
		return nil + l;
	int mid = (l + r) / 2;
	if(l < mid)
		nil[mid].sets(build(l, mid - 1), 0);
	if(mid < r)
		nil[mid].sets(build(mid + 1, r), 1);
	return nil + mid;
}

int N, M, l, r, cnt;

void show(Node *t){
	if(t != nil){
		t->push();
		show(t->s[0]);
		printf(++cnt == N ? "%d\n" : "%d ", t - nil - 1);
		show(t->s[1]);
	}
}

int main(){
	scanf("%d%d", &N, &M);
	root = build(1, N + 2);
	while(M--){
		scanf("%d%d", &l, &r);
		findRange(l, r)->rev ^= 1;
	}
	show(findRange(1, N));
	return 0;
}
