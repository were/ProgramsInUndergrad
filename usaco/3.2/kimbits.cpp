/*
PROG : kimbits
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

int N, L;
ll I, c[40][40];

int main(){
	freopen("kimbits.in", "r", stdin);
	freopen("kimbits.out", "w", stdout);
	std :: cin >> N >> L >> I;
	rep(i, 0, 31){
		c[i][0] = c[i][i] = 1;
		rep(j, 1, i - 1){
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
//fprintf(stderr, "%d %d %lld\n", i, j, c[i][j]);
		}
	}
	per(i, N, 1){
		ll sum = 0;
		rep(j, 0, L)
			sum += c[i - 1][j];
//fprintf(stderr, "%lld %lld\n", sum, I);
		if(sum < I){
			I -= sum;
			-- L;
			putchar('1');
		}else{
			putchar('0');
		}
	}
	puts("");
	return 0;
}

