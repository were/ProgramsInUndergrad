#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int T;
long long N, M, V, K;

int main() {
	cin >> T;
	while(T--) {
		cin >> N >> M >> V >> K;
		int ans = 0;
		while(M < N) {
			if((M - V) * K > M) {
				M = (M - V) * K;
				++ans;
			}
			else {
				ans = - 1;
				break;
			}
		}
		cout << ans << endl;
	}
}
