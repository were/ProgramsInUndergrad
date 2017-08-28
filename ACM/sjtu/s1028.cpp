#include <iostream>
#include <string>
#include <cstring>

using std::string;
using std::cin;
using std::cout;

string s[111];
int N, f[111][111];

bool work(int l, int r) {
	if(~f[l][r]) {
		return f[l][r];
	}
	if(l == r) {
		return false;
	}
	if(r < l) {
		return true;
	}
	for(int i = l + 1; i < r; ++i) {
		if((s[i + 1] == "if" || (s[i + 1] == "begin" && s[r] == "end")) && work(l, i) && work(i + 1, r)) {
			return f[l][r] = true;
		}
	}
	if(l + 1 <= r && s[l] == "if" && s[l + 1] == "then") {
		if(work(l + 2, r)) {
			return f[l][r] = true;
		}
		for(int i = l + 2; i <= r; ++i) {
			if(s[i] == "else" && work(l + 2, i - 1) && work(i + 1, r)) {
				return f[l][r] = true;
			}
		}
	}
	if(s[l] == "begin" && s[r] == "end") {
		if(work(l + 1, r - 1)) {
			return f[l][r] = true;
		}
	}
	return false;
}

int main() {
	memset(f, 0xff, sizeof f);
	cin >> N;
	for(int i = 1; i <= N; ++i) {
		std::cin >> s[i];
	}
	cout << (work(1, N) ? "YES" : "NO") << std::endl;
	return 0;
}

