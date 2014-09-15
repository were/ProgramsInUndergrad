#include <cstdio>
#include <vector>
#define forv(i,v) for(int i(0);i<int(v.size());++i)
typedef long long ll;

const int MaxN = 200010;
std :: vector<int> g[MaxN];
int N, M, b[MaxN], c[MaxN], l[MaxN];
ll ans;

/*tmplate balanced tree*/
#include <algorithm>
#include <queue>
struct Node{
	int ky, sz;
	ll sgm;
	Node*s[2];
	void rz(){
		sz = s[0]->sz + 1 + s[1]->sz;
		sgm = s[0]->sgm + ll(ky) + s[1]->sgm;
	}
	void leaf();
}nil[MaxN];
void Node :: leaf(){
	sgm = ky;
	sz = 1;
	s[0] = s[1] = nil;
}
Node*newNode(int ky){
	static Node*tot = nil;
	++ tot;
	tot->ky = ky;
	tot->leaf();
	return tot;
}
/*
    *
   / \
  *   *
 / \
*   *
*/
void rot(Node*&cur, int p){
	Node*tmp = cur->s[p];
	cur->s[p] = tmp->s[!p];
	tmp->s[!p] = cur;
	cur->rz();
	tmp->rz();
	cur = tmp;
}
void maintain(Node*&cur, int p){
	if(cur->s[p]->s[p]->sz > cur->s[!p]->sz){
		rot(cur, p);
	}else if(cur->s[p]->s[!p]->sz > cur->s[!p]->sz){
		rot(cur->s[p], !p);
		rot(cur, p);
	}
}
void insert(Node*&cur, Node*node){
	if(cur == nil){
		cur = node;
	}else{
		insert(cur->s[node->ky > cur->ky], node);
		cur->rz();
		maintain(cur, node->ky > cur->ky);
	}
}
void erase(Node*&cur, int ky){
	if(cur == nil)
		return;
	if(cur->ky == ky){
		if(cur->s[0] == nil || cur->s[1] == nil)
			cur = cur->s[0] - nil + cur->s[1];
		else{
			Node*tmp = cur->s[1];
			while(tmp->s[0] != nil)
				tmp = tmp->s[0];
			cur->ky = tmp->ky;
			erase(cur->s[1], tmp->ky);
			cur->rz();
		}
	}else{
		erase(cur->s[ky > cur->ky], ky);
		cur->rz();
	}
}
Node* merge(Node*a, Node*b){
	if(a->sz < b->sz)
		std :: swap(a, b);
	std :: queue<Node*> q;
	for(q.push(b);!q.empty();q.pop()){
		Node*tmp = q.front();
		for(int i = 0;i < 2;++ i)
			if(tmp->s[i] != nil)
				q.push(tmp->s[i]);
		tmp->leaf();
		insert(a, tmp);
	}
	return a;
}
void show(Node*cur){
	if(cur != nil){
		show(cur->s[0]);
		printf("%d %d\n", cur->ky, cur->sz);
		show(cur->s[1]);
	}
}
/*template end*/

Node*roots[MaxN];

ll select(Node*cur, int M){
	int ret = 0;
	while(cur != nil){
		if(cur->s[0]->sgm + ll(cur->ky) <= M){
			M -= cur->s[0]->sgm + ll(cur->ky);
			ret += cur->s[0]->sz + 1;
			cur = cur->s[1];
		}else
			cur = cur->s[0];
	}
	return ret;
}

void dfs(int x){
	roots[x] = newNode(c[x]);
	forv(i, g[x]){
		dfs(g[x][i]);
		roots[x] = merge(roots[g[x][i]], roots[x]);
	}
	ans = std :: max(ans, select(roots[x], M) * ll(l[x]));
}

int main(){
	nil->s[0] = nil->s[1] = nil;
	scanf("%d%d", &N, &M);
	for(int i = 1;i <= N;++ i){
		roots[i] = nil;
		scanf("%d%d%d", b + i, c + i, l + i);
		g[b[i]].push_back(i);
	}
	dfs(1);
	printf("%I64d\n", ans);
	return 0;
}
