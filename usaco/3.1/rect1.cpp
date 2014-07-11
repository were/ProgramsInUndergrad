/*
ID : weng_xo 2
PROB : rect1
LANG : C++
*/
#include <algorithm>
#include <cstdio>
#define area ((rx - lx) * (ry - ly))
using std :: min;
using std :: max;
const int MaxN = 1010;
int A, B, N, x1[MaxN], x2[MaxN], y1[MaxN], y2[MaxN], cl[MaxN];
int ans[2555];
void cover(int lx, int ly, int rx, int ry, int x, int cur){
	if(area != 0 && cur <= N){
		if(lx < x1[cur])
			cover(lx, max(ly, y1[cur]), min(rx, x1[cur]), max(ry, y1[cur]), x, cur + 1);
		if(ry > y2[cur])
			cover(max(x1[cur], lx), max(ly, y2[cur]), max(x1[cur], rx), ry, x, cur + 1);
		if(rx > x2[cur])
			cover(max(lx, x2[cur]), min(y2[cur], ly), rx, min(y2[cur], ry), x, cur + 1);
		if(ly < y1[cur])
			cover(min(x2[cur], lx), ly, min(x2[cur], rx), min(ry, y1[cur]), x, cur + 1);
	}else
		ans[x] += area;
}
int main(){
	freopen("rect1.in", "r", stdin);
	freopen("rect1.out", "w", stdout);
	scanf("%d%d%d", x2, y2, &N);
	cl[0] = 1;
	for(int i = 1;i <= N;++ i)
		scanf("%d%d%d%d%d", x1 + i, y1 + i, x2 + i, y2 + i, cl + i);
	for(int i = N;i > -1;-- i)
		cover(x1[i], y1[i], x2[i], y2[i], cl[i], i + 1);
	for(int i = 1;i <= 2500;++ i)
		if(ans[i])
			printf("%d %d\n", i, ans[i]);
	return 0;
}

