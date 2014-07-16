#include <cstdio>
#include <set>

const int inf = ~0u >> 1;

std::set<int> T_T;

int M, p, x;

long long abs(long long x) {
	return x < 0 ? -x : x;
}

long long min(long long a, long long b) {
	return a < b ? a : b;
}

int main() {
	scanf("%d", &M);
	T_T.insert(inf);
	T_T.insert(-inf);
	while(M--) {
		scanf("%d%d", &p, &x);
		if(p == 1) {
			T_T.insert(x);
		}
		if(p == 2) {
			T_T.erase(x);
		}
		if(p == 0) {
			std::set<int>::iterator nxt = T_T.lower_bound(x);
			long long ans = abs(x - *nxt);
			--nxt;
			ans = min(ans, abs(x - *nxt));
			printf("%lld\n", ans);
		}
	}
	return 0;
}
