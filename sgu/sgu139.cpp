#include <cstdio>
#define calc(x,y) (4 * (x) + (y))
int a[16], cnt;
int main(){
	for(int i = 0;i < 4;++ i)
		for(int j = 0;j < 4;++ j)
			scanf("%d", a + (i % 2 == 0 ? calc(i, j) : calc(i, 3 - j)));
	for(int i = 0;i < 16;++ i)
		if(a[i])
			for(int j = 0;j < i;++ j)
				if(a[i] < a[j])
					++ cnt;
	puts(cnt % 2 == 1 ? "YES" : "NO");
	return 0;
}
