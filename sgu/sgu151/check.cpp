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
typedef pair<double, double> pdd;

ifstream input("input"), output("output");
ofstream myLog("log");

double sqr(double a){
	return a * a;
}

pdd operator- (pdd a, pdd b){
	return pdd(a.X - b.X, a.Y - b.Y);
}

double len(pdd a){
	return sqrt(sqr(a.X) + sqr(a.Y));
}

pdd mid(pdd a, pdd b){
	return pdd((a.X + b.X) / 2., (a.Y + b.Y) / 2.);
}

int main(){
	pdd A, B, C;
	double AB, AC, AM;
	bool flag = true;
	output >> A.X >> A.Y;
	output >> B.X >> B.Y;
	output >> C.X >> C.Y;
	input >> AB >> AC >> AM;
	if(len(B - A) != AB){
		myLog << len(B - A) << " " << AB << endl;
		myLog << "AB not equal" << endl;
		flag = false;
	}
	if(len(A - C) != AC){
		myLog << len(A - C) << " " << AC << endl;
		myLog << "AC not equal" << endl;
		flag = false;
	}
	if(len(mid(B, C) - A) != AM){
		myLog << len(mid(B, C) - A) << " " << AM << endl;
		myLog << "AM not equal" << endl;
		flag = false;
	}
	if(flag)
		myLog << "Right!" << endl;
	return 0;
}

