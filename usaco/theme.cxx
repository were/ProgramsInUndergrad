/*
ID : weng_xo2
PROG : theme
LANG : C++11
Programmed by wereFluke
C++0x stardard head file
*/
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#define X first
#define Y second
#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)

using std::unique;
using std::sort;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::tuple;
using std::make_tuple;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::pair;
using std::make_pair;
using std::less;
using std::greater;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::clog;
using std::ifstream;
using std::ofstream;
using std::queue;
using std::stack;
using std::deque;
using std::list;
using std::bitset;

using ll = long long;
using vi = vector<int>;
using mii = map<int, int>;
using pii = pair<int, int>;

const int MaxN = 5555, Inf = ~0u >> 1;

pair<pii, int> data[MaxN], tmp[MaxN];

int N, n, a[MaxN], b[MaxN], rnk[MaxN], pos[MaxN], cnt[MaxN], h[MaxN];

int sortIt(int len) {
	rep(i, 1, N) data[i] = make_pair(pii(rnk[i], i + len - 1 <= N ? rnk[i + len - 1] : 0), i);
	//rep(i, 1, N) printf("%d: %d %d\n", i, data[i].X.X, data[i].X.Y); puts("");

	rep(i, 1, N) cnt[i] = 0;
	rep(i, 1, N) ++cnt[data[i].X.Y];
	rep(i, 1, N) cnt[i] += cnt[i - 1];
	per(i, N, 1) tmp[cnt[data[i].X.Y]--] = data[i];

	rep(i, 1, N) cnt[i] = 0;
	rep(i, 1, N) ++cnt[tmp[i].X.X];
	rep(i, 1, N) cnt[i] += cnt[i - 1];
	per(i, N, 1) data[cnt[tmp[i].X.X]--] = tmp[i];

	int ret = 0;
	rep(i, 1, N) {
		if(data[i].X != data[i - 1].X) {
			++ret;
		}
		rnk[data[i].Y] = ret;
		pos[ret] = data[i].Y;
	}
	//printf("%d\n", ret);
	return ret;
}

void show(int x) {
	rep(i, pos[x], N) printf("%d ", a[i]);
	puts("");
}

bool check(int len) {
	rep(i, 1, N) {
		int lcs = h[i], j = i;
		while(j - 1 >= 1 && lcs >= len) {
/*
			printf("@%d\n", pos[i]);
			show(i);
			printf("@%d\n", pos[j - 1]);
			show(j - 1);
			printf("lcs: %d\n", lcs);
*/
			if(abs(pos[j - 1] - pos[i]) > len) {
				return true;
			}
			lcs = min(lcs, h[--j]);
		}
	}
	return false;
}

int main(){
	freopen("theme.in", "r", stdin);
	freopen("theme.out", "w", stdout);
	scanf("%d", &N);
	--N;
	rep(i, 0, N) {
		scanf("%d", a + i);
	}
	per(i, N, 1) {
		a[i] -= a[i - 1];
		b[i] = a[i];
	}
	a[0] = Inf;
	//rep(i, 1, N) printf("%d ", a[i]); puts("");
	sort(b + 1, b + 1 + N);
	n = unique(b + 1, b + 1 + N) - b - 1;
	rep(i, 1, N) {
		rnk[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
	}
	for(int i = 1; sortIt(i + 1) < N; i *= 2);
//	puts("sa");
	int H = 0;
	rep(i, 1, N) {
		H = max(H - 1, 0);
		while(i + H <= N && pos[rnk[i] - 1] + H <= N && a[pos[rnk[i] - 1] + H] == a[i + H]) {
			++H;
		}
		h[rnk[i]] = H;
	}
/*
	rep(i, 1, N) {
		printf("%d\n", h[i]);
		//rep(j, pos[i], N) printf("%d ", a[j]);
		//puts("");
	}
*/
	int l = 1, r = N;
	while(l < r) {
		int mid = (l + r) / 2;
		if(check(mid)) {
			l = mid + 1;
		} else {
			r = mid;
		}
	}
	printf("%d\n", l >= 5 ? l : 0);
	return 0;
}

