/*
LANG : JAVA
ID : weng_xo2
PROG : subset
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class subset {
	Scanner input = new Scanner(System.in);

	int N;
	long ans[];

	void run() {
		N = input.nextInt();
		if((1 + N) * N / 2 % 2 != 0) {
			System.out.println(0);
			System.exit(0);
		}
		ans = new long[(1 + N) * N / 4 + 1];
		ans[0] = 1;
		for(int i = 1; i <= N; ++i) {
			for(int j = (1 + N) * N / 4; j >= i; --j) {
				ans[j] += ans[j - i];
			}
			//for(int j = 1; j <= (1 + N) * N / 4; ++j) {
			//	if(ans[j] != 0) {
			//		System.out.println(j + " " + ans[j]);
			//	}
			//}
		}
		System.out.println(ans[(1 + N) * N / 4] / 2);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("subset.in"));
			System.setOut(new PrintStream("subset.out"));
		}
		catch (Throwable T_T) {
		}
		new subset().run();
	}
}

