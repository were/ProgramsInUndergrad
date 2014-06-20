import java.util.ArrayList;
import java.util.Scanner;

public class Main {
	Scanner input = new Scanner(System.in);
	int N, g[][], f[][], sccNum[], isSingle[], sccCnt = 0, dp[], ans = 0;
	
	int dfs(int x) {
		if(dp[x] != -1) {
			return dp[x];
		}
		int ret = 1 - isSingle[x];
		for(int i = 0; i < sccCnt; ++i) {
			if(g[x][i] == 1) {
				ret = Math.max(ret, dfs(i) + (1 - isSingle[x]));
			}
		}
//		System.out.println(x + ": " + dp[x]);
		return dp[x] = ret;
	}
	
	void run() {
		N = input.nextInt();
		g = new int[N][N];
		f = new int[N][N];
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				f[i][j] = g[i][j] = input.nextInt();
			}
		}
		for(int k = 0; k < N; ++k) {
			for(int i = 0; i < N; ++i) {
				for(int j = 0; j < N; ++j) { 
					if(g[i][k] == 1 && g[k][j] == 1/* && i != j && i != k && k != j*/) {
						g[i][j] = 1;
					}
				}
			}
		}
		boolean circleExist = false;
		for(int i = 0; i < N; ++i) {
			if(g[i][i] == 1) {
				circleExist = true;
			}
		}
		if(!circleExist) {
			System.out.println(0);
			return;
		}
		sccNum = new int[N];
		isSingle = new int[N];
		for(int i = 0; i < N; ++i) {
			sccNum[i] = -1;
			isSingle[i] = 0;
		}
		for(int i = 0; i < N; ++i) if(sccNum[i] == -1) {
			ArrayList<Integer> sccV = new ArrayList<Integer>();
			sccNum[i] = sccCnt;
			sccV.add(i);
//			System.out.print(i);
			for(int j = i + 1; j < N; ++j) {
				if(g[i][j] == 1 && g[j][i] == 1) {
//					System.out.print(" " + j);
					sccV.add(j);
					sccNum[j] = sccCnt;
				}
			}
//			System.out.println();
//			System.out.println(sccV.size() + " " + f[i][i]);
			if(sccV.size() == 1) {
				isSingle[sccCnt] = 1 - f[i][i];
//				System.out.println("ok!" + sccCnt);
			}
			else {
				for(int j = 0; j < sccV.size(); ++j) {
					int in = 0, out = 0;
					for(int k = 0; k < sccV.size(); ++k) {
						if(f[sccV.get(j)][sccV.get(k)] == 1) {
							++out;
						}
						if(f[sccV.get(k)][sccV.get(j)] == 1) {
							++in;
						}
					}
					if(in != 1 || out != 1) {
						System.out.println(-1);
						return;
					}
				}
				isSingle[sccCnt] = 0;
			}
//			System.out.println("scc:" + sccCnt + " " + isSingle[sccCnt]);
			++sccCnt;
		}
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				g[i][j] = 0;
			}
		}
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) if(f[i][j] == 1 && sccNum[i] != sccNum[j]) {
				g[sccNum[i]][sccNum[j]] = 1;
//				System.out.println(sccNum[i] + " " + sccNum[j]);
			}
		}
		dp = new int[sccCnt];
		for(int i = 0; i < sccCnt; ++i) {
			dp[i] = -1;
		}
		for(int i = 0; i < sccCnt; ++i) {
			boolean isRoot = true;
			for(int j = 0; j < sccCnt; ++j) {
				if(g[j][i] == 1) {
					isRoot = false;
				}
			}
			if(isRoot) {
//				System.out.println(i);
				ans = Math.max(ans, dfs(i));
			}
		}
		System.out.println(ans - 1);
	}
	
	public static void main(String []args) {
		new Main().run();
	}
	
}
/*
6
0 1 0 0 0 0
0 0 1 0 0 0
1 0 0 0 1 0
0 0 0 0 1 0
0 0 0 0 0 1
0 0 1 1 0 0
*/
