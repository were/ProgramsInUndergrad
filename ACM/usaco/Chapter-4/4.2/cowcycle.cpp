/*
PROG : cowcycle
ID : weng_xo2
LANG : C++11
*/

#include <algorithm>
#include <cstdio>
#include <cstring>

using std::sort;

int F, R, a, b, c, d;
int f[11], r[11];
int ansF[11], ansR[11];
double ratio[100], res = 1e9;

void dffffs(int x, int l) {
	if(x < R) {
		for(r[x] = l; r[x] <= d; ++r[x]) {
			dffffs(x + 1, r[x] + 1);
		}
	}
	else {
		if(f[F - 1] * r[R - 1] < 3 * r[0] * f[0]) {
			return;
		}
/*
		puts("checking...");
		for(int i = 0; i < R; ++i) {
			printf("%d ", r[i]);
		}
		puts("");
*/
		for(int i = 0; i < F; ++i) {
			for(int j = 0; j < R; ++j) {
				ratio[i * R + j] = (double)(f[i]) / r[j];
//				printf("%d/%d=%f\n", f[i], r[j], ratio[i * R + j]);
			}
		}
//		puts("");
		sort(ratio, ratio + F * R);
		double avg = 0, var = 0;
		for(int i = F * R - 1; i > 0; --i) {
			ratio[i] -= ratio[i - 1];
			avg += ratio[i];
//			printf("%f\n", ratio[i]);
		}
		avg /= (F * R - 1);
//		printf("%f\n", avg);
		for(int i = 1; i < F * R; ++i) {
			var += (ratio[i] - avg) * (ratio[i] - avg);
		}
		var /= (F * R - 1);
//		printf("%f\n", var);
		if(var < res) {
			res = var;
			memcpy(ansF, f, sizeof(int) * F);
			memcpy(ansR, r, sizeof(int) * R);
		}
	}
}

void dfs(int x, int l) {
	if(x < F) {
		for(f[x] = l; f[x] <= b; ++f[x]) {
			dfs(x + 1, f[x] + 1);
		}
	}
	else {
/*
		puts("F...");
		for(int i = 0; i < F; ++i) {
			printf("%d ", f[i]);
		}
		puts("");
*/
		dffffs(0, c);
	}
}

int main() {
	freopen("cowcycle.in", "r", stdin);
	freopen("cowcycle.out", "w", stdout);
	scanf("%d%d%d%d%d%d", &F, &R, &a, &b, &c, &d);
//	printf("%d %d %d %d %d %d\n", F, R, a, b, c, d);
	dfs(0, a);
	for(int i = 0; i < F; ++i) {
		printf(i == F - 1 ? "%d\n" : "%d ", ansF[i]);
	}
	for(int i = 0; i < R; ++i) {
		printf(i == R - 1 ? "%d\n" : "%d ", ansR[i]);
	}
	return 0;
}
