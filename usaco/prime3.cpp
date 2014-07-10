/*
PROG : prime3
ID : weng_xo2
LANG : C++11
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
#include <list>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <tuple>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)
#define bit_up(i,f,t) for(int i(f);i<=(t);i+=i&-i)
#define bit_down(i,f) for(int i(f);i;i-=i&-i)

#define X first
#define Y second

using std::tuple;
using std::make_tuple;
using std::sort;
using std::bitset;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
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

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

struct Node {
	Node *nxt[10];
	int stat;
}buffer[4555], *tot = buffer, *root = buffer;

vector< tuple<int, int, int, int, int> > ans;

int s, u, num[1024];
bool hsh[100001];

void dfs(int dep, Node *a, Node *b, Node *c, Node *d, Node *e, Node *x, Node *y, int _a, int _b, int _c, int _d, int _e) {
	if(dep == 0) {
		if(a->nxt[u] && root->nxt[u]) {
			//printf("%d\n", u);
			//printf("%d %d\n", b->stat, root->nxt[u]->stat);
			for(int bb = b->stat & root->nxt[u]->stat; bb; bb -= bb & -bb) {
				//printf("%d\n", num[bb & -bb]);
				for(int cc = c->stat & root->nxt[u]->nxt[num[bb & -bb]]->stat; cc; cc -= cc & -cc) {
					for(int dd = d->stat & root->nxt[u]->nxt[num[bb & -bb]]->nxt[num[cc & -cc]]->stat; dd; dd -= dd & -dd) {
						int nums[5] = {u, num[bb & -bb], num[cc & -cc], num[dd & -dd]};
						nums[4] = s - nums[0] - nums[1] - nums[2] - nums[3];
						if(root->nxt[u]->nxt[nums[1]]->nxt[nums[2]]->nxt[nums[3]]->nxt[nums[4]] && e->nxt[nums[4]] && x->nxt[nums[dep]] && y->nxt[nums[4 - dep]]) {
							//printf("%d%d%d%d%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
							dfs(
								dep + 1,
								a->nxt[u], b->nxt[nums[1]], c->nxt[nums[2]], d->nxt[nums[3]], e->nxt[nums[4]],
								x->nxt[nums[dep]], y->nxt[nums[4 - dep]],
								_a * 10 + nums[0], _b * 10 + nums[1], _c * 10 + nums[2], _d * 10 + nums[3], _e * 10 + nums[4]
							);
						}
					}
				}
			}
		}
	} else if(dep < 5) {
		for(int aa = a->stat & root->stat; aa; aa -= aa & -aa) {
			for(int bb = b->stat & root->nxt[num[aa & -aa]]->stat; bb; bb -= bb & -bb) {
				for(int cc = c->stat & root->nxt[num[aa & -aa]]->nxt[num[bb & -bb]]->stat; cc; cc -= cc & -cc) {
					for(int dd = d->stat & root->nxt[num[aa & -aa]]->nxt[num[bb & -bb]]->nxt[num[cc & -cc]]->stat; dd; dd -= dd & -dd) {
						int nums[5] = {num[aa & -aa], num[bb & -bb], num[cc & -cc], num[dd & -dd]};
						nums[4] = s - nums[0] - nums[1] - nums[2] - nums[3];
						if(root->nxt[nums[0]]->nxt[nums[1]]->nxt[nums[2]]->nxt[nums[3]]->nxt[nums[4]] && e->nxt[nums[4]] && x->nxt[nums[dep]] && y->nxt[nums[4 - dep]]) {
							//printf("%d%d%d%d%d\n", nums[0], nums[1], nums[2], nums[3], nums[4]);
							dfs(
								dep + 1,
								a->nxt[nums[0]], b->nxt[nums[1]], c->nxt[nums[2]], d->nxt[nums[3]], e->nxt[nums[4]],
								x->nxt[nums[dep]], y->nxt[nums[4 - dep]],
								_a * 10 + nums[0], _b * 10 + nums[1], _c * 10 + nums[2], _d * 10 + nums[3], _e * 10 + nums[4]
							);
						}
					}
				}
			}
		}
	} else {
		ans.push_back(make_tuple(_a, _b, _c, _d, _e));
	}
}

int main(){
	freopen("prime3.in", "r", stdin);
	freopen("prime3.out", "w", stdout);
	scanf("%d%d", &s, &u);
	for(int i = 0; i < 10; ++i) {
		num[1 << i] = i;
	}
	for(int i = 2; i < 100000; ++i) {
		if(!hsh[i]) {
			if(i >= 10000) {
				int tmp = i, sum = 0;
				while(tmp) {
					sum += tmp % 10;
					tmp /= 10;
				}
				if(sum == s) {
					Node *cur = root;
					for(int j = 10000, x = i; j >= 1; j /= 10) {
						if(!cur->nxt[x / j]) {
							cur->stat |= 1 << (x / j);
							cur->nxt[x / j] = ++tot;
						}
						cur = cur->nxt[x / j];
						x %= j;
					}
				}
			}
			for(int j = i + i; j <= 100000; j += i) {
				hsh[j] = true;
			}
		}
	}
	dfs(0, root, root, root, root, root, root, root, 0, 0, 0, 0, 0);
	sort(ans.begin(), ans.end());
	for(unsigned i = 0; i < ans.size(); ++i) {
		printf("%d\n", std::get<0>(ans[i]));
		printf("%d\n", std::get<1>(ans[i]));
		printf("%d\n", std::get<2>(ans[i]));
		printf("%d\n", std::get<3>(ans[i]));
		printf("%d\n", std::get<4>(ans[i]));
		if(i + 1 < ans.size()) {
			puts("");
		}
	}
	if(!ans.size()) {
		puts("NONE");
	}
	return 0;
}

