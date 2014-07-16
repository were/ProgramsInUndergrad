#include <cstdio>
#include <cmath>

const int MaxN = 100010;

double x[MaxN], y[MaxN];
int T, N, cs;

double calc(double pos) {
	double ret = 0.;
	for(int i = 1; i <= N; ++i) {
		ret += sqrt((x[i] - pos) * (x[i] - pos) + y[i] * y[i]);
	}
	return ret;
}

double getAns() {
	double l = -1e6 - 10, r = 1e6 + 10;
	while(r - l > 1e-7) {
		double res1 = calc(l + (r - l) / 3.), res2 = calc(l + (r - l) / 3. * 2.);
		//printf("%f, %f: %f, %f\n", l, r, res1, res2);
		if(res1 < res2) {
			r = l + (r - l) / 3. * 2.;
		}
		else {
			l = l + (r - l) / 3.;
		}
	}
	return l;
}

int main() {
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		for(int i = 1; i <= N; ++i) {
			scanf("%lf%lf", x + i, y + i);
		}
		printf("Case %d: %f\n", ++cs, getAns());
	}
}
