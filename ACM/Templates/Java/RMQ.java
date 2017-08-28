class RMQ {
	int[][] data;

	RMQ(int[] a) {
		int n = a.length, m = log2(n) + 1;
		data = new int[m][n];
		for(int i = 0; i < n; ++i) {
			data[0][i] = a[i];
		}
		for(int i = 1, k = 1; i < m; ++i, k <<= 1) {
			for(int j = 0; j + k < n; ++j) {
				data[i][j] = data[i - 1][j] <= data[i - 1][j + k] ? data[i - 1][j] : data[i - 1][j + k];
			}
		}
	}
	//[l, r)
	int query(int l, int r) {
		int k = log2(r - l);
		return data[k][l] <= data[k][r - (1 << k)] ? data[k][l] : data[k][r - (1 << k)];
	}

	int log2(int b) {
		return 31 - Integer.numberOfLeadingZeros(b);
	}
}
