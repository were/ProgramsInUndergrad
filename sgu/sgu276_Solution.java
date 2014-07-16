import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
	static boolean LOCAL = System.getSecurityManager() == null;
	MyScanner input = new MyScanner(System.in);
	
	void run() {
		int t = input.nextInt() - input.nextInt();
		int ans;
		t = -t;
		if(t > 0) {
			t /= 60;
			if(t < 5) {
				ans = 1;
			}
			else {
				if(t < 15) {
					ans = 2;
				}
				else {
					if(t < 30) {
						ans = 3;
					}
					else {
						ans = 4;
					}
				}
			}
		}
		else {
			ans = 0;
		}
		System.out.println(ans);
	}

	void debug(Object...os) {
		System.err.println(deepToString(os));
	}

	public static void main(String []args) {
		if(LOCAL) {
			try {
				System.setIn(new FileInputStream("in.txt"));
			}
			catch (Throwable e) {
				LOCAL = false;
			}
		}
		new Solution().run();
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

	String next() {
		hasNext();
		return st.nextToken();
	}

	int nextInt() {
		return Integer.parseInt(next());
	}

	long nextLong() {
		return Long.parseLong(next());
	}

	double nextDouble() {
		return Double.parseDouble(next());
	}

	BigInteger nextBigInteger() {
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

