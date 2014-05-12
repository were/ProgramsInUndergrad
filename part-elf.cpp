#include <cstdio>

using ll = long long;

ll gcd(ll a, ll b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	int T, cs = 0;
	scanf("%d", &T);
	while(T--) {
		ll a, b;
		scanf("%lld/%lld", &a, &b);
		printf("Case #%d: ", ++cs);
		ll d = gcd(a, b);
		a /= d;
		b /= d;
		if((b & -b) != b) {
			puts("impossible");
		}
		else {
			for(ll i = b >> 1, j = 1;i;i >>= 1, ++j) {
				if(a & i) {
					printf("%lld\n", j);
					break;
				}
			}
		}
	}
	return 0;
}
