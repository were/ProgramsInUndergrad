#include <iostream>
typedef long long ll;
ll N, M, K, a, ans;
ll pow(ll a, ll b){
	if(b == 0)
		return 1;
	if(b == 1)
		return a;
	int tmp = pow(a, b / 2);
	tmp = tmp * tmp % K;
	return b % 2 ? tmp * a % K : tmp;
}
int main(){
	std :: cin >> N >> M >> K;
	for(int i = 1;i <= N;++i){
		std :: cin >> a;
		ans += pow(a, M) == 0ll;
	}
	std :: cout << ans << "\n";
	return 0;
}
