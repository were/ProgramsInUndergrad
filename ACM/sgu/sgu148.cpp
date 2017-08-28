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

#define need first
#define idx second

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

const int MaxN = 15001, Inf = ~0u >> 1;

int N, w[MaxN], l[MaxN], p[MaxN], s[MaxN], ans = Inf, cost;
priority_queue<pii> heap, res;

int main(){
	cin >> N;
	rep(i, 1, N){
		cin >> w[i] >> l[i] >> p[i];
		s[i] = s[i - 1] + w[i];
	}
	per(i, N, 1){
		for(cost += p[i];!heap.empty() && heap.top().need > s[i - 1];heap.pop())
			cost -= p[heap.top().idx];
		heap.push(pii(s[i] - l[i], i));
		if(cost < ans){
			ans = cost;
			res = heap;
		}
	}
	while(!res.empty()){
		cout << res.top().idx << endl;
		res.pop();
	}
	return 0;
}

