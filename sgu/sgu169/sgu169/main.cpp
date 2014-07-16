//  main.cpp
//  sgu169
//
//  Created by were on 2014/03/30.
//  Copyright (c) 2014年 were. All rights reserved.

#include <iostream>

int main(int argc, const char * argv[])
{
	int K;
	std :: cin >> K;
	if(K == 1){
		std :: cout << "8\n";
	}else{
		--K;
		int ans = 1 + (K % 3 == 0) * 2 + (K % 6 == 0);
		std :: cout << ans << "\n";
	}
    return 0;
}

