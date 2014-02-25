#include <cstdio>
#include <map>
#include <vector>
#define X first
#define Y second

typedef std :: map<int, int> mii;
typedef std :: vector<int> vi;
const int MaxN = 200010;
int N, M, c[MaxN], k[MaxN], ans[MaxN];
vi g[MaxN], q[MaxN];
mii buf[MaxN];

/*tmplate-balanced-tree*/
#include <algorithm>
#include <cstdio>
#include <queue>
//const int MaxN = ;
struct Node{
	int ky, sz;
	Node*s[2];
	void rz(){
		sz = s[0]->sz + 1 + s[1]->sz;
	}
	void leaf();
}nil[1000010];
void Node :: leaf(){
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
void show(Node*cur){
	if(cur != nil){
		show(cur->s[0]);
		printf("%d %d\n", cur->ky, cur->sz);
		show(cur->s[1]);
	}
}
/*tmplate-balanced-tree-end*/

typedef std :: pair<mii*, Node*> thing;

thing merge(thing a, thing b){
	if(a.Y->sz < b.Y->sz)
		std :: swap(a, b);
	std :: queue<Node*> q;
	for(mii :: iterator cur = b.X->begin();cur != b.X->end();++ cur){
		erase(a.Y, (*a.X)[cur->first]);
		insert(a.Y, newNode((*a.X)[cur->first] += cur->second));
	}
	return a;
}

int getAns(Node*cur, int ky){
	int ret = 0;
	while(cur != nil){
		if(ky > cur->ky){
			ret += cur->s[0]->sz + 1;
			cur = cur->s[1];
		}else
			cur = cur->s[0];
	}
	return ret;
}

thing dfs(int x, int pre){
	thing ret;
	ret.X = &buf[x];
	(*ret.X)[c[x]] = 1;
	ret.Y = newNode(1);
	for(int i = 0;i < int(g[x].size());++ i){
		if(g[x][i] != pre){
			ret = merge(ret, dfs(g[x][i], x));
		}
	}
	for(int i = 0;i < int(q[x].size());++ i){
		ans[q[x][i]] = ret.Y->sz - getAns(ret.Y, k[q[x][i]]);
	}
	return ret;
}

int main(){
	nil->s[0] = nil->s[1] = nil;
	scanf("%d%d", &N, &M);
	for(int i = 1;i <= N;++ i)
		scanf("%d", c + i);
	for(int i = 1;i < N;++ i){
		int u, v;
		scanf("%d%d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	for(int i = 1;i <= M;++ i){
		int v;
		scanf("%d%d", &v, k + i);
		q[v].push_back(i);
	}
	dfs(1, -1);
	for(int i = 1;i <= M;++ i)
		printf("%d\n", ans[i]);
	return 0;
}
