/*
PROG : barn1
ID : weng_xo2
LANG : JAVA
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class barn1 {
	Scanner input = new Scanner(System.in);

	int M, N, n, a[], b[], ans;

	void run() {
		M = input.nextInt();
		N = input.nextInt();
		n = input.nextInt();
		a = new int[n];
		for(int i = 0; i < n; ++i) {
			a[i] = input.nextInt();
		}
		Arrays.sort(a);
		ans = a[n - 1] - a[0] + 1;
		b = new int[n - 1];
		for(int i = 1; i < n; ++i) {
			b[i - 1] = a[i] - a[i - 1] - 1;
			//System.out.println(b[i - 1]);
		}
		Arrays.sort(b);
		for(int i = b.length - 1, j = 1; i >= 0 && j < M; --i, ++j) {
			ans -= b[i];
			//System.out.println(b[i]);
		}
		System.out.println(ans);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("barn1.in"));
			System.setOut(new PrintStream("barn1.out"));
		}
		catch (Throwable T_T){
		}
		new barn1().run();
	}
}

