/*
PROG : heritage
ID : weng_xo2
LANG : C++11
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
char in[27], pre[27], *hd = pre, root, l[27], r[27];
char work(int f, int t){
	int x;
	for(x = f;x <= t; ++x)
		if(in[x] == *hd)
			break;
	if(f < x){
		++hd;
		l[in[x] - 'A'] = work(f, x - 1);
	}
	if(x < t){
		++hd;
		r[in[x] - 'A'] = work(x + 1, t);
	}
	return in[x];
}
void show(char cur){
	if(cur){
		show(l[cur - 'A']);
		show(r[cur - 'A']);
		putchar(cur);
	}
}
int main(){
	fscanf(fopen("heritage.in", "r"), "%s%s", in, pre);
	root = work(0, strlen(in) - 1);
	freopen("heritage.out", "w", stdout);
	show(root);
	puts("");
	return 0;
}
