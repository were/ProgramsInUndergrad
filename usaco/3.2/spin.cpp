/*
PROG : spin
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

int s[5];
std :: vector<pii> w[5];

bool inRange(int x, int l, int r){
	if(r < l){
		return inRange(x, l, 359) || inRange(x, 0, r);
	}else
		return x >= l && x <= r;
}

bool check(int x, int y){
	rep(i, 0, 4){
		bool flag = false;
		for_vec(j, w[i])
			if(inRange(y, (w[i][j].X + x * s[i]) % 360, (w[i][j].Y + x * s[i]) % 360))
				flag = true;
		if(!flag){
			return false;
		}
	}
	return true;
}

int main(){
	freopen("spin.in", "r", stdin);
	freopen("spin.out", "w", stdout);
	rep(i, 0, 4){
		scanf("%d", s + i);
		int W;
		scanf("%d", &W);
		rep(j, 1, W){
			int l, r;
			scanf("%d%d", &l, &r);
			r += l;
			w[i].push_back(pii(l, r));
		}
	}
	rep(i, 0, 359){
//		rep(j, 0, 4)
//			for_vec(k, w[j]){
//				printf("%d %d\n", (w[j][k].X + s[j] * i) % 360, (w[j][k].Y + s[j] * i) % 360);
//				printf("%d %d\n", i, s[j] * i);
//			}
		rep(j, 0, 359){
			if(check(i, j)){
				printf("%d\n", i);
				return 0;
			}
		}
	}
	puts("none");
	return 0;
}

