#include <iostream>
#include <map>
#include <string>
#include <vector>
int caseCnt, vis[222];
std :: map<std :: string, int> hsh;
std :: vector<int> g[222];
bool dfs(int x, int col){
	vis[x] = col;
	for(std :: vector<int> :: iterator cur = g[x].begin();cur != g[x].end();++cur){
		if(vis[*cur] == 0){
			if(!dfs(*cur, col * -1))
				return false;
		}else{
			if(vis[*cur] == vis[x])
				return false;
		}
	}
	return true;
}
int main(){
	int T;
	std :: cin >> T;
	while(T--){
		int N, tot = 0;
		bool flag = true;
		std :: cin >> N;
		for(int i = 1;i <= N;++i){
			std :: string s1, s2;
			std :: cin >> s1 >> s2;
			if(!hsh[s1])
				vis[hsh[s1] = ++tot] = 0;
			if(!hsh[s2])
				vis[hsh[s2] = ++tot] = 0;
			g[hsh[s1]].push_back(hsh[s2]);
			g[hsh[s2]].push_back(hsh[s1]);
		}
		for(int i = 1;i <= tot;++i)
			if(vis[i] == 0 && !dfs(i, 1)){
				flag = false;
				break;
			}
		std :: cout << "Case #" << (++caseCnt) << ": " << (flag ? "Yes\n" : "No\n");
		for(int i = 1;i <= tot;++i)
			g[i].clear();
		hsh.clear();
	}
	return 0;
}
