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
typedef vi :: iterator Edge;

const int MaxN = 100010;

vi g[MaxN];
int N, M, v[MaxN];
int q[MaxN], dep[MaxN], nxt[MaxN], pre[MaxN], hd[MaxN], sz[MaxN], idx[MaxN];

struct Data{
	int sgm;
	int mx;
	Data(int sgm, int mx) : sgm(sgm), mx(mx) {}
	Data(int x) : sgm(x), mx(x) {}
	Data() : sgm(0ll), mx(-0x7fffffff) {}
}data[MaxN];

Data operator+ (const Data&a, const Data&b){
	return Data(
		a.sgm + b.sgm,
		max(a.mx, b.mx)
	);
}

#define mid ((f+t) / 2)
#define getId(f,t) (f+t|(f!=t))

void modify(int f, int t, int u, int v){
	if(u < f || u > t)
		return;
	if(f == t){
		data[getId(f, t)] = v;
	}else{
		modify(f, mid, u, v);
		modify(mid + 1, t, u, v);
		data[getId(f, t)] = data[getId(f, mid)] + data[getId(mid + 1, t)];
	}
}

void init(){
	int f = 0, t = 0, curIdx = 0;
	dep[1] = 1;
	for(q[t++] = 1;f < t;++f){
		for(Edge cur = g[q[f]].begin(), end = g[q[f]].end();cur != end;++cur)
			if(!dep[*cur]){
				q[t++] = *cur;
				dep[*cur] = dep[q[f]] + 1;
				pre[*cur] = q[f];
			}
	}
	per(i, N - 1, 0){
		sz[pre[q[i]]] += ++sz[q[i]];
		if(!nxt[pre[q[i]]] || sz[nxt[pre[q[i]]]] < sz[q[i]])
			nxt[pre[q[i]]] = q[i];
	}
	rep(i, 0, N - 1){
		if(!hd[q[i]]){
			for(int j = q[i];j;j = nxt[j]){
				idx[j] = ++curIdx;
				hd[j] = q[i];
				modify(1, N, curIdx, v[j]);
			}
		}
	}
}

Data query(int f, int t, int l, int r){
	if(r < f || l > t)
		return Data();
	if(l <= f && t <= r)
		return data[getId(f, t)];
	return query(f, mid, l, r) + query(mid + 1, t, l, r);
}

Data query(int a, int b){
	Data ret;
	while(hd[a] != hd[b]){
		if(dep[hd[a]] < dep[hd[b]])
			swap(a, b);
		ret = ret + query(1, N, idx[hd[a]], idx[a]);
		a = pre[hd[a]];
	}
	if(idx[a] > idx[b])
		swap(a, b);
	return ret + query(1, N, idx[a], idx[b]);
}

int main(){
//	freopen("input", "r", stdin);
//	freopen("output", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N - 1){
		int a, b;
		scanf("%d%d", &a, &b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	rep(i, 1, N)
		scanf("%d", v + i);
	init();
//puts("init done...");
	scanf("%d", &M);
	while(M--){
		char buffer[10];
		int a, b;
		scanf("%s%d%d", buffer, &a, &b);
//printf("%s %d %d\n", buffer, a, b);
		if(*buffer == 'Q'){
			Data ans = query(a, b);
			if(buffer[1] == 'S')
				printf("%d\n", ans.sgm);
			else
				printf("%d\n", ans.mx);
		}else{
			v[a] = b;
			modify(1, N, idx[a], b);
		}
	}
	return 0;
}

