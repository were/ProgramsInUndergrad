/*
LANG : C++11
ID : weng_xo2
PROG : combo
 * */

#include <fstream>
#include <tuple>
#include <set>

using namespace std;

ifstream fin("combo.in");
ofstream fout("combo.out");

set< tuple<int, int, int> > T_T;
int n, a, b, c;

bool in_range(int a, int b) {
	for (int i = -2; i <= 2; ++i) {
		if ((b + i + n) % n == a) {
			return true;
		}
	}
	return false;
}

void work() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			for (int k = 0; k < n; ++k) {
				if (in_range(i, a) && in_range(j, b) && in_range(k, c)) {
					T_T.insert(make_tuple(i, j, k));
				}
			}
		}
	}
}

int main() {
	fin >> n >> a >> b >> c;
	work();
	fin >> a >> b >> c;
	work();
	fout << T_T.size() << endl;
	return 0;
}

