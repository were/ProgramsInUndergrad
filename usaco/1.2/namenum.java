/*
ID : weng_xo2
LANG : JAVA
PROG : namenum
*/
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.PrintStream;
import java.util.Scanner;

public class namenum {
	Scanner input = new Scanner(System.in);

	BufferedReader dict;
	
	final char[][] num = { {}, {}, { 'A', 'B', 'C' }, { 'D', 'E', 'F' },
			{ 'G', 'H', 'I' }, { 'J', 'K', 'L' }, { 'M', 'N', 'O' },
			{ 'P', 'R', 'S' }, { 'T', 'U', 'V' }, { 'W', 'X', 'Y' } };

	String type;
	int cnt = 0;

	String getNum(String s) {
		String ret = "";
		for(int i = 0; i < s.length(); ++i) {
			for (int j = 2; j <= 9; ++j) {
				for (int k = 0; k < num[j].length; ++k) {
					if (s.charAt(i) == num[j][k]) {
						ret += (char) ('0' + j);
					}
				}
			}
		}
		//System.out.println(s + " " + ret);
		return ret;
	}

	void run() throws FileNotFoundException {
		type = input.next();
		try {
			dict = new BufferedReader(new FileReader("dict.txt"));
		} catch (Throwable element) {
			System.err.println("FileNotFound!");
			return;
		}
		for (;;) {
			String s;
			try {
				s = dict.readLine();
			} catch (IOException element) {
				break;
			}
			if(s == null) {
				break;
			}
			if (s.length() == type.length() && getNum(s).compareTo(type) == 0) {
				++cnt;
				System.out.println(s);
			}
		}
		if(cnt == 0) {
			System.out.println("NONE");
		}
	}

	public static void main(String args[]) throws FileNotFoundException {
		System.setIn(new FileInputStream("namenum.in"));
		System.setOut(new PrintStream("namenum.out"));
		new namenum().run();
	}
}


