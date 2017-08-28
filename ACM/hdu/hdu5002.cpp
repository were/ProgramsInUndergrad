#include <algorithm>
#include <cstdio>
#include <functional>
#include <map>
#include <vector>

using namespace std;

const int N = 111111, Empty = ~0u >> 1;

typedef pair<int, int> PII;

struct Node {
	int v, sz, same, delta, rev;
	int len;
	PII array[5];
	Node *s[2], *p;

	int d() {
		return this == p->s[1];
	}

	bool root() {
		return this != p->s[0] && this != p->s[1];
	}

	void rz() {
		len = 0;
		array[len++] = PII(v, 1);
		for(int i = 0; i < 2; ++i) {
			s[i]->push();
			for(int j = 0; j < s[i]->len; ++j) {
				array[len++] = s[i]->array[j];
			}
		}
		sort(array, array + len, greater< pair<int, int> >());
		for(int i = 0; i < len; ) {
			int j = i + 1;
			while(j < len && array[j].first == array[i].first) {
				array[i].second += array[j].second;
				++j;
			}
			++i;
			while(i < j) {
				array[i] = array[i - 1];
				++i;
			}
		}
		len = unique(array, array + len) - array;
		while(len > 2) {
			--len;
		}
		sz = s[0]->sz + 1 + s[1]->sz;
	}

	void makeSame(int);
	void addDelta(int);
	void push();
	void sets(Node*, int);
	void init(int);

}nil[N];

void dfs(Node *t) {
	if(t != nil) {
		dfs(t->s[0]);
		printf("%d, %d  %d\n", (int) (t - nil), t->v, t->sz);
		dfs(t->s[1]);
	}
}

void Node::init(int x) {
	len = 0;
	array[len++] = PII(v = x, 1);
	same = Empty;
	delta = rev = 0;
	s[0] = s[1] = p = nil;
}

void Node::makeSame(int x) {
	if(this == nil) {
		return;
	}
	same = x;
	delta = 0;
}


void Node::addDelta(int x) {
	if(this == nil) {
		return;
	}
	if(same != Empty) {
		same += x;
	} else {
		delta += x;
	}
}

void Node::sets(Node *t, int d) {
	if(this == nil) {
		return;
	}
	push();
	if((s[d] = t) != nil) {
		t->p = this;
	}
	rz();
}

void Node::push() {
	if(this == nil) {
		return;
	}
	if(same != Empty) {
		s[0]->makeSame(same);
		s[1]->makeSame(same);
		len = 0;
		array[len++] = PII(v = same, sz);
		same = Empty;
	} else {
		if(delta) {
			v += delta;
			for(int i = 0; i < len; ++i) {
				array[i].first += delta;
			}
			s[0]->addDelta(delta);
			s[1]->addDelta(delta);
			delta = 0;
		}
	}
	if(rev) {
		swap(s[0], s[1]);
		s[0]->rev ^= 1;
		s[1]->rev ^= 1;
		rev = 0;
	}
}

/*
	
	|
	p
   / \
  *   t
     / \
	*   *
*/
void rotate(Node *t) {
	Node *p = t->p;
	if(!p->root()) {
		p->p->push();
	}
	p->push();
	t->push();
	int d = t->d();
	p->sets(t->s[!d], d);
	if(p->root()) {
		t->p = p->p;
	} else {
		p->p->sets(t, p->d());
	}
	t->sets(p, !d);
}

void splay(Node *t) {
	for(; !t->root(); rotate(t)) {
		if(!t->p->root()) {
			rotate(t->d() != t->p->d() ? t : t->p);
		}
//puts("splay...");
	}
	t->push();
}

void access(Node *t) {
	Node *res;
	for(res = nil; t != nil; res = t, t = t->p) {
		splay(t);
		t->sets(res, 1);
//puts("accessing...");
	}
	t->push();
}

void evert(Node *t) {
	access(t);
//puts("access done");
//dfs(t);
//printf("%d %d\n", t->p->s[0] - nil, t->p->s[1] - nil);
	splay(t);
	t->rev ^= 1;
	t->push();
}

void link(int u, int v) {
	evert(nil + v);
	nil[v].p = nil + u;
	access(nil + v);
}

void cut(int u, int v) {
	evert(nil + u);
	access(nil + v);
	splay(nil + u);
//printf("sz %d\n", nil[u].sz);
	nil[u].s[1]->p = nil;
	nil[u].sets(nil, 1);
//printf("sz %d\n", nil[u].sz);
}

Node *chain(int u, int v) {
	evert(nil + u);
//puts("evert done");
	access(nil + v);
//puts("access done");
	splay(nil + u);
//puts("splay done");
	return nil + u;
}

struct Edge {
	int v;
	Edge *nxt;
}*g[N], buffer[N * 2], *tot;

int test, n, m, q[N], front, back;

int nextInt() {
	char ch;
	while(!isdigit(ch = getchar()) && ch != '-');
	if(ch == '-') {
		return -nextInt();
	}
	int res = ch - '0';
	while(isdigit(ch = getchar())) {
		res = res * 10 + ch - '0';
	}
	return res;
}

void addEdge(int u, int v) {
	++tot;
	tot->v = v;
	tot->nxt = g[u];
	g[u] = tot;
}

int main() {
	test = nextInt();
	nil->s[0] = nil->s[1] = nil;
	for(int curCase = 1; curCase <= test; ++curCase) {
		printf("Case #%d:\n", curCase);
		n = nextInt();
		m = nextInt();
		for(int i = 1; i <= n; ++i) {
			nil[i].init(nextInt());
			g[i] = NULL;
		}
		tot = buffer;
		for(int i = 1; i < n; ++i) {
			int u = nextInt(), v = nextInt();
			addEdge(u, v);
			addEdge(v, u);
//printf("%d %d\n", u, v);
		}
		front = back = 0;
		for(q[back++] = 1; front < back; ++front) {
			for(Edge *cur = g[q[front]]; cur; cur = cur->nxt) {
				if(cur->v != 1 && nil[cur->v].p == nil) {
					nil[cur->v].p = nil + q[front];
					q[back++] = cur->v;
				}
			}
		}
		while(m--) {
//fprintf(stderr, "%d\n", m);
			int op = nextInt();
			if(op == 1) {
				int x = nextInt();
				int y = nextInt();
				int a = nextInt();
				int b = nextInt();
				cut(x, y);
//puts("cut done");
				link(a, b);
//puts("link done");
			}
			if(op == 2) {
				int u = nextInt();
				int v = nextInt();
				int w = nextInt();
				chain(u, v)->makeSame(w);
			}
			if(op == 3) {
				int u = nextInt();
				int v = nextInt();
				int w = nextInt();
//puts("adding...");
				chain(u, v)->addDelta(w);
			}
			if(op == 4) {
				int u = nextInt();
				int v = nextInt();
				Node *route = chain(u, v);
//dfs(route);
//printf("%d\n", route->sz);
//printf("size %d\n", (int) route->res.size());
				if(route->len == 1) {
					puts("ALL SAME");
				} else {
					PII res = route->array[1];
					printf("%d %d\n", res.first, res.second);
				}
			}
//puts("done");
//printf("%d\n", m);
		}
	}
}
