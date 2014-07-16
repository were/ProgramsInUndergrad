#include <cstdio>
int main(){
	int N;
	scanf("%d", &N);
	if(N < 9)
		puts("0");
	else if(N == 9)
		puts("8");
	else if(N == 10)
		puts("72");
	else{
		printf("72");
		for(int i = 0;i < N - 10; ++i)
			putchar('0');
		puts("");
	}
	return 0;
}
