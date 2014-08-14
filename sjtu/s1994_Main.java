import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	static boolean LOCAL = System.getSecurityManager() == null;
	MyScanner input = new MyScanner(System.in);
	
	int N, M, ans = 0;
	int [][]a;
	boolean [][]hsh;
	
	boolean inRange(int x, int y) {
		return x >= 0 && x < N &&  y >= 0 && y < M && !hsh[x][y] && a[x][y] == 0;
	}
	
	void dfs(int x, int y) {
//		System.out.println(x + ", " + y);
		hsh[x][y] = true;
		for(int i = -1; i <= 1; ++i) {
			for(int j = -1; j <= 1; ++j) {
				if(abs(i) + abs(j) == 1 && inRange(x + i, y + j)) {
					dfs(x + i, y + j);
				}
			}
		}
	}
	
	void run() {
		N = input.nextInt();
		M = input.nextInt();
		a = new int[N][M];
		hsh = new boolean[N][M];
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				a[i][j] = input.nextInt();
				hsh[i][j] = false;
			}
		}
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				if(inRange(i, j)) {
					dfs(i, j);
//					System.out.println();
					++ans;
				}
			}
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
