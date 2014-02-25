#include <algorithm>
#include <cstdio>
#define ls (x + x)
#define rs (x + x + 1)
#define mid (f + t >> 1)
const int MaxN = 50001, inf = ~0u >> 1;
int N, l, r;
struct Data{
	int k, a, idx;
	void fromInput();
}data[MaxN];
struct Tree{
	int ky, idx;
	Tree() : ky(-inf), idx(-inf) {}
	Tree(int ky, int idx) : ky(ky), idx(idx) {}
	bool operator < (const Tree&a) const {
		return ky > a.ky;
	}
}T[MaxN * 4];
struct Answer{
	int p, l, r;
	void show();
}ans[MaxN];
void Data :: fromInput(){
	scanf("%d%d", &k, &a);
	idx = this - data;
}
void Answer :: show(){
	printf("%d %d %d\n", p, l, r);
}
bool cmp(const Data&a, const Data&b){
	return a.k < b.k;
}
void build(int f, int t, int x){
	if(f == t)
		T[x] = Tree(data[f].a, f);
	else{
		build(f, mid, ls);
		build(mid + 1, t, rs);
		T[x] = std :: max(T[ls], T[rs]);
	}
}
Tree query(int f, int t, int x){
	if(l <= f && t <= r)
		return T[x];
	if(r <= mid)
		return query(f, mid, ls);
	if(l > mid)
		return query(mid + 1, t, rs);
	return std :: max(query(f, mid, ls), query(mid + 1, t, rs));
}
#define cur data[res.idx].idx
int construct(int f, int t){
	l = f; r = t;
	Tree res = query(1, N, 1);
	if(f != t){
		if(f <= res.idx - 1)
			ans[ans[cur].l = construct(f, res.idx - 1)].p = cur;
		if(res.idx + 1 <= t)
			ans[ans[cur].r = construct(res.idx + 1, t)].p = cur;
	}
	return cur;
}
#undef cur
int main(){
	scanf("%d", &N);
	for(int i = 1;i <= N;++ i)
		data[i].fromInput();
	std :: sort(data + 1, data + N + 1, cmp);
	build(1, N, 1);
	construct(1, N);
	puts("YES");
	for(int i = 1;i <= N;++ i)
		ans[i].show();
	return 0;
}
