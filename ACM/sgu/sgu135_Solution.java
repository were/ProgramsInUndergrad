import java.util.*;
public class Solution{
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt(), ans = 1;
		for(int i = 0;i <= N;++ i)
			ans += i;
		System.out.println(ans);
	}
}
