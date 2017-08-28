#include <iostream>
#include <set>
#include <utility>
int N, X, Y;
std :: set< std :: pair<int, int> > ans;
int main(){
	std :: cin >> N >> X >> Y;
	for(int x = 0, y = 0;;(x += X) %= N, (y += Y) %= N){
		if(ans.find(std :: make_pair(x, y)) == ans.end())
			ans.insert(std :: make_pair(x, y));
		else
			break;
	}
	std :: cout << ans.size() << std :: endl;
	for(std :: set<std :: pair<int, int> > :: iterator cur = ans.begin();cur != ans.end();++cur)
		std :: cout << cur->first << " " << cur->second << std :: endl;
	return 0;
}
