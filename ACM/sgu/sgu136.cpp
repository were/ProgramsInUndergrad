#include <cstdio>
const int MaxN = 10000;
int N;
double x[MaxN], y[MaxN];
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i){
		scanf("%lf%lf", x + i, y + i);
		x[i] *= 2.;
		y[i] *= 2.;
	}
	for(int i = 0;i < N - 1;++ i){
		x[N - 1] += x[i] * (i % 2 == 0 ? -1 : 1);
		y[N - 1] += y[i] * (i % 2 == 0 ? -1 : 1);
	}
	if(N % 2 == 1){
		x[N - 1] /= 2.;
		y[N - 1] /= 2.;
	}else{
		if(x[N - 1] != 0 || y[N - 1] != 0){
			puts("NO");
			return 0;
		}
	}
	for(int i = N - 2;i >= 0;-- i){
		x[i] -= x[i + 1];
		y[i] -= y[i + 1];
	}
	puts("YES");
	for(int i = 0;i < N;++ i)
		printf("%f %f\n", x[i], y[i]);
}
