#include <cstdio>
#define l ((Y - X) * 60.)
double X, Y, Z;
int main(){
	scanf("%lf%lf%lf", &X, &Y, &Z);
	printf("%.7f\n", (l * l - (l - Z) * (l - Z)) / (l * l));
	return 0;
}
