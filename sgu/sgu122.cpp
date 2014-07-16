#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
const int MaxN = 1001;
int N, S, T, curN, a[MaxN], b[MaxN], nxt[MaxN];
bool g[MaxN][MaxN], hsh[MaxN];
char buffer[MaxN*MaxN], *hd;
int getNxt(int x){
	for(int i = 1;i <= N;++i)
		if(g[x][i] && !hsh[i])
			return i;
	return 0;
}
bool gi(int&x){
	while(*hd && !isdigit(*hd)) ++ hd;
	if(*hd){
		x = *hd ++ - '0';
		while(*hd && isdigit(*hd))
			x = x * 10 + *hd++ - '0';
		return true;
	}
	return false;
}
int main(){
	scanf("%d", &N);
	gets(buffer);
	for(int i = 1;i <= N;++i){
		gets(buffer);
		hd = buffer;
		int x = 0;
		while(gi(x))
			g[x][i] = g[i][x] = true;
	}
	nxt[S = 1] = T = getNxt(1);
	nxt[T] = S;
	hsh[S] = hsh[T] = true;
	curN = 2;
	while(curN != N){
		int tmp;
		while((tmp = getNxt(S)) != 0){
			nxt[tmp] = S;
			hsh[S = tmp] = true;
			++curN;
		}
		while((tmp = getNxt(T)) != 0){
			nxt[T] = tmp;
			hsh[T = tmp] = true;
			++curN;
		}
		if(!g[S][T]){
			for(int i = 0, x = S;i < curN;++i, x = nxt[x])
				if(g[S][nxt[x]] && g[x][T]){
					int pos = -1, sizeB = 0;
					for(int j = 0, y = S;j < curN;++j, y = nxt[y]){
						if(y == nxt[x])
							pos = j;
						a[j] = y;
					}
					for(int j = pos;j < curN;++j)
						b[sizeB++] = a[j];
					for(int j = pos - 1;j >= 0;--j)
						b[sizeB++] = a[j];
					for(int j = 0;j < curN;++j)
						nxt[b[j]] = b[(j + 1) % curN];
					break;
				}
		}
		for(int i = 0, x = S;i < curN;++i, x = nxt[x])
			if((tmp = getNxt(x)) != 0){
				int pos = -1, sizeB = 0;
				for(int j = 0, y = S;j < curN;++j, y = nxt[y]){
					a[j] = y;
					if(y == nxt[x])
						pos = j;
				}
				for(int j = pos;j < curN;++j)
					b[sizeB++] = a[j];
				for(int j = 0;j < pos;++j)
					b[sizeB++] = a[j];
				for(int j = 0;j < curN;++j)
					nxt[b[j]] = b[(j + 1) % curN];
				S = nxt[x];
				T = x;
				break;
			}
	}
	int pos = -1;
	for(int i = 0, x = S;i < N;++i, x = nxt[x]){
		if(x == 1)
			pos = i;
		a[i] = x;
	}
	for(int i = pos;i < N;++i)
		std :: cout  << a[i] << " ";
	for(int i = 0;i < pos;++i)
		std :: cout  << a[i] << " ";
	std :: cout << "1\n";
	return 0;
}
