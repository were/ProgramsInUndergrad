#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

typedef long long LL;

const int MaxN = 100010;

const LL Mod = 1000000000 + 7;

char s[MaxN];
string t[MaxN];
int N, d[MaxN];
LL a[20], b[20];

int main() {
	scanf("%s%d", s, &N);
	for(int i = 0; i < N; ++i) {
		scanf("%d-", d + i);
		cin >> t[i];
	}
	for(int i = 0; i < 10; ++i) {
		a[i] = i;
		b[i] = 10;
	}
	for(int i = N - 1; i >= 0; --i) {
		LL _a = 0, _b = 1;
		for(int j = t[i].size() - 1; j > 0; --j) {
			(_a += _b * a[t[i][j] - '0']) %= Mod;
			(_b *= b[t[i][j] - '0']) %= Mod;
		}
		a[d[i]] = _a;
		b[d[i]] = _b;
	}
	LL _a = 0, _b = 1;
	for(int i = strlen(s) - 1; i >= 0; --i) {
		(_a += _b * a[s[i] - '0']) %= Mod;
		(_b *= b[s[i] - '0']) %= Mod;
	}
	cout << _a << endl;
	return 0;
}
