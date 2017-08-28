/*
PROG : calfflac
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class calfflac {
	Scanner input = new Scanner(System.in);

	String s, lower;
	int ans, ansL, ansR;
	ArrayList<Data> pos = new ArrayList<Data>();

	void work(int l, int r, int len) {
		while(l >= 0 && r < pos.size() && pos.get(l).ch == pos.get(r).ch) {
			len += 2;
			--l;
			++r;
		}
		if(++l <= --r && len > ans) {
			ans = len;
			ansL = l;
			ansR = r;
		}
	}

	void run() {
		s = "";
		for(;;) {
			try {
				s += input.nextLine() + '\n';
			}
			catch(Throwable T_T) {
				break;
			}
		}
		//System.err.print(s);
		lower = s.toLowerCase();
		for(int i = 0; i < lower.length(); ++i) {
			char ch = lower.charAt(i);
			if(ch >= 'a' && ch <= 'z') {
				pos.add(new Data(ch, i));
				//System.err.print(ch);
			}
		}
		for(int i = 0; i < pos.size(); ++i) {
			work(i - 1, i + 1, 1);
			work(i, i + 1, 0);
			//System.err.println(ansL + " " + ansR);
		}
		System.out.println(ans);
		for(int i = pos.get(ansL).idx; i <= pos.get(ansR).idx; ++i) {
			System.out.print(s.charAt(i));
		}
		System.out.println();
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("calfflac.in"));
			System.setOut(new PrintStream("calfflac.out"));
		}
		catch (Throwable T_T){
		}
		new calfflac().run();
	}
}

class Data{
	char ch;
	int idx;
	Data(char ch, int idx) {
		this.ch = ch;
		this.idx = idx;
	}
}

