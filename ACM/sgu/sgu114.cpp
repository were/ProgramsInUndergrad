#include <algorithm>
#include <cmath>
#include <cstdio>
#include <utility>
const int MaxN = 15001;
const double eps = 1e-6;
int N;
std :: pair<double, double> a[MaxN];
double ans = 1e20, l, r, L, R;
double calc(double x){
	double ret = 0.;
	for(int i = 1;i <= N;++i)
		ret += fabs(a[i].first - x) * a[i].second;
	return ret;
}
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++i)
		scanf("%lf%lf", &a[i].first, &a[i].second);
	std :: sort(a + 1, a + 1 + N);
	l = a[1].first; r = a[N].first;
	while(r - l >= eps){
		L = l + (r - l) / 3.;
		R = r - (r - l) / 3.;
		if(calc(L) < calc(R))
			r = R;
		else
			l = L;
	}
	printf("%.0f\n", l);
	return 0;
}
