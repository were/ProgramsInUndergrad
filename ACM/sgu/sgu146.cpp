#include <algorithm>
#include <cstdio>
typedef long long ll;
double l;
int N, T, V;
ll total, L;
int main(){
	scanf("%lf%d", &l, &N);
	L = int(l * 10000. + .5);
	for(int i = 0;i < N;++ i){
		scanf("%d%d", &T, &V);
		(total += ll(T) * ll(V) * 10000ll) %= L;
	}
	total %= L;
	total = std :: min(total, L - total);
	printf("%lld.%04lld\n", total / 10000ll, total % 10000ll);
	return 0;
}
