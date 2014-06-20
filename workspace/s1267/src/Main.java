import java.io.BufferedReader;
import java.io.IOError;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.PriorityQueue;
import java.util.StringTokenizer;

public class Main {
	IntReader input = new IntReader(System.in);
	
	int N, M, w[], dis[];
	long ans;
	ArrayList<ArrayList<Edge>> g = new ArrayList<ArrayList<Edge>>();
	PriorityQueue<Edge> q = new PriorityQueue<Edge>();
	
	void run() {
		N = input.nextInt();
		M = input.nextInt();
		w = new int[N + 1];
		dis = new int[N + 1];
		g.add(new ArrayList<Edge>());
		for(int i = 1; i <= N; ++i) {
			w[i] = input.nextInt();
			dis[i] = Integer.MAX_VALUE;
			g.add(new ArrayList<Edge>());
		}
		for(int i = 0; i < M; ++i) {
			int u = input.nextInt();
			int v = input.nextInt();
			int w = input.nextInt();
			g.get(u).add(new Edge(v, w));
		}
		dis[1] = 0;
		q.add(new Edge(1, 0));
		while(!q.isEmpty()) {
			Edge top = q.peek();
			q.remove();
			for(Edge x: g.get(top.v)) {
				if(top.w + x.w < dis[x.v]) {
					dis[x.v] = top.w + x.w;
					q.add(new Edge(x.v, dis[x.v]));
				}
			}
		}
		for(int i = 1; i <= N; ++i) {
			if(dis[i] == Integer.MAX_VALUE) {
				System.out.println("No Answer");
				return;
			}
			ans += (long)dis[i] * w[i];
		}
		System.out.println(ans);
	}
	
	public static void main(String []args) {
		new Main().run();
	}
}

class Edge implements Comparable {
	int v, w;
	
	Edge(int v, int w) {
		this.v = v;
		this.w = w;
	}
	
	public int compareTo(Object o) {
		if(this.w < ((Edge)o).w) {
			return -1;
		}
		if(this.w == ((Edge)o).w) {
			return 0;
		}
		return 1;
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

