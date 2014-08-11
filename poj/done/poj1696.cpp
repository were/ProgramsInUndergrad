#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

const double Eps = 1e-10;

int T, N;

struct Cor {
	int x, y, idx;
	Cor() {}
	Cor(int x, int y) : x(x), y(y) {}
}O;

int sqr(int x) {
	return x * x;
}

int dis2(Cor a, Cor b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

int det(Cor a, Cor b) {
	return a.x * b.y - a.y * b.x;
}

bool cmp(Cor a, Cor b) {
	int key = det(Cor(a.x - O.x, a.y - O.y), Cor(b.x - O.x, b.y - O.y));
	return key ? key > 0 : dis2(O, a) < dis2(O, b);
}

int main() {
	for(cin >> T; T; --T) {
		cin >> N;
		vector<Cor> a(N, Cor());
		for(int i = 0; i < N; ++i) {
			cin >> a[i].idx >> a[i].x >> a[i].y;
			if(a[i].y < a[0].y) {
				swap(a[i], a[0]);
			}
		}
		vector<int> ans;
		for(int i = 0; i < N; ++i) {
			O = a[i];
			sort(a.begin() + i + 1, a.end(), cmp);
			ans.push_back(a[i].idx);
		}
		cout << N;
		for(int i = 0; i < N; ++i) {
			cout << " " << ans[i];
		}
		cout << endl;
	}
	return 0;
}
