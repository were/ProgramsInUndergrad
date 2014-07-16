#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstdio>
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long ll;
typedef double dbl;
int T, N, M, hsh[1111], u, v, cur;
const dbl eps= 1e-7;
int gi(){
	char ch;
	while(!isdigit(ch= getchar()) && ch!='-');
	if(ch == '-')
		return -gi();
	int ret= ch-'0';
	while(isdigit(ch= getchar()))
		ret= ret*10 + ch-'0';
	return ret;
}
struct __cor{
	ll x, y;
	void init(){
		x= gi();
		y= gi();
	}
	dbl dis(const __cor&a){
		return sqrt(dbl(sqr(ll(x-a.x)) + sqr(ll(y-a.y))));
	}
	__cor(ll x, ll y) : x(x), y(y) {}
	__cor() {}
};
struct __seg{
	__cor a, b;
	void init(){
		a.init();
		b.init();
	}
	dbl len(){
		return a.dis(b);
	}
	int l(){
		return min(a.x, b.x);
	}
	int r(){
		return max(a.x, b.x);
	}
	int u(){
		return max(a.y, b.y);
	}
	int d(){
		return min(a.y, b.y);
	}
}seg[1111];
int sign(ll x){
	return x < 0 ? -1 : x > 0;
}
__cor operator- (const __cor&x, const __cor&y){
	return __cor(
		x.x - y.x,
		x.y - y.y
	);
}
ll operator* (const __cor&x, const __cor&y){
	return ll(x.x) * ll(y.y) - ll(y.x) * ll(x.y);
}
bool isIntersect(__seg&x, __seg&y){
	if(x.d() > y.u()){
		return 0;
	}
	if(y.d() > x.u()){
		return 0;
	}
	if(x.l() > y.r()){
		return 0;
	}
	if(y.l() > x.r()){
		return 0;
	}
	return
		sign((y.a-x.a) * (y.b-x.a)) * sign((y.a-x.b) * (y.b-x.b)) <= 0 &&
		sign((x.a-y.a) * (x.b-y.a)) * sign((x.a-y.b) * (x.b-y.b)) <= 0;
}
void dfs(int x){
	hsh[x]= cur;
	for(int i= 1;i<= N;++ i)
		if(!hsh[i] && isIntersect(seg[x], seg[i]))
			dfs(i);
}
int main(){
	for(T= gi();T --;){
		N= gi(); M= gi();
		cur= 0;
		for(int i= 1;i<= N;++ i){
			seg[i].init();
			hsh[i]= 0;
		}
		for(int i= 1;i<= N;++ i)
			if(!hsh[i]){
				++ cur;
				dfs(i);
			}
		while(M --){
			u= gi();
			v= gi();
			puts(hsh[u] == hsh[v] ? "YES" : "NO");
		}
	}
	return 0;
}


