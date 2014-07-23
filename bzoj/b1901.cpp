#include <cctype>
#include <cstdio>

using namespace std;

const int MaxN = 10010, n = 1000000000;

int N, M, a[MaxN], notTwice[MaxN];

struct Node {
	int sum;
	Node *s[2];
}*bit[MaxN], *cur[MaxN], nil[MaxN * 200];

Node *newNode() {
	static Node *tot = nil;
	++tot;
	tot->sum = 0;
	tot->s[0] = tot->s[1] = nil;
//printf("%d\n", (int) (tot - nil));
	return tot;
}

void insert(Node *&cur, int l, int r, int ky, int delta) {
	if(cur == nil) {
		cur = newNode();
	}
	if(l != r) {
		int m = (l + r) / 2;
		if(ky <= m) {
			insert(cur->s[0], l, m, ky, delta);
		} else {
			insert(cur->s[1], m + 1, r, ky, delta);
		}
		cur->sum = cur->s[0]->sum + cur->s[1]->sum;
//printf("%d, %d: %d\n", l, r, cur->sum);
	} else {
		cur->sum += delta;
//printf("%d: %d\n", l, cur->sum);
	}
}

void turn(int x, int d) {
	for(; x; x -= x & -x) {
		if(notTwice[x] == M) {
			cur[x] = cur[x]->s[d];
		}
	}
}

int main() {
	nil->sum = 0;
	nil->s[0] = nil->s[1] = nil;
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		bit[i] = nil;
		notTwice[i] = n;
	}
	for(int i = 1; i <= N; ++i) {
		scanf("%d", a + i);
		for(int j = i; j <= N; j += j & -j) {
//printf("%d:\n", j);
			insert(bit[j], 0, n, a[i], 1);
		}
	}
	while(M--) {
		char ch;
		while(!isupper(ch = getchar()));
		if(ch == 'C') {
			int idx, num;
			scanf("%d%d", &idx, &num);
			for(int i = idx; i <= N; i += i & -i) {
				insert(bit[i], 0, n, a[idx], -1);
			}
			a[idx] = num;
			for(int i = idx; i <= N; i += i & -i) {
				insert(bit[i], 0, n, a[idx], 1);
			}
		} else {
			int l, r, k;
			scanf("%d%d%d", &l, &r, &k);
			for(int i = r; i; i -= i & -i) {
				notTwice[i] = M;
				cur[i] = bit[i];
			}
			for(int i = l - 1; i; i -= i & -i) {
				notTwice[i] = notTwice[i] == M ? n : M;
				cur[i] = bit[i];
			}
			int f = 0, t = n;
			while(f < t) {
				int rnk = 0, m = (f + t) / 2;
				for(int i = r; i; i -= i & -i) {
					if(notTwice[i] == M) {
//printf("+%d\n", i);
						rnk += cur[i]->s[0]->sum;
					}
				}
				for(int i = l - 1; i; i -= i & -i) {
					if(notTwice[i] == M) {
//printf("-%d\n", i);
						rnk -= cur[i]->s[0]->sum;
					}
				}
//printf("%d, %d: %d\n", f, m, rnk);
				if(k > rnk) {
					k -= rnk;
					turn(r, 1);
					turn(l - 1, 1);
					f = m + 1;
				} else {
					turn(r, 0);
					turn(l - 1, 0);
					t = m;
				}
			}
			printf("%d\n", f);
		}
	}
	return 0;
}
