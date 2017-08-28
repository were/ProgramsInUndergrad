#include <algorithm>
#include <cstdio>
#include <cstring>
const int MaxN = 100010;
int N, res = -1, opt[MaxN][4], pre[MaxN][4];
char s[MaxN], ans[MaxN];
int cnt(int x){
	int ret = 0;
	while(x){
		++ ret;
		x -= x & -x;
	}
	return ret;
}
int main(){
	scanf("%d%s", &N, s);
	memset(opt, 0xff, sizeof opt);
	for(int i = 0;i < N - 1;++ i){
		if(i == 0){
			for(int j = 0;j < 4;++ j)
				if(cnt(j) == s[i] - '0' || s[i] == '*')
					opt[i][j] = cnt(j);
		}else{
			for(int j = 3;j >= 0;-- j) if(~opt[i - 1][j])
				for(int k = 3;k >= 0;-- k) if((j >> 1 & 1) == (k & 1)){
					int x = j | (k << 1);
					if((cnt(x) == s[i] - '0' || s[i] == '*') && opt[i][k] < opt[i - 1][j] + (k >> 1)){
						opt[i][k] = opt[i - 1][j] + (k >> 1);
						pre[i][k] = j;
					}
				}
		}
	}
	for(int i = N - 2, sat;i >= 0;-- i){
		if(i == N - 2){
			for(int j = 3;j >= 0;-- j)
				if(cnt(j) == s[N - 1] - '0' || s[N - 1] == '*'){
					if(res < opt[i][j]){
						res = opt[i][j];
						sat = j;
					}
				}
			ans[i + 1] = (sat >> 1 & 1) + '0';
			ans[i] = (sat & 1) + '0';
			sat = pre[i][sat];
		}else{
			ans[i] = (sat & 1) + '0';
			sat = pre[i][sat];
		}
	}
	printf("%d\n%s\n", res, ans);
	return 0;
}
