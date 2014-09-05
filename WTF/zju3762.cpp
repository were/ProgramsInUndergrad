#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

using namespace std;

const double EPS = 1e-8;

int N, n, bottom;
double ans;

struct Cor {
	double x, y;
	Cor(double x, double y) : x(x), y(y) {}
	Cor() {}
}a[555], hull[555];

Cor operator- (Cor a, Cor b) {
	return Cor(a.x - b.x, a.y - b.y);
}

double det(Cor a, Cor b) {
	return a.x * b.y - a.y * b.x;
}

double sqr(double x) {
	return x * x;
}

double dis(Cor a, Cor b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

bool cmp(Cor a, Cor b) {
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}

int nxt(int x) {
	return x + 1 <= n ? x + 1 : 1;
}

double area(Cor a, Cor b, Cor c) {
	return fabs(det(c - a, c - b));
}

int main() {
	while(~scanf("%d", &N)) {
		rep(i, 1, N) {
			scanf("%lf%lf", &a[i].x, &a[i].y);
		}
		sort(a + 1, a + 1 + N, cmp);
		n = 0;
		rep(i, 1, N) {
			while(n >= 2 && det(hull[n] - hull[n - 1], a[i] - hull[n - 1]) < EPS) {
				--n;
			}
			hull[++n] = a[i];
		}
		bottom = n;
		per(i, N, 1) {
			while(n > bottom && det(hull[n] - hull[n - 1], a[i] - hull[n - 1]) < EPS) {
				--n;
			}
			hull[++n] = a[i];
		}
		/*
		rep(i, 1, n) {
			printf("%f %f\n", hull[i].x, hull[i].y);
		}
		*/
		--n;
		ans = 0.;
		rep(i, 1, n) {
			rep(j, 1, N) {
				ans = max(ans, area(hull[i], hull[nxt(i)], a[j]) / dis(hull[i], hull[nxt(i)]));
			}
		}
		rep(i, 1, n) {
			rep(j, 1, N) if(dis(hull[i], a[j]) > ans) {
				rep(k, j + 1, N) {
					ans = max(ans, area(hull[i], a[j], a[k]) / dis(a[j], a[k]));
				}
			}
		}
		printf("%.8f\n", ans);
	}
	return 0;
}
