#include <iostream>
#include <string>
#include <sstream>
#include <vector>
 
using namespace std;
 
vector< vector<string> > a;
vector<string> ans;
 
size_t T, N;
string s;
 
int main() {
	ios::sync_with_stdio(false);
	cin >> T;
	while(T--) {
		a.clear();
		N = 0;
		for(getline(cin, s); s != "@"; getline(cin, s)) {
			a.push_back(vector<string>());
			istringstream input(s);
			while(input >> s) {
				a.back().push_back(s);
			}
			N = max(N, a.back().size());
		}
		ans = vector<string>(a.size(), "");
		for(size_t i = 0, len = 0, tmp = 0; i < N; ++i, len = tmp + 1) {
			for(size_t j = 0; j < a.size(); ++j) {
				if(i < a[j].size()) {
					ans[j] += string(len - ans[j].size(), ' ') + a[j][i];
					tmp = max(tmp, ans[j].size());
				}
			}
		}
		for(size_t i = 0; i < a.size(); ++i) {
			cout << ans[i] << endl;
		}
	}
}

