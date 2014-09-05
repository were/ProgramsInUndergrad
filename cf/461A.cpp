#include <functional>
#include <iostream>
#include <queue>

using namespace std;

typedef long long LL;

int N, x;
long long sum, ans;
priority_queue<int> q;

int main() {
	cin >> N;
	for(int i = 0; i < N; ++i) {
		cin >> x;
		q.push(-x);
		sum += x;
	}
	while(!q.empty()) {
		if(q.size() != 1u) {
			ans += sum;
		}
		ans -= q.top();
		sum += q.top();
		q.pop();
	}
	cout << ans << endl;
}
