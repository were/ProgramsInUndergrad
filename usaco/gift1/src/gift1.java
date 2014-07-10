/*
LANG : JAVA
PROG : gift1
ID : weng_xo2
*/
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
import java.util.TreeMap;

public class gift1 {
	Scanner input = new Scanner(System.in);

	int N;
	String s[];
	TreeMap<String, Integer> money = new TreeMap<String, Integer>();

	void add(String key, int delta) {
		Integer value = money.get(key);
		money.put(key, value + delta);
	}

	void run() {
		N = input.nextInt();
		s = new String[N];
		for (int i = 0; i < N; ++i) {
			s[i] = input.next();
			money.put(s[i], 0);
		}
		for (int i = 0; i < N; ++i) {
			String from = input.next();
			int total = input.nextInt();
			int M = input.nextInt();
			if (M != 0) {
				//add(from, total % M);
				for (int j = 0; j < M; ++j) {
					add(input.next(), total / M);
					add(from, -(total / M));
				}
			} else {
				add(from, total);
			}
		}
		for (int i = 0; i < N; ++i) {
			System.out.println(s[i] + " " + money.get(s[i]));
		}
	}

	public static void main(String args[]) throws FileNotFoundException {
		System.setIn(new FileInputStream("gift1.in"));
		System.setOut(new PrintStream("gift1.out"));
		new gift1().run();
	}
}
