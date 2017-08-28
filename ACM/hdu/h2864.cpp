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

int N, A, B, caseCnt, a[100];

void trans(int x, int y){
	if(x / y != 0){
		a[++ a[0]] = x % y;
		trans(x / y, y);
	}else
		a[++ a[0]] = x % y;
}

int main(){
	while(~scanf("%d%d%d", &N, &A, &B)){
		a[0] = 0;
		printf("Case %d:", ++ caseCnt);
		trans(N, B);
		bool flag = true;
		while(flag){
			flag = false;
			per(i, a[0], 1){
				while(a[i] < A){
					-- a[i + 1];
					a[i] += B;
					flag = true;
				}
				if(flag)
					break;
				while(a[i] > A + B){
					-- a[i];
					a[i - 1] += B;
					flag = true;
				}
				if(flag)
					break;
			}
			while(a[a[0]] == 0 && a[0] > 1)
				-- a[0];
		}
		per(i, a[0], 1)
			printf(" %d", a[i]);
		puts("");
	}
	return 0;
}

