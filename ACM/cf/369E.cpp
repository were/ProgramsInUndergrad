/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

const int MaxN = 1000010;

int N, M, ans[MaxN], bit[MaxN];
vi a[MaxN];
std :: vector<pii> q[MaxN];

int main(int argv, char* argc[]){
	scanf("%d%d", &N, &M);
	rep(i, 1, N){
		int l, r;
		scanf("%d%d", &l, &r);
		a[r].push_back(l);
	}
	rep(i, 1, M){
		int p, pre = 0, x;
		scanf("%d", &p);
		for(int j = 0;j < p;++ j){
			scanf("%d", &x);
			q[x].push_back(pii(pre, i));
			pre = x;
		}
	}
	per(i, 1000000, 1){
		for_vec(j, a[i]){
			bit_up(k, a[i][j], 1000000)
				++ bit[k];
		}
		for_vec(j, q[i]){
			bit_down(k, i)
				ans[q[i][j].Y] += bit[k];
			bit_down(k, q[i][j].X)
				ans[q[i][j].Y] -= bit[k];
		}
	}
	rep(i, 1, M)
		printf("%d\n", ans[i]);
	return 0;
}

