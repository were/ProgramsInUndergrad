#include <algorithm>
#include <cstdio>
#include <vector>
#include <cmath>
typedef std::vector<double> vi;
const double eps = 1e-8;
int N, M;
vi a[100];
vi operator* (vi a, double b){
	for(int i = 0;i < M; ++i)
		a[i] *= b;
	return a;
}
vi operator- (vi a, vi b){
	for(int i = 0;i < M; ++i)
		a[i] -= b[i];
	return a;
}
void show(vi a){
	for(int i = 0;i < M; ++i)
		printf("%.10f ", a[i]);
	puts("");
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0;i < N; ++i)
		for(int j = 0;j < M;++ j){
			double x;
			scanf("%lf", &x);
			a[i].push_back(x);
		}
	for(int i = 0;i < N; ++i){
		for(int j = i;j < N; ++j)
			if(fabs(a[j][i]) > eps) {
				a[j].swap(a[i]);
			}
		if(fabs(a[i][i]) > eps){
			for(int j = i + 1;j < N; ++j) if(fabs(a[j][i]) > eps){
				a[j] = a[j] * a[i][i] - a[i] * a[j][i];
			}
		}
	}
	for(int i = N - 1;i >= 0; --i)
		if(fabs(a[i][i]) > eps) {
			for(int j = i - 1;j >= 0; --j)
				if(fabs(a[j][i]) > eps){
					a[j] = a[j] * a[i][i] - a[i] * a[j][i];
				}
			}
	for(int i = 0;i < N; ++i){
		show(a[i]);
		printf("%f\n", a[i].back() / a[i][i]);
	}
	return 0;
}
