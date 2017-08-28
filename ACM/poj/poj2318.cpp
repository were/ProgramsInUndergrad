#include <cstdio>
#include <utility>

typedef std::pair<int, int> PII;

const int MaxN = 5555;

int N, M, x1, y1, x2, y2, ans[MaxN];
PII u[MaxN], d[MaxN];

PII operator- (PII a, PII b) {
	return PII(a.first - b.first, a.second - b.second);
}

long long det(PII a, PII b) {
	return 1ll * a.first * b.second - 1ll * a.second * b.first;
}

int sgn(long long x) {
	return x < 0 ? -1 : x > 0;
}

int main() {
	while(scanf("%d%d%d%d%d%d", &N, &M, &x1, &y1, &x2, &y2) == 6) {
		u[0] = PII(x1, y1);
		d[0] = PII(x1, y2);
		ans[0] = 0;
		for(int i = 1; i <= N; ++i) {
			int a, b;
			ans[i] = 0;
			scanf("%d%d", &a, &b);
			u[i] = PII(a, y1);
			d[i] = PII(b, y2);
		}
		u[N + 1] = PII(x2, y1);
		d[N + 1] = PII(x2, y2);
		while(M--) {
			PII a;
			scanf("%d%d", &a.first, &a.second);
			for(int j = 0; j <= N; ++j) {
				if(sgn(det(d[j] - a, u[j] - a)) * sgn(det(d[j + 1] - a, u[j + 1] - a)) <= 0) {
//printf("%d %d in %d %d\n", a.first, a.second, j, j + 1);
					++ans[j];
					break;
				}
			}
		}
		for(int i = 0; i <= N; ++i) {
			printf("%d: %d\n", i, ans[i]);
		}
		puts("");
	}
}
