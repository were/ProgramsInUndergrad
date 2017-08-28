import java.util.*;
public class Solution{
	public static void main(String args[]){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt(), ans;
		ans = N / 3 * 2;
		if(N % 3 == 2)
			++ans;
		System.out.println(ans);
	}
}
