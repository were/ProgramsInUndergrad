/*
PROG : game1
ID : weng_xo2
LANG : C++
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

int N, a[201], sum[201], opt[201][201];

int work(int l, int r){
	if(~opt[l][r])
		return opt[l][r];
	if(l == r)
		return opt[l][r] = a[l];
	opt[l][r] = sum[r] - sum[l - 1] - std :: min(work(l + 1, r), work(l, r - 1));
//	printf("[%d,%d]:%d\n", l, r, opt[l][r]);
	return opt[l][r];
}

int main(){
	freopen("game1.in", "r", stdin);
	freopen("game1.out", "w", stdout);
	memset(opt, 0xff, sizeof opt);
	scanf("%d", &N);
	rep(i, 1, N){
		scanf("%d", a + i);
		sum[i] = sum[i - 1] + a[i];
	}
	printf("%d %d\n", work(1, N), sum[N] - work(1, N));
	return 0;
}

