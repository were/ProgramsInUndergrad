/*
Programmed by wereFluke
*/
#include <algorithm>
#include <bitset>
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
#include <sstream>
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

using std :: sort;
using std :: bitset;
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
using std :: istringstream;
using std :: ostringstream;
using std :: stringstream;
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

const int MaxN = 100010;

int N, M, x[MaxN], y[MaxN];

struct Node{
	int v, w;
	Node *nxt;
	Node(int v, int w, Node *nxt) : v(v), w(w), nxt(nxt) {}
}*g[MaxN];

int main(){
	scanf("%d", &N);
	rep(i, 1, N){
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		g[a] = new Node(b, c, g[a]);
	}
	rep(i, 0, 100000)
		x[i] = y[i] = i;
	scanf("%d", &M);
	while(M--){
		int op, a, b;
		scanf("%d%d%d", &op, &a, &b);
		if(op == 0){
			swap(x[a], x[b]);
		}
		if(op == 1){
			swap(y[a], y[b]);
		}
		if(op == 2){
			bool flag = false;
			for(Node *cur = g[x[a]];cur;cur = cur->nxt){
				if(cur->v == y[b]){
					printf("%d\n", cur->w);
					flag = true;
					break;
				}
			}
			if(!flag){
				puts("0");
			}
		}
	}
}

