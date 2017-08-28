#include <algorithm>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;

const int MaxN = 55555, Inf = (int) (1e9 + 5 * 1e8);

struct Edge;

struct V {
	int v, idx, size, dep;
	V *pre, *nxt, *belong;
	Edge *g;
	inline void init() {
		v = idx = dep = 0;
		size = 1;
		pre = nxt = belong = NULL;
		g = NULL;
	}
}vs[MaxN];

struct Edge {
	V *v;
	Edge *nxt;
}buffer[MaxN * 2], *tot;

inline void addEdge(V *u, V *v) {
	++tot;
	tot->v = v;
	tot->nxt = u->g;
	u->g = tot;
}

struct Data {
	int max, min, lr, rl;
	Data(int a, int b, int c, int d) : max(a), min(b), lr(c), rl(d) {}
	Data(int x) : max(x), min(x), lr(0), rl(0) {}
	Data() : max(-Inf), min(Inf), lr(0), rl(0) {}
	inline Data rev() {
		return Data(max, min, rl, lr);
	}
	void show() {
		printf("%d %d %d %d\n", max, min, lr, rl);
	}
}data[MaxN * 2];

inline int max(int a, int b, int c) {
	return max(a, max(b, c));
}

inline Data operator+ (Data a, Data b) {
	return Data(
		max(a.max, b.max),
		min(a.min, b.min),
		max(b.max - a.min, a.lr, b.lr),
		max(a.max - b.min, a.rl, b.rl)
	);
}

int test, n, v[MaxN], delta[MaxN * 2];
V *q[MaxN];

inline int getId(int l, int r) {
	return (l + r) | (l != r);
}

void build(int l, int r) {
	int id = getId(l, r);
	delta[id] = 0;
	if(l == r) {
		data[id] = Data(v[l]);
	} else {
		int m = (l + r) / 2;
		build(l, m);
		build(m + 1, r);
		data[id] = data[getId(l, m)] + data[getId(m + 1, r)];
	}
}

inline Data real(int l, int r) {
	int id = getId(l, r);
	Data res = data[id];
	res.max += delta[id];
	res.min += delta[id];
	return res;
}

inline void push(int l, int r) {
	int id = getId(l, r);
	data[id] = real(l, r);
	if(l != r) {
		int m = (l + r) / 2;
		delta[getId(l, m)] += delta[id];
		delta[getId(m + 1, r)] += delta[id];
	}
	delta[id] = 0;
}

Data query(int l, int r, int a, int b, int d) {
	int id = getId(l, r);
	Data res;
	if(a <= l && r <= b) {
		res = real(l, r);
		delta[id] += d;
	} else {
		push(l, r);
		int m = (l + r) / 2;
		if(b <= m) {
			res = query(l, m, a, b, d);
		} else {
			if(a > m) {
				res = query(m + 1, r, a, b, d);
			} else {
				res = query(l, m, a, b, d) + query(m + 1, r, a, b, d);
			}
		}
		data[id] = real(l, m) + real(m + 1, r);
	}
	return res;
}
inline Data query(V *u, V *v, int d) {
	Data l, r;
	while(u->belong != v->belong) {
		if(u->belong->dep > v->belong->dep) {
			l = l + query(1, n, u->belong->idx, u->idx, d).rev();
			u = u->belong->pre;
		} else {
			r = query(1, n, v->belong->idx, v->idx, d) + r;
			v = v->belong->pre;
		}
	}
	if(u->idx < v->idx) {
		return l + query(1, n, u->idx, v->idx, d) + r;
	} else {
		return l + query(1, n, v->idx, u->idx, d).rev() + r;
	}
}

int main() {
	scanf("%d", &test);
	while(test--) {
		scanf("%d", &n);
		tot = buffer;
		for(int i = 0; i <= n; ++i) {
			vs[i].init();
			if(i) {
				scanf("%d", &vs[i].v);
			}
		}
		for(int i = 1; i < n; ++i) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(vs + u, vs + v);
			addEdge(vs + v, vs + u);
		}
		//fakeFunction
		{
			int f = 0, t = 0;
			for((q[t++] = vs + 1)->dep = 1; f < t; ++f) {
				for(Edge *cur = q[f]->g; cur; cur = cur->nxt) {
					if(!cur->v->dep) {
						cur->v->dep = q[f]->dep + 1;
						cur->v->pre = q[f];
						q[t++] = cur->v;
					}
				}
			}
			for(int i = n - 1; i > 0; --i) {
				q[i]->pre->size += q[i]->size;
				if(!q[i]->pre->nxt || q[i]->pre->nxt->size < q[i]->size) {
					q[i]->pre->nxt = q[i];
				}
			}
			int idx = 0;
			for(int i = 0; i < n; ++i) {
				if(q[i]->belong == NULL) {
					for(V *v = q[i]; v; v = v->nxt) {
						v->belong = q[i];
						v->idx = ++idx;
					}
				}
			}
			for(int i = 1; i <= n; ++i) {
				v[vs[i].idx] = vs[i].v;
			}
			build(1, n);
		}
		int m;
		scanf("%d", &m);
		while(m--) {
			int u, v, d;
			scanf("%d%d%d", &u, &v, &d);
			printf("%d\n", query(vs + u, vs + v, d).lr);
		}
	}
	return 0;
}
