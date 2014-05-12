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

int M, s, p;
ll ans;
map<string, pii> hsh;
set<pii> T_T;
string op, nm;

int main(){
//	freopen("input", "r", stdin);
	std :: ios :: sync_with_stdio(false);
	cin >> M;
	while(M--){
		cin >> op;
		if(op[0] == 'A'){
			cin >> nm >> s >> p;
			pii tmp(s, p);
			hsh[nm] = tmp;
			T_T.insert(tmp);
			set<pii> :: iterator cur = T_T.find(tmp);
			set<pii> :: iterator pre = cur, nxt = cur;
			bool hasPre = false, hasNxt = false;
			if(cur != T_T.begin()){
				--pre;
				hasPre = true;
			}
			if(++nxt != T_T.end())
				hasNxt = true;
			if(hasPre && hasNxt)
				ans -= ll(pre->Y) * ll(nxt->Y);
			if(hasPre)
				ans += ll(pre->Y) * ll(cur->Y);
			if(hasNxt)
				ans += ll(nxt->Y) * ll(cur->Y);
		}else{
			cin >> nm;
			pii tmp = hsh[nm];
			set<pii> :: iterator cur = T_T.find(tmp);
			set<pii> :: iterator pre = cur, nxt = cur;
			bool hasPre = false, hasNxt = false;
			if(cur != T_T.begin()){
				--pre;
				hasPre = true;
			}
			if(++nxt != T_T.end())
				hasNxt = true;
			if(hasPre)
				ans -= ll(pre->Y) * ll(cur->Y);
			if(hasNxt)
				ans -= ll(nxt->Y) * ll(cur->Y);
			if(hasPre && hasNxt)
				ans += ll(pre->Y) * ll(nxt->Y);
			hsh.erase(nm);
			T_T.erase(tmp);
		}
		printf("%lld\n", ans);
	}
}

