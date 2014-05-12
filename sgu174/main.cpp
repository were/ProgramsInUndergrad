#include <cstdio>
#include <map>
#include <utility>

using std::pair;
using std::map;

const int MaxN = 400010;

int N, fa[MaxN];
map<pair<int, int>, int> hsh;

int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

int getId(const pair<int, int> &a) {
	if(hsh[a]) {
		return hsh[a];
	}
	static int cnt = 0;
	hsh[a] = ++cnt;
	fa[cnt] = cnt;
	return cnt;
}

int main(){
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) {
		pair<int, int> a, b;
		scanf("%d%d%d%d", &a.first, &a.second, &b.first, &b.second);
		int x = getId(a), y = getId(b);
		if(getfa(x) != getfa(y)) {
			fa[getfa(x)] = getfa(y);
		}
		else {
			printf("%d\n", i);
			return 0;
		}
	}
	puts("0");
	return 0;
}
