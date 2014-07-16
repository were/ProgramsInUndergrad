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
#include <sstream>
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
using std :: istringstream;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;

int T, N, M, tot;
string data[1111][1111], s, nm[1111], ans[1111];

int main(){
//	freopen("input", "r", stdin);
//	freopen("output", "w", stdout);
	getline(cin, s);
	istringstream sT(s);
	sT >> T;
	while(T--){
		tot = 0;
		getline(cin, s);
		istringstream sNM(s);
		sNM >> N >> M;
		getline(cin, s);
		for(unsigned j = 0;j < s.size();++j)
			if(s[j] == ',')
				s[j] = ' ';
		istringstream sName(s);
		for(int i = 0;i < M;++i){
			sName >> nm[i];
//			cout << nm[i] << endl;
		}
		for(int i = 0;i < N;++i){
			getline(cin, s);
			for(unsigned j = 0;j < s.size();++j)
				if(s[j] == ',')
					s[j] = ' ';
//			cout << s << endl;
			istringstream sData(s);
			for(int j = 0;j < M;++j)
				sData >> data[i][j];
		}
		for(int i = 0;i < M;++i){
//			cout << nm[i] << endl;
			int x = -1;
			for(int j = 0;j < N;++j)
				if(data[j][i] != "NA")
					x = j;
			if(~x){
				bool flag = true;
				for(int j = 0;j < N;++j){
					if(data[j][i] != "NA" && data[j][i] != data[x][i])
						flag = false;
//					cout << data[j][i] << endl;
				}
//				cout << flag << endl << endl;
				if(flag)
					ans[tot++] = nm[i];
			}else{
				ans[tot++] = nm[i];
			}
		}
		sort(ans, ans + tot);
		for(int i = 0;i < tot;++i)
			cout << ans[i] << endl;
		if(T){
//			cout << "not ended";
			cout << endl;
		}
	}
	return 0;
}

