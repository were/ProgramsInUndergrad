//
//  main.cpp
//  sgu184
//
//  Created by were on 2014/03/29.
//  Copyright (c) 2014年 were. All rights reserved.
//

#include <algorithm>
#include <iostream>

using std :: cin;
using std :: endl;
using std :: cout;
using std :: min;

int main(int argc, const char * argv[])
{
    // insert code here...
    int P, M, C, K, R, V;
    cin >> P >> M >> C >> K >> R >> V;
    cout << min(P / K, min(M / R, C / V)) << endl;
    return 0;
}

