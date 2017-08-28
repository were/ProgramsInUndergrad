/*
Programmed by wereFluke
*/
#include <algorithm>
#include <bitset>
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

using std :: bitset;
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

int T, N, M, g[333][333];

bool check(int a, int b, int c){
	if(a == b || a == c || b == c)
		return true;
	if(g[a][b] + g[b][c] == g[a][c])
		return true;
	if(g[a][c] + g[c][b] == g[a][b])
		return true;
	if(g[b][a] + g[a][c] == g[b][c])
		return true;
	return false;
}

int main(){
	cin >> T;
	while(T--){
		cin >> N >> M;
		rep(i, 1, N) rep(j, 1, N) g[i][j] = int(1e9);
		rep(i, 1, M){
			int u, v;
			cin >> u >> v;
			g[u][v] = g[v][u] = 1;
		}
		rep(k, 1, N)
			rep(i, 1, N)
				rep(j, 1, N)
					if(g[i][k] + g[k][j] < g[i][j])
						g[i][j] = g[i][k] + g[k][j];
		set< vi > T_T;
		rep(i, 1, N)
			rep(j, i + 1, N){
				vi tmp;
				rep(k, 1, N)
					if(check(i, j, k))
						tmp.push_back(k);
				T_T.insert(tmp);

			}
		cout << T_T.size() << endl;
	}
	return 0;
}

