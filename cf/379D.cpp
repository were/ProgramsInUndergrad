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

#define S "ABC"

struct Data{
	char f, t;
	ll m;
	Data(char f, ll m, char t) : f(f), t(t), m(m) {}
	void show(){
		printf("%c %I64d %c\n", f, m, t);
	}
};

Data operator+ (const Data&a, const Data&b){
	return Data(a.f, a.m + b.m + (a.t == 'A' && b.f == 'C'), b.t);
}

int K, x, N, M;
char A[111], B[111];

bool gen(int f, int m, int t, int len, char*s){
	if(len == 1 && f != t)
		return 0;
	for(int i = 0;i < len;++ i)
		s[i] = 0;
	s[0] = S[f];
	s[len - 1] = S[t];
	if(s[0] == 'A' && m){
		if(!s[1]){
			s[1] = 'C';
			-- m;
		}else{
			if(s[1] == 'C')
				-- m;
		}
	}
	if(s[len - 1] == 'C' && m){
		if(len - 2 >= 0 && !s[len - 2]){
			s[len - 2] = 'A';
			-- m;
		}
	}
	for(int i = 0;i < len;++ i){
		if(!s[i] && i + 1 < len && !s[i + 1] && m){
			s[i] = 'A';
			s[i + 1] = 'C';
			-- m;
		}else{
			if(!s[i])
				s[i] = 'B';
		}
	}
	return m == 0;
}

ll work(Data a, Data b){
	if(K == 1)
		return a.m;
	if(K == 2)
		return b.m;
	Data c(0, 0, 0);
	for(int i = 3;i <= K;++ i){
		c = a + b;
		a = b;
		b = c;
	}
	return c.m;
}

int main(){
	scanf("%d%d%d%d", &K, &x, &N, &M);
	rep(af, 0, 2) rep(at, 0, 2) rep(am, 0, N / 2) if(gen(af, am, at, N, A))
		rep(bf, 0, 2) rep(bt, 0, 2) rep(bm, 0, M / 2) if(gen(bf, bm, bt, M, B)){
			if(work(Data(S[af], am, S[at]), Data(S[bf], bm, S[bt])) == x){
				puts(A);
				puts(B);
				return 0;
			}
		}
	puts("Happy new year!");
	return 0;
}

