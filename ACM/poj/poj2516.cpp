#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

typedef std::pair<int, int> PII;

const int MaxN = 55, Inf = 1000000000;

int n, N, M, K, need[MaxN][MaxN], sup[MaxN][MaxN], fee[MaxN][MaxN][MaxN], dis[MaxN * 3], pre[MaxN * 3];
int cst[MaxN * 3][MaxN * 3], cap[MaxN * 3][MaxN * 3];
bool hsh[MaxN * 3];

void init() {
	for(int i = 1; i <= N; ++i) {
		for(int j = 1; j <= K; ++j) {
			scanf("%d", need[i] + j);
		}
	}
	for(int i = 1; i <= M; ++i) {
		for(int j = 1; j <= K; ++j) {
			scanf("%d", sup[i] + j);
		}
	}
	for(int i = 1; i <= K; ++i) {
		for(int j = 1; j <= N; ++j) {
			for(int k = 1; k <= M; ++k) {
				scanf("%d", fee[i][j] + k);
			}
		}
	}
}

void build(int x) {
	n = N + M + 2;
	memset(cst, 0, sizeof cst);
	memset(cap, 0, sizeof cap);
	for(int i = 1; i <= M; ++i) {
		cap[0][i] = sup[i][x];
	}
	for(int i = 1; i <= M; ++i) {
		for(int j = 1; j <= N; ++j) {
			cap[i][j + M] = Inf;
			cst[i][j + M] = fee[x][j][i];
			cst[j + M][i] = -cst[i][j + M];
		}
	}
	for(int i = 1; i <= N; ++i) {
		cap[i + M][n - 1] = need[i][x];
	}
}

bool spfa() {
	for(int i = 0; i < n; ++i) {
		dis[i] = Inf;
	}
	std::queue<int> q;
	for(q.push(0), hsh[0] = true, dis[0] = 0; !q.empty();) {
		int x = q.front();
		for(int i = 0; i < n; ++i) {
			if(cap[x][i] && dis[x] + cst[x][i] < dis[i]) {
				pre[i] = x;
				dis[i] = dis[x] + cst[x][i];
				if(!hsh[i]) {
					hsh[i] = true;
					q.push(i);
				}
			}
		}
		hsh[x] = false;
		q.pop();
	}
	return dis[n - 1] != Inf;
}

PII flow() {
	PII ret(0, 0);
	while(spfa()) {
		int delta = Inf;
		for(int x = n - 1; x; x = pre[x]) {
			delta = std::min(delta, cap[pre[x]][x]);
		}
		for(int x = n - 1; x; x = pre[x]) {
			cap[pre[x]][x] -= delta;
			cap[x][pre[x]] += delta;
		}
		ret.first += delta;
		ret.second += dis[n - 1] * delta;
	}
	return ret;
}

void work() {
	int ans = 0;
	for(int i = 1; i <= K; ++i) {
		build(i);
		PII res = flow();
		for(int j = 1; j <= N; ++j) {
			res.first -= need[j][i];
		}
		if(res.first != 0) {
			puts("-1");
			return;
		}
		ans += res.second;
	}
	printf("%d\n", ans);
}

int main() {
	while(scanf("%d%d%d", &N, &M, &K), N || M || K) {
		init();
		work();
	}
	return 0;
}
