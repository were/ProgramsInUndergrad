#include <iostream>

const int MaxN = 10001;

int N, a[MaxN], sum;

int main(){
	std :: cin >> N;
	for(int i = 1;i <= N;++i){
		std :: cin >> a[i];
		sum += a[i];
	}
	for(int i = 1, left = 0;i <= N;++i){
		int res = a[i] * 100 / sum;
		if((left += a[i] * 100 % sum) >= sum){
			++res;
			left -= sum;
		}
		std :: cout << res << " \n"[i == N];
	}
	return 0;
}
