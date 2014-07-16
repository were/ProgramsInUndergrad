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

const int MaxN = 300010;

int N, x, ans[MaxN];
pii a[MaxN];

int main(){
	scanf("%d", &N);
	rep(i, 1, N){
		scanf("%d", &a[i].X);
		a[i].Y = i;
	}
	sort(a + 1, a + N + 1);
	int cur = 0;
	rep(i, 1, N){
		cur = std :: max(cur + 1, a[i].X);
		ans[a[i].Y] = cur;
	}
	rep(i, 1, N)
		printf("%d ", ans[i]);
	return 0;
}

