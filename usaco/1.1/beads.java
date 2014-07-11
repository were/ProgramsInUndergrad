/*
PROG : beads
LANG : JAVA
ID : weng_xo2
*/
import java.util.*;
import java.io.*;

public class beads {
	Scanner input = new Scanner(System.in);
	int N, ans;
	String s;
	void run() {
		N = input.nextInt();
		s = input.next();
		s = s + s;
		ans = 0;
		for(int i = 0; i < N; ++i) {
			int l = i, r = i + N - 1, tmp = 0;
			while(l <= r && s.charAt(l) == 'w') {
				++l;
				++tmp;
			}
			int _l = l;
			while(r >= l && s.charAt(r) == 'w') {
				--r;
				++tmp;
			}
			int _r = r;
			//System.out.println(l + " " + r + ": " + tmp);
			while(l <= r && (s.charAt(l) == s.charAt(_l) || s.charAt(l) == 'w')) {
				++l;
				++tmp;
			}
			while(r >= l && (s.charAt(r) == s.charAt(_r) || s.charAt(r) == 'w')) {
				--r;
				++tmp;
			}
			if(tmp > ans) {
				ans = tmp;
			}
			//System.out.printf("%c%c\n", s.charAt(l), s.charAt(r));
			//System.out.println(i + " " + tmp);
		}
		System.out.println(ans);
	}
	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("beads.in"));
			System.setOut(new PrintStream("beads.out"));
		}
		catch(Throwable T_T) {
			System.err.println("Cao Cao Cao!");
		}
		new beads().run();
	}
}
