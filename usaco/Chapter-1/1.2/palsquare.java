/*
ID : weng_xo2
LANG : JAVA
PROG : palsquare
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class palsquare {
	Scanner input = new Scanner(System.in);
	int N;
	String num = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int[] trans(int x) {
		ArrayList<Integer> tmp = new ArrayList<Integer>();
		while(x != 0) {
			tmp.add(x % N);
			x /= N;
		}
		int ret[] = new int[tmp.size()];
		for(int i = 0; i < tmp.size(); ++i) {
			ret[tmp.size() - 1 - i] = tmp.get(i);
		}
		return ret;
	}

	boolean isPal(int x) {
		int res[] = trans(x * x);
		for(int l = 0, r = res.length - 1; l <= r; ++l, --r) {
			if(res[l] != res[r]) {
				return false;
			}
		}
		return true;
	}

	void print(int x) {
		int a[] = trans(x), b[] = trans(x * x);
		for(int i = 0; i < a.length; ++i) {
			System.out.print(num.charAt(a[i]));
		}
		System.out.print(' ');
		for(int i = 0; i < b.length; ++i) {
			System.out.print(num.charAt(b[i]));
		}
		System.out.println();
	}

	void run() {
		N = input.nextInt();
		for(int i = 1; i <= 300; ++i) {
			if(isPal(i)) {
				print(i);
			}
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("palsquare.in"));
			System.setOut(new PrintStream("palsquare.out"));
		}
		catch (Throwable element) {
			System.err.println("T_T");
		}
		new palsquare().run();
	}
}

