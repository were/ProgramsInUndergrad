/*
ID : weng_xo2
LANG : JAVA
PROG : milk2
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class milk2 {
	static boolean LOCAL = System.getSecurityManager() == null;
	MyScanner input = new MyScanner(System.in);

	int N, work = 0, rest = 0;
	Range a[];
	
	void run() throws IOException, NumberFormatException {
		N = input.nextInt();
		a = new Range[N];
		for(int i = 0; i < N; ++i) {
			int l = input.nextInt();
			int r = input.nextInt();
			a[i] = new Range(l, r);
		}
		sort(a);
		//for(int i = 0; i < N; ++i) System.out.println(a[i].l + " " + a[i].r);
		for(int i = 0; i < N; ++i) {
			int j = i + 1;
			int l = a[i].l;
			int r = a[i].r;
			while(j < N && a[j].l <= r) {
				r = max(r, a[j].r);
				++j;
			}
			work = max(work, r - l);
			if(j < N) {
				rest = max(rest, a[j].l - r);
			}
			i = j - 1;
			//System.err.println(l + " " + r);
		}
		System.out.println(work + " " + rest);
	}

	void debug(Object...os) {
		System.err.println(deepToString(os));
	}

	public static void main(String []args) throws NumberFormatException, IOException {
		try {
			System.setIn(new FileInputStream("milk2.in"));
			System.setOut(new PrintStream("milk2.out"));
		}
		catch (Throwable e) {
			LOCAL = false;
		}
		new milk2().run();
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
		}
		catch(IOException e) {
			throw new IOError(e);
		}
	}

	boolean hasNext() {
		while(!st.hasMoreTokens()) {
			String s = nextLine();
			if(s == null) {
				return false;
			}
			eat(s);
		}
		return true;
	}

	String next() throws IOException {
		if(hasNext()) {
			return st.nextToken();
		}
		else {
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
class Range implements Comparable {
	int l, r;

	public int compareTo(Object b) {
		if(l != ((Range)b).l) {
			return l - ((Range)b).l;
		}
		return r - ((Range)b).r;
	}
	
	Range(int l, int r) {
		this.l = l;
		this.r = r;
	}

}
