#include <algorithm>
#include <iostream>
typedef long long ll;
ll a, b, d, ans;
int main(){
	std :: cin >> a >> b;
	while(a && b){
		if(a > b) std :: swap(a, b);
		a <<= 1;
		b -= a >> 1;
		if(++ans > 40)
			break;
	}
	std :: cout << (!a || !b ? ans : -1) << std :: endl;
	return 0;
}
