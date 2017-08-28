/*
PROG : concom
LANG : JAVA
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class concom {
	IntReader input = new IntReader(System.in);

	int N, g[][] = new int[101][101], dis[] = new int[101];
	boolean hsh[] = new boolean[101];

	void run() {
		N = input.nextInt();
		for(int i = 1; i <= N; ++i) {
			int x = input.nextInt();
			int y = input.nextInt();
			g[x][y] = input.nextInt();
		}
		for(int i = 1; i <= 100; ++i) {
			for(int j = 1; j <= 100; ++j) {
				dis[j] = 0;
				hsh[j] = false;
			}
			dis[i] = 100;
			for(int j = 1; j <= 100; ++j) {
				int done;
				for(done = 1; done <= 100; ++done) {
					if(!hsh[done] && dis[done] > 50) {
						break;
					}
				}
				if(done == 101) {
					break;
				}
				hsh[done] = true;
				for(int k = 1; k <= 100; ++k) {
					dis[k] += g[done][k];
				}
			}
			for(int j = 1; j <= 100; ++j) {
				if(i != j && dis[j] > 50) {
					System.out.println(i + " " + j);
				}
			}
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("concom.in"));
			System.setOut(new PrintStream("concom.out"));
		}
		catch (Throwable T_T) {
		}
		new concom().run();
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

