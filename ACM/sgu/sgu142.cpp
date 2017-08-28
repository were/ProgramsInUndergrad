#include <cstdio>
const int MaxN = (1 << 20) - 1;
unsigned N, L, hsh[MaxN];
char s[MaxN];
void show(unsigned x, int n){
	for(int i = n - 1;i >= 0;-- i)
		putchar('a' + (x >> i & 1));
	puts("");
}
int main(){
	scanf("%u%s", &N, s);
	for(L = 1u;(1u << L) <= N - L + 1;++ L);
	for(unsigned i = 1;i <= L;++ i){
		for(unsigned j = 0, cur = 0;j < N;++ j){
			cur = ((cur << 1) | (s[j] == 'b')) & ((1 << i) - 1);
			if(j >= i - 1){
				hsh[cur] = i;
//				printf("%u\n", cur);
//				show(cur, i);
			}
		}
		for(unsigned j = 0;j < 1u << i;++ j)
			if(hsh[j] != i){
				printf("%d\n", i);
				for(int k = i - 1;k >= 0;-- k)
					printf("%c", 'a' + (j >> k & 1));
				puts("");
				return 0;
			}
	}
	return 0;
}
