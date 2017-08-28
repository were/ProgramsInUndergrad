/*
PROG : ratios
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

vi a[3];
int x[4];
bool flag, zero;

vi operator - (const vi&a, const vi&b){
	vi ret;
	for_vec(i, a)
		ret.push_back(a[i] - b[i]);
	return ret;
}

vi operator * (int a, const vi&b){
	vi ret;
	for_vec(i, b)
		ret.push_back(a * b[i]);
	return ret;
}

int lcm(int a, int b){
	return a * b / std :: __gcd(a, b);
}

void show(vi&a){
	for_vec(i, a)
		fprintf(stderr, "%d ", a[i]);
	fputs("\n", stderr);
}

int main(){
	freopen("ratios.in", "r", stdin);
	freopen("ratios.out", "w", stdout);
	rep(i, 0, 3)
		rep(j, 0, 2){
			int x;
			std :: cin >> x;
			if(i == 0)
				x = -x;
			a[j].push_back(x);
		}
	rep(i, 0, 2){
		bool flag = false;
		rep(j, i, 2)
			if(a[j][i]){
				a[j].swap(a[i]);
				flag = true;
				break;
			}
		if(flag){
			rep(j, i + 1, 2) if(a[j][i]){
				int mul = lcm(a[i][i], a[j][i]);
				a[j] = (mul / a[j][i]) * a[j] - (mul / a[i][i]) * a[i];
			}
		}
	}
	rep(i, 0, 2){
		int d = -1;
		for_vec(j, a[i]){
			if(a[i][j])
				d = d == -1 ? a[i][j] : std :: __gcd(abs(a[i][j]), d);
		}
		if(~d)
			for_vec(j, a[i])
				a[i][j] /= d;
	}
	rep(X, 0, 100){
		x[3] = X;
		zero = flag = true;
		if(X != 0)
			zero = false;
		per(i, 2, 0){
			int sum = 0;
			rep(j, i + 1, 3)
				sum += a[i][j] * x[j];
			if(a[i][i]){
				if(sum % a[i][i] == 0)
					x[i] = -sum / a[i][i];
				else{
					flag = false;
					break;
				}
			}else{
				if(sum == 0)
					x[i] = 0;
			}
			if(x[i] != 0)
				zero = false;
			if(x[i] < 0){
				flag = false;
				break;
			}
		}
		if(flag && !zero){
			printf("%d %d %d %d\n", x[1], x[2], x[3], x[0]);
			return 0;
		}
	}
	puts("NONE");
	return 0;
}

