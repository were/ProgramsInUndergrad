#include <cstdio>

int N, ans;
bool hsh[1000001];

int main() {
	scanf("%d", &N);
	hsh[0] = hsh[1] = true;
	for(int i = 2; i <= N; ++i) {
		if(!hsh[i]) {
			for(int j = i + i; j <= N; j += i) {
				hsh[j] = true;
			}
			if(!hsh[i - 2]) {
				++ans;
			}
		}
	}
	printf("%d\n", ans);
	for(int i = 3; i + 2 <= N; ++i) {
		if(!hsh[i] && !hsh[i + 2]) {
			printf("2 %d\n", i);
		}
	}
}