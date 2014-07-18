#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MS(_) memset(_,0,sizeof _)
using namespace std;
const int MaxN= 111;
int N, gra[MaxN][MaxN], u, v, Time[MaxN], Pre[MaxN], cur_time, hsh[MaxN], low[MaxN], ans;
char s[MaxN * MaxN], *hd;
void dfs(int x,int pre) {
	if(Time[x])
		return;
	Time[x] = ++cur_time;
	Pre[x] = pre;
	int res = Time[x];
	for(int i = 1; i <= N; ++i)
		if(gra[x][i])
			dfs(i,x);
	for(int i = 1;i <= N; ++i){
		if(gra[x][i] && Time[i] < Time[x] && Pre[x] != i)
			res = min(res, Time[i]);
		if(gra[x][i] && Time[i] > Time[x])
			res = min(res, low[i]);
	}
	low[x] = res;
	bool flag = 0;
	for(int i = 1; i <= N; ++i)
		flag |= Pre[i] == x;
	if(flag)
		for(int i = 1; i <= N; ++i){
			if(x != 1 && gra[x][i] && Pre[i] == x && Time[x] <= low[i]){
				ans++;
				break;
			}
		}
}
int main(){
	while(scanf("%d", &N) && N){
		gets(s);
		MS(gra);
		MS(Time);
		MS(Pre);
		MS(hsh);
		MS(low);
		ans = 0;
		while(gets(s) && strcmp(s, "0")){
			hd = s;
			sscanf(hd, "%d", &u);
			while(*hd){
				while(*hd && isdigit(*hd)) hd++;
				while(*hd &&!isdigit(*hd)) hd++;
				sscanf(hd, "%d", &v);
				gra[u][v] = 1;
				gra[v][u] = 1;
			}
		}
		dfs(1, 0);
		int cnt = 0;
		for(int j = 1; j<= N; ++j)
			cnt += Pre[j] == 1;
		ans += cnt != 1;
		printf("%d\n", ans);
	}
	return 0;
}
