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

int A, a, b, c, M, k, i;
ll cur;
int hsh[10001];

int main(){
	cin >> A >> a >> b >> c >> M >> k;
	for(i = 0, cur = A;!hsh[cur];++i){
		if(i == k){
			printf("%d\n", cur);
			return 0;
		}
		hsh[cur] = i;
		cur = cur * cur * a + b * cur + c;
		cur %= M;
	}
	k = (k - hsh[cur] + 1) % (i - hsh[cur]);
	if(!k)
		k = i - hsh[cur];
	for(int ans = 0;ans <= 10000;++ans){
		if(hsh[ans] - hsh[cur] == k - 1){
			printf("%d\n", ans);
			return 0;
		}
	}
	return 0;
}

