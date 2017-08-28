import java.util.*;
public class Solution{
	static int N, M, row;
	static long opt[][];
	static void show(int x){
		for(int i = M - 1;i >= 0;-- i)
			System.out.print(x >> i & 1);
		System.out.println();
	}
	static void dfs(int x, int y, long delta){
		if(x == (1 << M) - 1){
			opt[row][y] += delta;
		}else{
			for(int i = 1;i < (1 << M);i <<= 1) if((x & i) == 0){
				x ^= i;
				if((y & i) == 0){
					dfs(x, y ^ i, delta);
					if((i << 1) < (1 << M) && ((i << 1) & y) == 0)
						dfs(x, y ^ i ^ (i << 1), delta);
					if((i >> 1) > 0 && ((i >> 1) & y) == 0)
						dfs(x, y ^ i ^ (i >> 1), delta);
				}
				if((i << 1) < (1 << M) && (x & (i << 1)) == 0){
					dfs(x ^ (i << 1), y, delta);
					if((y & i) == 0)
						dfs(x ^ (i << 1), y ^ i, delta);
					if((y & (i << 1)) == 0)
						dfs(x ^ (i << 1), y ^ (i << 1), delta);
				}
				break;
			}
		}
	}
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		N = in.nextInt();
		M = in.nextInt();
		opt = new long[N + 1][1 << M];
		opt[0][0] = 1;
		for(int i = 1;i <= N;++ i)
			for(int j = 0;j < 1 << M;++ j) if(opt[i - 1][j] != 0){
				row = i;
				dfs(j, 0, opt[i - 1][j]);
			}
		System.out.println(opt[N][0]);
	}
}
