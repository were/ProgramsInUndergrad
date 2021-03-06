/*
ID : weng_xo2
LANG : JAVA
PROG : job
*/
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;


public class job {
	Scanner input = new Scanner(System.in);
	
	int N, M[] = new int[2], t[][], cost[][];
	
	void run() {
		N = input.nextInt();
		M[0] = input.nextInt();
		M[1] = input.nextInt();
		t = new int[2][Math.max(M[0], M[1])];
		cost = new int[2][N];
		for(int i = 0; i < 2; ++i) {
			for(int j = 0; j < M[i]; ++j) {
				t[i][j] = input.nextInt();
			}
		}
		for(int i = 0; i < 2; ++i) {
			int x = -1;
			int cur[] = new int[M[i]];
			for(int j = 0; j < N; ++j) {
				for(int k = 0; k < M[i]; ++k) {
					if(x == -1 || cur[x] + t[i][x] > cur[k] + t[i][k]) {
						x = k;
					}
				}
				cost[i][j] = cur[x] + t[i][x];
				cur[x] = cost[i][j];
			}
		}
		int ans = 0;
		for(int i = 0; i < N; ++i) {
			ans = Math.max(ans, cost[0][i] + cost[1][N - i - 1]);
		}
		System.out.println(cost[0][N - 1] + " " + ans);
	}
	
	public static void main(String args[]) throws FileNotFoundException {
		System.setIn(new FileInputStream("job.in"));
		System.setOut(new PrintStream("job.out"));
		new job().run();
	}
}
