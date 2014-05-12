#include <algorithm>
#include <cstdio>
#include <set>

using std::sort;
using std::set;

int T, N, ans1, ans2, cs;
bool hsh[1010];
double a[1010], b[1010];

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		ans1 = ans2 = 0;
		set<double> T_T;
		for(int i = 0; i < N; ++i){
			scanf("%lf", a + i);
		}
		for(int i = 0; i < N; ++i){
			scanf("%lf", b + i);
			T_T.insert(b[i]);
		}
		sort(a, a + N);
		sort(b, b + N);
		for(int f = 0, t = N - 1, i = N - 1; i >= 0; --i){
			if(a[t] > b[i]){
				--t;
				++ans1;
			}else{
				++f;
			}
		}
		for(int i = 0; i < N; ++i){
			if(T_T.upper_bound(a[i]) != T_T.end()){
				T_T.erase(T_T.upper_bound(a[i]));
			}else{
				T_T.erase(T_T.begin());
				++ans2;
			}
		}
		printf("Case #%d: %d %d\n", ++cs, ans1, ans2);
	}
}
