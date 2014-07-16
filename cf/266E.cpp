/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <istream>
#include <map>
#include <ostream>
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

#define ls (x+x)
#define rs (x+x+1)
#define mid ((f+t)/2)

const int MaxN = 100010;
const ll mod = (1e9) + 7;

ll len[MaxN * 4][6], tag[MaxN * 4], fac[10];
int N, M, l, r, k;

ll pow(ll a, ll b){
	ll ret = 1ll;
	for(int i = 0;i < b;++ i){
		ret *= a;
		ret %= mod;
	}
	return ret;
}

ll C(int a, int b){
	return (fac[a] / fac[b] / fac[a - b]) % mod;
}

struct Data{
	ll sgm[6];
	ll calc(ll l, ll k){
		ll ret = 0;
		for(int i = 0;i <= k;++ i){
			ret += (sgm[i] * pow(-l, k - i) % mod) * C(k, i) % mod;
			ret %= mod;
		}
		return ret < 0 ? ret + mod : ret;
	}
}data[MaxN * 4];

std :: ostream& operator<< (std :: ostream&out, Data x){
	for(int i = 0;i < 6;++ i)
		out << x.sgm[i] << " ";
	return out;
}

Data getAns(int x){
	if(~tag[x]){
		Data ret;
		for(int i = 0;i < 6;++ i){
			ret.sgm[i] = len[x][i] * tag[x] % mod;
		}
		return ret;
	}
	return data[x];
}

void push(int x){
	if(~tag[x]){
		tag[ls] = tag[rs] = tag[x];
		data[x] = getAns(x);
		tag[x] = -1;
	}
}

Data operator+ (const Data&a, const Data&b){
	Data ret;
	for(int i = 0;i < 6;++ i){
		ret.sgm[i] = (a.sgm[i] + b.sgm[i]) % mod;
	}
	return ret;
}

void build(int f, int t, int x){
	tag[x] = -1;
	if(f == t){
		scanf("%I64d", data[x].sgm);
		for(int i = 0;i < 6;++ i){
			len[x][i] = pow(f, i);
			data[x].sgm[i] = (data[x].sgm[0] * len[x][i]) % mod;
		}
	}else{
		build(f, mid, ls);
		build(mid + 1, t, rs);
		data[x] = data[ls] + data[rs];
		for(int i = 0;i < 6;++ i)
			len[x][i] = (len[ls][i] + len[rs][i]) % mod;
	}
}

void modify(int f, int t, int x){
	if(f != t)
		push(x);
	if(l <= f && t <= r){
		tag[x] = k;
	}else{
		if(l <= mid)
			modify(f, mid, ls);
		if(mid < r)
			modify(mid + 1, t, rs);
		data[x] = getAns(ls) + getAns(rs);
	}
}

Data query(int f, int t, int x){
	if(f != t)
		push(x);
	if(l <= f && t <= r){
		return getAns(x);
	}else{
		if(r <= mid)
			return query(f, mid, ls);
		if(mid + 1 <= l)
			return query(mid + 1, t, rs);
		return query(f, mid, ls) + query(mid + 1, t, rs);
	}
}

int main(){
	scanf("%d%d", &N, &M);
	fac[0] = 1;
	for(int i = 1;i <= 5;++ i)
		fac[i] = fac[i - 1] * ll(i);
	build(1, N, 1);
	while(M --){
		char s[2];
		scanf("%s%d%d%d", s, &l, &r, &k);
		if(*s == '='){
			modify(1, N, 1);
		}else{
			printf("%I64d\n", query(1, N, 1).calc(l - 1, k));
		}
	}
	return 0;
}
