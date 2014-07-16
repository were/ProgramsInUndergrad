/*
PROG : milk
LANG : JAVA
ID : weng_xo2
*/

import java.util.Arrays;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.PrintStream;


public class milk {
	Scanner input = new Scanner(System.in);
	
	int N, M, ans;
	Data data[];
	
	void run() {
		N = input.nextInt();
		M = input.nextInt();
		data = new Data[M];
		for(int i = 0; i < M; ++i) {
			int p = input.nextInt();
			int a = input.nextInt();
			data[i] = new Data(p, a);
		}
		Arrays.sort(data);
		for(int i = 0; N != 0; ++i) {
			ans += Math.min(N, data[i].a) * data[i].p;
			N -= Math.min(N, data[i].a);
		}
		System.out.println(ans);
	}
	
	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("milk.in"));
			System.setOut(new PrintStream("milk.out"));
		}
		catch (Throwable element) {
		}
		new milk().run();
	}
}

class Data implements Comparable {
	int p, a;

	Data(int p, int a) {
		this.p = p;
		this.a = a;
	}
	
	public int compareTo(Object o) {
		return this.p - ((Data)o).p;
	}
}

