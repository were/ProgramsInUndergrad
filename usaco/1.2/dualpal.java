/*
PROG : dualpal
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class dualpal {
	Scanner input = new Scanner(System.in);
	int N, S;
	ArrayList<Integer> ans = new ArrayList<Integer>();
	
	int[] trans(int x, int base) {
		ArrayList<Integer> tmp = new ArrayList<Integer>();
		while(x != 0) {
			tmp.add(x % base);
			x /= base;
		}
		int ret[] = new int[tmp.size()];
		for(int i = 0; i < tmp.size(); ++i) {
			ret[i] = tmp.get(tmp.size() - i - 1);
		}
		return ret;
	}
	
	boolean isPal(int a[]) {
		for(int l = 0, r = a.length - 1; l <= r; ++l, --r) {
			if(a[l] != a[r]) {
				return false;
			}
		}
		return true;
	}
	
	boolean isDual(int x) {
		int cnt = 0;
		for(int i = 2; i <= 10; ++i) {
			if(isPal(trans(x, i))) {
				++cnt;
			}
		}
		return cnt > 1;
	}

	void run() {
		N = input.nextInt();
		S = input.nextInt();
		for(int i = S + 1; ans.size() < N; ++i) {
			if(isDual(i)) {
				ans.add(i);
			}
		}
		for(Iterator<Integer> cur = ans.iterator(); cur.hasNext(); ) {
			System.out.println(cur.next());
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("dualpal.in"));
			System.setOut(new PrintStream("dualpal.out"));
		}
		catch (Throwable element) {
			return;
		}
		new dualpal().run();
	}
}


