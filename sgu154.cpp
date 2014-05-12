#include <cstdio>

int N, l, r;

int calc(int x){
	int ret = 0;
	x *= 5;
	for(int mul = 5;mul <= x;mul *= 5)
		ret += x / mul;
	return ret;
}

int main(){
	scanf("%d", &N);
	if(!N){
		puts("1");
		return 0;
	}
	l = 1, r = N;
	while(l < r){
		int mid = (l + r) / 2;
		int res = calc(mid);
		if(res != N){
			res < N ? l = mid + 1 : r = mid;
		}else
			l = r = mid;
	}
//	printf("%d %d\n", l * 5, calc(l));
	if(calc(l) == N)
		printf("%d\n", l * 5);
	else
		printf("No solution");
	return 0;
}
