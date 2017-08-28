/*
ID : weng_xo2
LANG : JAVA
PROG : ride
*/
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;


public class ride {
	Scanner input = new Scanner(System.in);
	String s1, s2;
	
	int calc(String s) {
		int ret = 1;
		for(int i = 0; i < s.length(); ++i) {
			ret *= (int) (s.charAt(i) - 'A') + 1;
			ret %= 47;
		}
		return ret;
	}
	
	String calc(String s1, String s2) {
		return calc(s1) == calc(s2) ? "GO" : "STAY";
	}
	
	void run() {
		s1 = input.next();
		s2 = input.next();
		System.out.println(calc(s1, s2));
	}
	
	public static void main(String args[]) throws FileNotFoundException {
		System.setIn(new FileInputStream("ride.in"));
		System.setOut(new PrintStream("ride.out"));
		new ride().run();
	}
}
