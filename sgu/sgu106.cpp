#include <algorithm>
#include <iostream>
#define debug(x) std :: cout << #x << " = " << (x) << "\n"
typedef long long ll;
const ll inf = ~0ull >> 1ll;
ll a, b, c, x1, x2, y1, y2, ans, x, y, p, d, l = -inf, r = inf;
void extendEuclid(ll a, ll b){
	if(b){
		extendEuclid(b, a % b);
		ll x2 = x, y2 = y;
		x = y2;
		y = x2 - (a / b) * y2;
	}else{
		x = 1ll;
		y = 0ll;
		d = a;
	}
}
void calc(ll k, ll L, ll R){
	l = std :: max(l, L <= 0 ? L / k : (L - 1) / k + 1);
	r = std :: min(r, R >= 0 ? R / k : (R + 1) / k - 1);
}
int main(){
	std :: cin >> a >> b >> c >> x1 >> x2 >> y1 >> y2;
	if(!a && !b){
		ans = c ? 0 : (x2 - x1 + 1) * (y2 - y1 + 1);
	}else if(!a && b){
		ans = (c % b == 0 && -c / b >= x1 && -c / b <= x2) ? (y2 - y1 + 1) : 0;
	}else if(a && !b){
		ans = (c % a == 0 && -c / a >= y1 && -c / a <= y2) ? (x2 - x1 + 1) : 0;
	}else{
		extendEuclid(a, b);
		if(c % d)
			ans = 0;
		else{
			x *= -c / d;
			y *= -c / d;
			(b / d > 0) ? calc(b / d, x1 - x, x2 - x) : calc(-b / d, x - x2, x - x1);
			(a / d < 0) ? calc(-a / d, y1 - y, y2 - y) : calc(a / d, y - y2, y - y1);
			ans = std :: max(0ll, r - l + 1);
		}
	}
	std :: cout << ans << "\n";
	return 0;
}
