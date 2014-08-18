import java.math.BigInteger;
import java.util.Scanner;


public class Main {
	Scanner input = new Scanner(System.in);
	int N, M;
	Edge g[];
	boolean hsh[];
	BigInteger ans = BigInteger.ONE;
	
	int dfs(int x) {
		int ret = 1;
		hsh[x] = true;
		for(Edge cur = g[x]; cur != null; cur = cur.nxt) {
			if(!hsh[cur.v]) {
				ret += dfs(cur.v);
			}
		}
		return ret;
	}
	
	void run() {
		N = input.nextInt();
		M = input.nextInt();
		g = new Edge[N + 1];
		hsh = new boolean[N + 1];
		for(int i = 0; i < M; ++i) {
			int u = input.nextInt();
			int v = input.nextInt();
			g[u] = new Edge(v, g[u]);
			g[v] = new Edge(u, g[v]);
		}
		for(int i = 1; i <= N; ++i) {
			if(!hsh[i]) {
				//System.out.println(ans.multiply(BigInteger.valueOf(2).pow(dfs(i) - 1)));
				ans = ans.multiply(BigInteger.valueOf(2).pow(dfs(i) - 1));
			}
		}
		System.out.println(ans);
	}
	
	public static void main(String args[]) {
		new Main().run();
	}
}

class Edge {
	int v;
	Edge nxt;
	
	Edge(int v, Edge nxt) {
		this.v = v;
		this.nxt = nxt;
	}
}