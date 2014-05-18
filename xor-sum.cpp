#include <cstdio>
#define rep(i,f,t) for(int i(f);i<=(t);++i)

const int MaxN = 100010;

int T, N, M, cs;

struct Node {
	Node *s[2];
}*root, nil[MaxN * 33], *tot;

Node *newNode() {
	++tot;
	tot->s[0] = tot->s[1] = nil;
	return tot;
}

int main() {
	scanf("%d", &T);
	nil->s[0] = nil->s[1] = nil;
	while(T--) {
		scanf("%d%d", &N, &M);
		printf("Case #%d:\n", ++cs);
		tot = nil;
		root = newNode();
		rep(i, 1, N) {
			unsigned x;
			scanf("%u", &x);
			Node *cur = root;
			for(int j = 31; j >= 0; --j) {
				if(cur->s[x >> (unsigned)j & 1] == nil) {
					cur->s[x >> (unsigned)j & 1] = newNode();
				}
//				printf("%u", x >> (unsigned)j & 1);
				cur = cur->s[x >> (unsigned)j & 1];
			}
//			puts("");
		}
		rep(i, 1, M) {
			unsigned x, ans = 0;
			scanf("%u", &x);
			Node *cur = root;
			for(int j = 31; j >= 0; --j) {
				if(cur->s[~x >> (unsigned)j & 1] != nil) {
					cur = cur->s[~x >> (unsigned)j & 1];
					ans |= (~x >> (unsigned)j & 1) << (unsigned)j;
				}
				else {
					cur = cur->s[x >> (unsigned)j & 1];
					ans |= (x >> (unsigned)j & 1) << (unsigned)j;
				}
			}
			printf("%u\n", ans);
		}
	}
	return 0;
}
