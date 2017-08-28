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

const int MaxN = 333;

int N, a[MaxN], total, sum;
char s[1000010];

int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++ i){
		scanf("%d", a + i);
		sum += a[i];
	}
	int cur = 1, dir = 1;
	while(sum){
		if(a[cur]){
			s[total ++] = 'P';
			-- a[cur];
			-- sum;
		}
		if(cur + dir < 1 || cur + dir > N)
			dir *= -1;
		cur += dir;
		s[total ++] = dir == -1 ? 'L' : 'R';
	}
	puts(s);
	return 0;
}

