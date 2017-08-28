/*
PROG : vans
ID : weng_xo2
LANG : JAVA
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class vans {
	IntReader input = new IntReader(System.in);
	
	BigInteger f[], g[];
	
	void run() {
		int N = input.nextInt();
		f = new BigInteger[max(N + 1, 5)];
		f[1] = BigInteger.ZERO;
		f[2] = BigInteger.valueOf(2);
		f[3] = BigInteger.valueOf(4);
		g = new BigInteger[max(N + 1, 5)];
		g[1] = BigInteger.valueOf(2);
		g[2] = BigInteger.valueOf(2);
		g[3] = BigInteger.valueOf(8);
		for(int i = 4; i <= N; ++i) {
			g[i] = f[i - 1].multiply(BigInteger.valueOf(2)).add(g[i - 1]).add(g[i - 2]).subtract(g[i - 3]);
			f[i] = f[i - 1].add(g[i - 1]);
		}
		System.out.println(f[N]);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("vans.in"));
			System.setOut(new PrintStream("vans.out"));
		}
		catch (Throwable T_T) {
		}
		new vans().run();
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

