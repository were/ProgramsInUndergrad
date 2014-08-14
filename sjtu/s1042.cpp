//
//  main.cpp
//  s1042
//
//  Created by were on 2014/04/14.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

const int MaxN = 12346;

int N, l[MaxN], r[MaxN], root;
bool hsh[MaxN];
std::vector<int> ans;

void firstOrder(int x) {
	if (x) {
		ans.push_back(x);
		firstOrder(l[x]);
		firstOrder(r[x]);
	}
}

void lastOrder(int x) {
	if (x) {
		lastOrder(l[x]);
		ans.push_back(x);
		lastOrder(r[x]);
	}
}

void depOrder(int x) {
	memset(hsh, 0, sizeof hsh);
	std::queue<int> q;
	q.push(x);
	hsh[x] = true;
	while (!q.empty()) {
		int x = q.front();
		ans.push_back(x);
		if (l[x]){
			for (x = l[x]; x && !hsh[x]; x = r[x]) {
				hsh[x] = true;
				q.push(x);
			}
		}
		q.pop();
	}
}

int main(int argc, const char * argv[])
{
	scanf("%d", &N);
	for (int i = 1; i <= N; ++i) {
		int x;
		scanf("%d", &x);
		scanf("%d%d", l + x, r + x);
		hsh[l[x]] = true;
		hsh[r[x]] = true;
	}
	for (int i = 1; i <= N; ++i) {
		if (!hsh[i]) {
			root = i;
		}
	}
	firstOrder(root);
	lastOrder(root);
	depOrder(root);
	for (int i = 0; i < N; ++i) {
		printf(i == N - 1 ? "%d\n" : "%d ", ans[i]);
	}
	for (int i = N; i < 2 * N; ++i) {
		printf(i == 2 * N - 1 ? "%d\n" : "%d ", ans[i]);
	}
	for (int i = 2 * N; i < 3 * N; ++i) {
		printf(i == 3 * N - 1 ? "%d\n" : "%d ", ans[i]);
	}
    return 0;
}
