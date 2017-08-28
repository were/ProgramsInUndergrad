/*
PROG : range
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

int N, s[252][252], ans[252];
char m[252][252];

int main(){
	freopen("range.in", "r", stdin);
	freopen("range.out", "w", stdout);
	scanf("%d", &N);
	rep(i, 1, N){
		scanf("%s", m[i] + 1);
		rep(j, 1, N)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + m[i][j] - '0';
	}
	rep(len, 2, N){
		rep(i, 1, N - len + 1)
			rep(j, 1, N - len + 1){
				int sum = 0;
				sum += s[i + len - 1][j + len - 1];
				sum -= s[i - 1][j + len - 1];
				sum -= s[i + len - 1][j - 1];
				sum += s[i - 1][j - 1];
				if(sum == len * len)
					++ ans[len];
			}
	}
	rep(i, 2, N)
		if(ans[i])
			printf("%d %d\n", i, ans[i]);
	return 0;
}

