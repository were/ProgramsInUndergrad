/*
PROG : fence9
ID : weng_xo2
LANG : C++
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

int N, M, P, ans;
ifstream fin("fence9.in");
ofstream fout("fence9.out");

int gcd(int a, int b){
	return b ? gcd(b, a % b) : a;
}

int calcBound(int a, int b){
	return !a || !b ? a + b + 1 : gcd(a, b) + 1;
}

int calcInside(int a, int b){
	int A = a + 1, B = b + 1;
	return (A * B - calcBound(a, b)) / 2 - A - B + 3;
}

int main(){
	fin >> N >> M >> P;
	if(P > N){
		ans = calcInside(N, M) + calcInside(P - N, M) + M - 1;
	}
	if(P < N){
		ans = calcInside(N, M) - calcInside(N - P, M) - calcBound(N - P, M) + 2;
	}
	if(P == N)
		ans = calcInside(N, M);
	fout << ans << endl;
	fin.close();
	fout.close();
	return 0;
}

