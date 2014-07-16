#include <cstdio>
#include <cmath>
#define min(a,b) ((a)<(b)?(a):(b))
const double eps = 1e-10;
double sqr(double x){
	return x * x;
}
struct Coordinate{
	double x, y, z;
	Coordinate() : x(0.), y(0.), z(0.) {}
	Coordinate(double x, double y, double z) : x(x), y(y), z(z) {}
	void fromInput(){
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	double Length() const {
		return sqrt(sqr(x) + sqr(y) + sqr(z));
	}
};
Coordinate operator- (const Coordinate&a, const Coordinate&b){
	return Coordinate(a.x - b.x, a.y - b.y, a.z - b.z);
}
Coordinate operator+ (const Coordinate&a, const Coordinate&b){
	return Coordinate(a.x + b.x, a.y + b.y, a.z + b.z);
}
double operator* (const Coordinate&a, const Coordinate&b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
Coordinate operator* (const Coordinate&a, const double&b){
	return Coordinate(a.x * b, a.y * b, a.z * b);
}
Coordinate operator* (const double a, const Coordinate&b){
	return Coordinate(a * b.x, a * b.y, a * b.z);
}
double calcCosine(const Coordinate&a, const Coordinate&b){
	return a * b / a.Length() / b.Length();
}
struct Laser{
	Coordinate O, dir;
	void fromInput(){
		O.fromInput();
		dir.fromInput();
		dir = dir - O;
	}
}laser, newLazer;
struct Sphere{
	Coordinate O;
	double r;
	void fromInput(){
		O.fromInput();
		scanf("%lf", &r);
	}
	bool intersection(const Laser&laser, double&t){
	 	Coordinate tmp = laser.O - O;
		double a = laser.dir * laser.dir, b = 2. * (tmp * laser.dir), c = tmp * tmp - r * r;
		double delta = b * b - 4. * a * c;
		if(delta < -eps)
			return false;
		bool ret = false;
		delta = sqrt(delta);
		double t1 = (-b + delta) / 2. / a, t2 = (-b - delta) / 2. / a;
		if(t1 > eps && t1 < t){
			t = t1;
			ret = true;
		}
		if(t2 > eps && t2 < t){
			t = t2;
			ret = true;
		}
		return ret;
	}
}sphere[51];
int N, ans[12];
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++i)
		sphere[i].fromInput();
	laser.fromInput();
	for(int i = 1, hitOn = -1;i <= 11;++i, hitOn = -1){
		double t = 1e9;
		for(int j = 1;j <= N;++j)
			if(sphere[j].intersection(laser, t))
				hitOn = j;
		if(~hitOn){
			ans[++ans[0]] = hitOn;
			const Sphere&curSphere = sphere[hitOn];
			newLazer.O = laser.O + laser.dir * t;
			Coordinate Nomal = curSphere.O - newLazer.O;
			t = 2. * (Nomal * laser.dir) / sqr(Nomal.Length());
			newLazer.dir = laser.dir - Nomal * t;
			laser = newLazer;
		}else
			break;
	}
	for(int i = 1;i <= min(ans[0], 10);++i)
		printf(i == 1 ? "%d" : " %d", ans[i]);
	if(ans[0] <= 10)
		puts("");
	else
		puts(" etc.");
	return 0;
}
