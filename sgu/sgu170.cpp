//
//  main.cpp
//  sgu170
//
//  Created by were on 2014/03/30.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

const int MaxN = 5000;

char s1[MaxN], s2[MaxN];
std :: queue<int> a, b;

int main(int argc, const char * argv[])
{
	scanf("%s%s", s1, s2);
	if(strlen(s1) != strlen(s2)){
		puts("-1");
	}else{
		for(int i = 0;s1[i];++i){
			if(s1[i] == '+')
				a.push(i);
			if(s2[i] == '+')
				b.push(i);
		}
		if(a.size() != b.size()){
			//puts("diff size");
			puts("-1");
		}else{
			int ans = 0;
			while(!a.empty()){
				ans += abs(a.front() - b.front());
				a.pop();
				b.pop();
			}
			printf("%d\n", ans);
		}
	}
    return 0;
}

