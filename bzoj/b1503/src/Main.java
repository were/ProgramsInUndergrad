import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static boolean LOCAL = System.getSecurityManager() == null;
	IntReader input = new IntReader(System.in);
	
	int N, M, delta;
	
	Node nil, root;
	
	void rotate(Node cur, int d) {
		Node tmp = cur.s[d];
		cur.s[d] = tmp.s[1 - d];
		tmp.s[1 - d] = cur;
		tmp.sz = cur.sz;
		cur.rz();
		cur = tmp;
	}
	
	void maintain(Node cur, int d) {
		if(cur.s[d].s[d].sz > cur.s[1 - d].sz) {
			rotate(cur, d);
		}
		else {
			if(cur.s[d].s[1 - d].sz > cur.s[1 - d].sz) {
				rotate(cur.s[d], 1 - d);
				rotate(cur, d);
			}
		}
	}
	
	void insert(Node cur, int ky) {
		if(cur == nil) {
			cur = new Node(ky, nil);
		}
		else {
			int d = ky > cur.ky ? 1 : 0;
			insert(cur.s[d], ky);
			cur.rz();
			maintain(cur, d);
		}
	}
	
	int select(int k) {
		Node cur = root;
		if(k > cur.sz) {
			return -1;
		}
		while(k != cur.s[0].sz + 1) {
			if(cur.s[0].sz + 1 < k) {
				k -= cur.s[0].sz + 1;
				cur = cur.s[1];
			}
			else {
				cur = cur.s[0];
			}
		}
		return cur.ky;
	}
	
	void erase(Node cur, int ky) {
		if(cur == nil) {
			return;
		}
		if(cur.ky + delta < ky) {
			cur = cur.s[1];
			cur.rz();
			erase(cur, ky);
		}
		else {
			erase(cur.s[0], ky);
		}
	}
	
	void show(Node cur) {
		if(cur != nil) {
			show(cur.s[0]);
			System.out.println(cur.ky + " " + cur.sz);
			show(cur.s[1]);
		}
	}
	
	void run() {
		N = input.nextInt();
		nil = new Node(0, null);
		nil.sz = 0;
		nil.s[0] = nil.s[1] = nil;
		root = nil;
		for(M = input.nextInt(); N > 0; --N) {
			char op;
			op = (char) input.read();
			while(op < 'A' || op > 'Z') {
				op = (char) input.read();
			}
			debug(op);
			if(op == 'I') {
				int ky = input.nextInt();
				insert(root, ky - delta);
			}
			if(op == 'A') {
				delta += input.nextInt();
			}
			if(op == 'S') {
				delta -= input.nextInt();
				erase(root, M);
			}
			if(op == 'F') {
				System.out.println(select(input.nextInt()) + delta);
			}
			System.out.println("===========================");
			show(root);
			System.out.println("===========================");
		}
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
		new Main().run();
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

class Node{
	int ky, sz;
	Node s[];
	Node(int ky, Node nil) {
		this.ky = ky;
		this.sz = 1;
		this.s = new Node[2];
		this.s[0] = this.s[1] = nil; 
	}
	void rz() {
		sz = s[0].sz + 1 + s[1].sz;
	}
}
