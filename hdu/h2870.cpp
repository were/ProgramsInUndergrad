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

int N, M, len[3][1001][1001], l[1001][1001], r[1001][1001], q[1001], t, ans;
char s[1001][1002];

int main(){
	while(~scanf("%d%d", &N, &M)){
		ans = 0;
		rep(i, 1, N)
			scanf("%s", s[i] + 1);
		rep(j, 1, M)
			rep(i, 1, N){
				rep(k, 0, 2)
					len[k][i][j] = 0;
				if(s[i][j] >= 'a' && s[i][j] <= 'c')
					len[s[i][j] - 'a'][i][j] = len[s[i][j] - 'a'][i - 1][j] + 1;
				else{
					if(s[i][j] == 'w'){
						len[0][i][j] = len[0][i - 1][j] + 1;
						len[1][i][j] = len[1][i - 1][j] + 1;
					}
					if(s[i][j] == 'x'){
						len[1][i][j] = len[1][i - 1][j] + 1;
						len[2][i][j] = len[2][i - 1][j] + 1;
					}
					if(s[i][j] == 'y'){
						len[0][i][j] = len[0][i - 1][j] + 1;
						len[2][i][j] = len[2][i - 1][j] + 1;
					}
					if(s[i][j] == 'z'){
						len[0][i][j] = len[0][i - 1][j] + 1;
						len[1][i][j] = len[1][i - 1][j] + 1;
						len[2][i][j] = len[2][i - 1][j] + 1;
					}
				}
			}
		rep(k, 0, 2){
			rep(i, 1, N){
				l[i][1] = q[0] = 0; t = 0; q[++ t] = 1;
				rep(j, 2, M){
					while(t >= 1 && len[k][i][j] <= len[k][i][q[t]])
						-- t;
					l[i][j] = q[t];
					q[++ t] = j;
				}
				r[i][M] = q[0] = M + 1; t = 0; q[++ t] = M;
				per(j, M - 1, 1){
					while(t >= 1 && len[k][i][j] <= len[k][i][q[t]])
						-- t;
					r[i][j] = q[t];
					q[++ t] = j;
				}
				rep(j, 1, M)
					ans = std :: max(ans, len[k][i][j] * ((r[i][j] - 1) - (l[i][j] + 1) + 1));
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

