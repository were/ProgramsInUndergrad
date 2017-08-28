/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <list>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)
#define bit_up(i,f,t) for(int i(f);i<=(t);i+=i&-i)
#define bit_down(i,f) for(int i(f);i;i-=i&-i)

#define X first
#define Y second

using std :: max;
using std :: min;
using std :: swap;
using std :: lower_bound;
using std :: upper_bound;
using std :: vector;
using std :: map;
using std :: set;
using std :: priority_queue;
using std :: string;
using std :: pair;
using std :: make_pair;
using std :: less;
using std :: greater;
using std :: cin;
using std :: cout;
using std :: endl;
using std :: cerr;
using std :: clog;
using std :: ifstream;
using std :: ofstream;
using std :: queue;
using std :: stack;
using std :: deque;
using std :: list;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;
typedef vector<pii> :: iterator edge;

const int MaxN = 200010, Mod = 99990001;

struct Node{
	ll mul, add, v;
	int sz;
	Node *s[2], *p;
	Node();
	void sets(Node *, int d);
	int d();
	ll ans();
	void rz();
	void addTag(ll);
	void mulTag(ll);
	void push();
	bool root(){
		return this != p->s[0] && this != p->s[1];
	}
}nil[MaxN * 2], *dfn[MaxN * 2];

int N, u[MaxN], v[MaxN], tot, dep[MaxN];
vector<pii> g[MaxN];

Node :: Node(){
	mul = 1ll;
	add = 0ll;
	sz = (this - nil) % 2;
	s[0] = s[1] = p = nil;
}

void Node :: sets(Node *t, int d){
	push();
	if((s[d] = t) != nil)
		t->p = this;
	rz();
}

void Node :: rz(){
	sz = s[0]->sz + (this - nil) % 2 + s[1]->sz;
}

void Node :: addTag(ll x){
	(add += x) %= Mod;
}

void Node :: mulTag(ll x){
	(add *= x) %= Mod;
	(mul *= x) %= Mod;
}

ll Node :: ans(){
	return (v * mul % Mod + add) % Mod;
}

void Node :: push(){
	v = ans();
	if(mul != 1ll){
		s[0]->mulTag(mul);
		s[1]->mulTag(mul);
		mul = 1ll;
	}
	if(add != 0ll){
		s[0]->addTag(add);
		s[1]->addTag(add);
		add = 0ll;
	}
}

int Node :: d(){
	return this == p->s[1];
}

/*
    x
    |
    p
   / \
  t   *
 / \
*   *
*/
void rotate(Node *t){
	Node *p = t->p;
	if(!p->root())
		p->p->push();
	p->push();
	t->push();
	int d = t->d();
	p->sets(t->s[!d], d);
	if(p->root())
		t->p = p->p;
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

void realShow(Node *cur){
	if(cur != nil){
		realShow(cur->s[0]);
		printf("idx %d %d\n", int(cur - nil), cur->sz);
		printf("v %lld mul %lld add %lld ans %lld\n", cur->v, cur->mul, cur->add, cur->ans());
		realShow(cur->s[1]);
	}
}

Node *subtree(int x){
	splay(nil + x + x - 1, nil);
	splay(nil + x + x, nil[x + x - 1].s[1]);
	return nil + x + x - 1;
}

void dfs(int x, int depth){
	dep[x] = depth;
	dfn[++tot] = &nil[x + x - 1];
//	printf("dfs %d %lld\n", x, nil[x + x - 1].v);
	for(edge cur = g[x].begin(), end = g[x].end();cur != end;++cur){
		if(!dep[cur->X]){
			nil[cur->X * 2 - 1].v = cur->Y;
			dfs(cur->X, depth + 1);
		}
	}
	dfn[++tot] = nil + x + x;
}

Node *build(int l, int r){
	int x = (l + r) / 2;
	if(l < x)
		dfn[x]->sets(build(l, x - 1), 0);
	if(x < r)
		dfn[x]->sets(build(x + 1, r), 1);
	return dfn[x];
}

int findMin(Node *cur){
	return cur == nil ? N + 1 : min(int(cur - nil + 1) / 2, min(findMin(cur->s[0]), findMin(cur->s[1])));
}

void show(Node *cur){
	if(cur != nil){
		show(cur->s[0]);
		if((cur - nil) % 2){
			printf("idx %d\n", int(cur - nil + 1) / 2);
			printf("v %lld mul %lld add %lld ans %lld\n", cur->v, cur->mul, cur->add, cur->ans());
		}
		show(cur->s[1]);
	}
}

void tagShow(Node *cur, ll mul, ll add){
	if(cur != nil){
		mul *= cur->mul;
		add = add * cur->mul + cur->add;
		tagShow(cur->s[0], mul, add);
		if((cur - nil) % 2){
			printf("idx %d %d\n", int(cur - nil + 1) / 2, cur->sz);
			printf("mul %lld add %lld v %lld\n", mul, add, cur->v * mul + add);
		}
		tagShow(cur->s[1], mul, add);
	}
}

Node* merge(Node *a, Node *b){
	if(a == nil || b == nil)
		return a - nil + b;
	for(a->push();a->s[1] != nil;(a = a->s[1])->push());
	a->sets(b, 1);
	splay(b, nil);
	return b;
}

int main(){
//	freopen("input", "r", stdin);
//	freopen("output", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N - 1){
		int w;
		scanf("%d%d%d", u + i, v + i, &w);
		g[u[i]].push_back(pii(v[i], w));
		g[v[i]].push_back(pii(u[i], w));
	}
	dfs(1, 1);
	build(1, tot);
//rep(i, 1, tot)
//	printf("%d ", int(dfn[i] - nil));
//puts("");
	rep(i, 1, N - 1){
		int p;
		scanf("%d", &p);
		int sz1 = subtree(u[p])->s[1]->s[0]->sz + 1;
		int sz2 = subtree(v[p])->s[1]->s[0]->sz + 1;
		int x = sz1 < sz2 ? u[p] : v[p];
//printf("subtree %d\n", x);
//printf("%d: %d %d: %d\n", u[p], sz1, v[p], sz2);
		Node *root1 = subtree(x);
		Node *a = root1->s[0], *b = root1->s[1]->s[1];
//puts("root");
//show(root1);
//puts("comp");
//realShow(root1);
		root1->s[1]->sets(nil, 1);
		root1->sets(nil, 0);
		a->p = b->p = nil;
		Node *root2 = merge(a, b);
//printf("%d vs %d\n", root1->sz, root2->sz);
//puts("root1");
//show(root1);
//realShow(root1);
//puts("root2");
//show(root2);
//realShow(root2);
		ll w = root1->ans();
		printf("%lld\n", w);
		fflush(stdout);
		if(root1->sz > root2->sz || ((root1->sz == root2->sz) && (findMin(root1) > findMin(root2))))
			swap(root1, root2);
		root1->mulTag(w);
		root2->addTag(w);
//puts("root1");
//tagShow(root1, 1, 0);
//puts("");
//puts("root2");
//tagShow(root2, 1, 0);
//puts("");
	}
	return 0;
}

