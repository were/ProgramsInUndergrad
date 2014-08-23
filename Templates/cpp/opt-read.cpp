/*opt-read-template*/
#include <cctype>
#include <cstdio>
int gi(){
	char ch;
	while(!isdigit(ch = getchar()) && ch != '-');
	if(ch == '-')
		return -gi();
	int ret = ch - '0';
	while(isdigit(ch = getchar()))
		ret = ret * 10 + ch - '0';
	return ret;
}
/*opt-read-template-end*/
