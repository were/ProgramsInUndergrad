/*
Programmed by wereFluke
*/
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <list>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#define rep(i,f,t) for(int i(f);i<=(t);++i)
#define per(i,t,f) for(int i(t);i>=(f);--i)
#define for_vec(i,v) for(unsigned i(0);i<v.size();++i)
#define bit_up(i,f,t) for(int i(f);i<=(t);i+=i&-i)
#define bit_down(i,f) for(int i(f);i;i-=i&-i)

#define X first
#define Y second

using std :: max;
using std :: min;
using std :: swap;
using std :: lower_bound;
using std :: upper_bound;
using std :: vector;
using std :: map;
using std :: set;
using std :: priority_queue;
using std :: string;
using std :: pair;
using std :: make_pair;
using std :: less;
using std :: greater;
using std :: cin;
using std :: cout;
using std :: endl;
using std :: cerr;
using std :: clog;
using std :: ifstream;
using std :: ofstream;
using std :: queue;
using std :: stack;
using std :: deque;
using std :: list;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

int N, ans;
bool g[8][8];

int check(){
	for(int a = 0;a < N;++a)
		for(int b = a + 1;b < N;++b)
			for(int c = b + 1;c < N;++c)
				for(int d = c + 1;d < N;++d){
					int cnt = g[a][b] + g[a][c] + g[a][d] + g[b][c] + g[b][d] + g[c][d];
					if(cnt % 2)
						return 0;
				}
	return 1;
}

void dfs(int x, int y){
	if(y == N){
		++x;
		y = x + 1;
	}
	if(x == N - 1){
		ans += check();
	}else{
		dfs(x, y + 1);
		g[x][y] = g[y][x] = true;
		dfs(x, y + 1);
		g[x][y] = g[y][x] = false;
	}
}

int T;

int main(){
	scanf("%d", &T);
	while(T--){
		scanf("%d", &N);
		const int res[] = {0, 1, 2, 8, 32, 32, 2, 2, 2};
		printf("%d\n", res[N]);
	}
//	dfs(0, 1);
//	printf("%d\n", ans);
	return 0;

