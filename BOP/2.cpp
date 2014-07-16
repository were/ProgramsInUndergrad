#include <cstdio>
#include <iostream>
#include <vector>
#include <map>

const int MaxN = 100010, mod = (int)1e9 + 7, magic = 12347;

typedef long long ll;
typedef std::pair<int, int> pii;
using std::vector;

struct Data{
	int l, r;
	ll d;
	Data(int l, int r, ll d) : l(l), r(r), d(d) {}
};

vector<int> g[MaxN];
vector<Data> q[MaxN];

int T, N, M, d[MaxN], cs;
ll bit[MaxN], ans[MaxN], res;

void add(int x, ll d){
	for(; x <= N; x += x & -x)
		bit[x] += d;
}

ll query(int x){
	ll ret = 0ll;
	for(; x; x -= x & -x)
		ret += bit[x];
	return ret;
}

void dfs(int x){
	for(vector<Data> :: iterator cur = q[x].begin(); cur != q[x].end(); ++cur){
		add(cur->l, cur->d);
		add(cur->r + 1, -cur->d);
	}
	ans[x] = query(d[x]);
	for(vector<int> :: iterator cur = g[x].begin(); cur != g[x].end(); ++cur) {
		d[*cur] = d[x] + 1;
		dfs(*cur);
	}
	for(vector<Data> :: iterator cur = q[x].begin(); cur != q[x].end(); ++cur){
		add(cur->l, -cur->d);
		add(cur->r + 1, cur->d);
	}
}

int main(){
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		for(int i = 2, p; i <= N; ++i) {
			scanf("%d", &p);
			g[p].push_back(i);
		}
		scanf("%d", &M);
		for(int i = 1; i <= M; ++i){
			int u, l, r, d;
			scanf("%d%d%d%d", &u, &l, &r, &d);
			q[u].push_back(Data(l, r, (ll)d));
		}
		d[1] = 1;
		dfs(1);
		res = 0ll;
		for(int i = 1; i <= N; ++i) {
			res = (res * (ll)magic + ans[i]) % (ll)mod;
			ans[i] = d[i] = bit[i] = 0;
			g[i].clear();
			q[i].clear();
		}
		std::cout << "Case " << ++cs << ": " << res << std::endl;
	}
	return 0;
}
