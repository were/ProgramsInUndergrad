/*
ID : weng_xo2
PROG : fence4
LANG : C++
*/
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

struct P {
	double x, y;
	
	P() {}

	P(double x, double y) : x(x), y(y) {}
	
	P sub(P b) {
		return P(x - b.x, y - b.y);
	}
	
	P add(P b) {
		return P(x + b.x, y + b.y);
	}
	
	double dot(P b) {
		return x * b.x + y * b.y;
	}
	
	P mul(double t) {
		return P(x * t, y * t);
	}
	
	double det(P b) {
		return x * b.y - y * b.x;
	}
};


using std::max;
using std::min;

int N, x, y, ans;
double length[200];
bool hsh[200];
P a, b, p[200];
	
const double EPS = 1e-10, PI = 3.141592653589793;
	
int sig(double x) {
	if(x < -EPS) {
		return -1;
	}
	if(x > EPS) {
		return 1;
	}
	return 0;
}

bool crsSS(P p1, P p2, P q1, P q2) {
	if(max(p1.x, p2.x) + EPS < min(q1.x, q2.x)) {
		return false;
	}
	if(max(q1.x, q2.x) + EPS < min(p1.x, p2.x)) {
		return false;
	}
	if(max(p1.y, p2.y) + EPS < min(q1.y, q2.y)) {
		return false;
	}
	if(max(q1.y, q2.y) + EPS < min(p1.y, p2.y)) {
		return false;
	}
	return sig(p2.sub(p1).det(q1.sub(p1))) * sig(p2.sub(p1).det(q2.sub(p1))) < 0
		&& sig(q2.sub(q1).det(p1.sub(q1))) * sig(q2.sub(q1).det(p2.sub(q1))) < 0;
}
	
bool crsSS1(P p1, P p2, P q1, P q2) {
	if(max(p1.x, p2.x) + EPS < min(q1.x, q2.x)) {
		return false;
	}
	if(max(q1.x, q2.x) + EPS < min(p1.x, p2.x)) {
		return false;
	}
	if(max(p1.y, p2.y) + EPS < min(q1.y, q2.y)) {
		return false;
	}
	if(max(q1.y, q2.y) + EPS < min(p1.y, p2.y)) {
		return false;
	}
	return sig(p2.sub(p1).det(q1.sub(p1))) * sig(p2.sub(p1).det(q2.sub(p1))) <= 0
		&& sig(q2.sub(q1).det(p1.sub(q1))) * sig(q2.sub(q1).det(p2.sub(q1))) <= 0;
}

double isLL(P p1, P p2, P q1, P q2) {
	if(!crsSS(p1, p2, q1, q2)) {
		return 1e9;
	}
	double d = q2.sub(q1).det(p2.sub(p1));
	if(fabs(d) < EPS) {
		return 1e9;
	}
	return q2.sub(q1).det(q1.sub(p1)) / d;
}

void print(int i, int j) {
	printf("%d %d %d %d\n", (int)p[i].x, (int)p[i].y, (int)p[j].x, (int)p[j].y);
}
	
int main() {
	freopen("fence4.in", "r", stdin);
	freopen("fence4.out", "w", stdout);
	scanf("%d", &N);
	scanf("%lf%lf", &a.x, &a.y);
	for(int i = 0; i < N; ++i) {
		scanf("%lf%lf", &p[i].x, &p[i].y);
	}
	for(int i = 0; i < N; ++i) {
		for(int j = i + 1; j < N; ++j) {
			if(crsSS(p[i], p[(i + 1) % N], p[j], p[(j + 1) % N])) {
				puts("NOFENCE");
				return 0;
			}
		}
	}
	for(double angle = 0; angle < PI * 2; angle += 0.0001) {
		b.x = a.x + 1e9 * cos(angle);
		b.y = a.y + 1e9 * sin(angle);
		for(int i = 0; i < N; ++i) {
			length[i] = isLL(a, b, p[i], p[(i + 1) % N]);
		}
		int pos = -1, neg = -1;
		for(int i = 0; i < N; ++i) {
			if(length[i] != 1e9 && length[i] > 0){
				if(pos == -1 || length[pos] > length[i]) {
					pos = i;
				}
			}
			if(length[i] != 1e9 && length[i] < 0){
				if(neg == -1 || length[neg] < length[i]) {
					neg = i;
				}
			}
		}
		if(pos != -1) {
			hsh[pos] = true;
		}
		if(neg != -1) {
			hsh[neg] = true;
		}
	}
	for(int i = 0; i < N; ++i) {
		if(hsh[i]) {
			++ans;
		}
	}
	printf("%d\n", ans);
	for(int i = 0; i < N - 2; ++i) {
		if(hsh[i]) {
			print(i, (i + 1) % N);
		}
	}
	if(hsh[N - 1]) {
		print(0, N - 1);
	}
	if(hsh[N - 2]) {
		print(N - 2, N - 1);
	}
	return 0;
}
