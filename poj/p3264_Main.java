import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

class RMQmin {
	int[][] data;

	RMQmin(int[] a) {
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

	int query(int l, int r) {
		int k = log2(r - l);
		return data[k][l] <= data[k][r - (1 << k)] ? data[k][l] : data[k][r - (1 << k)];
	}

	int log2(int b) {
		return 31 - Integer.numberOfLeadingZeros(b);
	}
}

class RMQmax {
	int[][] data;

	RMQmax(int[] a) {
		int n = a.length, m = log2(n) + 1;
		data = new int[m][n];
		for(int i = 0; i < n; ++i) {
			data[0][i] = a[i];
		}
		for(int i = 1, k = 1; i < m; ++i, k <<= 1) {
			for(int j = 0; j + k < n; ++j) {
				data[i][j] = data[i - 1][j] >= data[i - 1][j + k] ? data[i - 1][j] : data[i - 1][j + k];
			}
		}
	}

	int query(int l, int r) {
		int k = log2(r - l);
		return data[k][l] >= data[k][r - (1 << k)] ? data[k][l] : data[k][r - (1 << k)];
	}

	int log2(int b) {
		return 31 - Integer.numberOfLeadingZeros(b);
	}
}

public class Main {
	Scanner input = new Scanner(System.in);
	int[] a;
	int n, m;

	void run() {
		n = input.nextInt();
		m = input.nextInt();
		a = new int[n];
		for(int i = 0; i < n; ++i) {
			a[i] = input.nextInt();
		}
		RMQmin rmq1 = new RMQmin(a);
		RMQmax rmq2 = new RMQmax(a);
		for(int i = 0; i < m; ++i) {
			int l = input.nextInt() - 1;
			int r = input.nextInt();
			System.out.println(rmq2.query(l, r) - rmq1.query(l, r));
		}
	}

	public static void main(String args[]) {
		new Main().run();
	}
}


