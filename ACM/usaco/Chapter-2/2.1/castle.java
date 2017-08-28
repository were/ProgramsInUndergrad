/*
ID : weng_xo2
PROG : castle
LANG : JAVA
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class castle {
	Scanner input = new Scanner(System.in);

	final int dx[] = {0, -1, 0, 1};
	final int dy[] = {-1, 0, 1, 0};
	int N, M, a[][], sz[], belong[][], cur = 0, ans1, ans2;
	char ch;
	Data q[], res;

	void bfs(int x, int y) {
		int f = 0, t = 0;
		for(q[t++] = new Data(x, y), belong[x][y] = ++cur; f < t; ++f) {
			for(int i = 0; i < 4; ++i) if((a[q[f].x][q[f].y] >> i & 1) == 0) {
				x = q[f].x + dx[i];
				y = q[f].y + dy[i];
				//System.out.println(x + " " + y);
				if(x >= 0 && x < N && y >= 0 && y < M && belong[x][y] == 0) {
					belong[x][y] = cur;
					q[t++] = new Data(x, y);
				}
			}
		}
		sz[cur] = t;
		ans1 = max(ans1, sz[cur]);
	}

	void run() {
		M = input.nextInt();
		N = input.nextInt();
		a = new int[N][M];
		q = new Data[N * M];
		sz = new int[M * M + 1];
		belong = new int[N][M];
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				a[i][j] = input.nextInt();
			}
		}
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
				if(belong[i][j] == 0) {
					bfs(i, j);
				}
			}
		}
		//for(int i = 0; i < N; ++i) {
		//	for(int j = 0; j < M; ++j) {
		//		System.out.print(belong[i][j] + " ");
		//	}
		//	System.out.println();
		//}
		for(int j = 0; j < M; ++j) {
			for(int i = N - 1; i >= 0; --i) {
				if(i - 1 >= 0 && belong[i][j] != belong[i - 1][j] && sz[belong[i][j]] + sz[belong[i - 1][j]] > ans2) {
					ans2 = sz[belong[i][j]] + sz[belong[i - 1][j]];
					ch = 'N';
					res = new Data(i + 1, j + 1);
				}
				if(j + 1 < M && belong[i][j] != belong[i][j + 1] && sz[belong[i][j]] + sz[belong[i][j + 1]] > ans2) {
					ans2 = sz[belong[i][j]] + sz[belong[i][j + 1]];
					ch = 'E';
					res = new Data(i + 1, j + 1);
				}
			}
		}
		System.out.println(cur);
		System.out.println(ans1);
		System.out.println(ans2);
		System.out.println(res.x + " " + res.y + " " + ch);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("castle.in"));
			System.setOut(new PrintStream("castle.out"));
		}
		catch(Throwable T_T) {
		}
		new castle().run();
	}
}

class Data {
	int x, y;
	Data(int x, int y) {
		this.x = x;
		this.y = y;
	}
}

