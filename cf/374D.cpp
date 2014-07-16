/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)

typedef std :: vector<int> vi;
typedef std :: map<int, int> mii;

const int MaxN = 1000010;
int N, M, a[MaxN], total;
bool flag = false;
char ans[MaxN];

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
}nil[MaxN];
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
		putchar(ans[cur->ky]);
		flag = true;
		show(cur->s[1]);
	}
}
int select(Node*cur, int k){
	while(k != cur->s[0]->sz + 1){
		if(k > cur->s[0]->sz + 1){
			k -= cur->s[0]->sz + 1;
			cur = cur->s[1];
		}else
			cur = cur->s[0];
	}
	return cur->ky;
}
/*tmplate-balanced-tree-end*/

Node*root;

int main(int argv, char* argc[]){
	root = nil->s[0] = nil->s[1] = nil;
	scanf("%d%d", &N, &M);
	for(int i = 1;i <= M;++ i)
		scanf("%d", a + i);
	while(N --){
		int x;
		scanf("%d", &x);
		if(x == -1){
			x = M + 1;
			for(int i = 1;i <= M && x == M + 1;++ i)
				if(a[i] > root->sz)
					x = i;
			for(int i = 1;i < x;++ i){
				int ky = select(root, a[i] - i + 1);
				erase(root, ky);
			}
		}else{
			ans[++ total] = x + '0';
			insert(root, newNode(total));
		}
	}
	show(root);
	puts(!flag ? "Poor stack!" : "");
	return 0;
}
