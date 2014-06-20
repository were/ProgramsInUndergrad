#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MaxN = 111;

int N, M, l[MaxN], v[MaxN], cnt[MaxN];
bool hsh[1000];

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 0; i < N; ++i) {
		scanf("%d", l + i);
	}
	for(int i = 0; i < N; ++i) {
		scanf("%d", v + i);
	}
	for(int i = 0; i < N; ++i) {
		for(int j = i + 1; j < N; ++j) if(v[i] * v[j] < 0) {
			int a = l[i], b = l[j];
			for(int k = 0; k < M; ++k) {
				memset(hsh, 0, sizeof hsh);
				bool flag = false;
				for(int t = 0; t < abs(v[i]); ++t) {
					if(v[i] > 0) {
						(++a) %= 1000;
					}
					else {
						(--a += 1000) %= 1000;
					}
					hsh[a] = true;
				}
				for(int t = 0; t < abs(v[j]); ++t) {
					if(hsh[b]) {
						flag = true;
					}
					if(v[j] > 0) {
						(++b) %= 1000;
					}
					else {
						(--b += 1000) %= 1000;
					}
				}
				if(hsh[b]) {
					flag = true;
				}
				if(flag) {
					++cnt[i];
					++cnt[j];
				}
			}
		}
	}
	for(int i = 0; i < N; ++i) {
		printf("%d ", cnt[i]);
	}
	puts("");
	return 0;
}
