/*
PROG : runround
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class runround {
	Scanner input = new Scanner(System.in);

	int N;

	boolean check(long x) {
		String s = Long.toString(x);
		boolean exist[] = new boolean[10];
		for(int i = 0; i < s.length(); ++i) {
			if(s.charAt(i) == '0' || exist[(int) (s.charAt(i) - '0')]) {
				return false;
			}
			exist[(int) (s.charAt(i) - '0')] = true;
		}
		boolean hsh[] = new boolean[s.length()];
		int loop = 0, i;
		for(i = 0; !hsh[i]; i = (i + (int) (s.charAt(i) - '0')) % s.length()) {
			//System.out.println(i);
			hsh[i] = true;
			++loop;
		}
		return loop == s.length() && i == 0;
	}

	void run() {
		N = input.nextInt();
		for(long i = N + 1; ; ++i) {
			if(check(i)) {
				System.out.println(i);
				break;
			}
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("runround.in"));
			System.setOut(new PrintStream("runround.out"));
		}
		catch (Throwable T_T){
		}
		new runround().run();
	}
}

