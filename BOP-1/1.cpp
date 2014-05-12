#include <cctype>
#include <cstdio>
#include <cstring>

int T, cs;
char a[100], b[100], c[100];

double getNum(char const *s){
	double ret = 0.;
	while(isdigit(*s)) {
		ret = ret * 10. + *s - '0';
		++s;
	}
	if(*s == '.') {
		double p = .1;
		++s;
		while(isdigit(*s)){
			ret += (*s - '0') * p;
			p /= 10.;
			++s;
		}
	}
	if(!strcmp(s, "dm"))
		ret /= 10.;
	if(!strcmp(s, "cm"))
		ret /= 100.;
	if(!strcmp(s, "mm"))
		ret /= 1000.;
	if(!strcmp(s, "um"))
		ret /= 1e6;
	if(!strcmp(s, "nm"))
		ret /= 1e9;
	return ret;
}

int main() {
	scanf("%d", &T);
	while(T--){
		scanf("%s%s%s", a, b, c);
		printf("Case %d: %.2fpx\n", ++cs, getNum(c) * getNum(a) / getNum(b));
	}
	return 0;
}
