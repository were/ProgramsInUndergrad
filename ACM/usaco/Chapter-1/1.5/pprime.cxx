/*
PROG : pprime
LANG : C++11
ID : weng_xo2
*/
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

int l, r;
vector<int> num;

bool isPrime(int x) {
	if(x == 1) {
		return false;
	}
	if(x == 2) {
		return true;
	}
	for(int i = 2; i * i <= x; ++i) {
		if(x % i == 0) {
			return false;
		}
	}
	return true;
}
int main() {
	freopen("pprime.in", "r", stdin);
	freopen("pprime.out", "w", stdout);
	scanf("%d%d", &l, &r);
	for(int a = 1; a <= 9; a += 2) {
		if(isPrime(a)) {
			num.push_back(a);
		}
		if(isPrime(a * 10 + a)) {
			num.push_back(a * 10 + a);
		}
		for(int b = 0; b <= 9; ++b) {
			if(isPrime(a * 100 + b * 10 + a)) {
				num.push_back(a * 100 + b * 10 + a);
			}
			if(isPrime(a * 1000 + b * 100 + b * 10 + a)) {
				num.push_back(a * 1000 + b * 100 + b * 10 + a);
			}
			for(int c = 0; c <= 9; ++c) {
				if(isPrime(a * 10000 + b * 1000 + c * 100 + b * 10 + a)) {
					num.push_back(a * 10000 + b * 1000 + c * 100 + b * 10 + a);
				}
				if(isPrime(a * 100000 + b * 10000 + c * 1000 + c * 100 + b * 10 + a)) {
					num.push_back(a * 100000 + b * 10000 + c * 1000 + c * 100 + b * 10 + a);
				}
				for(int d = 0; d <= 9; ++d) {
					if(isPrime(a * 1000000 + b * 100000 + c * 10000 + d * 1000 + c * 100 + b * 10 + a)) {
						num.push_back(a * 1000000 + b * 100000 + c * 10000 + d * 1000 + c * 100 + b * 10 + a);
					}
					if(isPrime(a * 10000000 + b * 1000000 + c * 100000 + d * 10000 + d * 1000 + c * 100 + b * 10 + a)) {
						num.push_back(a * 10000000 + b * 1000000 + c * 100000 + d * 10000 + d * 1000 + c * 100 + b * 10 + a);
					}
				}
			}
		}
	}
	//printf("%d\n", (int)num.size());
	sort(num.begin(), num.end());
	for(unsigned i = 0; i < num.size(); ++i) {
		int x = num[i];
		if(x >= l && x <= r) {
			printf("%d\n", x);
		}
	}
}
