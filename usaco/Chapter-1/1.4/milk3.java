/*
PROG : milk3
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class milk3 {
	Scanner input = new Scanner(System.in);
	Data q[] = new Data[10000];
	boolean hsh[][][] = new boolean[21][21][21];
	int f = 0, t = 0;
	int cap[] = new int[3];
	
	void push(int a, int b, int c) {
		if(!hsh[a][b][c]) {
			q[t++] = new Data(a, b, c);
			hsh[a][b][c] = true;
		}
	}

	void dump(Data a, int from, int to) {
		while(a.a[from] != 0 && a.a[to] < cap[to]) {
			--a.a[from];
			++a.a[to];
		}
	}

	void run() {
		for(int i = 0; i < 3; ++i) {
			cap[i] = input.nextInt();
		}
		for(push(0, 0, cap[2]); f < t; ++f) {
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) if(j != i) {
					Data tmp = new Data(q[f]);
					dump(tmp, i, j);
					push(tmp.a[0], tmp.a[1], tmp.a[2]);
				}
			}
		}
		boolean vergin = true;
		for(int i = 0; i <= cap[2]; ++i) {
			if(hsh[0][cap[2] - i][i]) {
				if(vergin) {
					vergin = false;
					System.out.print(i);
				} else {
					System.out.print(" " + i);
				}
			}
		}
		System.out.println();
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("milk3.in"));
			System.setOut(new PrintStream("milk3.out"));
		} catch(Throwable T_T) {
		}
		new milk3().run();
	}
}

class Data {
	int a[] = new int[3];
	Data(int a, int b, int c) {
		this.a[0] = a;
		this.a[1] = b;
		this.a[2] = c;
	}
	Data(Data o) {
		for(int i = 0; i < 3; ++i) {
			this.a[i] = o.a[i];
		}
	}
}
