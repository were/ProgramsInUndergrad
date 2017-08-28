/*
Programmed by wereFluke
*/
#include <algorithm>
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
 
typedef long long ll;
typedef std :: vector<int> vi;
typedef std :: map<int, int> mii;
typedef std :: pair<int, int> pii;
 
using std :: swap;
 
const int MaxN = 100010;
const unsigned mod = 51061;
 
struct Node{
    Node *s[2], *p;
    unsigned sum, mul, add, v, sz;
    bool rev;
    Node();
    unsigned ans();
    void rz();
    void pushAdd(unsigned);
    void pushMul(unsigned);
    void sets(Node*, int);
    bool d();
    void push();
    bool root();
}nil[MaxN];
 
Node :: Node() : sum(1u), mul(1u), add(0u), v(1u), sz(1u), rev(false) {
    p = s[0] = s[1] = nil;
}
 
void Node :: pushAdd(unsigned x){
    (add += x) %= mod;
}
 
void Node :: pushMul(unsigned x){
    (mul *= x) %= mod;
    (add *= x) %= mod;
}
 
unsigned Node :: ans(){
    if(this == nil)
        return 0u;
    return (sum * mul % mod + add * sz % mod) % mod;
}
 
void Node :: rz(){
    sum = (s[0]->ans() + v + s[1]->ans()) % mod;
    sz = (s[0]->sz + 1 + s[1]->sz) % mod;
}
 
void Node :: sets(Node *t, int d){
    (s[d] = t)->p = this;
    rz();
}
 
bool Node :: d(){
    return this == p->s[1];
}
 
void Node :: push(){
    if(rev){
        s[0]->rev ^= true;
        s[1]->rev ^= true;
        swap(s[0], s[1]);
        rev = false;
    }
    sum = ans();
    if(mul != 1u){
        (v *= mul) %= mod;
        s[0]->pushMul(mul);
        s[1]->pushMul(mul);
        mul = 1u;
    }
    if(add != 0u){
        (v += add) %= mod;
        s[0]->pushAdd(add);
        s[1]->pushAdd(add);
        add = 0u;
    }
}
 
bool Node :: root(){
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
 
void rotate(Node *t){
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
 
void splay(Node *t){
    while(!t->root())
        if(t->p->root())
            rotate(t);
        else{
            if(t->d() != t->p->d()){
                rotate(t);
                rotate(t);
            }else{
                rotate(t->p);
                rotate(t);
            }
        }
    t->push();
}
 
Node *access(Node *t){
    Node *ret;
    for(ret = nil;t != nil;ret = t, t = t->p){
        splay(t);
        t->sets(ret, 1);
    }
    return ret;
}
 
void evert(Node *t){
    access(t);
    splay(t);
    t->rev ^= true;
}
 
void linkEdge(int u, int v){
    evert(nil + u);
    nil[u].p = nil + v;
}
 
void cutEdge(int u, int v){
    evert(nil + u);
    access(nil + v);
    splay(nil + v);
    nil[v].s[0]->p = nil;
    nil[v].s[0] = nil;
    nil[v].rz();
}
 
Node *chain(int u, int v){
    evert(nil + u);
    access(nil + v);
    splay(nil + v);
    return nil + v;
}
 
int N, M;

char inputBuffer[10000010], outputBuffer[10000010], *hd = inputBuffer, *tl = outputBuffer;

int nextInt(){
	while(!isdigit(*hd))
		++hd;
	int ret = *hd++ - '0';
	while(isdigit(*hd))
		ret = ret * 10 + *hd++ - '0';
	return ret;
}

void printInt(int x){
	if(x >= 10)
		printInt(x / 10);
	*tl++ = x % 10 + '0';
}

int main(){
//freopen("input.txt", "r", stdin);
	fread(inputBuffer, 1, 10000000, stdin);
    nil->sz = 0;
	N = nextInt();
	M = nextInt();
    for(int i = 1, u, v;i < N;++i){
		u = nextInt();
		v = nextInt();
        linkEdge(u, v);
    }
    while(M--){
        char buffer[5];
		while(!ispunct(*hd))
			++hd;
		*buffer = *hd;
        if(*buffer == '+'){
            int u, v, c;
			u = nextInt();
			v = nextInt();
			c = nextInt();
            chain(u, v)->pushAdd(c);
        }
        if(*buffer == '-'){
            int u1, v1, u2, v2;
			u1 = nextInt();
			v1 = nextInt();
			u2 = nextInt();
			v2 = nextInt();
            cutEdge(u1, v1);
            linkEdge(u2, v2);
        }
        if(*buffer == '*'){
            int u, v, c;
			u = nextInt();
			v = nextInt();
			c = nextInt();
            chain(u, v)->pushMul(c);
        }
        if(*buffer == '/'){
            int u, v;
			u = nextInt();
			v = nextInt();
            printInt(chain(u, v)->ans());
			*tl++ = '\n';
        }
    }
	fwrite(outputBuffer, 1, tl - outputBuffer, stdout);
    return 0;
}

