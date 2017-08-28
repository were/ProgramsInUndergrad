#include <algorithm>
#include <cmath>
#include <cstdio>
const int MaxN = 1000;
const double eps = 1e-8;
struct Coordinate{
	double x, y;
	Coordinate() : x(0.), y(0.) {}
	Coordinate(double x, double y) : x(x), y(y) {}
	bool operator< (const Coordinate&a) const {
		return x != a.x ? x < a.x : y < a.y;
	}
	Coordinate operator- (const Coordinate&a) const {
		return Coordinate(x - a.x, y - a.y);
	}
	double operator% (const Coordinate&a) const {
		return x * a.y - y * a.x;
	}
	double length(){
		return sqrt(x * x + y * y);
	}
	void fromInput(){
		scanf("%lf%lf", &x, &y);
	}
}cor[MaxN], hull[MaxN], O, a, b;
int sgn(double x){
	return x < -eps ? -1 : x > eps;
}
bool cmp(const Coordinate&a, const Coordinate&b){
	double ret = (a - O) % (b - O);
	if(sgn(ret) == 0)
		return sgn((a - O).length() - (b - O).length()) < 0;
	return sgn(ret) > 0;
}
int N, M, top;
double calc(const Coordinate&a, const Coordinate&b){
	double l = 0., r = 1.;
	for(int i = 0;i < N;++ i){
		Coordinate p = hull[i], q = hull[(i + 1) % N];
		if(sgn((q - p) % (a - p)) <= 0 && sgn((q - p) % (b - p)) <= 0)
			return 0.;
		if(sgn((q - p) % (a - b))){
			double
				s1 = (q - p) % (a - p),
				s2 = (q - p) % (b - p);
			double
				t = s1 / (s1 - s2);
			if(sgn(t) >= 0 && sgn(t - 1.) <= 0){
				if(sgn(s1) > 0)
					r = std :: min(r, t);
				if(sgn(s2) > 0)
					l = std :: max(l, t);
			}
		}
	}
	return (b - a).length() * std :: max(r - l, 0.);
}
int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++ i)
		cor[i].fromInput();
	O = *std :: min_element(cor, cor + N);
	std :: sort(cor, cor + N, cmp);
	for(int i = 0;i < N;++ i){
		while(top > 1 && sgn((hull[top - 1] - hull[top - 2]) % (cor[i] - hull[top - 1])) < 0)
			-- top;
		hull[top ++] = cor[i];
	}
	scanf("%d", &M);
	for(int i = 0;i < M;++ i){
		a.fromInput();
		b.fromInput();
		printf("%f\n", calc(a, b));
	}
	return 0;
}

