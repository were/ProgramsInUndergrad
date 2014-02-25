/*
PROB : contact
USER : weng_xo2
LANG : C++
*/
#include <cctype>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
const int MaxN = 200010;
int A, B, N, hsh[13][1 << 12], len;
char s[MaxN];
std :: vector< std :: pair<int, int> > cnt[MaxN];
int main(){
	freopen("contact.in", "r", stdin);
	freopen("contact.out", "w", stdout);
	scanf("%d%d%d", &A, &B, &N);
	for(char *hd = s;(*hd = getchar()) != -1;isdigit(*hd) ? ++ hd : hd);
	s[strlen(s) - 1] = 0;
	for(int i = A;i <= B;++ i){
		for(int j = 0, cur = 0;s[j];++ j){
			cur = cur << 1 | s[j] - '0';
			if(j + 1 >= i)
				++ hsh[i][cur & (1 << i) - 1];
		}
		for(int j = 0;j < 1 << i;++ j)
			if(hsh[i][j])
				cnt[hsh[i][j]].push_back(std :: make_pair(i, j));
	}
	for(int i = MaxN - 1;i >= 0 && N;-- i)
		if(cnt[i].size()){
			N --;
			printf("%d\n", i);
			for(unsigned j = 0;j < cnt[i].size();++ j){
				for(int k = cnt[i][j].first - 1;k >= 0;-- k)
					putchar('0' + (cnt[i][j].second >> k & 1));
				printf(j % 6 == 5 || j + 1 == cnt[i].size() ? "\n" : " ");
			}
		}
	return 0;
}
