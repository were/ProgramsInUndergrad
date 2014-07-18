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
 
const int MaxN = 1111111;
 
int N, a[MaxN], ans1, ans2, hsh[MaxN], flag;
 
int calc(int x) {
	if(x >= 3) {
		return 2;
	}
	return x == 2 ? 1 : 0;
}
 
int main(){
	while(~scanf("%d", &N)) {
		++flag;
		rep(i, 1, N) scanf("%d", a + i);
		ans1 = ans2 = 0;
		rep(i, 1, N) if(hsh[i] != flag) {
			int x = i, delta = 0;
			while(hsh[x] != flag) {
				//printf("%d ", x);
				hsh[x] = flag;
				x = a[x];
				++delta;
			}
			//puts("");
			//printf("%d: %d\n", i, calc(delta));
			ans1 += (delta - 1);
			ans2 = max(delta, ans2);
		}
		printf("%d\n%d\n", ans1, calc(ans2));
	}
}

