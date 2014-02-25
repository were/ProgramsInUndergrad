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

const int MaxN = 1 << 19;

int N, M, n, lowBit[MaxN], highBit[MaxN];
ll data[MaxN], delta[MaxN];

ll ans(int f, int t){
	return data[f + t] + delta[f + t] * ll(t - f);
}

void push(int f, int t){
	int mid = (f + t) / 2;
	data[f + t] = ans(f, t);
	delta[f + mid] += delta[f + t];
	delta[mid + t] += delta[f + t];
	delta[f + t] = 0ll;
}

void getPre(int &f, int &t){
	if(f / (t - f) % 2)
		f -= (t - f);
	else
		t += (t - f);
}

void update(int f, int t){
	int mid = (f + t) / 2;
	data[f + t] = ans(f, mid) + ans(mid, t);
}

void down(int l, int r){
	for(int f = 0, t = n, mid;l > f || t > r;){
		mid = (f + t) / 2;
		push(f, t);
		r <= mid ? t = mid : l >= mid ? f = mid : t = mid;
	}
	for(int f = 0, t = n, mid;l > f || t > r;){
		mid = (f + t) / 2;
		push(f, t);
		l >= mid ? f = mid : r <= mid ? t = mid : f = mid;
	}
}

void up(int f, int t, int l, int r){
	while(f != l || t != r){
		if(t - f < r - l){
			getPre(f, t);
			update(f, t);
		}else{
			getPre(l, r);
			update(l, r);
		}
	}
	while(t - f < n){
		getPre(f, t);
		update(f, t);
	}
}

int main(){
//freopen("input", "r", stdin);
//freopen("output", "w", stdout);
//	std :: ios :: sync_with_stdio(false);
//	cin >> N >> M;
	scanf("%d%d", &N, &M);
	for(n = 1;n < N;n <<= 1);
	lowBit[0] = n;
	rep(i, 1, n){
		lowBit[i] = i & -i;
		highBit[i] = i == lowBit[i] ? i : highBit[i - 1];
	}
	for(int i = 0;i < N;++i)
		scanf("%lld", data + i + i + 1);
//		cin >> data[i + i + 1];
	for(int len = 2;len <= n;len <<= 1)
		for(int f = 0, t = len;f < n;f += len, t += len)
			data[f + t] = data[f + (f + t) / 2] + data[(f + t) / 2 + t];
	while(M--){
		char buffer[10];
		int l, r;
		scanf("%s%d%d", buffer, &l, &r);
//		cin >> buffer >> l >> r;
		--l;
		down(l, r);
		if(*buffer == 'Q'){
			ll res = 0ll;
			while(l < r){
				int t = l + min(lowBit[l], highBit[r - l]);
				res += ans(l, t);
				l = t;
			}
			cout << res << endl;
		}else{
			ll d;
			scanf("%lld", &d);
//			cin >> d;
			int l1 = -1, r1 = -1, l2 = -1, r2 = -1;
			while(l < r){
				int t = l + min(lowBit[l], highBit[r - l]);
				if(l1 == -1){
					l1 = l2 = l;
					r1 = r2 = t;
				}else{
					l2 = l;
					r2 = t;
				}
                //printf("[%d, %d) ", l, t);
				delta[l + t] += d;
				l = t;
			}
            //puts("");
            //printf("1: [%d, %d)\n", l1, r1);
			up(l1, r1, l2, r2);
		}
	}
	return 0;
}
