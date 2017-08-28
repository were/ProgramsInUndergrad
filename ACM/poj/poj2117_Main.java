import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	Scanner input = new Scanner(System.in);

	int N, M;
	V[] v;

	ArrayList<E> bridge;

	int connection(V[] vs) {
		bridge = new ArrayList<E>();
		int res = 0;
		for(V v : vs) {
			if(v.num < 0) {
				dfs(v, 0);
				++res;
				if(v.cnt > 0) {
					--v.cnt;
				}
			}
		}
		return res;
	}

	int dfs(V v, int c) {
		v.num = c;
		int low = c;
		boolean rev = false;
		for(V u : v.g) {
			if(u.num < 0) {
				int t = dfs(u, c + 1);
				low = min(low, t);
				if(v.num <= t) {
					++v.cnt;
				}
				if(v.num < t) {
					bridge.add(new E(v, u));
				}
			} else {
				if(u.num != v.num - 1 || rev) {
					low = min(low, u.num);
				} else {
					rev = true;
				}
			}
		}
		return low;
	}

	void run() {
		for(N = input.nextInt(), M = input.nextInt(); N != 0; N = input.nextInt(), M = input.nextInt()) {
			if(M == 0) {
				System.out.println(N - 1);
				continue;
			}
			v = new V[N];
			for(int i = 0; i < N; ++i) {
				v[i] = new V();
			}
			for(int i = 0; i < M; ++i) {
				int a = input.nextInt();
				int b = input.nextInt();
				v[a].g.add(v[b]);
				v[b].g.add(v[a]);
			}
			int cnt = connection(v);
			int res = 0;
			for(V u : v) {
				res = max(res, u.cnt);
			}
			System.out.println(cnt + res);
		}
	}

	public static void main(String args[]) {
		new Main().run();
	}
}

class V {
	int num = -1, cnt;
	ArrayList<V> g = new ArrayList<V>();
}

class E {
	V u, v;
	E(V u, V v) {
		this.u = u;
		this.v = v;
	}
}
