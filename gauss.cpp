#include <algorithm>
#include <cstdio>
#include <vector>
typedef std :: vector<int> vi;
int N, M;
vi a[100];
vi operator* (vi a, int b){
	for(int i = 0;i < M;++ i)
		a[i] *= b;
	return a;
}
vi operator- (vi a, vi b){
	for(int i = 0;i < M;++ i)
		a[i] -= b[i];
	return a;
}
void show(vi a){
	for(int i = 0;i < M;++ i)
		printf("%d ", a[i]);
	puts("");
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i = 0, x;i < N;++ i)
		for(int j = 0;j < M;++ j){
			scanf("%d", &x);
			a[i].push_back(x);
		}
	for(int i = 0;i < N;++ i){
		for(int j = i;j < N;++ j)
			if(a[j][i])
				a[j].swap(a[i]);
		if(a[i][i]){
			for(int j = i + 1, lcm;j < N;++ j) if(a[j][i]){
				lcm = a[i][i] * a[j][i] / std :: __gcd(a[i][i], a[j][i]);
				a[j] = a[j] * (lcm / a[j][i]) - a[i] * (lcm / a[i][i]);
			}
		}
	}
	for(int i = 0, d = 0;i < N;++ i, d = 0){
		for(int j = 0;j < M;++ j)
			if(a[i][j])
				d = d == 0 ? a[i][j] : std :: __gcd(a[i][j], d);
		for(int j = 0;j < M;++ j)
			a[i][j] /= d;
	}
	for(int i = N - 1, lcm = 0;i >= 0;-- i)
		if(a[i][i])
			for(int j = i - 1;j >= 0;-- j)
				if(a[j][i]){
					lcm = a[i][i] * a[j][i] / std :: __gcd(a[i][i], a[j][i]);
					a[j] = a[j] * (lcm / a[j][i]) - a[i] * (lcm / a[i][i]);
				}
	for(int i = 0, d = 0;i < N;++ i, d = 0){
		for(int j = 0;j < M;++ j)
			if(a[i][j])
				d = d == 0 ? a[i][j] : std :: __gcd(a[i][j], d);
		for(int j = 0;j < M;++ j)
			a[i][j] /= d;
		show(a[i]);
	}
	return 0;
}
