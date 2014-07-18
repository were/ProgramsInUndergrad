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
 
using std::sort;
using std::bitset;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::pair;
using std::make_pair;
using std::less;
using std::greater;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::clog;
using std::ifstream;
using std::ofstream;
using std::queue;
using std::stack;
using std::deque;
using std::list;
 
typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;
typedef pair<int, int> pii;
 
const int MaxN = 300000;
 
int N, ans;
ll T, cur, empty;
pair<ll, ll> a[MaxN];
priority_queue<ll> heap;
 
int main(){
	std::ios::sync_with_stdio(false);
	cin >> N >> T;
	rep(i, 1, N) {
		cin >> a[i].X >> a[i].Y;
	}
	sort(a + 1, a + 1 + N);
	rep(i, 1, N) {
		if(cur + a[i].Y <= T - a[i].X) {
			heap.push(a[i].Y);
			cur += a[i].Y;
		} else {
			heap.push(a[i].Y);
			cur += a[i].Y;
			while(!heap.empty() && cur > T - a[i].X) {
				cur -= heap.top();
				heap.pop();
			}
		}
		ans = max(ans, (int) heap.size());
	}
	cout << ans << endl;
	return 0;
}

