#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime> 
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <bitset>
#include "ElementNotExist.h"
#include "IndexOutOfBound.h"
#include "PriorityQueue.h"

typedef long long LL;
#define pb push_back
#define MPII make_pair<int, int>
#define PII pair<int, int>
#define sz(x) (int)x.size()

using namespace std;

template<class T> T abs(T x){if (x < 0) return -x; else return x;}
int a[100010];

int main(){
//	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	srand(time(0));
	PriorityQueue<int> Q;
	multiset<int> S;
	FILE *input = fopen("test.in", "w");
	for (int i = 0; i < 100000; ++i){
		int t = rand();
		fprintf(input, "%d\n", t);
		Q.push(t);
		S.insert(t);
	}
	fclose(input);
/*
	for (int i = 0; i < 100000; ++i){
		int t;
		scanf("%d", &t);
		Q.push(t);
		S.insert(t);
	}
*/
//	for (auto iter = Q.iterator(); iter.hasNext(); ){
//		cout << iter.next() << ' ';
//	}
//	cout << endl;
	
	int tot = 0;
	for (auto iter = Q.iterator(); iter.hasNext(); ){
		int t = iter.next();
//cout << t;
		static int i = 0;
		++i;
		if (rand() % 2 || i == 100000){
//cout << '!';
			iter.remove();
			S.erase(S.lower_bound(t));
			++tot;
		}
		if(Q.front() == 0) {
			cout << i << endl;
		}
//cout << ' ';
	}
//cout << endl;
	vector<int> V;
	for (auto iter = Q.iterator(); iter.hasNext(); ){
		int t = iter.next();
//cout << t << ' ';
		V.push_back(t);
		if(t == 0) {
			cout << "ri" << endl;
		}
	}
//cout << endl;
	sort(V.begin(), V.end());
	bool ok = true;
	multiset<int>::iterator iter = S.begin();
	for (int i = 0; i < (int)V.size(); ++i){
		cout << V[i] << ' ' << *iter;
		if (V[i] != *iter){
			ok = false;
			cout << ' ' << '!';
		}
		cout << endl;
		++iter;
	}
	if (!ok) {
		for(;;);
	}
	return 0;
}


