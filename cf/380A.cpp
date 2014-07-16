#include <algorithm>
#include <cstdio>
#include <utility>
#define rep(i,f,t) for(int i(f);i<=(t);++i)

const int MaxN = 100010;

typedef long long ll;

int M, N, p[MaxN], x[MaxN], y[MaxN], a[MaxN], ans[MaxN];
ll len, q[MaxN];

int main(){
	scanf("%d", &M);
	rep(i, 1, M){
		scanf("%d", p + i);
		if(p[i] == 1)
			scanf("%d", x + i);
		else
			scanf("%d%d", x + i, y + i);
	}
	scanf("%d", &N);
	rep(i, 1, N)
		scanf("%lld", q + i);
	std :: sort(q + 1, q + 1 + N);
	len = 0;
	int cur = 1;
	rep(i, 1, M){
		ll pre = len;
		if(p[i] == 1){
			if(a[0] < 100001)
				a[++ a[0]] = x[i];
			++ len;
		}else{
			rep(j, 1, y[i]){
				rep(k, 1, x[i]){
					if(a[0] < 100001)
						a[++ a[0]] = a[k];
					else
						break;
				}
				if(a[0] >= 100001)
					break;
			}
			len += ll(x[i]) * ll(y[i]);
		}
		while(cur <= N && q[cur] <= len){
			if(q[cur] <= a[0]){
				ans[cur] = a[q[cur]];
			}else{
				if(p[i] == 1)
					ans[cur] = x[i];
				else{
					int idx = (q[cur] - pre) % ll(x[i]);
					if(idx == 0)
						idx = x[i];
					ans[cur] = a[idx];
				}
			}
			++ cur;
		}
	}
	rep(i, 1, N)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
