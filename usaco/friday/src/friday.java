/*
ID : weng_xo2
LANG : JAVA
PROG : friday
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class friday {
	static boolean LOCAL = System.getSecurityManager() == null;
	MyScanner input = new MyScanner(System.in);
	
	int N;
	int ans[] = new int[8];
	
	final int months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int days(int year, int month) {
		if(month != 2) {
			return months[month];
		}
		if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
		return 28;
	}
	
	void run() throws IOException, NumberFormatException {
		N = input.nextInt();
		int week = 0;
		for(int i = 0; i < N; ++i) {
			//System.err.println(i);
			for(int month = 1; month <= 12; ++month) {
				for(int day = 1; day <= days(i + 1900, month); ++day) {
					if(++week == 8) {
						week = 1;
					}
					if(day == 13) {
						++ans[week];
					}
				}
			}
		}
		//System.err.println(ans[6] + " " + ans[7] + " " + ans[1] + " " + ans[2] + " " + ans[3] + " " + ans[4] + " " + ans[5]);
		System.out.println(ans[6] + " " + ans[7] + " " + ans[1] + " " + ans[2] + " " + ans[3] + " " + ans[4] + " " + ans[5]);
	}

	void debug(Object... os) {
		System.err.println(deepToString(os));
	}

	public static void main(String[] args) throws NumberFormatException, IOException {
		try {
			System.setIn(new FileInputStream("friday.in"));
			System.setOut(new PrintStream("friday.out"));
		} catch (Throwable e) {
			LOCAL = false;
		}
		new friday().run();
	}
}

class MyScanner {
	BufferedReader br;
	StringTokenizer st;

	MyScanner(InputStream in) {
		br = new BufferedReader(new InputStreamReader(in));
		eat("");
	}

	void eat(String s) {
		st = new StringTokenizer(s);
	}

	String nextLine() {
		try {
			return br.readLine();
		} catch (IOException e) {
			throw new IOError(e);
		}
	}

	boolean hasNext() {
		while (!st.hasMoreTokens()) {
			String s = nextLine();
			if (s == null) {
				return false;
			}
			eat(s);
		}
		return true;
	}

	String next() throws IOException {
		if (hasNext()) {
			return st.nextToken();
		} else {
			throw new IOException();
		}
	}

	int nextInt() throws NumberFormatException, IOException {
		return Integer.parseInt(next());
	}

	long nextLong() throws NumberFormatException, IOException {
		return Long.parseLong(next());
	}

	double nextDouble() throws NumberFormatException, IOException {
		return Double.parseDouble(next());
	}

	BigInteger nextBigInteger() throws IOException {
		return new BigInteger(next());
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
