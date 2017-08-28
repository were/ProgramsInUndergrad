import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

class Intervals {
	TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer> ();

	Intervals() {
		map.put(Integer.MIN_VALUE, -1);
		map.put(Integer.MAX_VALUE, -1);
	}

	void paint(int s, int t, int c) {
		int p = get(t);
		map.subMap(s, t).clear();
		map.put(s, c);
		map.put(t, p);
	}

	int get(int k) {
		return map.floorEntry(k).getValue();
	}
	
	int cnt(int s, int t, int c) {
		int ret = 0;
		SortedMap<Integer, Integer> sub = map.subMap(s, t);
		int colorS = get(s);
		for(int i = 1; i <= c; ++i) {
			if(sub.containsValue(i) || i == colorS) {
				++ret;
			}
		}
		return ret;
	}
}

public class Main {
	MyReader input = new MyReader(System.in);

	int N, M, K;
	Intervals a = new Intervals();

	void run() {
		N = input.nextInt();
		K = input.nextInt();
		a.paint(1, N + 1, 1);
		for(M = input.nextInt(); M != 0; --M) {
			char ch;
			for(ch = (char) input.read(); MyReader.isWhitespace(ch); ch = (char) input.read());
			int l = input.nextInt();
			int r = input.nextInt() + 1;
			if(ch == 'C') {
				int c = input.nextInt();
				a.paint(l, r, c);
			} else {
				System.out.println(a.cnt(l, r, K));
			}
		}
	}

	public static void main(String args[]) {
		new Main().run();
	}
}


class MyReader {

	private InputStream stream;
	private byte[] buf = new byte[1024];
	private int curChar;
	private int numChars;
	private SpaceCharFilter filter;

	public MyReader(InputStream stream) {
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


