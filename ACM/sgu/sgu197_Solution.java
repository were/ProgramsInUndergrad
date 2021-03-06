import static java.lang.Math.*;
import static java.util.Arrays.*;
import java.io.*;
import java.util.*;
import java.math.*;

public class Solution {
	static boolean LOCAL = System.getSecurityManager() == null;
	Scanner input = new Scanner(System.in);
	Segment []T_T;
	
	int N, ans = 0;
	
	void run() {
		N = input.nextInt();
		T_T = new Segment[N + 1];
		for(int i = 1; i <= N; ++i) {
			T_T[i] = new Segment(N);
		}
		for(int M = input.nextInt(); M > 0; --M) {
			int x1 = input.nextInt();
			int y1 = input.nextInt();
			int x2 = input.nextInt();
			int y2 = input.nextInt();
			int tmp;
			String s = input.next();
			int color = s.charAt(0) == 'b' ? 1 : 0;
			/*
			System.out.println(s);
			System.out.println(s.charAt(0) == 'b');
			System.out.println(color);
			*/
			if(x1 > x2) {
				tmp = x1;
				x1 = x2;
				x2 = tmp;
			}
			if(y1 > y2) {
				tmp = y1;
				y1 = y2;
				y2 = tmp;
			}
			for(int i = x1; i <= x2; ++i) {
				T_T[i].insert(y1, y2, color);
			}
			/*
			for(int i = 1; i <= N; ++i) {
				for(int j = 1; j <= N; ++j) {
					System.out.print(T_T[i].query(j) + " ");
				}
				System.out.println();
			}
			System.out.println();
			*/
		}
		for(int i = 1; i <= N; ++i) {
			for(int j = 1; j <= N; ++j) {
				ans += 1 - T_T[i].query(j);
//				System.out.print(T_T[i].query(j) + " ");
			}
//			System.out.println();
		}
		System.out.print(ans);
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
		while(st.hasMoreTokens()) {
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

class Segment {
	int[] T;
	final int N;
	
	Segment(int n) {
		T = new int[n * 2 + 5];
		for(int i = 0; i < T.length; ++i) {
			T[i] = -1;
		}
		T[getId(1, n)] = 0;
		N = n;
	}
	
	int getId(int l, int r) {
		return (l != r) ? (l + r | 1) : (l + r);
	}
	
	void push(int l, int r) {
		int x = getId(l, r);
		if(l != r && T[x] != -1) {
			int m = (l + r) / 2;
			T[getId(l, m)] = T[x];
			T[getId(m + 1, r)] = T[x];
			T[x] = -1;
		}
	}
	
	void insert(int l, int r, int a, int b, int color) {
		if(b < l || a > r) {
			return;
		}
		if(a <= l && r <= b) {
			T[getId(l, r)] = color;
//			System.out.println(l + ", " + r + ": " + color);
		}
		else {
			push(l, r);
			int m = (l + r) / 2;
			insert(l, m, a, b, color);
			insert(m + 1, r, a, b, color);
		}
	}
	
	void insert(int l, int r, int color) {
		insert(1, N, l, r, color);
	}
	
	int query(int l, int r, int x) {
		if(l == r) {
			return T[getId(l, r)] == 0 || T[getId(l, r)] == -1 ? 0 : 1;
		}
		int m = (l + r) / 2;
		push(l, r);
		return x <= m ? query(l, m, x) : query(m + 1, r, x);
	}
	
	int query(int x) {
		return query(1, N, x);
	}
}
