import java.util.*;
public class Solution {
	static public void main(String[]args){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt();
		int x = N;
		for(int i = 2;i * i <= x;++ i) if(x % i == 0){
			N = N / i * (i - 1);
			while(x % i == 0)
				x /= i;
		}
		if(x != 1)
			N = N / x * (x - 1);
		System.out.println(N);
	}
}
