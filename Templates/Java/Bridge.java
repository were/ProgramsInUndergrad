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
