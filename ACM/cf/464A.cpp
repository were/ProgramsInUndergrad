#include <iostream>
#include <string>

using namespace std;

int N, P;
string s, ans;

bool check(int pos) {
	for(int i = pos + 1; i < (int) s.size(); ++i) {
		bool res = false;
		for(int j = P - 1; j >= 0; --j) {
			if((i - 1 < 0 || (j + 'a') != ans[i - 1]) && (i - 2 < 0 || (j + 'a') != ans[i - 2])) {
				ans[i] = j + 'a';
				res = true;
				break;
			}
		}
		if(!res) {
			return false;
		}
	}
	return s < ans;
}

int main() {
	cin >> N >> P >> s;
	ans = string(N, 'a');
	ans[0] = 'a' + P - 1;
	if(!check(0)) {
		cout << "NO\n";
	} else {
		for(int i = 0; i < (int) s.size(); ++i) {
			for(int j = 0; j < P; ++j) {
				if((i - 1 < 0 || (j + 'a') != ans[i - 1]) && (i - 2 < 0 || (j + 'a') != ans[i - 2])) {
					ans[i] = j + 'a';
					if(check(i)) {
						break;
					}
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
