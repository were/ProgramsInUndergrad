#include <cstdio>
#include <cmath>
const double g = 9.8, pi = 3.1415926535897932384626433832795;
int T, caseCnt;
double V, D, ans;
int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%lf%lf", &V, &D);
		ans = asin(D / V / V * g) / 2.;
		printf("Case #%d: %.10f\n", ++caseCnt, ans * 180. / pi);
	}
	return 0;
}
