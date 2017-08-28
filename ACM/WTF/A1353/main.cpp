#include <algorithm>
#include <cstdio>
#include <vector>

using std :: vector;
using std :: min;
using vi = vector<int>;

const int MaxN = 10010;

int N, M, v[MaxN], root;
vi g[MaxN];
int sz[MaxN], dfn[MaxN], idx;
int data[MaxN * 2];

//I'm a LCT
struct Node{
	Node *s[2], *p;
	Node();
	void sets(Node*, int d);
	bool root(){
		return this != p->s[0] && this != p->s[1];
	}
	int d(){
		return this == p->s[1];
	}
}nil[MaxN];

Node :: Node(){
	s[0] = s[1] = p = nil;
}

void :: Node :: sets(Node *t, int d){
	(s[d] = t)->p = this;
}

void rotate(Node *t){
	Node *p = t->p;
	int d = t->d();
	p->sets(t->s[!d], d);
	if(p->root()){
		t->p = p->p;
	}else{
		p->p->sets(t, p->d());
	}
	t->sets(p, !d);
}

void splay(Node *t){
	for(;!t->root();rotate(t)){
		if(!t->p->root()){
			rotate(t->d() != t->p->d() ? t : t->p);
		}
	}
}

void access(Node *t){
	for(Node *ret = nil;t != nil;ret = t, t = t->p){
		splay(t);
		t->sets(ret, 1);
	}
}

int findMin(Node *t){
	for(splay(t);t->s[0] != nil;t = t->s[0]);
	return t - nil;
}

int getNxt(Node *t){
	splay(t);
	for(t = t->s[1];t->s[0] != nil;t = t->s[0]);
	return t - nil;
}
//I'm the end of LCT

//dfs & seg
int getId(int f, int t){
	return (f + t) | (f != t);
}

void modify(int f, int t, int a, int b){
	if(a < f || a > t)
		return;
	if(f == t){
		data[getId(f, t)] = b;
	}else{
		int m = (f + t) / 2;
		modify(f, m, a, b);
		modify(m + 1, t, a, b);
		data[getId(f, t)] = min(data[getId(f, m)], data[getId(m + 1, t)]);
	}
}

int query(int f, int t, int l, int r){
	if(r < f || l > t || l > r){
		return ~0u >> 1;
	}
	if(l <= f && t <= r){
//printf("[%d, %d]:%d\n", l, r, data[getId(f, t)]);
		return data[getId(f, t)];
	}else{
		int m = (f + t) / 2;
		return min(query(f, m, l, r), query(m + 1, t, l, r));
	}
}

void dfs(int x){
	dfn[x] = ++idx;
	modify(1, N, dfn[x], v[x]);
	sz[x] = 1;
	for(auto v: g[x]){
		dfs(v);
		nil[v].p = nil + x;
//printf("%d %d\n", x, v);
		sz[x] += sz[v];
	}
}
//end of dfs & seg

int main(){
	scanf("%d%d", &N, &M);
	for(int i = 1;i <= 2 * N;++i)
		data[i] = ~0u >> 1;
	for(int i = 1;i <= N;++i){
		int f;
		scanf("%d%d", &f, v + i);
		if(f){
			g[f].push_back(i);
		}
	}
	dfs(root = 1);
//for(int i = 1;i <= N;++i) printf("%d ", dfn[i]); puts("");
	while(M--){
		char s[5];
		int a, b, ans;
		scanf("%s%d", s, &a);
		if(*s == 'Q'){
			if(a == root){
				ans = data[getId(1, N)];
			}else{
				if(findMin(nil + a) == 1){
//puts("on route");
					b = getNxt(nil + a);
					ans = min(query(1, N, 1, dfn[b] - 1), query(1, N, dfn[b] + sz[b], N));
				}else{
					ans = query(1, N, dfn[a], dfn[a] + sz[a] - 1);
//printf("%d %d\n", dfn[a], dfn[a] + sz[a] - 1);
				}
			}
			printf("%d\n", ans);
		}
		if(*s == 'E'){
			access(nil + a);
			root = a;
		}
		if(*s == 'V'){
			scanf("%d", &b);
			modify(1, N, dfn[a], b);
		}
	}
	return 0;
}
