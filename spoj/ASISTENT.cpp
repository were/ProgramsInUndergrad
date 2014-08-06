#include <algorithm>
#include <cctype>
#include <cstdio>
#include <utility>
#include <vector>

using namespace std;

typedef long long LL;

const int MaxN = 50010;
const LL Mod = 1000000000 + 7;

char inBuffer[10000000], outBuffer[10000000], *hd = inBuffer, *tl = outBuffer;

struct Data {
	int first;
	LL second;
	Data(int first, LL second) : first(first), second(second) {}
	Data() : first(0), second(0ll) {}
	Data & operator+= (const Data &b) {
		first += b.first;
		((second += b.second) += Mod) %= Mod;
		return *this;
	}
};


int N, M, a[MaxN], backup[MaxN], l[MaxN], r[MaxN], n[MaxN], myBit[MaxN], lowbit[MaxN];
LL fac[MaxN], ans;
vector<Data> bit[MaxN];
vector<int> num[MaxN];

__inline int nextInt() {
	while(!isdigit(*hd)) {
		++hd;
	}
	int ret = *hd++ - '0';
	while(isdigit(*hd)) {
		ret = ret * 10 + *hd++ - '0';
	}
	return ret;
}

void printInt(int x) {
	if(x >= 10) {
		printInt(x / 10);
	}
	*tl++ = x % 10 + '0';
}

__inline void printLn(int x) {
	if(x) {
		printInt(x);
	} else {
		*tl++ = '0';
	}
	*tl++ = '\n';
}

__inline void insert(int x, int ky) {
	for(int i = x; i <= N; i += lowbit[i]) {
		num[i].push_back(ky);
	}
	for(int i = x - 1; i; i -= lowbit[i]) {
		num[i].push_back(ky);
	}
}

__inline void modify(int x, int ky, Data delta) {
	for(int i = x; i <= N; i += lowbit[i]) {
		for(int j = lower_bound(num[i].begin(), num[i].begin() + n[i], ky) - num[i].begin() + 1; j <= n[i]; j += lowbit[j]) {
			bit[i][j] += delta;
		}
	}
}

__inline Data query(int x, int ky) {
	Data ret;
	for(int i = x; i; i -= lowbit[i]) {
		for(int j = lower_bound(num[i].begin(), num[i].begin() + n[i], ky) - num[i].begin() + 1; j; j -= lowbit[j]) {
			ret += bit[i][j];
		}
	}
	return ret;
}

int main() {
	fread(hd, 1, 10000000, stdin);
	N = nextInt();
	M = nextInt();
	for(int i = N; i >= 1; --i) {
		lowbit[i] = i & -i;
		a[i] = backup[i] = nextInt();
		for(int j = i; j <= N; j += j & -j) {
			num[j].push_back(a[i]);
		}
	}
	for(int i = 1; i <= M; ++i) {
		l[i] = N - nextInt() + 1;
		r[i] = N - nextInt() + 1;
		if(l[i] > r[i]) {
			swap(l[i], r[i]);
		}
		insert(l[i], a[l[i]]);
		insert(r[i], a[r[i]]);
		swap(a[l[i]], a[r[i]]);
		insert(l[i], a[l[i]]);
		insert(r[i], a[r[i]]);
	}
	*fac = 1;
	for(int i = 1; i <= N; ++i) {
		num[i].push_back(N);
		a[i] = backup[i];
		fac[i] = fac[i - 1] * i % Mod;
		sort(num[i].begin(), num[i].end());
		n[i] = (int) (unique(num[i].begin(), num[i].end()) - num[i].begin());
		bit[i] = vector<Data>(n[i] + 1, Data(0, 0ll));
	}
	for(int i = 1; i <= N; ++i) {
		modify(i, a[i], Data(1, fac[i - 1]));
		for(int j = a[i]; j; j -= j & -j) {
			ans = (ans + fac[i - 1] * myBit[j]) % Mod;
		}
		for(int j = a[i]; j <= N; j += j & -j) {
			++myBit[j];
		}
	}
	for(int i = 1; i <= M; ++i) {
		Data l0(query(l[i] - 1, a[l[i]]));
		Data r0(query(r[i] - 1, a[r[i]]));
		modify(l[i], a[l[i]], Data(-1, -fac[l[i] - 1]));
		modify(r[i], a[r[i]], Data(-1, -fac[r[i] - 1]));
		swap(a[l[i]], a[r[i]]);
		modify(l[i], a[l[i]], Data(1, fac[l[i] - 1]));
		modify(r[i], a[r[i]], Data(1, fac[r[i] - 1]));
		Data l1(query(l[i] - 1, a[l[i]]));
		Data r1(query(r[i] - 1, a[r[i]]));
		ans = (ans + fac[l[i] - 1] * (l1.first - l0.first) + fac[r[i] - 1] * (r1.first - r0.first)) % Mod;
		ans = (ans + (r1.second - l0.second) - (r0.second - l1.second)) % Mod;
		if(a[r[i]] < a[l[i]]) {
			ans = (ans + fac[l[i] - 1]) % Mod;
		} else {
			ans = (ans - fac[l[i] - 1]) % Mod;
		}
		ans = (ans + Mod) % Mod;
		printLn(ans + 1);
	}
	fwrite(outBuffer, 1, tl - outBuffer, stdout);
	return 0;
}


