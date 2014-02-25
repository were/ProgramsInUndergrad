#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

#define X first
#define Y second

const int MaxN = 1000010, MaxM = 100010;
typedef std :: pair<int, int> pii;

char s[MaxN];
int N, M, bit[MaxN], ans[MaxM], st[MaxN];
std :: vector<pii> q[MaxN];

void add(int x){
	for(;x <= N;x += x & -x)
		++ bit[x];
}

int query(int l, int r){
	int ret = 0;
	for(;r;r -= r & -r)
		ret += bit[r];
	for(-- l;l;l -= l & -l)
		ret -= bit[l];
	return ret;
}

int main(){
	scanf("%s%d", s + 1, &M);
	N = strlen(s + 1);
	for(int i = 1;i <= M;++ i){
		int l, r;
		scanf("%d%d", &l, &r);
		q[l].push_back(pii(r, i));
	}
	for(int i = N;i >= 1;-- i){
		if(s[i] == '('){
			if(st[0]){
				add(st[st[0]]);
				-- st[0];
			}
		}else
			st[++ st[0]] = i;
		for(unsigned j = 0;j < q[i].size();++ j)
			ans[q[i][j].Y] = query(i, q[i][j].X);
	}
	for(int i = 1;i <= M;++ i)
		printf("%d\n", ans[i] * 2);
	return 0;
}
