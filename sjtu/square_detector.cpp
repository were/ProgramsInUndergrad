#include <algorithm>
#include <cstdio>
int T, N, caseCnt;
char s[21][21];
bool check(int x, int y, int d){
	for(int i = 0;i < d;++ i)
		for(int j = 0;j < d;++ j)
			if(s[x + i][y + j] != '#')
				return false;
	for(int i = 0;i < d;++ i)
		for(int j = 0;j < d;++ j)
			s[x + i][y + j] = '.';
	return true;
}
int main(){
	scanf("%d", &T);
	while(T --){
		scanf("%d", &N);
		for(int i = 0;i < N;++ i)
			scanf("%s", s[i]);
		bool found = false;
		for(int i = 0;i < N && !found;++ i)
			for(int j = 0;j < N && !found;++ j)
				for(int k = std :: min(N - i, N - j);k > 0 && !found;-- k)
					found = check(i, j, k);
		bool flag = true;
		for(int i = 0;i < N && flag;++ i)
			for(int j = 0;j < N && flag;++ j)
				if(s[i][j] == '#')
					flag = false;
		printf("Case #%d: %s\n", ++ caseCnt, flag && found ? "YES" : "NO");
	}
	return 0;
}
