//
//  main.cpp
//  sgu180
//
//  Created by were on 2014/03/30.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <cstdio>

const int MaxN = 65538;

int N, n, a[MaxN], b[MaxN], bit[MaxN];
long long ans;

int main(int argc, const char * argv[])
{
	scanf("%d", &N);
	for(int i = 1;i <= N;++i){
		scanf("%d", a + i);
		b[i] = a[i];
	}
	std :: sort(b + 1, b + 1 + N);
	n = std :: unique(b + 1, b + 1 + N) - b - 1;
	//printf("%d\n", n);
	for(int i = 1;i <= N;++i){
		a[i] = std :: lower_bound(b + 1, b + 1 + n, a[i]) - b;
		int cnt = i - 1;
		for(int j = a[i];j;j -= j & -j)
			cnt -= bit[j];
		for(int j = a[i];j <= n;j += j & -j)
			++bit[j];
		ans += cnt;
	}
	std :: cout << ans << std :: endl;
    return 0;
}

