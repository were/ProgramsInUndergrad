#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MaxN = 100010;

int N, M, pre[MaxN], a[MaxN];
vector<int> g[MaxN];

void dfs(int x, int _pre) {
	pre[x] = _pre;
	for(auto &v : g[x]) {
		if(!pre[v] && v != 1) {
			dfs(v, x);
		}
	}
}

int main() {
	cin >> N >> M;
	for(int i = 1; i <= N; ++i) {
		cin >> a[i];
	}
	for(int i = 1; i < N; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(1, -1);
	while(M--) {
		int op, x;
		cin >> op >> x;
		if(op == 1) {
			int v = a[x];
			x = pre[x];
			for(; ~x; x = pre[x]) {
				if(__gcd(v, a[x]) > 1) {
					break;
				}
			}
			cout << x << endl;
		} else {
			cin >> a[x];
		}
	}
	return 0;
}
