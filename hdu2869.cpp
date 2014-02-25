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

int N, M;

int cnt(int x){
	int ret = 0;
	for(int i = 2;i * i <= x;++ i)
		while(x % i == 0){
			x /= i;
			++ ret;
		}
	return ret + (x != 1);
}

int main(){
	while(~scanf("%d%d", &N, &M))
		puts(cnt(N) > cnt(M) ? "Win" : "Lose");
	return 0;
}

