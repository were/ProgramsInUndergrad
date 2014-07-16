//
//  main.cpp
//  s1246
//
//  Created by were on 2014/04/01.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstring>

const int MaxN = 1111;

int N, M, a, b, c, d;
int s[MaxN][MaxN], q[MaxN], idx[MaxN][MaxN];
int tmp[MaxN], ans, x1, y1, x2, y2;

int getSum(int a, int b, int c, int d) {
	return s[c][d] - s[c][b - 1] - s[a - 1][d] + s[a - 1][b - 1];
}

int main(int argc, const char * argv[]) {
	scanf("%d%d%d%d%d%d", &M, &N, &b, &a, &d, &c);
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= M; ++j) {
			scanf("%d", s[i] + j);
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
		}
	}
	for (int i = 1, k = b - d - 1; i + c - 1<= N; ++i) {
		int l = 1, r = 0;
		for (int j = 1; j + d - 1 <= M; ++j) {
			tmp[j] = getSum(i, j, i + c - 1, j + d - 1);
			while (l <= r && q[l] < j - k + 1) {
				++l;
			}
			while (l <= r && tmp[q[r]] >= tmp[j]) {
				--r;
			}
			q[++r] = j;
			if (j >= k) {
				idx[i][j - k + 1] = q[l];
			}
		}
	}
	for (int j = 1, k = a - c - 1; j + (c - 1) + (k - 1) <= M; ++j) {
		int l = 1, r = 0;
		for (int i = 1; i < N; ++i) {
			tmp[i] = getSum(i, idx[i][j], i + c - 1, idx[i][j] + d - 1);
			while (l <= r && q[l] < i - k + 1) {
				++l;
			}
			while (l <= r && tmp[q[r]] >= tmp[i]) {
				--r;
			}
			q[++r] = i;
			if (i >= k) {
				if (i - k >= 1 && j - 1 >= 1 && i - k + a - 1 <= N && j - 1 + b - 1 <= M) {
					int tmpAns = getSum(i - k, j - 1, i - k + a - 1, j - 1 + b - 1);
					tmpAns -= tmp[q[l]];
					if (tmpAns > ans) {
						ans = tmpAns;
						x1 = i - k;
						y1 = j - 1;
						x2 = q[l];
						y2 = idx[q[l]][j];
					}
				}
			}
		}
	}
	printf("%d %d\n%d %d\n", y1, x1, y2, x2);
    return 0;
}
