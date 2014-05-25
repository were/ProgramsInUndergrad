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

using std :: sort;
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
using std :: istringstream;
using std :: ostringstream;
using std :: stringstream;
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

const int MaxN = 2000000;
const ll Mod = (ll)1e9 + 7;

ll f[MaxN + 1], inv[MaxN + 1];

ll pow(ll a, ll b) {
	if(b == 1ll) {
		return a % Mod;
	}
	if(b == 0) {
		return 1ll;
	}
	ll ret = pow(a, b / 2ll);
	ret = ret * ret % Mod;
	if(b % 2 == 1) {
		ret = ret * a % Mod;
	}
	return ret;
}

ll C(ll a, ll b) {
	if(a < b) {
		return 0ll;
	}
	if(a == b) {
		return 1ll;
	}
	return f[a] * inv[b] % Mod * inv[a - b] % Mod;
}

int main(){
	*f = 1;
	for(int i = 1; i <= MaxN; ++i) {
		f[i] = f[i - 1] * (ll)i % Mod;
	}
	inv[MaxN] = pow(f[MaxN], Mod - 2);
	for(int i = MaxN - 1; i >= 1; --i) {
		inv[i] = inv[i + 1] * (ll)(i + 1) % Mod;
	}
	int T, cs = 0;
	scanf("%d", &T);
	while(T--) {
		int N;
		scanf("%d", &N);
		ll ans = (C(N * 2, N) - C(N * 2, N + 1) + Mod) % Mod;
		printf("Case #%d:\n", ++cs);
		printf("%d\n", (int)ans);
	}
	return 0;
}

