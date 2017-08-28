/*
ID : weng_xo2
LANG : JAVA
PROG : frac1
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class frac1 {
	Scanner input = new Scanner(System.in);

	ArrayList<Data> ans = new ArrayList<Data>();
	int N;

	int gcd(int a, int b) {
		return b != 0 ? gcd(b, a % b) : a;
	}

	void run() {
		N = input.nextInt();
		ans.add(new Data(0, 1));
		ans.add(new Data(1, 1));
		for(int i = 1; i <= N; ++i) {
			for(int j = i + 1; j <= N; ++j) {
				if(gcd(i, j) == 1) {
					ans.add(new Data(i, j));
				}
			}
		}
		Collections.sort(ans);
		for(int i = 0; i < ans.size(); ++i) {
			System.out.println(ans.get(i).x + "/" + ans.get(i).y);
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("frac1.in"));
			System.setOut(new PrintStream("frac1.out"));
		}
		catch (Throwable T_T) {
		}
		new frac1().run();
	}
}

class Data implements Comparable{
	int x, y;
	Data(int x, int y) {
		this.x = x;
		this.y = y;
	}
	public int compareTo(Object o) {
		Data O = (Data) o;
		return this.x * O.y - this.y * O.x;
	}
}
