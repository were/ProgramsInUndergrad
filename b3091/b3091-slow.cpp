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

using std :: pair;
using std :: make_pair;
using std :: swap;

typedef long long ll;
typedef std :: vector<int> vi;
typedef std :: map<int, int> mii;
typedef std :: pair<int, int> pii;

const int MaxN = 50010;

struct Data{
	ll sum, isum, iisum, sz;
	Data(ll x) : sum(x), isum(x), iisum(x), sz(1) {}
	Data(ll a, ll b, ll c, ll d) : sum(a), isum(b), iisum(c), sz(d) {}
	Data() : sum(0), isum(0), iisum(0), sz(1) {}
	Data tag(ll x){
		return Data(
			sum + sz * x,
			isum + (1ll + sz) * sz / 2ll * x,
			iisum + sz * (sz + 1ll) * (2ll * sz + 1ll) / 6ll * x,
			sz
		);
	}
	inline ll getSum(){
		return isum * (sz + 1) - iisum;
	}
/*
	void show(){
		printf("%lld %lld %lld %lld\n", sum, isum, iisum, sz);
	}
*/
};

typedef pair<Data, Data> pdd;

Data operator+ (const Data &a, const Data &b){
	return Data(
		a.sum + b.sum,
		a.isum + b.isum + b.sum * a.sz,
		a.iisum + b.iisum + a.sz * 2ll * b.isum + a.sz * a.sz * b.sum,
		a.sz + b.sz
	);
}

struct Node{
	Node *s[2], *p;
	pdd data;
	bool rev;
	ll add, v;
	Node();
	pdd ans();
	void rz();
	void sets(Node *, int);
	bool d();
	void push();
	bool root();
}nil[MaxN];

Node :: Node(){
	s[0] = s[1] = p = nil;
	data = make_pair(Data(0), Data(0));
	rev = false;
	add = v = 0ll;
}

inline pdd Node :: ans(){
	if(this == nil)
		return make_pair(Data(0, 0, 0, 0), Data(0, 0, 0, 0));
	return !rev ? make_pair(data.X.tag(add), data.Y.tag(add)) : make_pair(data.Y.tag(add), data.X.tag(add));
}

inline void Node :: sets(Node *t, int d){
	(s[d] = t)->p = this;
	rz();
}

inline void Node :: rz(){
	pdd l = s[0]->ans(), r = s[1]->ans();
	data = make_pair(l.X + Data(v) + r.X, r.Y + Data(v) + l.Y);
}

inline bool Node :: d(){
	return this == p->s[1];
}

inline void Node :: push(){
	data = ans();
	if(rev){
		swap(s[0], s[1]);
		s[0]->rev ^= true;
		s[1]->rev ^= true;
		rev = false;
	}
	if(add != 0ll){
		v += add;
		s[0]->add += add;
		s[1]->add += add;
		add = 0ll;
	}
}

inline bool Node :: root(){
	return this != p->s[0] && this != p->s[1];
}

/*
    X
    |
    p
   / \
  t   *
 / \
*   *
*/

inline void rotate(Node *t){
	Node *p = t->p;
	if(!p->root())
		p->p->push();
	p->push();
	t->push();
	bool d = t->d();
	p->sets(t->s[!d], d);
	if(p->root())
		t->p = p->p;
	else
		p->p->sets(t, p->d());
	t->sets(p, !d);
}

inline void splay(Node *t){
	while(!t->root())
		if(t->p->root())
			rotate(t);
		else{
			if(t->p->d() != t->d()){
				rotate(t);
				rotate(t);
			}else{
				rotate(t->p);
				rotate(t);
			}
		}
	t->push();
}

inline Node *access(Node *t){
	Node *ret;
	for(ret = nil;t != nil;ret = t, t = t->p){
		splay(t);
		t->sets(ret, 1);
	}
	return ret;
}

inline void evert(Node *t){
	access(t);
	splay(t);
	t->rev ^= true;
	t->push();
}

inline Node *root(int x){
	access(nil + x);
	splay(nil + x);
	Node *ret;
	for((ret = nil + x)->push();ret->s[0] != nil;(ret = ret->s[0])->push());
	return ret;
}

inline void linkEdge(int u, int v){
	evert(nil + u);
	if(root(v) != nil + u){
		nil[u].p = nil + v;
		access(nil + u);
	}
}

inline void cutEdge(int u, int v){
	evert(nil + u);
	if(root(v) != nil + u)
		return;
	if(nil[v].s[0]->ans().X.sz != 1)
		return;
	nil[v].s[0]->p = nil;
	nil[v].s[0] = nil;
	nil[v].rz();
}

inline Node *chain(int u, int v){
	evert(nil + u);
	access(nil + v);
	if(root(v) != nil + u)
		return nil;
	return nil + v;
}

ll gcd(ll a, ll b){
	return b ? gcd(b, a % b) : a;
}

inline ll choice2(ll n){
	return (n - 1) * n / 2ll;
}

char inputBuffer[10000010], outputBuffer[10000010], *hd = inputBuffer, *tl = outputBuffer;

int gi(){
	while(!isdigit(*hd) && *hd != '-')
		++hd;
	if(*hd == '-'){
		++hd;
		return -gi();
	}
	int ret = *hd++ - '0';
	while(isdigit(*hd))
		ret = ret * 10 + *hd++ - '0';
	return ret;
}

void print(ll x){
	if(x > 9ll)
		print(x / 10ll);
	*tl++ = '0' + x % 10;
}

struct Edge{
	int v;
	Edge *nxt;
}edgeBuf[MaxN * 2], *g[MaxN];

inline void addEdge(int u, int v){
	static Edge *tot = edgeBuf;
	++tot;
	tot->v = v;
	tot->nxt = g[u];
	g[u] = tot;
}

int N, M, u, v, op, f, t, q[MaxN];
bool hsh[MaxN];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	fread(hd, 1, 10000000, stdin);
	N = gi();
	M = gi();
	for(int i = 1;i <= N;++i){
		nil[i].v = gi();
		nil[i].data = make_pair(Data(nil[i].v), Data(nil[i].v));
	}
	for(int i = 1;i < N;++i){
		u = gi();
		v = gi();
		addEdge(u, v);
		addEdge(v, u);
	}
	for(q[t++] = 1, hsh[1] = true;f < t;++f){
		for(Edge *cur = g[q[f]];cur;cur = cur->nxt)
			if(!hsh[cur->v]){
				hsh[cur->v] = true;
				q[t++] = cur->v;
				nil[cur->v].p = nil + q[f];
			}
	}
	while(M--){
		op = gi();
		u = gi();
		v = gi();
		if(op == 1){
			cutEdge(u, v);
		}else
		if(op == 2){
			linkEdge(u, v);
		}else
		if(op == 3){
			int d = gi();
			Node *route = chain(u, v);
			if(route != nil){
				route->add += ll(d);
			}
		}else
		if(op == 4){
			Node *route = chain(u, v);
			if(route != nil){
				Data data = route->ans().X;
				ll a = data.getSum(), b = choice2(data.sz + 1);
				ll d = gcd(a, b);
				print(a / d);
				*tl++ = '/';
				print(b / d);
				*tl++ = '\n';
			}else{
				*tl++ = '-';
				*tl++ = '1';
				*tl++ = '\n';
			}
		}
	}
	fwrite(outputBuffer, 1, tl - outputBuffer, stdout);
	return 0;
}

