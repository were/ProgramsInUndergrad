#include <cmath>
#include <cstdio>
#include <cstdlib>
const int MaxN = 10001;
const double eps = 1e-6;
int N, cnt;
struct Coordinate{
	double x, y;
	Coordinate() : x(0.), y(0.) {}
	Coordinate(double x, double y) : x(x), y(y) {}
	void fromInput(){
		scanf("%lf%lf", &x, &y);
	}
}O;
Coordinate operator- (const Coordinate&a, const Coordinate&b){
	return Coordinate(a.x - b.x, a.y - b.y);
}
double operator* (const Coordinate&a, const Coordinate&b){
	return a.x * b.y - a.y * b.x;
}
struct Ray{
	Coordinate O, dir;
	void fromInput(){
		O.fromInput();
		dir.fromInput();
		dir = dir - O;
	}
}seg[MaxN], laser;
void intersection(const Ray&a, const Ray&b, double&t0, double&t1){
	double
		a0 = a.dir.x, b0 = -b.dir.x, c0 = b.O.x - a.O.x,
		a1 = a.dir.y, b1 = -b.dir.y, c1 = b.O.y - a.O.y;
	double det = Coordinate(a0, b0) * Coordinate(a1, b1);
	t0 = Coordinate(c0, b0) * Coordinate(c1, b1) / det;
	t1 = Coordinate(a0, c0) * Coordinate(a1, c1) / det;
}
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++i)
		seg[i].fromInput();
	O.fromInput();
	laser.O = O;
	laser.dir = Coordinate(1., 0.);
	for(int i = 1;i <= N;++i){
		double t0, t1;
		intersection(laser, seg[i], t0, t1);
		if(fabs(t0) < eps){
			puts("BORDER");
			return 0;
		}
		if(t0 >= 0 && t1 > 0 && t1 <= 1.)
			++cnt;
	}
	puts(cnt % 2 == 0 ? "OUTSIDE" : "INSIDE");
	return 0;
}

