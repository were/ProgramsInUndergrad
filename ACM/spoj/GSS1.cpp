#include <cstdio>
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

const int inf = ~0u >> 1;

char bufferIn[10000000], *hd = bufferIn;
char bufferOut[10000000], *tl = bufferOut;
int N, n, M, l, r, highBit[1 << 17], lowBit[1 << 17];

struct Data{
	int l, r, s, m;
}data[1 << 17];

int gi(){
	while((*hd < '0' || *hd > '9') && *hd != '-')
		++hd;
	bool flag = *hd == '-';
	int ret = flag ? 0 : *hd - '0';
	++hd;
	while(*hd >= '0' && *hd <= '9')
		ret = (ret << 1) + (ret << 3) + *hd++ - '0';
	return flag ? -ret : ret;
}

void writeInt(int x){
	if(x < 0){
		*tl++ = '-';
		writeInt(-x);
	}else{
		if(x > 9)
			writeInt(x / 10);
		*tl++ = x % 10 + '0';
	}
}

int main(){
	fread(hd, 1, 10000000, stdin);
	N = gi();
	for(n = 1;n < N;n <<= 1);
	lowBit[0] = n;
	for(int i = 1;i < n;++ i){
		lowBit[i] = i & -i;
		highBit[i] = lowBit[i] == i ? i : highBit[i - 1];
	}
	highBit[0] = 1;
	for(int i = 0, idx;i < n; ++i){
		idx = (i << 1) + 1;
		if(i < N)
			data[idx].l = data[idx].r = data[idx].s = data[idx].m = gi();
		else
			data[idx].m = -inf;
	}
	for(int len = 2;len <= n;len <<= 1)
		for(int i = 0;i < n;i += len){
			Data &L = data[(i << 1) + (len >> 1)];
			Data &R = data[(i << 1) + (len >> 1) + len];
			Data &idx = data[(i << 1) + len];
			idx.l = max(L.l, L.s + R.l);
			idx.r = max(R.r, R.s + L.r);
			idx.s = L.s + R.s;
			idx.m = max(L.r + R.l, max(L.m, R.m));
		}
	M = gi();
	while(M --){
		l = gi() - 1;
		r = gi();
		Data ans;
		ans.l = ans.r = ans.s = 0;
		ans.m = -inf;
		while(l < r){
			Data &idx = data[(l << 1) + min(lowBit[l], highBit[r - l])];
			ans.m = max(ans.r + idx.l, max(ans.m, idx.m));
			ans.l = max(ans.l, ans.s + idx.l);
			ans.r = max(idx.r, idx.s + ans.r);
			ans.s += idx.s;
			l += min(lowBit[l], highBit[r - l]);
		}
		writeInt(ans.m);
		*tl++ = '\n';
	}
	fwrite(bufferOut, 1, tl - bufferOut, stdout);
	return 0;
}


