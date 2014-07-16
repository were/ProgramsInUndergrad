#include <algorithm>
#include <cctype>
#include <cstdio>
#include <stack>
#include <set>
#include <utility>
#include <vector>

const int MaxN = 100010;

using std::max;
using std::stack;
using std::set;
using std::pair;
using std::vector;
using std::make_pair;

int N;
char s[MaxN * 10];
bool hsh[MaxN];
stack<int> vex;
set<int> g[MaxN];
set< pair<unsigned, int> > T_T;

void add(int u, int v) {
//	printf("%d %d\n", u, v);
	g[u].insert(v);
	g[v].insert(u);
}

int main(){
	gets(s);
	for (int i = 0; s[i]; ++i) {
		if (isdigit(s[i])) {
			int x = 0;
			while (isdigit(s[i])) {
				x = x * 10 + s[i++] - '0';
			}
			--i;
			if (!vex.empty()) {
				add(vex.top(), x);
			}
			vex.push(x);
			N = max(x, N);
		}
		else {
			if (s[i] == ')') {
				vex.pop();
			}
		}
	}
	for (int i = 1; i <= N; ++i) {
		T_T.insert(make_pair(g[i].size(), i));
//		printf("%u %d\n", g[i].size(), i);
	}
	for (int i = 1; i < N; ++i) {
		int x = T_T.begin()->second, ans = 0;
		T_T.erase(T_T.begin());
		for (set<int> :: iterator cur = g[x].begin(); cur != g[x].end(); ++cur) {
			if (!hsh[*cur]) {
				T_T.erase(make_pair(g[*cur].size(), *cur));
				g[*cur].erase(x);
				T_T.insert(make_pair(g[*cur].size(), *cur));
//				printf("%u %d\n", g[*cur].size(), *cur);
				ans = *cur;
			}
		}
		printf(i == N - 1 ? "%d\n" : "%d ", ans);
	}
	return 0;
}