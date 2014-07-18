import java.io.IOException;
import java.io.InputStream;
import java.util.Arrays;
import java.util.InputMismatchException;

public class Main {
	IntReader input = new IntReader(System.in);
	
	int N, M, ans = Integer.MAX_VALUE;
	int[] fa;
	Edge[] e;

	int getfa(int x) {
		if (x == fa[x]) {
			return x;
		}
		else {
			return fa[x] = getfa(fa[x]);
		}
	}
	
	boolean work(int l) {
		for(int i = 0; i < N; ++i) {
			fa[i] = i;
		}
		int cnt = N;
		for(int i = l; i < M; ++i) {
			int x = getfa(e[i].u);
			int y = getfa(e[i].v);
//			System.out.println(e[i].u + " " + e[i].v);
			if(x != y) {
				fa[x] = y;
				if(--cnt == 1) {
					ans = Math.min(ans, e[i].w - e[l].w);
					return true;
				}
			}
		}
		return false;
	}
	
	void run() {
		N = input.nextInt();
		M = input.nextInt();
		e = new Edge[M];
		fa = new int[N];
		for(int i = 0; i < M; ++i) {
			int u = input.nextInt() - 1;
			int v = input.nextInt() - 1;
			int w = input.nextInt();
			e[i] = new Edge(u, v, w);
		}
		Arrays.sort(e);
		for(int i = 0; i < M; ++i) {
			if(!work(i)) {
				break;
			}
		}
		System.out.println(ans);
	}
	
	public static void main(String []args) {
		new Main().run();
	}
}

class Edge implements Comparable {
	int u, v, w;
	
	Edge(int u, int v, int w) {
		this.u = u;
		this.v = v;
		this.w = w;
	}
	
	public int compareTo(Object b) {
		if(this.w < ((Edge)b).w) {
			return -1;
		}
		else {
			return this.w > ((Edge)b).w ? 1 : 0;
		}
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

