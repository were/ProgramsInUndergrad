#include <cstdio>
#include <cstring>

char s[10010];
int pos = -1;

int main(){
	scanf("%s", s);
	for(int i = 0, a = 0; s[i]; ++i) {
		if(a && s[i] == '(')
			pos = i;
		a += s[i] == '(';
		a -= s[i] == ')';
	}
	if(~pos){
		for(int i = 0, cnt = (int)strlen(s) / 2; s[i]; ++i) {
			if(i < pos) {
				cnt -= s[i] == '(';
			}
			if(i == pos) {
				s[i] = ')';
			}
			if(i > pos) {
				if(cnt) {
					s[i] = '(';
					--cnt;
				}
				else {
					s[i] = ')';
				}
			}
		}
	}
	else {
		puts("No solution");
	}
	puts(s);
	return 0;
}
