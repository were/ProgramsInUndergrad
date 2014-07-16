/*
PROG : money
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class money {
	Scanner input = new Scanner(System.in);

	int N, M, a[];
	long ans[];

	void run() {
		N = input.nextInt();
		M = input.nextInt();
		a = new int[N];
		for(int i = 0; i < N; ++i) {
			a[i] = input.nextInt();
		}
		ans = new long[M + 1];
		ans[0] = 1;
		for(int i = 0; i < N; ++i) {
			for(int j = a[i]; j <= M; ++j) {
				ans[j] += ans[j - a[i]];
			}
		}
		System.out.println(ans[M]);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("money.in"));
			System.setOut(new PrintStream("money.out"));
		}
		catch (Throwable T_T) {
		}
		new money().run();
	}
}

