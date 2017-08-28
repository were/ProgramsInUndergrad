#include <algorithm>
#include <iostream>
#include <utility>
#define debug(x) std :: cout << #x << (x) << "\n"
typedef long long ll;
typedef std :: pair<ll, ll> llll;
ll N, B, a[101], d, x[101];
llll extendEuclid(ll a, ll b){
	if(b){
#define x2 tmp.first
#define y2 tmp.second
		llll tmp = extendEuclid(b, a % b);
		return std :: make_pair(y2, x2 - (a / b) * y2);
#undef x2
#undef y2
	}else
		return std :: make_pair(1ll, 0ll);
}
void getIt(ll&x){
	x = (x % a[0] + a[0]) % a[0];
}
int main(){
	std :: cin >> N >> a[0] >> B;
	d = a[0];
	std :: fill(x, x + N + 1, 1);
	for(int i = 1;i <= N;++ i){
		std :: cin >> a[i];
		a[i] %= a[0];
		llll tmp = extendEuclid(d, a[i]);
		d = d * tmp.first + a[i] * tmp.second;
		getIt(tmp.first);
		getIt(tmp.second);
//		debug(d);
		for(int j = 0;j < i;++ j)
			x[j] = x[j] * tmp.first % a[0];
		x[i] = tmp.second;
	}
	if(B % d == 0){
		std :: cout << "YES\n";
		for(int i = 1;i <= N;++ i)
			std :: cout << x[i] * (B / d) % a[0] << " ";
	}else
		std :: cout << "NO";
	std :: cout << "\n";
	return 0;
}
