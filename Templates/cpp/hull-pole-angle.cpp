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
	double length(){
		return sqrt(x * x + y * y);
	}
	double operator% (const Coordinate&a) const {
		return x * a.y - y * a.x;
	}
}O;
int N;
int sgn(double x){
	return x < -eps ? -1 : x > eps;
}
bool cmp(const Coordinate&a, const Coordinate&b){
	double ret = (a - O) % (b - O);
	if(sgn(ret) == 0)
		return sgn((a - O).length() - (b - O).length()) < 0;
	return sgn(ret) > 0;
}
void makeHull(Coordinate*cor, Coordinate*hull){
	O = *std::min_element(cor, cor + N);
	std::sort(cor, cor + N, cmp);
	int top = 0;
	for(int i = 0;i < N; ++i){
		while(top > 1 && sgn((hull[top - 1] - hull[top - 2]) % (cor[i] - hull[top - 1])) < 0)
			-- top;
		hull[top ++] = cor[i];
	}
}
int main(){
}
