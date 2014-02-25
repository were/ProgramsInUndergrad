#include <iostream>
#include <string>
int N, T, ans, caseCnt;
std :: string s[100];
bool flag;
int main(){
	std :: cin >> T;
	while(T--){
		std :: cin >> N;
		std :: getline(std :: cin, s[0]);
		for(int i = 0;i < N;++i)
			std :: getline(std :: cin, s[i]);
		ans = 0;
		for(int i = 1;i < N;++i)
			if(s[i] < s[i - 1]){
				for(int j = i;j > 0 && s[j] < s[j - 1];--j)
					s[j].swap(s[j - 1]);
				++ans;
			}
		std :: cout << "Case #" << ++caseCnt << ": " << ans << "\n";
	}
	return 0;
}
