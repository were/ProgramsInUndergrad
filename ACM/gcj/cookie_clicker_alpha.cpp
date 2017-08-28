#include <cstdio>

int T, cs;
double c, f, x, g, ans;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%lf%lf%lf", &c, &f, &x);
		g = 2.;
		ans = 0.;
		while(x / g > c / g + x / (g + f)){
			ans += c / g;
			g += f;
		}
		printf("Case #%d: %.10f\n", ++cs, ans + x / g);
	}
	return 0;
}
