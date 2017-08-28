#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

using namespace std;

typedef pair<int, int> PII;

int N;

PII operator- (PII a, PII b) {
	return PII(a.first - b.first, a.second - b.second);
}

PII O;

int det(PII a, PII b) {
	return a.first * b.second - a.second * b.first;
}

int dis2(PII a, PII b) {
	PII d = a - b;
	return d.first * d.first + d.second * d.second;
}

bool cmp(PII a, PII b) {
	int ky = det(a - O, b - O);
	return ky ? ky > 0 : dis2(a, O) < dis2(b, O);
}

int main() {
	scanf("%d", &N);
	vector<pair<int, int> > a(N, make_pair(0, 0)), hull(N, make_pair(0, 0));
	for(int i = 0; i < N; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
	}
	O = *min_element(a.begin(), a.end());
	sort(a.begin(), a.end(), cmp);
	int n = 0;
	for(int i = 0; i < N; ++i) {
		while(n > 1 && det(hull[n - 1] - hull[n - 2], a[i] - hull[n - 1]) < 0)
			--n;
		hull[n++] = a[i];
	}
	int ans = 0;
	for(int i = 2; i < n; ++i) {
		ans += det(hull[i - 1] - hull[0], hull[i] - hull[0]);
	}
	printf("%d\n", ans / 100);
	return 0;
}
