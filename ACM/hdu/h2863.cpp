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

int N, M, h[51], A[1001], H[1001], ans;
bool hsh[1001];

void solve(){
	ans = 0;
	rep(i, 1, N)
		scanf("%d", h + i);
	rep(i, 1, M){
		scanf("%d%d", A + i, H + i);
		hsh[i] = false;
	}
	rep(i, 1, 1000){
		rep(k, 1, N){
			int idx = -1, hei;
			rep(j, 1, M)
				if(!hsh[j] && A[j] <= i && H[j] - (i - A[j]) >= h[k]){
					if(idx == -1){
						idx = j;
						hei = H[j] - (i - A[j]);
					}else{
						if(hei > H[j] - (i - A[j])){
							hei = H[j] - (i - A[j]);
							idx = j;
						}
					}
				}
			if(idx != -1){
				hsh[idx] = true;
				++ ans;
			}
		}
	}
	printf("%d\n", ans);
}

int main(){
	while(~scanf("%d%d", &N, &M))
		solve();
	return 0;
}

