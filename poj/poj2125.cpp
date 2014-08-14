#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

using std::min;
using std::pair;
using std::make_pair;
using std::vector;

const int MaxN = 11111, Inf = 1000000000;

int N, M, source, terminal, vCnt, h[MaxN], gap[MaxN], g[MaxN][MaxN];
bool hsh[MaxN];

vector<pair<int, char> > ans;

int dfs(int x, int flow) {
	//printf("%d: %d\n", x, h[x]);
	if(x == terminal) {
		return flow;
	}
	int minH = vCnt, delta, ret = 0;
	for(int i = 0; i < vCnt; ++i) {
		if(g[x][i]) {
			if(h[i] + 1 == h[x]) {
				delta = dfs(i, min(flow, g[x][i]));
				g[x][i] -= delta;
				g[i][x] += delta;
				ret += delta;
				flow -= delta;
				if(!flow || h[source] >= vCnt) {
					return ret;
				}
			}
			minH = min(minH, h[i]);
		}
	}
	if(ret) {
		return ret;
	}
	if(--gap[h[x]] == 0) {
		h[source] = vCnt;
	}
	h[x] = minH + 1;
	++gap[h[x]];
	return 0;
}

void dfs(int x) {
	hsh[x] = true;
	for(int i = 0; i < vCnt; ++i) {
		if(g[x][i] && !hsh[i]) {
			dfs(i);
		}
	}
}

void flow() {
	int res = 0;
	gap[0] = vCnt;
	while(h[source] < vCnt) {
		int delta = dfs(source, Inf);
		//printf("aug: %d\n", delta);
		res += delta;
	}
	printf("%d\n", res);
	dfs(source);
	for(int i = 1; i <= N; ++i) {
		if(!hsh[i]) {
			ans.push_back(make_pair(i, '-'));
		}
		if(hsh[i + N]) {
			ans.push_back(make_pair(i, '+'));
		}
	}
	printf("%d\n", (int) ans.size());
	for(vector<pair<int, char> >::iterator cur = ans.begin(); cur != ans.end(); ++cur) {
		printf("%d %c\n", cur->first, cur->second);
	}
}

int main() {
	scanf("%d%d", &N, &M);
	source = 0;
	terminal = 2 * N + 1;
	vCnt = terminal + 1;
	for(int i = 1; i <= N; ++i) {
		scanf("%d", g[i + N] + terminal);
	}
	for(int i = 1; i <= N; ++i) {
		scanf("%d", g[source] + i);
	}
	for(int i = 1; i <= M; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		g[u][v + N] = Inf;
	}
	flow();
	return 0;
}
