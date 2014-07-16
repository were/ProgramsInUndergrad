import java.util.*;
import java.math.*;
public class Solution{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		BigInteger s[] = new BigInteger[41], f[] = new BigInteger[41];
		f[1] = f[2] = BigInteger.valueOf(1);
		s[1] = f[1];
		s[2] = f[1].add(f[2]);
		int N = input.nextInt();
		for(int i = 3;i <= N;++i){
			f[i] = f[i - 1].add(f[i - 2]);
			s[i] = s[i - 1].add(f[i]);
		}
		System.out.println(s[N]);
	}
}
