/*
ID : weng_xo 2
PROB : rect1
LANG : C++
*/
#include <cstdio>

#define area ((rx - lx) * (ry - ly))

double max(double a, double b) {
	return a > b ? a : b;
}

double min(double a, double b) {
	return a < b ? a : b;
}

const int MaxN = 1010;
int N;
double x1[MaxN], x2[MaxN], y1[MaxN], y2[MaxN], ans;

void cover(double lx, double ly, double rx, double ry, int cur){
	if(area != 0 && cur <= N){
		if(lx < x1[cur])
			cover(lx, max(ly, y1[cur]), min(rx, x1[cur]), max(ry, y1[cur]), cur + 1);
		if(ry > y2[cur])
			cover(max(x1[cur], lx), max(ly, y2[cur]), max(x1[cur], rx), ry, cur + 1);
		if(rx > x2[cur])
			cover(max(lx, x2[cur]), min(y2[cur], ly), rx, min(y2[cur], ry), cur + 1);
		if(ly < y1[cur])
			cover(min(x2[cur], lx), ly, min(x2[cur], rx), min(ry, y1[cur]), cur + 1);
	} else {
		ans += area;
	}
}

int main(){
	while(scanf("%d", &N), N) {
		static int cs = 0;
		for(int i = 1; i <= N; ++i) {
			scanf("%lf%lf%lf%lf", x1 + i, y1 + i, x2 + i, y2 + i);
		}
		ans = 0.;
		for(int i = N; i >= 0; --i) {
			cover(x1[i], y1[i], x2[i], y2[i], i + 1);
		}
		printf("Test case #%d\nTotal explored area: %.2f\n\n", ++cs, ans);
	}
	return 0;
}

