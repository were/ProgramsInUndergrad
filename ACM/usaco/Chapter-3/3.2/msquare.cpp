/*
PROG : msquare
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

int Origin[] = {0, 1, 2, 3, 7, 6, 5, 4};

int cantor(vi&a){
	int ret = 0, fac = 5040;
	for(int i = 0;i < 7;++ i){
		for(int j = i + 1;j < 8;++ j)
			if(a[j] < a[i])
				ret += fac;
		fac /= 7 - i;
	}
	return ret;
}

int Tar, len, f, t;
bool hsh[50320], flag;
char res[50320], ans[50320];

void A(vi&a){
	static int b[8];
	rep(i, 0, 7) b[i] = a["45670123"[i] - '0'];
	a = vi(b, b + 8);
}

void B(vi&a){
	static int b[8];
	rep(i, 0, 7) b[i] = a["30127456"[i] - '0'];
	a = vi(b, b + 8);
}

void C(vi&a){
	static int b[8];
	rep(i, 0, 7) b[i] = a["05134627"[i] - '0'];
	a = vi(b, b + 8);
}

typedef std :: pair<vi, int> Data;
Data q[50320];
vi tar(8, 0), origin(Origin, Origin + 8);

void add(vi&a, char ch){
	int x = cantor(a);
	if(hsh[x])
		return;
	hsh[x] = true;
	res[t] = ch;
	q[t] = Data(a, f);
	if(x == Tar){
		while(t != 0){
			ans[len ++] = res[t];
			t = q[t].Y;
		}
		printf("%d\n", len);
		for(int i = len - 1, j = 0;i >= 0;-- i){
			putchar(ans[i]);
			if(++ j == 60){
				puts("");
				j = 0;
			}
		}
		if(len % 60 != 0 || !len)
			puts("");
		exit(0);
	}
	++ t;
}

int main(){
	freopen("msquare.in", "r", stdin);
	freopen("msquare.out", "w", stdout);
	rep(i, 0, 3){
		scanf("%d", &tar[i]);
		-- tar[i];
	}
	per(i, 7, 4){
		scanf("%d", &tar[i]);
		-- tar[i];
	}
	Tar = cantor(tar);
	add(origin, 0);
	while(f < t){
		vi tmp;
		tmp = q[f].X; A(tmp); add(tmp, 'A');
		tmp = q[f].X; B(tmp); add(tmp, 'B');
		tmp = q[f].X; C(tmp); add(tmp, 'C');
		++ f;
	}
	return 0;
}

