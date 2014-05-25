#include <cstdio>
#include <queue>
#include <utility>

using std::priority_queue;
using std::pair;
using std::make_pair;

typedef long long ll;

const int MaxN = 10000000;

ll f[MaxN + 1];
/*
priority_queue< pair<int, int> > q;

void push(int a, int b) {
	if(a <= MaxN) {
		q.push(make_pair(-a, -b));
	}
}
*/
int main() {
	for(int i = 1; i <= MaxN; i += 2) {
		for(int j = i; j <= MaxN; j += i) {
			++f[j];
		}
	}
	for(int i = 1; i <= MaxN; ++i) {
		f[i] += f[i - 1];
	}
	for(int i = 1; i <= MaxN; ++i) {
		f[i] += f[i - 1];
	}
/*
	for(int i = 1, ans = 0; i <= MaxN; ++i) {
		printf("%d:\n", i);
		while(!q.empty() && -q.top().first <= i) {
			pair<int, int> top = q.top();
			printf("%d\n", -top.second);
			q.pop();
			++ans;
			push(-top.first-top.second, -top.second);
		}
		if(i % 2) {
			printf("%d\n", i);
			++ans;
			push(i + i, i);
		}
		puts("");
		f[i] = ans;
//		printf("%lld\n", f[i]);
	}
//	printf("%lld\n", f[MaxN]);
	for(int i = 1; i <= MaxN; ++i) {
		f[i] += f[i - 1];
	}
*/
	int T, N, cs = 0;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		printf("Case #%d:\n%I64d\n", ++cs, 1ll + N + f[N - 1]);
	}
	return 0;
}
