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

const int MaxN = 50010;

int N, M, l, r, X;
char buffer[10];

struct Data{
	int l, r, s, m, sum;
	Data(int l, int r, int s, int m, int sum) : l(l), r(r), s(s), m(m), sum(sum) {}
	Data() : l(0), r(0), s(0), m(0), sum(0) {}
};

Data operator+ (const Data&a, const Data&b){
	Data ret;
	ret.l = a.l;
	if(a.l == a.s)
		ret.l = std :: max(ret.l, a.s + b.l);
	ret.r = b.r;
	if(b.r == b.s)
		ret.r = std :: max(ret.r, b.s + a.r);
	ret.s = a.s + b.s;
	ret.m = std :: max(a.r + b.l, std :: max(a.m, b.m));
	ret.sum = a.sum + b.sum;
	return ret;
}

struct Tag{
	int f, t;
	Tag(int f, int t) : f(f), t(t) {}
	Tag() : f(-1), t(-1) {}
};

Data data[MaxN * 4];
Tag tag[MaxN * 4];
int len[MaxN * 4], head[MaxN * 4];

#define mid ((f + t) / 2)
#define ls (x + x)
#define rs (ls + 1)

Data getAns(int x){
	if(tag[x].f == -1 && tag[x].t == -1){
		return data[x];
	}
	if(tag[x].f == 0 && tag[x].t == 0)
		return Data(len[x], len[x], len[x], len[x], 0);
	return Data(0, 0, len[x], 0, head[x]);
}

void push(int x){
	if(tag[x].f == -1 && tag[x].t == -1)
		return;
	data[x] = getAns(x);
	tag[ls] = tag[rs] = tag[x];
	head[ls] = head[x];
	head[x] = head[rs] = 0;
	tag[x] = Tag();
}

void build(int f, int t, int x){
	len[x] = t - f + 1;
	tag[x] = Tag(-1, -1);
	if(f == t){
		data[x] = Data(1, 1, 1, 1, 0);
	}else{
		build(f, mid, ls);
		build(mid + 1, t, rs);
		data[x] = getAns(ls) + getAns(rs);
	}
}

void Reset(){
	tag[1] = Tag(0, 0);
	puts("Reset Now");
}

void getRange(int f, int t, int x){
	if(f != t)
		push(x);
	if(getAns(x).m == getAns(x).s){
		l = f;
		r = l + X - 1;
		return;
	}
	if(getAns(ls).m >= X)
		return getRange(f, mid, ls);
	if(getAns(ls).r + getAns(rs).l >= X){
		l = mid - getAns(ls).r + 1;
		X -= getAns(ls).r;
		r = mid + X;
		return;
	}
	if(getAns(rs).m >= X)
		return getRange(mid + 1, t, rs);
}

void getBlock(int f, int t, int x){
	if(f != t)
		push(x);
	if(f == t){
		l = tag[x].f;
		r = tag[x].t;
	}else{
		if(X <= mid)
			return getBlock(f, mid, ls);
		getBlock(mid + 1, t, rs);
	}
}

void cover(int f, int t, int x){
	if(f != t)
		push(x);
	if(l <= f && t <= r){
		if(!strcmp(buffer, "New")){
			tag[x] = Tag(l, r);
			head[x] = (l == f);
		}
		if(!strcmp(buffer, "Free")){
			tag[x] = Tag(0, 0);
			head[x] = -(l == f);
		}
	}else{
		if(l <= mid)
			cover(f, mid, ls);
		if(r > mid)
			cover(mid + 1, t, rs);
		data[x] = getAns(ls) + getAns(rs);
	}
}

void New(){
	scanf("%d", &X);
	if(getAns(1).m >= X){
		getRange(1, N, 1);
		printf("New at %d\n", l);
		cover(1, N, 1);
	}else
		puts("Reject New");
}

void Free(){
	scanf("%d", &X);
	getBlock(1, N, 1);
	if(l + r <= 0)
		puts("Reject Free");
	else{
		cover(1, N, 1);
		printf("Free from %d to %d\n", l, r);
	}
}

int getSum(int f, int t, int x){
	if(f != t)
		push(x);
	if(f == t){
		return f;
	}else{
		if(getAns(ls).sum < X){
			X -= getAns(ls).sum;
			return getSum(mid + 1, t, rs);
		}else
			return getSum(f, mid, ls);
	}
}

void Get(){
	scanf("%d", &X);
	if(X > getAns(1).sum)
		puts("Reject Get");
	else
		printf("Get at %d\n", getSum(1, N, 1));
}

int main(){
	while(~scanf("%d%d", &N, &M)){
		build(1, N, 1);
		while(M --){
			scanf("%s", buffer);
			if(!strcmp(buffer, "Reset"))
				Reset();
			if(!strcmp(buffer, "New"))
				New();
			if(!strcmp(buffer, "Free"))
				Free();
			if(!strcmp(buffer, "Get"))
				Get();
		}
		puts("");
	}
	return 0;
}

