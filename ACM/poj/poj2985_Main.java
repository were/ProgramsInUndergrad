import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	MyReader input = new MyReader(System.in);

	int N, M, n;
	BIT bit;
	DSU dsu;

	void run() {
		n = N = input.nextInt();
		bit = new BIT(N);
		dsu = new DSU(N);
		bit.add(0, N);
		for(M = input.nextInt(); M != 0; --M){
			int op = input.nextInt();
			if(op == 0) {
				int a = input.nextInt() - 1;
				int b = input.nextInt() - 1;
				if(dsu.get(a) != dsu.get(b)) {
					--n;
					bit.add(dsu.size(a) - 1, -1);
					bit.add(dsu.size(b) - 1, -1);
					dsu.merge(a, b);
					bit.add(dsu.size(a) - 1, 1);
				}
			} else {
				int k = n - input.nextInt() + 1;
				System.out.println(bit.get(k) + 1);
			}
		}
	}

	public static void main(String args[]) {
		new Main().run();
	}
}

class DSU {
	int[] fa, sz;

	DSU(int n) {
		fa = new int[n];
		sz = new int[n];
		for(int i = 0; i < n; ++i) {
			sz[i] = 1;
			fa[i] = i;
		}
	}

	int get(int x) {
		if(fa[x] == x) {
			return x;
		}
		return fa[x] = get(fa[x]);
	}

	int size(int x) {
		return sz[get(x)];
	}

	void merge(int a, int b) {
		a = get(a);
		b = get(b);
		if(sz[a] > sz[b]) {
			merge(b, a);
		} else {
			sz[a] += sz[b];
			fa[b] = a;
		}
	}
}

class BIT {
	int[] vs;

	BIT(int n) {
		vs = new int[n + 1];
	}

	void add(int k, int a) {
		for(int i = k + 1; i < vs.length; i += i & -i) {
			vs[i] += a;
		}
	}
	
	//[s, t)
	int sum(int s, int t) {
		if(s > 0) {
			return sum(0, t) - sum(0, s);
		}
		int res = 0;
		for(int i = t; i > 0; i -= i & -i) {
			res += vs[i];
		}
		return res;
	}

	int get(int k) {
		int p = Integer.highestOneBit(vs.length - 1);
		for(int q = p; q > 0; q >>= 1, p |= q) {
			if(p < vs.length && k > vs[p]) {
				k -= vs[p];
			} else {
				p ^= q;
			}
		}
		return p;
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


