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

int N, ans;

bool hsh[1000010];

ll cube(ll i){
	return i * i * i;
}

ll sqr(ll i){
	return i * i;
}

int main(){
	rep(i, 2, 1000000) if(!hsh[i]){
		for(int j = i + i;j <= 1000000;j += i)
			hsh[j] = true;
	}
	while(~scanf("%d", &N)){
		ans = 0;
		for(int i = 1;cube(i + 1) - cube(i) <= N;++ i){
			ll tmp;
			printf("%I64d %I64d %I64d\n", cube(i + 1), cube(i), tmp = cube(i + 1) - cube(i));
			printf("%I64d\n", cube(cube(i)) + sqr(cube(i)) * tmp);
			if(!hsh[cube(i + 1) - cube(i)])
				++ ans;
		}
		if(ans)
			printf("%d\n", ans);
		else
			puts("No Special Prime!");
	}
	return 0;
}

