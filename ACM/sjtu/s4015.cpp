#include <cstdio>
#include <cstring>
struct Matrix{
	int a[2][2];
	Matrix(int x = 0){
		memset(a, 0, sizeof a);
		a[0][0] = a[1][1] = x;
	}
	int& operator() (int x, int y){
		return a[x][y];
	}
	void show(){
		for(int i = 0;i < 2;++ i){
			for(int j = 0;j < 2;++ j)
				printf("%d ", a[i][j]);
			puts("");
		}
		puts("");
	}
}M, T(1), d(1);
int A, B, N;
Matrix operator* (Matrix a, Matrix b){
	Matrix ret;
	for(int k = 0;k < 2;++ k)
		for(int i = 0;i < 2;++ i)
			for(int j = 0;j < 2;++ j){
				ret(i, j) += a(i, k) * b(k, j);
				ret(i, j) %= 7;
			}
	return ret;
}
int main(){
	scanf("%d%d%d", &A, &B, &N);
	M(0, 0) = A;
	M(0, 1) = B;
	M(1, 0) = 1;
	M(1, 1) = 0;
	-- N;
	for(int i = 1;i <= N;i <<= 1){
		if(N & i)
			T = T * M;
		M = M * M;
	}
	printf("%d\n", (T(1, 0) + T(1, 1)) % 7);
	return 0;
}
