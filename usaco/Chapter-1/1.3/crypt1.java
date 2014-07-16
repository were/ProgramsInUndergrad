/*
PROG : crypt1
LANG : JAVA
ID : weng_xo2
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class crypt1 {
	Scanner input = new Scanner(System.in);
	int N, a[], ans = 0;

	boolean inRange(int x, int l, int r) {
		for(int tmp = x; tmp != 0; tmp /= 10) {
			boolean flag = false;
			for(int i = 0; i < N; ++i) {
				if(a[i] == tmp % 10) {
					flag = true;
					break;
				}
			}
			if(!flag) {
				return false;
			}
		}
		return l <= x && x <= r;
	}

	void run() {
		N = input.nextInt();
		a = new int[N];
		for(int i = 0; i < N; ++i) {
			a[i] = input.nextInt();
		}
		for(int x: a) for(int y: a) for(int z: a) for(int p: a) for(int q: a) {
			int num1 = x * 100 + y * 10 + z;
			int num2 = p * 10 + q;
			if(inRange(p * num1, 100, 1000) && inRange(q * num1, 100, 1000) && inRange(num1 * num2, 1000, 10000)) {
				//System.out.println(num1 + " " + num2 + " " + num1 * num2);
				++ans;
			}
		}
		System.out.println(ans);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("crypt1.in"));
			System.setOut(new PrintStream("crypt1.out"));
		}
		catch (Throwable T_T){
		}
		new crypt1().run();
	}
}

