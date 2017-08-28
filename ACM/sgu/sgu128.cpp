#include <algorithm>
#include <cstdio>
#include <cstdlib>
#define HOR 1
#define VER -1
#define NON 0

const int MaxN = 11111;
typedef long long ll;

int N, sol[MaxN], solSize, horSize, verSize, cnt[MaxN], fa[MaxN], n;
ll ans;

struct Coordinate{
	int x, y, idx;
	void fromInput();
	void show(){
		printf("(%d,%d)\n", x, y);
	}
	Coordinate() {}
	Coordinate(int x, int y, int idx) : x(x), y(y), idx(idx) {}
}cor[MaxN];
void Coordinate :: fromInput(){
	scanf("%d%d", &x, &y);
	idx = this - cor;
	fa[idx] = idx;
}
bool cmpX(const Coordinate&a, const Coordinate&b) {
	return a.x != b.x ? a.x < b.x : a.y < b.y;
}
bool cmpY(const Coordinate&a, const Coordinate&b){
	return a.y != b.y ? a.y < b.y : a.x < b.x;
}

struct Segment{
	Coordinate a, b;
	Segment() {}
	Segment(const Coordinate&_a, const Coordinate&_b) : a(_a), b(_b) {
		if(a.x > b.x) std :: swap(a.x, b.x);
		if(a.y > b.y) std :: swap(a.y, b.y);
	}
	ll length(){
		return b.x - a.x + b.y - a.y;
	}
	void show(){
		a.show();
		b.show();
		puts("");
	}
}horSeg[MaxN], verSeg[MaxN];

bool operator== (const Coordinate&a, const Coordinate&b){
	return a.x == b.x && a.y == b.y;
}

bool intersected(const Segment&ver, const Segment&hor){
	if(ver.a == hor.a || ver.a == hor.b || ver.b == hor.a || ver.b == hor.b)
		return false;
	return ver.a.y <= hor.a.y && hor.a.y <= ver.b.y && hor.a.x <= ver.a.x && ver.a.x <= hor.b.x;
}

int getfa(int x){
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

void noSolution(){
	puts("0");
	exit(0);
}

int main(){
	scanf("%d", &N);
	for(int i = 0;i < N;++i)
		cor[i].fromInput();
	cor[n = N] = Coordinate(999999, 999999, N);
	std :: sort(cor, cor + N, cmpX);
	for(int i = 1, pre = 0;i <= N;++i)
		if(cor[i].x != cor[i - 1].x){
			for(int j = pre;j < i;j += 2)
				if(j + 1 < i){
					ans += (verSeg[verSize++] = Segment(cor[j], cor[j + 1])).length();
					++cnt[cor[j].idx];
					++cnt[cor[j + 1].idx];
					if(getfa(cor[j].idx) != getfa(cor[j + 1].idx)){
						fa[getfa(cor[j].idx)] = getfa(cor[j + 1].idx);
						--n;
					}
				}else
					noSolution();
			pre = i;
		}
	std :: sort(cor, cor + N, cmpY);
	for(int i = 1, pre = 0;i <= N;++i)
		if(cor[i].y != cor[i - 1].y){
			for(int j = pre;j < i;j += 2)
				if(j + 1 < i){
					ans += (horSeg[horSize++] = Segment(cor[j], cor[j + 1])).length();
					++cnt[cor[j].idx];
					++cnt[cor[j + 1].idx];
					if(getfa(cor[j].idx) != getfa(cor[j + 1].idx)){
						fa[getfa(cor[j].idx)] = getfa(cor[j + 1].idx);
						--n;
					}
				}else
					noSolution();
			pre = i;
		}
	if(n != 1)
		noSolution();
	for(int i = 0;i < N;++i)
		if(cnt[i] != 2)
			noSolution();
	for(int i = 0;i < verSize;++i){
		for(int j = 0;j < horSize;++j){
			if(intersected(verSeg[i], horSeg[j]))
				noSolution();
		}
	}
	printf("%lld\n", ans);
	return 0;
}

