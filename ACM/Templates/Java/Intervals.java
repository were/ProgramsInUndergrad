class Intervals {
	TreeMap<Integer, Integer> map = new TreeMap<Integer, Integer> ();

	Intervals() {
		map.put(Integer.MIN_VALUE, -1);
		map.put(Integer.MAX_VALUE, -1);
	}
	//[s, t)
	void paint(int s, int t, int c) {
		int p = get(t);
		map.subMap(s, t).clear();
		map.put(s, c);
		map.put(t, p);
	}

	int get(int k) {
		return map.floorEntry(k).getValue();
	}
}

