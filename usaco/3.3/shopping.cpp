/*
PROG : shopping
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

int S, B, num[1000], total, goal[5], dis[6][6][6][6][6];
bool hsh[6][6][6][6][6];

struct Goods{
	int a[5], p;
	Goods(){
		memset(a, 0, sizeof a);
		p = 0;
	}
};

std :: vector<Goods> goods;
std :: queue<Goods> q;

Goods operator+ (const Goods&a, const Goods&b){
	Goods tmp;
	rep(i, 0, 4)
		tmp.a[i] = a.a[i] + b.a[i];
	tmp.p = a.p + b.p;
	return tmp;
}

void insert(const Goods&x){
	rep(i, 0, 4)
		if(x.a[i] < 0 || x.a[i] > goal[i])
			return;
	if(dis[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]] > x.p){
		dis[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]] = x.p;
		if(!hsh[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]]){
			hsh[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]] = true;
			q.push(x);
		}
	}
}

int main(){
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	scanf("%d", &S);
	rep(i, 1, S){
		int N;
		scanf("%d", &N);
		Goods tmp;
		rep(j, 1, N){
			int C, K;
			scanf("%d%d", &C, &K);
			if(!num[C]){
				num[C] = ++ total;
			}
			tmp.a[num[C] - 1] = K;
		}
		scanf("%d", &tmp.p);
		goods.push_back(tmp);
	}
	scanf("%d", &B);
	rep(i, 1, B){
		int C, K, P;
		scanf("%d%d%d", &C, &K, &P);
		if(!num[C]){
			num[C] = ++ total;
		}
		goal[num[C] - 1] = K;
		Goods tmp;
		tmp.a[num[C] - 1] = 1;
		tmp.p = P;
		goods.push_back(tmp);
	}
	memset(dis, 127, sizeof dis);
	insert(Goods());
	while(!q.empty()){
		Goods x(q.front());
		x.p = dis[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]];
		for_vec(i, goods)
			insert(x + goods[i]);
		hsh[x.a[0]][x.a[1]][x.a[2]][x.a[3]][x.a[4]] = false;
		q.pop();
	}
	printf("%d\n", dis[goal[0]][goal[1]][goal[2]][goal[3]][goal[4]]);
	return 0;
}

