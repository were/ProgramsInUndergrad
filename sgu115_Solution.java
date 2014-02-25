import java.util.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt(), M = in.nextInt(), ans = 0, n = 0, m = 1;
		int[] a = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for(int i = 1;i <= 365;++i){
			if(n == N && m == M){
				System.out.println(ans);
				return;
			}
			++ans;
			ans = (ans - 1) % 7 + 1;
			if(++n > a[m]){
				n = 1;
				++ m;
			}
		}
		System.out.println("Impossible");
	}
}
