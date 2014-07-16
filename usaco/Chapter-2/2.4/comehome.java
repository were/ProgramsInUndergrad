/*
PROG : comehome
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class comehome {
	Scanner input = new Scanner(System.in);

	int N, g[][] = new int[256][256], dis[] = new int[256], ans = Integer.MAX_VALUE;
	int f, t, q[] = new int[300];
	boolean hsh[] = new boolean[256];
	char ansCh;

	void run() {
		N = input.nextInt();
		for(int i = 0; i < 256; ++i) {
			for(int j = 0; j < 256; ++j) {
				g[i][j] = -1;
			}
		}
		for(int i = 0; i < N; ++i) {
			String s1 = input.next();
			String s2 = input.next();
			char ch1 = s1.charAt(0);
			char ch2 = s2.charAt(0);
			if(g[ch1][ch2] == -1) {
				g[ch1][ch2] = g[ch2][ch1] = input.nextInt();
			} else {
				g[ch1][ch2] = min(g[ch1][ch2], input.nextInt());
				g[ch2][ch1] = g[ch1][ch2];
			}
			//System.out.println(ch1 + " " + ch2 + " " + g[ch1][ch2]);
		}
		for(int s = 'A'; s < 'Z'; ++s) {
			for(int i = 0; i < 256; ++i) {
				dis[i] = Integer.MAX_VALUE;
			}
			f = t = 0;
			for(q[t++] = s, dis[s] = 0, hsh[s] = true; f != t; f = (f + 1) % 256) {
				//System.out.println(q[f]);
				for(int i = 0; i < 256; ++i) {
					//if(g[q[f]][i] != -1) {
					//	System.out.println(q[f] + "->" + i + ": " + dis[q[f]] + " + " + g[q[f]][i] + " ? " + dis[i]);
					//}
					if(g[q[f]][i] != -1 && dis[q[f]] + g[q[f]][i] < dis[i]) {
						dis[i] = dis[q[f]] + g[q[f]][i];
						if(!hsh[i]) {
							hsh[i] = true;
							q[t] = i;
							t = (t + 1) % 256;
						}
					}
				}
				hsh[q[f]] = false;
			}
			//System.out.println("res: " + dis['Z']);
			//System.out.println("end" + (int) 'Z');
			if(dis['Z'] < ans) {
				ans = dis['Z'];
				ansCh = (char) s;
			}
		}
		System.out.println(ansCh + " " + ans);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("comehome.in"));
			System.setOut(new PrintStream("comehome.out"));
		}
		catch (Throwable T_T) {
		}
		new comehome().run();
	}
}

class IntReader {

	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;
	private SpaceCharFilter filter;

	public IntReader(InputStream stream) {
		this.stream = stream;
	}

	public int read() {
		if (numChars == -1)
			throw new InputMismatchException();
		if (curChar >= numChars) {
			curChar = 0;
			try {
				numChars = stream.read(buf);
			} catch (IOException e) {
				throw new InputMismatchException();
			}
			if (numChars <= 0)
				return -1;
		}
		return buf[curChar++];
	}

	public int nextInt() {
		int c = read();
		while (isSpaceChar(c))
			c = read();
		int sgn = 1;
		if (c == '-') {
			sgn = -1;
			c = read();
		}
		int res = 0;
		do {
			if (c < '0' || c > '9')
				throw new InputMismatchException();
			res *= 10;
			res += c - '0';
			c = read();
		} while (!isSpaceChar(c));
		return res * sgn;
	}

	public boolean isSpaceChar(int c) {
		if (filter != null)
			return filter.isSpaceChar(c);
		return isWhitespace(c);
	}

	public static boolean isWhitespace(int c) {
		return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
	}

	public interface SpaceCharFilter {
		public boolean isSpaceChar(int ch);
	}
}

