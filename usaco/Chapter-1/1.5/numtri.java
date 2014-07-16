/*
LANG : JAVA
PROG : numtri
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class numtri {
	IntReader input = new IntReader(System.in);
	//Scanner input = new Scanner(System.in);
	int N, a[][], f[][], ans;

	void run() {
		N = input.nextInt();
		a = new int[N][N];
		f = new int[N][N];
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j <= i; ++j) {
				//System.out.println(i + ", " + j);
				a[i][j] = input.nextInt();
			}
		}
		f[0][0] = a[0][0];
		for(int i = 1; i < N; ++i) {
			f[i][0] = f[i - 1][0] + a[i][0];
			f[i][i] = f[i - 1][i - 1] + a[i][i];
			for(int j = 1; j < i; ++j) {
				f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + a[i][j];
				//System.out.println(i + " " + j + " " + f[i][j]);
			}
		}
		for(int i = 0; i < N; ++i) {
			ans = max(ans, f[N - 1][i]);
		}
		System.out.println(ans);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("numtri.in"));
			System.setOut(new PrintStream("numtri.out"));
		} catch (Throwable T_T) {
		}
		new numtri().run();
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

