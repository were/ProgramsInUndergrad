#include <algorithm>
#include <cstdio>
#include <utility>
#define rep(i,f,t) for(int i(f);i<=(t);++i)

using std::sort;
using std::pair;

const int MaxN = 100010;

struct Data {
	int s, b, idx;
}data[MaxN];

int N, idx[MaxN], f[MaxN], g[MaxN], pre[MaxN], ans;

bool cmp(const Data &a, const Data &b) {
	return a.s != b.s ? a.s < b.s : a.b < b.b;
}

void work(int x) {
	int l = 1, r = x;
	while(l < r) {
		int mid = (l + r) / 2;
		if(data[g[mid]].b < data[x].b) {
			l = mid + 1;
		}
		else {
			r = mid;
		}
	}
//	printf("%d %d\n", x, l);
//	for(int i = 0; i <= N; ++i) {
//		printf("%d ", data[g[i]].b);
//	}
//	puts("");
	f[x] = l;
	pre[x] = g[l - 1];
}

int main() {
	scanf("%d", &N);
	data->s = data->b = ~0u >> 1;
	rep(i, 1, N) {
		scanf("%d%d", &data[i].s, &data[i].b);
		data[i].idx = i;
	}
	sort(data + 1, data + 1 + N, cmp);
	rep(l, 1, N) {
		int r = l;
		while(data[r].s == data[l].s) {
			++r;
		}
		for(int i = l; i < r; ++i) {
			work(i);
		}
		for(int i = l; i < r; ++i) {
			if(data[i].b < data[g[f[i]]].b) {
				g[f[i]] = i;
			}
			if(f[i] > f[ans]) {
				ans = i;
			}
		}
		l = r - 1;
	}
	printf("%d\n", f[ans]);
	while(ans) {
		printf("%d ", data[ans].idx);
		ans = pre[ans];
	}
	puts("");
	return 0;
}
