#include <cstdio>
#include <cstdlib>
#include <cstring>

char prog[30010], inBuffer[30010], mm[30010], *hd, *cur, *is;
int T;//, caseCnt;

void init(){
	memset(prog, 0, sizeof prog);
	memset(inBuffer, 0, sizeof inBuffer);
	memset(mm, 0, sizeof mm);
	hd = prog;
	cur = mm;
	char *tmp = prog;
	while((*tmp = getchar()) != '$'){
		bool flag = false;
		for(const char *i = "+-><.,[]";*i && !flag; ++i)
			if(*i == *tmp)
				flag = true;
		if(flag)
			++tmp;
	}
	*tmp = 0;
	tmp = inBuffer;
	while((*tmp = getchar()) != '$')
		++tmp;
	is = inBuffer + 1;
//	puts(prog)
//	puts(is);
}

char *exe(char *bf){
	if(*bf != '['){
		if(*bf == '>')
			++cur;
		if(*bf == '<')
			--cur;
		if(*bf == '+')
			++(*cur);
		if(*bf == '-')
			--(*cur);
		if(*bf == ','){
			if(is[0] == ' ' && is[1] == '$')
				*cur = -1;
			else
				*cur = *is++;
		}
		if(*bf == '.')
			putchar(*cur);
		return bf + 1;
	}else{
		int cnt = 1;
		char *end = bf;
		while(cnt){
			++end;
			cnt += *end == '[';
			cnt -= *end == ']';
		}
		while(*cur){
			char *tmp = bf + 1;
			while(tmp < end)
				tmp = exe(tmp);
		}
		return end + 1;
	}
}

int main(){
	scanf("%d", &T);
	while(T --){
		init();
		printf("Case %d: ", ++ caseCnt);
		while(*hd){
			hd = exe(hd);
//			printf("%d\n", hd - prog);
		}
		puts("");
	}
	return 0;
}
