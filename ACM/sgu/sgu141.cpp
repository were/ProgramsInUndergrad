#include <cstdlib>
#include <iostream>
typedef long long ll;
ll x1, x2, P, K, x, y, d, dx, dy, P1, P2, N1, N2;
ll abs(ll a){
	return a > 0 ? a : -a;
}
void extendEuclid(ll a, ll b, ll&x, ll&y){
	if(b){
		extendEuclid(b, a % b, y, x);
		y -= (a / b) * x;
	}else{
		x = 1ll;
		y = 0ll;
		d = a;
	}
}
void noSolution(){
	std :: cout << "NO\n";
	exit(0);
}
int main(){
	std :: cin >> x1 >> x2 >> P >> K;
	extendEuclid(x1, x2, x, y);
	if(abs(P) % d != 0)
		noSolution();
	x *= P / d; y *= P / d;
	dx = x2 / d; dy = x1 / d;
	for(;abs(x + dx) + abs(y - dy) < abs(x) + abs(y);x += dx, y -= dy);
	for(;abs(x - dx) + abs(y + dy) < abs(x) + abs(y);x -= dx, y += dy);
	if(abs(x) + abs(y) > K)
		noSolution();
	if((K - abs(x) - abs(y)) % 2  == 1){
		if((abs(dx) + abs(dy)) % 2 == 0)
			noSolution();
		if(abs(x + dx) + abs(y - dy) < abs(x - dx) + abs(y + dy)){
			x += dx;
			y -= dy;
		}else{
			x -= dx;
			y += dy;
		}
		if(abs(x) + abs(y) > K)
			noSolution();
	}
	x > 0 ? P1 = x : N1 = -x;
	y > 0 ? P2 = y : N2 = -y;
	K = K - abs(x) - abs(y) >> 1;
	std :: cout << "YES\n" << P1 + K << " " << N1 + K << " " << P2 << " " << N2 << "\n";
	return 0;
}
