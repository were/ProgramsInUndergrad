#include <algorithm>
#include <cstdio>
int N, K, k, hsh[312502], ned[312502], s[5001], cnt, a[5001], b[5001];
int nxt(int x){
	int ret = x;
	while(x){
		ret += x % 10;
		x /= 10;
	}
	return ret;
}
bool get(int*hsh, int x){
	return hsh[x >> 5] >> (x & 31) & 1;
}
void set(int*hsh, int x){
	hsh[x >> 5] |= 1 << (x & 31);
}
int main(){
	scanf("%d%d", &N, &K);
	for(int i = 1;i <= K; ++i){
		scanf("%d", s + i);
		b[i] = s[i];
		set(ned, s[i]);
	}
	std :: sort(b + 1, b + 1 + K);
	k = std :: unique(b + 1, b + 1 + K) - b - 1;
	for(int i = 1;i <= N; ++i) if(get(hsh, i) == 0){
		++cnt;
		if(get(ned, cnt))
			a[++a[0]] = i;
		for(int j = nxt(i);!get(hsh, j) && j <= N;j = nxt(j))
			set(hsh, j);
	}
	printf("%d\n", cnt);
	for(int i = 1;i <= K; ++i){
		s[i] = std :: lower_bound(b + 1, b + 1 + k, s[i]) - b;
		printf(i == K ? "%d\n" : "%d ", a[s[i]]);
	}
	return 0;
}

