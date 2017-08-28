/*
ID : weng_xo2
LANG : JAVA
PROG : clocks
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class clocks {
	Scanner input = new Scanner(System.in);

	final String b[] = {
		"ABDE",
		"ABC",
		"BCEF",
		"ADG",
		"BDEFH",
		"CFI",
		"DEGH",
		"GHI",
		"EFHI"
	};

	int a[] = new int[9];

	ArrayList<Integer> ans = new ArrayList<Integer>();

	void operate(int x, int delta) {
		for(int i = 0; i < b[x].length(); ++i) {
			int idx = (int) (b[x].charAt(i) - 'A');
			a[idx] = (a[idx] + delta + 4) % 4;
		}
	}
	
	boolean allZero() {
		for(int i = 0; i < 9; ++i) {
			if(a[i] != 0) {
				return false;
			}
		}
		return true;
	}
	
	void dfs(int x, int cnt) {
		if(allZero()) {
			for(int i = 0; i < ans.size(); ++i) {
				if(i == ans.size() - 1) {
					System.out.println(ans.get(i));
				} else {
					System.out.print(ans.get(i) + " ");
				}
			}
			System.exit(0);
		}
		if(x < 9) {
			if(cnt < 3) {
				operate(x, 1);
				ans.add(x + 1);
				dfs(x, cnt + 1);
				ans.remove(ans.size() - 1);
				operate(x, -1);
			}
			dfs(x + 1, 0);
		}
	}

	void run() {
		for(int i = 0; i < 9; ++i) {
			a[i] = (input.nextInt() / 3) % 4;
		}
		dfs(0, 0);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("clocks.in"));
			System.setOut(new PrintStream("clocks.out"));
		} catch (Throwable T_T) {
		}
		new clocks().run();
	}
}

