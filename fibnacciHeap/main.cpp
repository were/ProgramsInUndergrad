#include <algorithm>
#include <cstdio>

using std :: sort;
using std :: swap;

const int MaxN = 10000010;

struct Node{
	Node *l, *r, *p, *s;
	int deg;
	bool flag;
	int ky;
	Node();
	void isolate();
	bool isFir(){
		return this == p->s;
	}
	void addSon(Node *);
	bool single();
}nil[MaxN], *root = nil;

int a[MaxN];

bool Node :: single(){
	return (l == this && r == this) || this == nil;
}

void addLane(Node *&head, Node *cur){
	if(cur == nil)
		return;
	if(head == nil){
		head = cur;
	}else{
		(cur->r = head->r)->l = cur;
		(head->r = cur)->l = head;
	}
}

void addRoot(Node *cur){
	if(cur == nil)
		return;
	addLane(root, cur);
	if(root->ky > cur->ky)
		root = cur;
//printf("%x %x\n", cur, root);
}

Node :: Node(){
	l = r = this;
	p = s = nil;
	deg = flag = 0;
}

void Node :: isolate(){
	if(this == nil)
		return;
	l->r = r;
	r->l = l;
	if(p != nil){
		--p->deg;
		p->flag = true;
		if(isFir()){
			p->s = single() ? nil : r;
		}
	}
	l = r = this;
	flag = false;
}

void showRootList(){
	puts("root list...");
	printf("%d\n", root->ky);
	for(Node *cur = root->r;cur != root;cur = cur->r)
		printf("%d ", cur->ky);
	printf("%d\n", root->ky);
}

void Node :: addSon(Node *cur){	
//printf("%x %x\n", this->ky, cur->ky);
	if(cur == nil)
		return;
	addLane(s, cur);
	++deg;
	cur->p = this;
	cur->flag = flag = false;
}

void rebuild(Node *&root){
//puts("rebuild...");
	if(root == nil)
		return;
	static Node* hsh[25];
	for(int i = 0;i < 25;++i)
		hsh[i] = nil;
	Node *cur = root, *nxt, *tmp;
	while(!cur->single()){
		nxt = cur->r;
		cur->isolate();
		while(hsh[cur->deg] != nil){
			tmp = hsh[cur->deg];
			hsh[cur->deg] = nil;
			if(cur->ky > tmp->ky)
				swap(tmp, cur);
			cur->addSon(tmp);
		}
		hsh[cur->deg] = cur;
		cur = nxt;
	}
	while(hsh[cur->deg] != nil){
		tmp = hsh[cur->deg];
		hsh[cur->deg] = nil;
		if(cur->ky > tmp->ky)
			swap(tmp, cur);
		cur->addSon(tmp);
	}
	hsh[cur->deg] = cur;
	root = nil;
	for(int i = 0;i < 25;++i){
		if(hsh[i] != nil){
			addRoot(hsh[i]);
		}
	}
//puts("done");
}

Node *newNode(int ky){
	static Node *tot = nil;
	++tot;
	tot->ky = ky;
	tot->deg = 0;
	tot->flag = false;
	tot->l = tot->r = tot;
	tot->p = tot->s = nil;
	return tot;
}

//insert
void insert(int ky){
	Node *tmp = newNode(ky);
//printf("%x\n", tmp);
	addRoot(tmp);
}

//merge
Node* merge(Node *a, Node *b){
	if(a == nil || b == nil)
		return b - nil + a;
	if(a->ky > b->ky)
		swap(a, b);
	Node *cur = b, *nxt;
	while(!cur->single()){
		nxt = cur->r;
		cur->isolate();
		addLane(a, cur);
		cur = nxt;
	}
	addLane(a, cur);
	return a;
}

//extract
Node* extract(){
	if(root == nil)
		return nil;
	Node *ret = root, *cur = root->s, *nxt;
//showRootList();
	while(!cur->single()){
		nxt = cur->r;
		cur->isolate();
		addRoot(cur);
		cur= nxt;
	}
	addRoot(cur);
//showRootList();
	root = root->r;
	ret->isolate();
	rebuild(root);
//showRootList();
	return ret;
}

//decrease
void decrease(Node *cur, int ky){
	if(ky < cur->ky)
		ky = cur->ky;
	else
		return;
	Node *p;
	while(cur->p != nil && cur->p->flag){
		p = cur->p;
		cur->isolate();
		addRoot(cur);
		cur = p;
	}
	cur->isolate();
	addRoot(cur);
}

int main(){
freopen("input", "r", stdin);
freopen("output", "w", stdout);
	int N;
	scanf("%d", &N);
	for(int i = 1;i <= N;++i){
		scanf("%d", a + i);
		insert(a[i]);
	}
	for(int i = 1;i <= N;++i){
		int y = extract()->ky;
		printf("%d\n", y);
	}
//	puts("^_^");
	return 0;
}

