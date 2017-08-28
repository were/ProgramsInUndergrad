/*
LANG : JAVA
ID : weng_xo2
PROG : preface
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class preface {
	Scanner input = new Scanner(System.in);

	final String one[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
	final String ten[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
	final String hun[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
	final String tho[] = {"", "M", "MM", "MMM"};
	final String ch = "IVXLCDM";

	int N, cnt[] = new int[256];
	
	void run() {
		N = input.nextInt();
		for(int i = 1; i <= N; ++i) {
			int a = i / 1000;
			int b = i / 100 % 10;
			int c = i / 10 % 10;
			int d = i % 10;
			String tmp = tho[a] + hun[b] + ten[c] + one[d];
			for(int j = 0; j < tmp.length(); ++j) {
				++cnt[tmp.charAt(j)];
			}
		}
		for(int i = 0; i < ch.length(); ++i) {
			if(cnt[ch.charAt(i)] != 0) {
				System.out.println(ch.charAt(i) + " " + cnt[ch.charAt(i)]);
			}
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("preface.in"));
			System.setOut(new PrintStream("preface.out"));
		}
		catch (Throwable T_T) {
		}
		new preface().run();
	}
}

