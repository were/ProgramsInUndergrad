#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define debug(x) std :: cout << #x << "=" << (x) << "\n";
const double pi = 3.1415926535897932384626433832795, eps = 1e-6;
int N, N1, N2;
double OAngle, OA;
double sqr(double x){
	return x * x;
}
struct Coordinate{
	double x, y;
	Coordinate() : x(0.), y(0.) {}
	Coordinate(double x, double y) : x(x), y(y) {}
	void fromInput(){
		scanf("%lf%lf", &x, &y);
	}
	Coordinate vertical(){
		return Coordinate(y, -x);
	}
	double distanceSqr(const Coordinate&a){
		return sqr(a.x - x) + sqr(a.y - y);
	}
	double getLengthSqr(){
		return distanceSqr(Coordinate(0., 0.));
	}
	Coordinate setLength(double length = 1.){
		double len = sqrt(getLengthSqr());
		return Coordinate(x / len * length, y / len * length);
	}
	Coordinate clockwiseRotate(double theta){
		return Coordinate(x * cos(2. * pi - theta) - y * sin(2. * pi - theta), x * sin(2. * pi - theta) + y * cos(2. * pi - theta));
	}
	void show(){
		if(fabs(x) < eps) x = 0.;
		if(fabs(y) < eps) y = 0.;
		printf("%.6f %.6f\n", x, y);
	}
}ans[155], O, delta;
Coordinate operator- (const Coordinate&a, const Coordinate&b){
	return Coordinate(a.x - b.x, a.y - b.y);
}
Coordinate operator+ (const Coordinate&a, const Coordinate&b){
	return Coordinate(a.x + b.x, a.y + b.y);
}
Coordinate operator* (const Coordinate&a, const double&b){
	return Coordinate(a.x * b, a.y * b);
}
double operator% (const Coordinate&a, const Coordinate&b){
	return a.x * b.y - a.y * b.x;
}
bool operator!= (const Coordinate&a, const Coordinate&b){
	return fabs(a.x - b.x) > eps || fabs(a.y - b.y) > eps;
}
int main(){
	scanf("%d%d%d", &N, &N1, &N2);
	ans[N1].fromInput();
	ans[N2].fromInput();
	if(N1 > N2)
		std :: swap(N1, N2);
	OAngle = (N2 - N1) * (pi * 2. / N);
	OA = sqrt(ans[N1].distanceSqr(ans[N2]) / (2. - 2. * cos(OAngle)));
	delta = (ans[N2] - ans[N1]).clockwiseRotate((pi - OAngle) / 2.).setLength(OA);
	O = ans[N1] + delta;
	delta = (delta * -1).clockwiseRotate(pi * 2. / N);
	for(int i = N1 % N + 1;i != N1;i = i % N + 1){
		ans[i] = O + delta;
		delta = delta.clockwiseRotate(pi * 2. / N);
	}
	for(int i = 1;i <= N;++i)
		ans[i].show();
	return 0;
}
