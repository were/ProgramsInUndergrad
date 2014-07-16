//  main.cpp
//  sgu175
//
//  Created by were on 2014/03/30.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>

using std :: min;
using std :: max;

int N, Q;

int inRange(int x, int l, int r){
	return x >= min(l, r) && x <= max(l, r);
}

int work(int f, int t, int l, int r, int x) {
//	printf("%d %d %d\n", l, r, k);
//	assert(l > 0);
//	assert(r > 0);
	if(l != r){
		int len = abs(l - r) + 1;
		int m = (f + t) / 2;
		//l, l + len * x - x
		//l + len * x, r
		if(inRange(Q, r, l + len / 2 * x)){
			return work(f, m, r, l + len / 2 * x, -x);
		}else{
			return work(m + 1, t, l + len / 2 * x - x, l, -x);
		}
	}else{
		return f;
	}
}

int main(int argc, const char * argv[])
{
	scanf("%d%d", &N, &Q);
	printf("%d\n", work(1, N, 1, N, 1));
	return 0;
}

