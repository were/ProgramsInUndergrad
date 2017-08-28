#include <algorithm>
#include <cstdio>

const int MaxN = 10010;

int T, N, K, cs;
int x[MaxN], h[MaxN], H[MaxN];

void work() {
	for(int i = 0, l = -1, r = -1; i < N; ++i) {
		if(!h[i]) {
			if(l == -1) {
				l = i;
				while(l >= 0 && !h[l]) {
					--l;
				}
			}
			if(r == -1) {
				r = i;
				while(r < N && !h[r]) {
					++r;
				}
			}
			int d = ~0u >> 1;
			if(l >= 0 && l < N) {
				if(x[i] - x[l] < d) {
					d = x[i] - x[l];
					H[i] = h[l];
				}
			}
			if(r >= 0 && r < N) {
				if(x[r] - x[i] < d) {
					H[i] = h[r];
				}
				else {
					if(x[r] - x[i] == d && h[r] > H[i]) {
						H[i] = h[r];
					}
				}
			}
		}
		else {
			l = i;
			r = -1;
		}
	}
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		for(int i = 0; i < N; ++i) {
			scanf("%d%d", x + i, h + i);
		}
		scanf("%d", &K);
		work();
		printf("Case #%d:\n", ++cs);
		while(K--) {
			char s[2];
			scanf("%s", s);
			if(*s == 'U') {
				int a, b;
				scanf("%d%d", &a, &b);
				h[a] = b;
				work();
			}
			else {
				int r, ans = 0;
				scanf("%d", &r);
				for(int i = 0; i < N; ++i) {
					if(h[i] && h[i] <= r) {
						++ans;
					}
					if(!h[i] && H[i] <= r) {
						++ans;
					}
				}
				printf("%d\n", ans);
			}
		}
	}
}
