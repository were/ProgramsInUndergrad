import java.util.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt();
		for(int i = 1;i <= N;++i){
			int cnt = 0, a = in.nextInt();
			for(int j = 2;j * j <= a;++j)
				while(a % j == 0){
					a /= j;
					++ cnt;
				}
			if(a != 1)
				++ cnt;
			System.out.println(cnt == 2 ? "Yes" : "No");
		}
	}
}
