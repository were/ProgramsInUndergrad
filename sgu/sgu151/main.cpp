#include <algorithm>
#include <cmath>
#include <cstdio>

using std :: max;

const double eps = 1e-8;

int sgn(double x){
	return x < -eps ? -1 : x > eps;
}

double mySqrt(double x){
	return sqrt(max(x, 0.0));
}

double fixZero(double x){
	return !sgn(x) ? 0 : x;
}

double c, b, m;

int main(){
	scanf("%lf%lf%lf", &c, &b, &m);
	if(sgn(b + c - 2 * m) >= 0 && sgn(fabs(b - c) - 2 * m) <= 0){
		double a = mySqrt(2. * (b * b + c * c - 2. * m * m));
		double x = fixZero((c * c - b * b) / 2. / a);
		double y = mySqrt(b * b - (a / 2. - x) * (a / 2. - x));
		printf("%.5f %.5f\n%.5f %.5f\n%.5f %.5f\n", x, y, -a / 2., 0., a / 2., 0.);
	}else{
		puts("Mission impossible");
	}
	return 0;
}
